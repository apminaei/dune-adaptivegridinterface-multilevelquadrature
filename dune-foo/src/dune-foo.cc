#include <config.h>

#include <vector>
#include <math.h>
#include <dune/common/function.hh>

#include <dune/geometry/quadraturerules.hh>

// { include_uggrid_begin }
#include <dune/grid/uggrid.hh>
#include <dune/grid/uggrid.hh>
#include <dune/grid/yaspgrid.hh>
# include "dune/foo/gridviews.hh"
//#include "dune/foo/basicunitcube.hh"
// { include_uggrid_end }
//#include <dune/grid/io/file/gmshreader.hh>
#include <dune/grid/io/file/vtk/vtkwriter.hh>

#include <dune/istl/matrix.hh>
// { include_matrix_vector_begin }
#include <dune/istl/bvector.hh>
#include <dune/istl/bcrsmatrix.hh>
// { include_matrix_vector_end }
#include <dune/istl/matrixindexset.hh>
#include <dune/istl/preconditioners.hh>
#include <dune/istl/solvers.hh>
#include <dune/istl/matrixmarket.hh>

#include <dune/functions/functionspacebases/pqknodalbasis.hh>
#include <dune/functions/functionspacebases/interpolate.hh>


// Journal Bearing Data

const double eta0 = 45.0e-3; // 45 mPa*s
const double p_eta_index = 2.2e-8 ;
const double eta_max = 50 ;
const double E_1 = 210e3; // Youngs modulus
const double E_2 = 210e3;
const double nu_1 = 0.3; // Poison ratio
const double nu_2 = 0.3;
const double bearing_diameter = 8.016e-3;
const double journal_diameter = 7.984e-3;
const double bearing_width = 4e-3;
const double rotational_speed = 2500 * 2 * M_PI / 60 ; // rpm
const double load = 1000 ;


// Journal Bearing Data





// { using_namespace_dune_begin }
using namespace Dune;
// { using_namespace_dune_end }

// Compute the stiffness matrix for a single element
// { local_assembler_signature_begin }
template <class LocalView, class MatrixType>
void assembleElementStiffnessMatrix( const LocalView& localView, MatrixType& elementMatrix,
									const std::function<double(FieldVector<double,LocalView::Element::dimension>)> diffusTerm)
// { local_assembler_signature_end }
{
    // { local_assembler_get_geometry_begin }
    using Element = typename LocalView::Element;
    auto element = localView.element();
    const int dim = Element::dimension;
    auto geometry = element.geometry();
    // { local_assembler_get_geometry_end }

    // Get set of shape functions for this element
    // { get_shapefunctions_begin }
    const auto& localFiniteElement = localView.tree().finiteElement();
    // { get_shapefunctions_end }

    // Set all matrix entries to zero
    // { init_element_matrix_begin }
    elementMatrix.setSize(localFiniteElement.size(),localFiniteElement.size());
    elementMatrix = 0;      // fills the entire matrix with zeros
    // { init_element_matrix_end }

    // Get a quadrature rule
    // { get_quadrature_rule_begin }
    int order = 2*(dim*localFiniteElement.localBasis().order()-1);       /*@\label{li:poissonequation_quad_order}@*/
    const auto& quadRule = QuadratureRules<double, dim>::rule(element.type(), order);  /*@\label{li:poissonequation_quad_rule}@*/
    // { get_quadrature_rule_end }

    // Loop over all quadrature points
    // { loop_over_quad_points_begin }
    for (const auto& quadPoint : quadRule) {
    // { loop_over_quad_points_end }

        // { get_quad_point_info_begin }
        // Position of the current quadrature point in the reference element
        const auto quadPos = quadPoint.position();

        // The transposed inverse Jacobian of the map from the reference element to the element
        const auto jacobian = geometry.jacobianInverseTransposed(quadPos);
		double functionValue = diffusTerm(element.geometry().global(quadPos));
		
        // The multiplicative factor in the integral transformation formula
        const auto integrationElement = geometry.integrationElement(quadPos);
        // { get_quad_point_info_end }

        // { compute_gradients_begin }
        // The gradients of the shape functions on the reference element
        std::vector<FieldMatrix<double,1,dim> > referenceGradients;       /*@\label{li:poissonequation_referencegradients}@*/
        localFiniteElement.localBasis().evaluateJacobian(quadPos, referenceGradients);

        // Compute the shape function gradients on the real element
        std::vector<FieldVector<double,dim> > gradients(referenceGradients.size());
        for (size_t i=0; i<gradients.size(); i++)
        {
            jacobian.mv(referenceGradients[i][0], gradients[i]);          /*@\label{li:poissonequation_transformgradients}@*/
        // { compute_gradients_end }
			gradients[i][1] *= (bearing_diameter/(2*bearing_width));
		}
		
        // Compute the actual matrix entries
        // { compute_matrix_entries_begin }
        for (size_t i=0; i<elementMatrix.N(); i++)
            for (size_t j=0; j<elementMatrix.M(); j++ )
                elementMatrix[localView.tree().localIndex(i)][localView.tree().localIndex(j)]
                    += functionValue * (  gradients[i] * gradients[j] )  * quadPoint.weight() * integrationElement;
        // { compute_matrix_entries_end }

    }

}



