//Adaptive multilevel integration
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
# include <iostream>
# include <array>
# include <iomanip>
# include <dune/grid/io/file/vtk/vtkwriter.hh> // VTK output routines
# include <dune/common/parallel/mpihelper.hh> // include mpi helper class
# include <dune/grid/uggrid.hh>

# include "integrateentity.hh"
# include "gridviews.hh"

// ! adaptive refinement test
template < class Grid, class Functor >
void adaptiveintegration( Grid & grid, const Functor & f , const double tol)
  {
    // get grid view type for leaf grid
    typedef typename Grid::LeafGridView GridView ;
    // get iterator type
    typedef typename GridView::template Codim <0>::Iterator ElementLeafIterator;

    // get grid view on leaf part
    GridView gridView = grid.leafGridView();

    // algorithm parameters
    
    const int loworder = 1;
    const int highorder = 3;

    // loop over grid sequence
    double oldvalue = 10.0 ;
    int count = 0 ;
    for ( int k = 0; k < 2; k++)
    {
        // compute integral on current mesh
        double value =0;
        for ( ElementLeafIterator it = gridView.template begin<0>();
              it != gridView.template end<0>(); ++it )
                value += integrateEntity(*it ,f , highorder);

        // print result
        double estimated_error = std::abs( value - oldvalue );
        // save value for next estimate
        oldvalue = value ;
        std::cout << " elements = "
                  << std::setw(8) << std::right
                  << grid.size(0)
                  << " integral = "
                  << std::scientific << std::setprecision(8)
                  << value
                  << " error = " << estimated_error
                  << std::endl;

        // check convergence
        if ( estimated_error<= tol*value )
        {
            std::cout << "The number of refinement needed: " << count << std::endl;
            break ;
        }

        // refine grid globally in first step to ensure
        // that every element has a father
        if ( k == 0)
        {
            grid.globalRefine(1);
            continue ;
        }

        // compute threshold for subsequent refinement
        double maxerror = -1E5 ;
        double maxextrapolatederror = -1E5 ;
        for ( ElementLeafIterator it = gridView.template begin <0>();
              it != gridView.template end <0>(); ++it)
        {
            // error on this entity
            double lowresult = integrateEntity(*it ,f , loworder );
            double highresult = integrateEntity(*it ,f , highorder );
            double error = std::abs( lowresult-highresult );

            // max over whole grid
            maxerror = std::max( maxerror , error );
            // error on father entity
            double fatherlowresult = integrateEntity( it-> father(), f, loworder);
            double fatherhighresult = integrateEntity( it-> father(), f, highorder);
            double fathererror = std::abs(fatherlowresult - fatherhighresult);

            // local extrapolation
            double extrapolatederror = error * error /( fathererror + 1E-30);
            maxextrapolatederror = std::max( maxextrapolatederror, extrapolatederror);
        }
        double kappa = std::min( maxextrapolatederror , 0.5* maxerror );

        // mark elements for refinement
        for ( ElementLeafIterator it = gridView.template begin<0>();
              it != gridView.template end<0>(); ++it )
        {
            double lowresult = integrateEntity (*it ,f , loworder );
            double highresult = integrateEntity (*it ,f , highorder );
            double error = std::abs( lowresult - highresult );
            if ( error > kappa ) grid.mark (1 ,*it );
        }

        // adapt the mesh
        grid.preAdapt();
        grid.adapt();
        grid.postAdapt();
        ++count;
    }

    writeAllGridViews(grid, "uggrid");

}
