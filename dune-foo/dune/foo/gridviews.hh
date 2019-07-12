// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_FOO_SRC_GRIDVIEWS_HH
#define DUNE_FOO_SRC_GRIDVIEWS_HH

// included standard library headers
#include <string>
#include <array>
#include <math.h>
// included dune-common headers
#include <dune/common/fvector.hh>
#include <dune/common/stringutility.hh>

// included dune-grid headers
#include <dune/grid/io/file/vtk/vtkwriter.hh>
#include <dune/grid/utility/structuredgridfactory.hh>

#include <dune/grid/common/gridfactory.hh>
#include <dune/grid/yaspgrid.hh>
#include <dune/grid/uggrid.hh>



template<class Grid>
auto createCubeGrid()
{
  static const int dim = Grid::dimension;

  auto lowerLeft = Dune::FieldVector<double,dim>((0,0));
  static const double up = 2*M_PI;
  auto upperRight = Dune::FieldVector<double,dim>((up,1));
  auto elementsPerDirection = std::array<unsigned int,dim>();
  for(auto& e : elementsPerDirection)
    e = 2;

  return Dune::StructuredGridFactory<Grid>::createCubeGrid(lowerLeft, upperRight, elementsPerDirection);
}

template<class Grid>
auto createSimplexGrid()
{
  static const int dim = Grid::dimension;

  auto lowerLeft = Dune::FieldVector<double,dim>((0,0));
  static const double up = 2*M_PI;
  auto upperRight = Dune::FieldVector<double,dim>((1,up));
  auto elementsPerDirection = std::array<unsigned int,dim>();
  for(auto& e : elementsPerDirection)
    e = 2;

  return Dune::StructuredGridFactory<Grid>::createSimplexGrid(lowerLeft, upperRight, elementsPerDirection);
}



namespace Dune {

  template <class Grid>
  Grid* make2DSimplexGrid()
  {
    static_assert(Grid::dimension == 2,
                  "Instantiate make2dHybridTestGrid only for 2d grids!");

    // Start grid creation
    GridFactory<Grid> factory;

    // The list of grid vertex positions
    int numVertices = 10;

    Dune::FieldVector<double,2> pos;

    pos[0] = 0;  pos[1] = 0;  //0
    factory.insertVertex(pos);                         /*@\label{uc:iv}@*/

    pos[0] = M_PI/2;  pos[1] = 0; //1
    factory.insertVertex(pos);

    pos[0] = M_PI;  pos[1] = 0;   //2
    factory.insertVertex(pos);
    
    pos[0] = 3*M_PI/2;  pos[1] = 0;   //3
    factory.insertVertex(pos);

    pos[0] = 2*M_PI;  pos[1] = 0;   //4
    factory.insertVertex(pos);

    pos[0] = 0;  pos[1] = 1;    //5
    factory.insertVertex(pos);    

    pos[0] = M_PI/2;  pos[1] = 1;   //6
    factory.insertVertex(pos);

    pos[0] = M_PI;  pos[1] = 1;   //7
    factory.insertVertex(pos);
    
    pos[0] = 3*M_PI/2;  pos[1] = 1;   //8
    factory.insertVertex(pos);

    
    pos[0] = 2*M_PI;  pos[1] = 1;   //9
    factory.insertVertex(pos);

   
 // Create the triangle elements
    int numTriangles = 8;
    unsigned int triangles[8][3] = {{0, 1, 5},
                                    {5, 6, 1},
                                    {1, 2, 6},
                                    {6, 7, 2},
                                    {2, 3, 7},
                                    {7, 8, 3},
                                    {3, 4, 8},
                                    {8, 9, 4}};

    for (int i=0; i<numTriangles; i++) {
      std::vector<unsigned int> cornerIDs(3);
      for (int j=0; j<3; j++)
        cornerIDs[j] = triangles[i][j];
      factory.insertElement(Dune::GeometryType(Dune::GeometryType::simplex,2),cornerIDs);
    }

     
    Grid *grid = factory.createGrid();
    grid->globalRefine(2);

    // Finish initialization
    return grid;
  }


  template <class GridType>
  GridType* make2DCubeGrid()
  {
    static_assert(GridType::dimension == 2,
                  "Instantiate make3DHybridTestGrid only for 3d grids!");

    // Start grid creation
    GridFactory<GridType> factory;

    int numVertices = 10;

    Dune::FieldVector<double,2> pos;

    pos[0] = 0;  pos[1] = 0;  //0
    factory.insertVertex(pos);                         /*@\label{uc:iv}@*/

    pos[0] = M_PI/2;  pos[1] = 0; //1
    factory.insertVertex(pos);

    pos[0] = M_PI;  pos[1] = 0;   //2
    factory.insertVertex(pos);
    
    pos[0] = 3*M_PI/2;  pos[1] = 0;   //3
    factory.insertVertex(pos);

    pos[0] = 2*M_PI;  pos[1] = 0;   //4
    factory.insertVertex(pos);

    pos[0] = 0;  pos[1] = 1;    //5
    factory.insertVertex(pos);    

    pos[0] = M_PI/2;  pos[1] = 1;   //6
    factory.insertVertex(pos);

    pos[0] = M_PI;  pos[1] = 1;   //7
    factory.insertVertex(pos);
    
    pos[0] = 3*M_PI/2;  pos[1] = 1;   //8
    factory.insertVertex(pos);

    
    pos[0] = 2*M_PI;  pos[1] = 1;   //9
    factory.insertVertex(pos);

    


    // Create the tetrahedron elements
    int numcubes = 4;
    unsigned int cube[4][4] = {{0, 1, 5, 6},
                                      {1, 2, 6, 7},
                                      {2, 3, 7, 8},
                                      {3, 4, 8, 9}};

    for (int i=0; i<numcubes; i++) {
      std::vector<unsigned int> cornerIDs(4);
      for (int j=0; j<4; j++)
        cornerIDs[j] = cube[i][j];
      factory.insertElement(Dune::GeometryType(Dune::GeometryType::cube,2),cornerIDs);
    }


    GridType *grid = factory.createGrid();
    grid->globalRefine(2);

    // Finish initialization
    return grid;
  }

}






template<class GridView>
void writeGridView(const GridView& gridView, std::string postFix)
{
  Dune::VTKWriter<GridView> vtkWriter(gridView);
  vtkWriter.write(std::string("gridviews-")+postFix);
}

template<class Grid>
void writeAllGridViews(const Grid& grid, std::string gridName)
{
  for(int level = 0; level <= grid.maxLevel(); ++level)
    writeGridView(grid.levelGridView(level), Dune::formatString(gridName+"-level-%02d", level));

  writeGridView(grid.leafGridView(), gridName+"-leaf");
}


#endif // DUNE_FUTUTORIAL_SRC_04GRIDVIEWS_HH