// Compute the source term for a single element
template <class LocalView>
void getVolumeTerm( const LocalView& localView,
                    BlockVector<FieldVector<double,1> >& localRhs,
                    const std::function<double(FieldVector<double,LocalView::Element::dimension>)> volumeTerm)
{
    using Element = typename LocalView::Element;
    auto element = localView.element();
    const int dim = Element::dimension;

    // Set of shape functions for a single element
    const auto& localFiniteElement = localView.tree().finiteElement();

    // Set all entries to zero
    localRhs.resize(localFiniteElement.size());
    localRhs = 0;

    // A quadrature rule
    int order = dim;
    const auto& quadRule = QuadratureRules<double, dim>::rule(element.type(), order);

    // Loop over all quadrature points
    for (const auto& quadPoint : quadRule) {

        // Position of the current quadrature point in the reference element
        const FieldVector<double,dim>& quadPos = quadPoint.position();

        // The multiplicative factor in the integral transformation formula
        const double integrationElement = element.geometry().integrationElement(quadPos);

        double functionValue = volumeTerm(element.geometry().global(quadPos));

        // Evaluate all shape function values at this point
        std::vector<FieldVector<double,1> > shapeFunctionValues;
        localFiniteElement.localBasis().evaluateFunction(quadPos, shapeFunctionValues);

        // Actually compute the vector entries
        for (size_t i=0; i<localRhs.size(); i++)
            localRhs[i] += shapeFunctionValues[i] * functionValue * quadPoint.weight() * integrationElement;
    }

}

// Get the occupation pattern of the stiffness matrix
template <class Basis>
void getOccupationPattern(const Basis& basis, MatrixIndexSet& nb)
{
  nb.resize(basis.size(), basis.size());

  auto gridView = basis.gridView();
	const auto &indexset = gridView.indexSet();
			auto predicate_periodic_left = [](auto p){return  p[0] == 0 && p[1] != 0 && p[1] != 1 ; };
		
		    // Interpolating the predicate will mark all desired periodic_left degrees of freedom
		    std::vector<char> periodicNodesLeft;
		    Functions::interpolate(basis, periodicNodesLeft, predicate_periodic_left);
		    // { periodic_left_marking_end }
			auto predicate_periodic_right = [](auto p){return p[0] == 2*M_PI && p[1] != 0 && p[1] !=1 ;};
		
			// Interpolating the predicate will mark all desired periodic_right degrees of freedom
			std::vector<char> periodicNodesRight;
			Functions::interpolate(basis, periodicNodesRight, predicate_periodic_right);
			    // { periodic_right_marking_end }
		
		auto localView = basis.localView();
		auto localIndexSet = basis.localIndexSet();
 		for (  const auto& element : elements(gridView))
 			{
 				localView.bind(element);
 				localIndexSet.bind(localView);
 				
 				for (size_t i=0; i<localIndexSet.size(); i++ )
 				{	
 					auto x = element.geometry().corner(i);
 					for (size_t j=0; j<localIndexSet.size(); j++ )
 					{ 					      
 					 nb.add(localIndexSet.index(i),localIndexSet.index(j));
 					}
 						if (periodicNodesLeft[localIndexSet.index(i)] )
 						{
 							for (const auto& element1 : elements(gridView))
 							{
 					    		localView.bind(element1);
 					   			localIndexSet.bind(localView);
 								for (size_t k=0; k<localIndexSet.size(); k++ )
 					      		{
	 					      		auto y = element1.geometry().corner(k);
 					        		// The global index of the j-th vertex of the element
 					        		if (periodicNodesRight[localIndexSet.index(k)] && (x[1]==y[1]) )
 					        		 nb.add(localIndexSet.index(i),localIndexSet.index(k));
 					        	}
 					       	}
 					     }
				}
 			}
  
}


