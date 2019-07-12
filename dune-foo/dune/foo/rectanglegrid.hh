
# include <math.h>
# include <dune/grid/uggrid.hh>





template<class grid>
auto createrectangleGrid()
{
  static const int dim = grid::dimension;
  typedef Dune :: UGGrid <dim> grid ;

  grid.createBegin ();

// Insert vertices
	Dune::FieldVector < double ,2 > pos ;

	pos [0] = 0; pos [1] = 0;
	grid.insertVertex ( pos );

	pos [0] = 2*M_PI; pos [1] = 0;
	grid.insertVertex ( pos );

	pos [0] = 0; pos [1] = 1;
	grid.insertVertex ( pos );

	pos [0] = 2*M_PI; pos [1] = 1;
	grid.insertVertex ( pos );

// I n s e r t e l e m e n t
	std :: vector < unsigned int > cornerIDs (4);
	cornerIDs [0] = 0;
	cornerIDs [1] = 1;
	cornerIDs [2] = 2;
	cornerIDs [3] = 3;

	grid.insertElement ( Dune :: GeometryType ( Dune :: GeometryType :: cube ,2) , cornerIDs );

// Finish i n i t i a l i z a t i o n
	grid.createEnd ();




  return grid;
}




