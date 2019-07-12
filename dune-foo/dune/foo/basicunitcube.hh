// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef  BASICUNITCUBE_HH
#define  BASICUNITCUBE_HH

#include <dune/geometry/type.hh>
#include <dune/grid/common/gridfactory.hh>


template<typename T>                      /*@\label{uc:uc0}@*/
class BasicUnitCube
{
public:
  typedef T GridType;
  static const int dim = GridType::dimension;

  BasicUnitCube ()
  {
    void insertVertices ( Dune::GridFactory< GridType > &factory );
    void insertSimplices ( Dune::GridFactory< GridType > &factory );
    void insertCubes ( Dune::GridFactory< GridType > &factory );
  }


   T& grid ()
  {
    return grid;
  }

// declaration of a basic unit cube that uses the GridFactory

// unit cube in two dimensions with 2 variants: triangle and rectangle elements

protected:
  template< class Grid >
  static void insertVertices ( Dune::GridFactory< Grid > &factory )
  {
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
  }

  template< class Grid >
  static void insertSimplices ( Dune::GridFactory< Grid > &factory )
  {
    const Dune::GeometryType type( Dune::GeometryType::BasicType::simplex );
    std::vector< unsigned int > cornerIDs( 3 );

    cornerIDs[0] = 0;  cornerIDs[1] = 1;  cornerIDs[2] = 5;
    factory.insertElement( type, cornerIDs );          /*@\label{uc:ie}@*/

    cornerIDs[0] = 5;  cornerIDs[1] = 6;  cornerIDs[2] = 1;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 1;  cornerIDs[1] = 2;  cornerIDs[2] = 6;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 6;  cornerIDs[1] = 7;  cornerIDs[2] = 2;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 2;  cornerIDs[1] = 3;  cornerIDs[2] = 7;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 7;  cornerIDs[1] = 8;  cornerIDs[2] = 3;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 3;  cornerIDs[1] = 4;  cornerIDs[2] = 8;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 8;  cornerIDs[1] = 9;  cornerIDs[2] = 4;
    factory.insertElement( type, cornerIDs );

  }

  template< class Grid >
  static void insertCubes ( Dune::GridFactory< Grid > &factory )
  {
    const Dune::GeometryType type( Dune::GeometryType::BasicType::cube );
    std::vector< unsigned int > cornerIDs( 4 );
    
    cornerIDs[0] = 0;  cornerIDs[1] = 1;  cornerIDs[2] = 5;   cornerIDs[3] = 6;
    factory.insertElement( type, cornerIDs );          /*@\label{uc:ie}@*/

    cornerIDs[0] = 1;  cornerIDs[1] = 2;  cornerIDs[2] = 6;   cornerIDs[3] = 7;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 2;  cornerIDs[1] = 3;  cornerIDs[2] = 7;   cornerIDs[3] = 8;
    factory.insertElement( type, cornerIDs );

    cornerIDs[0] = 3;  cornerIDs[1] = 4;  cornerIDs[2] = 8;   cornerIDs[3] = 9;
    factory.insertElement( type, cornerIDs );
  }
  


    
    double vertices[10][2] = {{0, 0},
                              {M_PI/2, 0},
                              {M_PI, 0},
                              {3*M_PI/2, 0},
                              {2*M_PI, 0},
                              {0, 1},
                              {M_PI/2, 1},
                              {M_PI, 1},
                              {3*M_PI/2, 1},
                              {2*M_PI, 1}};
                              

    // Create the grid vertices
    for (int i=0; i<numVertices; i++) {
      Dune::FieldVector<double,2> pos;
      pos[0] = vertices[i][0];
      pos[1] = vertices[i][1];
      factory.insertVertex(pos);
    }

    // Create the triangle elements
    int numTriangles = 2;
    unsigned int triangles[2][3] = {{9, 10, 11},
                                    {15, 13, 14}};

    for (int i=0; i<numTriangles; i++) {
      std::vector<unsigned int> cornerIDs(3);
      for (int j=0; j<3; j++)
        cornerIDs[j] = triangles[i][j];
      factory.insertElement(Dune::GeometryType(Dune::GeometryType::simplex,2),cornerIDs);
    }

    // Create the quadrilateral elements
    int numQuadrilaterals = 9;
    unsigned int quadrilaterals[9][4] = {{0, 4, 7, 8},
                                         {4, 1, 8, 5},
                                         {8, 5, 6, 2},
                                         {7, 8, 3, 6},
                                         {1, 9, 5, 11},
                                         {5, 11, 2, 10},
                                         {2, 10, 13, 12},
                                         {3, 6, 14, 15},
                                         {6, 2, 15, 13}};

    for (int i=0; i<numQuadrilaterals; i++) {
      std::vector<unsigned int> cornerIDs(4);
      for (int j=0; j<4; j++)
        cornerIDs[j] = quadrilaterals[i][j];
      factory.insertElement(Dune::GeometryType(Dune::GeometryType::cube,2),cornerIDs);
    }

 

private:
  // the constructed grid object
  std::shared_ptr<T> grid_;
};



#endif  /*BASICUNITCUBE_HH*/
