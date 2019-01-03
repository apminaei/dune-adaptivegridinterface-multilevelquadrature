
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

// included standard library headers
#include <iostream>
#include <array>
// included dune-common headers
#include <dune/common/parallel/mpihelper.hh>
#include <dune/common/exceptions.hh>
#include <dune/common/fvector.hh>
#include <dune/common/stringutility.hh>
// included dune-grid headers
#include <dune/grid/yaspgrid.hh>
#include <dune/grid/uggrid.hh>
#include <dune/grid/io/file/vtk/vtkwriter.hh>
// include external headers

#include "dune/howto-adaptive-grid-multilevel-quad/adaptivemultilevelintegration.hh"
// included dune-geometry headers
#include <dune/geometry/quadraturerules.hh>

//-------------------------------
int main(int argc, char** argv)
{
  try{
      // create grid
      const int dim = 2;
      using Grid = Dune::UGGrid<dim>;
      auto gridPointer = createCubeGrid<Grid>();
      Grid& grid = *gridPointer;

      const int d = Grid::dimension;
      std::cout << "grid dimension is " << d << std::endl;

      auto function = [](auto x) {
        return 1.0/(x.two_norm());
      };

      adaptiveintegration(grid, function);

    return 0;
  }
  catch (Dune::Exception &e){
    std::cerr << "Dune reported error: " << e << std::endl;
  }
  catch (...){
    std::cerr << "Unknown exception thrown!" << std::endl;
  }
}