/** \brief Assemble the Laplace stiffness matrix on the given grid view */
// { global_assembler_signature_begin }
template <class Basis>
void assemblePoissonProblem(const Basis& basis,
                            BCRSMatrix<FieldMatrix<double,1,1> >& matrix,
                            BlockVector<FieldVector<double,1> >& rhs,
                            BCRSMatrix<FieldMatrix<double,1,1> >& matrix_reduced,
                            BlockVector<FieldVector<double,1> >& rhs_reduced,
                            const std::function<double(FieldVector<double,Basis::GridView::dimension>)> diffusTerm,
                            const std::function<double(FieldVector<double,Basis::GridView::dimension>)> volumeTerm)
// { global_assembler_signature_end }
{


    // { assembler_get_grid_info_begin }
    auto gridView = basis.gridView();
    
    const auto &indexset = gridView.indexSet();
    // { assembler_get_grid_info_end }

	using MatrixType = BCRSMatrix<Dune::FieldMatrix<double,1,1>>;
	ImplicitMatrixBuilder<MatrixType> matrixBuilder(matrix, indexset.size(2),indexset.size(2),100, 0.1);
	ImplicitMatrixBuilder<MatrixType> matrixBuilder1(matrix_reduced, indexset.size(2),indexset.size(2),100, 0.1);
	// matrix_reduced = 0;
			auto predicate_periodic_left = [](auto p){return  p[0] == 0 && p[1] != 0 && p[1] != 1 ; };
		
		    // Interpolating the predicate will mark all desired periodic_left degrees of freedom
		    std::vector<char> periodicNodesLeft;
		    Functions::interpolate(basis, periodicNodesLeft, predicate_periodic_left);
		    // { periodic_left_marking_end }
			auto predicate_periodic_right = [](auto p){return p[0] == 2*M_PI && p[1] != 0 && p[1] !=1 ;};
		
			// Interpolating the predicate will mark all desired periodic_right degrees of freedom
			std::vector<char> periodicNodesRight;
			Functions::interpolate(basis, periodicNodesRight, predicate_periodic_right);
			    // { periodic_right_marking_end }

    // { assembler_zero_vector_begin }
    // set rhs to correct length
    rhs.resize(basis.size());

    // Set all entries to zero
    rhs = 0;
    // { assembler_zero_vector_end }

    // A loop over all elements of the grid
    // { assembler_element_loop_begin }
    auto localView = basis.localView();
    auto localIndexSet = basis.localIndexSet();

    for (const auto& element : elements(gridView))             /*@\label{li:poissonequation_elementloop}@*/
    {
    // { assembler_element_loop_end }

        // Now let's get the element stiffness matrix
        // A dense matrix is used for the element stiffness matrix
        // { assembler_assemble_element_matrix_begin }
        localView.bind(element);
        localIndexSet.bind(localView);

        Matrix<FieldMatrix<double,1,1> > elementMatrix;
        assembleElementStiffnessMatrix(localView, elementMatrix, diffusTerm);
        // { assembler_assemble_element_matrix_end }

        //
        // { assembler_add_element_matrix_begin }
        for(size_t i=0; i<elementMatrix.N(); i++)
        {
            // The global index of the i-th degree of freedom of the element
            auto row = localIndexSet.index(i);

            for (size_t j=0; j<elementMatrix.M(); j++ )
            {
                // The global index of the j-th degree of freedom of the element
                auto col = localIndexSet.index(j);
                matrixBuilder[row][col] += elementMatrix[i][j];
            }
        }
        // { assembler_add_element_matrix_end }

        // Now get the local contribution to the right-hand side vector
        BlockVector<FieldVector<double,1> > localRhs;
        getVolumeTerm(localView, localRhs, volumeTerm);

        for (size_t i=0; i<localRhs.size(); i++)
        {
            // The global index of the i-th vertex of the element
            auto row = localIndexSet.index(i);
            rhs[row] += localRhs[i];
        }


        
    }
/*
   
		int count = 0 ;
		for ( int i=0; i< periodicNodesLeft.size(); i++)
			if (periodicNodesLeft[i])
				{
					count++ ;
				} 
	
			
		const int reducedSize = basis.size()-count;
		matrix_reduced.setSize(reducedSize,reducedSize);
*/
			for (  const auto & vertex : vertices ( gridView ))
			{
				int i = indexset.index( vertex );
				auto cIti    = matrix[i].begin();
				auto cEndIti = matrix[i].end();
				for (; cIti!=cEndIti; ++cIti)
				matrixBuilder1[i][cIti.index()] = *cIti;
				if (periodicNodesLeft[i] )
				{
					for (  const auto & vertex1 : vertices ( gridView ))
					{
						int j = indexset.index( vertex1 );
						if (periodicNodesRight[j] && (vertex.geometry().center()[1]==vertex1.geometry().center()[1]) )
						{
							
							auto cItj    = matrix[j].begin();
							auto cEndItj = matrix[j].end();
							// loop over nonzero matrix entries in current row
					
							for (; cItj!=cEndItj; ++cItj)
							
						       matrixBuilder1[i][cItj.index()] = *cItj; 
						    
						}                 
					}
				}
			}
//	std::cout << matrix[2][10] << std::endl;	
//
	rhs_reduced = 0;
    
 //   	std::cout << matrix[4][11] << std::endl;	
 matrix.compress();
matrix_reduced.compress();

}



