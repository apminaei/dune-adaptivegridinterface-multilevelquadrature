// vi : set et ts =4 sw =2 sts =2:
# ifndef DUNE_INTEGRATEENTITY_HH
# define DUNE_INTEGRATEENTITY_HH

# include <dune/common/exceptions.hh>
# include <dune/geometry/quadraturerules.hh>

// ! compute integral of function over entity with given order
template < class Entity , class Function >
double integrateEntity( const Entity & entity , const Function & f , int p )
{
    // dimension of the entity
    const int dim = Entity::dimension ;

    // type used for coordinates in the grid
    typedef typename Entity::Geometry::ctype ctype ;

    // get geometry
    const typename Entity::Geometry geometry = entity.geometry();

    // get geometry type
    const Dune::GeometryType gt = geometry.type();

    // get quadrature rule of order p
    const Dune::QuadratureRule <ctype, dim>& rule = Dune::QuadratureRules <ctype , dim >::rule( gt, p );

    // ensure that rule has at least the requested order
    if ( rule.order() < p )
      DUNE_THROW ( Dune::Exception , " order not available " );

    // compute approximate integral
    double result =0;
    for ( typename Dune::QuadratureRule < ctype , dim >::const_iterator i = rule.begin(); i != rule.end(); ++i )
    {
      double fval = f( geometry.global (i -> position()));
      double weight = i -> weight();
      double detjac = geometry.integrationElement(i -> position());
      result += fval * weight * detjac ;
    }

    // return result
    return result ;

}

# endif
