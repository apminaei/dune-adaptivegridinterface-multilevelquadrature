// -*- tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set ts=8 sw=2 et sts=2:
#ifndef DUNE_ADAPTIVEGRIDINTERFACE_MULTILEVELQUADRATURE_REFERENCEELEMENTUTILITY_hh
#define DUNE_ADAPTIVEGRIDINTERFACE_MULTILEVELQUADRATURE_REFERENCEELEMENTUTILITY_hh

#include <dune/common/reservedvector.hh>
#include <dune/common/power.hh>
#include <dune/geometry/referenceelements.hh>
#include <dune/geometry/dimension.hh>

namespace Dune {
namespace foo {



/**
 * \brief Encapsulate dynamic codim value
 */
class DynamicCodim
{
public:
  constexpr DynamicCodim():
    value_(0)
  {}

  constexpr explicit DynamicCodim(std::size_t value) :
    value_(value)
  {}

  /**
   * \brief Allow conversion from static Codim value
   */
  template<int value>
  constexpr DynamicCodim(Dune::Codim<value> staticCodim):
    value_(value)
  {}

  constexpr operator std::size_t() const
  {
    return value_;
  }

private:
  std::size_t value_;
};



/**
 * \brief Generate dynamic codim from dynamic raw value
 */
auto codim(std::size_t i)
{
  return DynamicCodim(i);
}



/**
 * \brief Encapsulate dynamic subentity information
 *
 * This is a strongly typed pair of codimension and index
 */
class DynamicSubEntity
{
public:

  constexpr DynamicSubEntity():
    codim_(0),
    index_(0)
  {}

  constexpr DynamicSubEntity(DynamicCodim codim, std::size_t index):
    codim_(codim),
    index_(index)
  {}

  constexpr DynamicCodim codim() const
  {
    return codim_;
  }

  constexpr std::size_t index() const
  {
    return index_;
  }

  constexpr operator std::size_t() const
  {
    return index_;
  }

private:
  DynamicCodim codim_;
  std::size_t index_;
};



/**
 * \brief Create subentity identifier for given codim and index
 */
auto subEntity(DynamicCodim codim, std::size_t index)
{
  return DynamicSubEntity(codim, index);
}



/**
 * \brief Create subentity identifier for facet of given index
 */
auto facet(std::size_t index)
{
  return subEntity(codim(1), index);
}



/**
 * \brief Create subentity identifier for inside facet
 */
template<class Intersection>
auto insideFacet(const Intersection& intersection)
{
  return subEntity(codim(1), intersection.indexInInside());
}



/**
 * \brief Get reference element for given entity
 */
template<class FieldType, class Entity>
const auto& referenceElement(const Entity& entity)
{
  return Dune::ReferenceElements<FieldType, Entity::dimension>::general(entity.type());
}


/**
 * \brief Get reference element for given entity
 */
template<class Entity>
const auto& referenceElement(const Entity& entity)
{
  return Dune::ReferenceElements<double, Entity::dimension>::general(entity.type());
}


/**
 * \brief Get number of subentities of given codim
 *
 * This should (maybe) be a member of ReferenceElement.
 */
template<class ReferenceElementType>
std::size_t referenceElementSize(const ReferenceElementType& referenceElement, DynamicCodim codim)
{
  return referenceElement.size(codim);
}



/**
 * \brief Get GeometryType of subentity
 *
 * This should (maybe) be a member of ReferenceElement.
 */
template<class ReferenceElementType>
Dune::GeometryType type(const ReferenceElementType& referenceElement, DynamicSubEntity subEntity)
{
  return referenceElement.type(subEntity.index(), subEntity.codim());
}



/**
 * \brief Get number of subsubentities of given codim for a subentity
 *
 * This should (maybe) be a member of ReferenceElement.
 */
template<class ReferenceElementType>
std::size_t referenceElementSize(const ReferenceElementType& referenceElement, DynamicSubEntity subEntity, DynamicCodim subSubEntityCodim)
{
  return referenceElement.size(subEntity.index(), subEntity.codim(), subSubEntityCodim);
}



/**
 * \brief Get index of a subsubentity for a subentity within the ReferenceElement
 *
 * This should (maybe) be a member of ReferenceElement.
 * However, this could also be hidden, because the
 * functionality is often misunderstood and you normaly
 * need all subsubentities anyway.
 */
template<class ReferenceElementType>
auto subEntity(const ReferenceElementType& referenceElement, DynamicSubEntity se, DynamicSubEntity subSubEntity)
{
  return subEntity(subSubEntity.codim(), referenceElement.subEntity(se.index(), se.codim(), subSubEntity.index(), subSubEntity.codim()));
}



/**
 * \brief Get index-range of subsubentities of given codim for a subentity within the ReferenceElement
 *
 * This should (maybe) be a member of ReferenceElement.
 */
template<class ReferenceElementType>
auto subEntities(const ReferenceElementType& referenceElement, const DynamicSubEntity subEntityTag, DynamicCodim codim)
{
  static constexpr int dimension = ReferenceElementType::dimension;
  static const std::size_t maxSubEntityCount = Dune::StaticPower<2,dimension>::power;
  std::size_t subEntityCount = referenceElementSize(referenceElement, subEntityTag, codim);

  // Todo: This could be replaced by an on-the fly range by doing a
  // transformation to an index range. Unfortunately these range tools
  // have not arrived in std yet.
  Dune::ReservedVector<DynamicSubEntity, maxSubEntityCount > indices;
  indices.resize(subEntityCount);
  for(std::size_t i=0; i<subEntityCount; ++i)
    indices[i] = subEntity(referenceElement, subEntityTag, subEntity(codim, i));

  return indices;
}



/**
 * \brief Get index-range of subentities of given codim
 *
 * This should (maybe) be a member of ReferenceElement.
 */
template<class ReferenceElementType>
auto subEntities(const ReferenceElementType& referenceElement, DynamicCodim cd)
{
  return subEntities(referenceElement, subEntity(codim(0), 0), cd);
}



/**
 * \brief Get index-range of vertices of given subentity within the ReferenceElement
 */
template<class ReferenceElementType>
auto subVertices(const ReferenceElementType& referenceElement, const DynamicSubEntity subEntityTag)
{
  static constexpr int dimension = ReferenceElementType::dimension;
  return subEntities(referenceElement, subEntityTag, codim(dimension));
}



/**
 * \brief Get index of subentity
 *
 * This should (maybe) be a member of IndexSet
 */
template<class IndexSet, class Entity>
auto subIndex(const IndexSet& indexSet, const Entity& entity, DynamicSubEntity subEntity)
{
  return indexSet.subIndex(entity, subEntity.index(), subEntity.codim());
}



/**
 * \brief Get id of subentity
 *
 * This should (maybe) be a member of IdSet.
 */
template<class IdSet, class Entity>
auto subId(const IdSet& idSet, const Entity& entity, DynamicSubEntity subEntity)
{
  return idSet.subId(entity, subEntity.index(), subEntity.codim());
}



} // end namespace foo
} // end namespace Dune



#endif // DUNE_FU_TUTORIAL_REFERENCEELEMENTUTILITY_hh