/** \brief Assemble the Laplace stiffness matrix on the given grid view */
// { global_assembler_signature_begin }
template <class Basis, class vectorType>
void cal_Deformation(const Basis& basis,
                            vectorType vec_pressure,
                            BlockVector<FieldVector<double,1> >& deformation,
                            const std::function<double(FieldVector<double,Basis::GridView::dimension>)> kernelTerm)
// { global_assembler_signature_end }
{
    // { assembler_get_grid_info_begin }
    auto gridView = basis.gridView();
    // { assembler_get_grid_info_end }
	

    // { assembler_zero_vector_begin }
    // set rhs to correct length
    deformation.resize(basis.size());

    // Set all entries to zero
    deformation = 0;
    // { assembler_zero_vector_end }

    const auto &indexset = gridView.indexSet();

	for ( const auto & vertex : vertices ( gridView ))
	{
		// A loop over all elements of the grid
		// { assembler_element_loop_begin }
		auto localView = basis.localView();
		auto localIndexSet = basis.localIndexSet();
		// { assembler_element_loop_end }
		BlockVector<FieldVector<double,1> > def;
		// Set all entries to zero
		def.resize(gridView.size ( 0 ));
		def = 0;
		
		for (const auto& element : elements(gridView))             /*@\label{li:poissonequation_elementloop}@*/
			{
				// Now let's get the element stiffness matrix
				localView.bind(element);
				localIndexSet.bind(localView);
			
			    auto geometry = element.geometry();
			    // { local_assembler_get_geometry_end }
			
			    // Get set of shape functions for this element
			    // { get_shapefunctions_begin }
			    const auto& localFiniteElement = localView.tree().finiteElement();
			    // { get_shapefunctions_end }
				BlockVector<FieldVector<double,1> > localDeformation;
				// Set all entries to zero
				localDeformation.resize(localFiniteElement.size());
				localDeformation = 0;
				
			   
			    // Get a quadrature rule
			    // { get_quadrature_rule_begin }
			    int order = 2*(2*localFiniteElement.localBasis().order()-1);       /*@\label{li:poissonequation_quad_order}@*/
			    const auto& quadRule = QuadratureRules<double, 2>::rule(element.type(), order);  /*@\label{li:poissonequation_quad_rule}@*/
			    // { get_quadrature_rule_end }
			
			    // Loop over all quadrature points
			    // { loop_over_quad_points_begin }
			    for (const auto& quadPoint : quadRule) 
			    {
			   
			
			        // { get_quad_point_info_begin }
			        // Position of the current quadrature point in the reference element
			        const auto quadPos = quadPoint.position();
			
			       
					double functionValue = kernelTerm(vertex.geometry().center()-element.geometry().global(quadPos));
					
			        // The multiplicative factor in the integral transformation formula
			        const auto integrationElement = geometry.integrationElement(quadPos);
			        // { get_quad_point_info_end }
			
			        // The values of the shape functions at the quadrature point
			        std::vector<FieldVector<double,1> > values;
			        localFiniteElement.localBasis().evaluateFunction(quadPoint.position(), values);
			        
					for (size_t i=0; i<localDeformation.size(); i++)
			            localDeformation[i] +=  vec_pressure[localIndexSet.index(i)]*values[i] * functionValue * quadPoint.weight() * integrationElement;
			        
			       
			    } // { loop_over_quad_points_end }
			    for (size_t i=0; i<localDeformation.size(); i++)
			    	def[indexset.index( element )] += localDeformation[i];
				
			}
			for (size_t i=0; i<def.size(); i++)
						    deformation[indexset.index( vertex )] += def[i];	
	}      
   
}



