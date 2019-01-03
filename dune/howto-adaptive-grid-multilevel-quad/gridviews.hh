// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_FOO_SRC_GRIDVIEWS_HH
#define DUNE_FOO_SRC_GRIDVIEWS_HH

// included standard library headers
#include <string>
#include <array>

// included dune-common headers
#include <dune/common/fvector.hh>
#include <dune/common/stringutility.hh>

// included dune-grid headers
#include <dune/grid/io/file/vtk/vtkwriter.hh>
#include <dune/grid/utility/structuredgridfactory.hh>
#include <dune/grid/yaspgrid.hh>
#include <dune/grid/uggrid.hh>



template<class Grid>
auto createCubeGrid()
{
  static const int dim = Grid::dimension;

  auto lowerLeft = Dune::FieldVector<double,dim>(0);
  auto upperRight = Dune::FieldVector<double,dim>(1);
  auto elementsPerDirection = std::array<unsigned int,dim>();
  for(auto& e : elementsPerDirection)
    e = 2;

  return Dune::StructuredGridFactory<Grid>::createCubeGrid(lowerLeft, upperRight, elementsPerDirection);
}

template<class Grid>
auto createSimplexGrid()
{
  static const int dim = Grid::dimension;

  auto lowerLeft = Dune::FieldVector<double,dim>(0);
  auto upperRight = Dune::FieldVector<double,dim>(1);
  auto elementsPerDirection = std::array<unsigned int,dim>();
  for(auto& e : elementsPerDirection)
    e = 2;

  return Dune::StructuredGridFactory<Grid>::createSimplexGrid(lowerLeft, upperRight, elementsPerDirection);
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
