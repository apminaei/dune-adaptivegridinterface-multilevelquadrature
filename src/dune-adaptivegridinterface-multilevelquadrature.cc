// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif


// included dune-common headers
#include <dune/common/parallel/mpihelper.hh>
#include <dune/common/exceptions.hh>

// included standard library headers
#include <iostream>
#include <array>
// included dune-common headers
#include <dune/common/fvector.hh>
#include <dune/common/stringutility.hh>
// included dune-grid headers
#include <dune/grid/yaspgrid.hh>
#include <dune/grid/uggrid.hh>
#include <dune/grid/io/file/vtk/vtkwriter.hh>
// include external headers

#include "dune/adaptivegridinterface-multilevelquadrature/adaptivemultilevelintegration.hh"
// included dune-geometry headers
#include <dune/geometry/quadraturerules.hh>


int main(int argc, char** argv)
{
  try{
    // Maybe initialize MPI
    Dune::MPIHelper& helper = Dune::MPIHelper::instance(argc, argv);

   

    // Given Tolerance
      const double Tol = 1E-3;
    // create grid
      const int dim = 2;
      using Grid = Dune::UGGrid<dim>;
      auto gridPointer = createSimplexGrid<Grid>();
      Grid& grid = *gridPointer;

      const int d = Grid::dimension;
      std::cout << "grid dimension is " << d << std::endl;

      auto function = [](auto x) {
        return 1.0/(x.two_norm());
      };
    adaptiveintegration(grid, function , Tol);

    return 0;
  }
  catch (Dune::Exception &e){
    std::cerr << "Dune reported error: " << e << std::endl;
  }
  catch (...){
    std::cerr << "Unknown exception thrown!" << std::endl;
  }
}