/** \brief Assemble the Laplace stiffness matrix on the given grid view */
// { global_assembler_signature_begin }
template <class Basis, class vectorType>
void cal_Force(const Basis& basis,
                            vectorType vec_pressure,
                            BlockVector<FieldVector<double,1> >& generated_Force)
// { global_assembler_signature_end }
{
    // { assembler_get_grid_info_begin }
    auto gridView = basis.gridView();
    // { assembler_get_grid_info_end }

	
	// A loop over all elements of the grid
	// { assembler_element_loop_begin }
	auto localView = basis.localView();
	auto localIndexSet = basis.localIndexSet();
	// { assembler_element_loop_end }
	

    // { assembler_zero_vector_begin }
    // set rhs to correct length
    generated_Force.resize(1);

    // Set all entries to zero
    generated_Force = 0;
    // { assembler_zero_vector_end }

		for (const auto& element : elements(gridView))             /*@\label{li:poissonequation_elementloop}@*/
			{
				// Now let's get the element stiffness matrix
				localView.bind(element);
				localIndexSet.bind(localView);
			
			    auto geometry = element.geometry();
			    // { local_assembler_get_geometry_end }
			
			    // Get set of shape functions for this element
			    // { get_shapefunctions_begin }
			    const auto& localFiniteElement = localView.tree().finiteElement();
			    // { get_shapefunctions_end }
				BlockVector<FieldVector<double,1> > localforce;
				// Set all entries to zero
				localforce.resize(localFiniteElement.size());
				localforce = 0;
				
			   
			    // Get a quadrature rule
			    // { get_quadrature_rule_begin }
			    int order = 2*(2*localFiniteElement.localBasis().order()-1);       /*@\label{li:poissonequation_quad_order}@*/
			    const auto& quadRule = QuadratureRules<double, 2>::rule(element.type(), order);  /*@\label{li:poissonequation_quad_rule}@*/
			    // { get_quadrature_rule_end }
			
			    // Loop over all quadrature points
			    // { loop_over_quad_points_begin }
			    for (const auto& quadPoint : quadRule) 
			    {
			   
			
			        // { get_quad_point_info_begin }
			        // Position of the current quadrature point in the reference element
			        const auto quadPos = quadPoint.position();
			
			       
					double functionValue = cos(element.geometry().global(quadPos)[0]);
					
			        // The multiplicative factor in the integral transformation formula
			        const auto integrationElement = geometry.integrationElement(quadPos);
			        // { get_quad_point_info_end }
			
			        // The values of the shape functions at the quadrature point
			        std::vector<FieldVector<double,1> > values;
			        localFiniteElement.localBasis().evaluateFunction(quadPoint.position(), values);
			        
					for (size_t i=0; i<localforce.size(); i++)
					{
						localforce[i] += abs(vec_pressure[localIndexSet.index(i)])*values[i] * functionValue * quadPoint.weight() * integrationElement;
			       	} 
			       
			    } // { loop_over_quad_points_end }
			   
					for (size_t i=0; i<localforce.size(); i++)
						generated_Force [0]+= localforce[i];	
			}
      
   
}




int main (int argc, char *argv[]) try
{
  // Set up MPI, if available
  MPIHelper::instance(argc, argv);

		////////////////// nondimensional coefficients ///////////////////////

		double base_speed = rotational_speed * journal_diameter / 2.0;

		double zoom_H = (bearing_diameter + journal_diameter) * (bearing_diameter - journal_diameter) / ( 4.0 * bearing_diameter) ;
		if (zoom_H < 0.001e-6)
			zoom_H = 0.001e-6;

		const double c = zoom_H;
		const double R1 = bearing_diameter / 2.0;
		const double zoom_P =  base_speed * eta0 * R1/( c*c );
	
		
		double zoom_X = R1;
		double zoom_Y = bearing_width;

		double Elastic_modulus = 2.0/((1.0 - nu_1*nu_1) / E_1 + (1.0 - nu_2*nu_2) / E_2);
		const double deformation_coeff =  (1.0 - nu_1*nu_1) / Elastic_modulus * bearing_diameter * zoom_P /( 2*c ) / (4*M_PI);

		
		std::cout << Elastic_modulus << std::endl;
		std::cout << zoom_P << std::endl;
		std::cout << zoom_X << std::endl;
		std::cout << zoom_Y << std::endl;
		std::cout << deformation_coeff << std::endl;
	
		
		auto density = [](const FieldVector<double,1>& x, const double zoom_P)
						{ return  (x[0]==0)? 1:(5.1e8+1.34*zoom_P*x[0])/(5.1e8+zoom_P*x[0]);};   /*@\label{li:density}@*/
						
		auto viscosity_inverse = [](const FieldVector<double,1>& x,  const double zoom_P)
						{ return  (x[0]==0)? 1: exp(-(log(eta0)+9.67)*(-1+pow(1+5.1*zoom_P*x[0],
										(p_eta_index*1e9/(log(eta0)+9.67)/5.1))));};			 /*@\label{li:inverse_of_viscosity}@*/

		

		
										
		/////////////////////         ///////////////////////////////


    // ////////////////////////////////
    //   Generate the grid
    // ////////////////////////////////

    // { create_grid_begin }
    const int dim = 2;

  	//using GridType = Dune::YaspGrid<dim>;
	using GridType = Dune::UGGrid<dim>;
	//FieldVector<double,dim> upperRight = {2*M_PI, 1};
	//std::array<int,dim> elements = {{16, 4}};
	//GridType grid(upperRight,elements);
	
	
 	auto gridPointer = make2DSimplexGrid<GridType>();
    //auto gridPointer = createCubeGrid<GridType>();

	GridType& grid = *gridPointer;
	grid.globalRefine(2);                        /*@\label{li:poissonequation_global_refinement}@*/

    typedef GridType::LeafGridView GridView;
    GridView gridView = grid.leafGridView();
	
	//int n = gridView.size ( dim );
    //std::cout << n << std::endl;
    //for ( const auto & vertex : vertices ( gridView )){std::cout << vertex.geometry().center() << std::endl;}
	writeGridView(gridView, "uggrid");
	//writeAllGridViews(grid, "uggrid");

	/*@\label{li:poissonequation_gridcreation_end}@*/
    // { create_grid_end }

    // ///////////////////////////////////////////////////////
    //   Stiffness matrix and right hand side vector
    // ///////////////////////////////////////////////////////

    // { create_matrix_vector_begin }
    typedef BlockVector<FieldVector<double,1> > VectorType;          /*@\label{li:poissonequation_declare_vectortype}@*/
    typedef BCRSMatrix<FieldMatrix<double,1,1> > MatrixType;         /*@\label{li:poissonequation_declare_matrixtype}@*/

    VectorType rhs;
    VectorType rhs_reduced;
    VectorType deformation;
    VectorType generated_Force;
    MatrixType stiffnessMatrix;
    MatrixType stiffnessMatrix_reduced;
    // { create_matrix_vector_end }

    // ///////////////////////////////////////////////////////
    //   Assemble the system
    // ///////////////////////////////////////////////////////

    // { call_assembler_begin }
    Functions::PQkNodalBasis<GridView,1> basis(gridView);            /*@\label{li:poissonequation_select_fe_basis}@*/
    
    auto sourceTerm = [](const FieldVector<double,dim>& x){ return  0.973*sin(x[0]);};   /*@\label{li:poissonequation_strong_rhs}@*/
    auto diffusionTerm = [](const FieldVector<double,dim>& x)
	    { return (1+0.973*cos(x[0]))*(1+0.973*cos(x[0]))*(1+0.973*cos(x[0]))/6;};   /*@\label{li:poissonequation_diffusion_coefficient}@*/

	
    assemblePoissonProblem(basis, stiffnessMatrix, rhs, stiffnessMatrix_reduced, rhs_reduced, diffusionTerm, sourceTerm);        /*@\label{li:poissonequation_call_assembleLaplaceMatrix}@*/
    // { call_assembler_end }

    // Determine Dirichlet dofs by marking all degrees of freedom whose Lagrange nodes comply with a
    // given predicate.
    // Since interpolating into a vector<bool> is currently not supported,
    // we use a vector<char> which, in contrast to vector<bool>
    // is a real container.
    // { dirichlet_marking_begin }
    auto predicate = [](auto p){return  p[1] ==0 or p[1] == 1;};

    // Interpolating the predicate will mark all desired Dirichlet degrees of freedom
    std::vector<char> dirichletNodes;
    Functions::interpolate(basis, dirichletNodes, predicate);
    // { dirichlet_marking_end }



		
  // /////////////////////////////////////////
  //   Modify Dirichlet rows
  // /////////////////////////////////////////
  // { dirichlet_matrix_modification_begin }
  // loop over the matrix rows
  for (size_t i=0; i<stiffnessMatrix.N(); i++)      /*@\label{li:poissonequation_loop_matrix_rows}@*/
  {
    if (dirichletNodes[i])                          /*@\label{li:poissonequation_test_for_dirichlet_row}@*/
    {
      auto cIt    = stiffnessMatrix[i].begin();
      auto cEndIt = stiffnessMatrix[i].end();
      // loop over nonzero matrix entries in current row
      for (; cIt!=cEndIt; ++cIt)                       /*@\label{li:poissonequation_loop_over_dirichlet_row}@*/
        *cIt = (i==cIt.index()) ? 1.0 : 0.0;             /*@\label{li:poissonequation_modify_dirichlet_row}@*/
    }
  }
  // { dirichlet_matrix_modification_end }

  // Set Dirichlet values
  // { dirichlet_rhs_modification_begin }
  auto dirichletValues = [](auto p){return 0;};   /*@\label{li:poissonequation_dirichlet_values}@*/
  Functions::interpolate(basis,rhs,dirichletValues, dirichletNodes);
  // { dirichlet_rhs_modification_end }

  /////////////////////////////////////////////////////////////////////////////
  // Write matrix and load vector to files, to be used in later examples
  /////////////////////////////////////////////////////////////////////////////
  // { matrix_rhs_writing_begin }
  storeMatrixMarket(stiffnessMatrix, "poisson-matrix.mm");
  storeMatrixMarket(rhs, "poisson-rhs.mm");
  // { matrix_rhs_writing_end }

  // /////////////////////////
  //   Compute solution
  // /////////////////////////

  // { algebraic_solving_begin }
  // Choose an initial iterate
  VectorType x(basis.size());
  x = 0;

  // Technicality:  turn the matrix into a linear operator
  MatrixAdapter<MatrixType,VectorType,VectorType> linearOperator(stiffnessMatrix);

  // Sequential incomplete LU decomposition as the preconditioner
  SeqILDL<MatrixType,VectorType,VectorType> preconditioner(stiffnessMatrix,1.0);


  // Preconditioned conjugate-gradient solver
  CGSolver<VectorType> cg(linearOperator,
                          preconditioner,
                          1e-8, // desired residual reduction factor
                          100,   // maximum number of iterations
                          2);   // verbosity of the solver

  // Object storing some statistics about the solving process
  InverseOperatorResult statistics;

  // Solve!
  cg.apply(x, rhs, statistics);
  // { algebraic_solving_end }

auto kernel =[](const FieldVector<double,dim>& z){return 1.0/z.two_norm();};

///////////////////////////////////////////////////////////////////////////////////////////
 
    cal_Deformation(basis, x, deformation, kernel);
     cal_Force(basis, x, generated_Force);
   
//for ( size_t i=0; i<deformation.size(); i++)
   // std::cout << deformation[i] << " "  << x[i] << std::endl;
	generated_Force *= (zoom_P*bearing_diameter*bearing_width/2);
   deformation *=(zoom_H*deformation_coeff);
   x *= zoom_P;
   std::cout << deformation.size() << " "  << x.size() <<   " "  << generated_Force <<std::endl;
//////////////////////////////////////////////////////////////////////////////////////////

  		                                	    
 
  // Output result
  // { vtk_output_begin }
  VTKWriter<GridView> vtkWriter(gridView);
  vtkWriter.addVertexData(x, "solution");
  vtkWriter.write("poissonequation-result");
  // { vtk_output_end }

  // { vtk_output_begin }
  VTKWriter<GridView> vtkWriter1(gridView);
  vtkWriter1.addVertexData(deformation, "deformation");
  vtkWriter1.write("deformation-result");
  // { vtk_output_end }

  return 0;
 }
// Error handling
 catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
 }
