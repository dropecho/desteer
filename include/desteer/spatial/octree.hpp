#pragma once
#include "ISpatialQueryable.hpp"
#include <vector>

namespace desteer{
namespace spatial{

class Octree : public ISpatialQueryable
{
private:
    EntityGroup _indices;
    Octree** _children;
    unsigned short int _maxDepth;
    unsigned short int _depth;
    unsigned int _maxIndices;
    irr::core::vector3df _origin;
    float _size;

    void Prune();
    void Grow();

    bool CanPruneLeafs();
    bool ShouldSplit();
    void InsertIntoChild(entity::IBaseEntity* item);
public:
    Octree(unsigned short int maxDepth = 8, unsigned int maxIndices = 36, float size = 256.0f,
           unsigned short int depth = 0, irr::core::vector3df origin = irr::core::vector3df(0,0,0));
    ~Octree();
    void Insert(entity::IBaseEntity* item);
    bool Remove(entity::IBaseEntity* item);
    bool IsLeaf();
    bool IsFull();

    unsigned int IndicesCount();
    unsigned int IndicesCountWithChildren();

    void RecalculateIndices();
    void UpdateIndex(entity::IBaseEntity* item);

    EntityGroup& GetIndices();
    EntityGroup GetIndicesWithChildren();
    virtual EntityGroup GetNeighbors(entity::IBaseEntity* item);
};

static unsigned short int GetOctreeOctant(irr::core::vector3df index, irr::core::vector3df origin = irr::core::vector3df(0,0,0))
{
    unsigned short int octant = 0;
    if(index.X < origin.X) octant |= 1;
    if(index.Z < origin.Z) octant |= 2;
    if(index.Y < origin.Y) octant |= 4;

    return octant;
}

static irr::core::vector3df GetUnitVectorForOctant(unsigned short int octant)
{
    irr::core::vector3df unit = irr::core::vector3df(0,0,0);

    unit.X = octant & 1 ? -1 : 1;
    unit.Z = octant & 2 ? -1 : 1;
    unit.Y = octant & 4 ? -1 : 1;

    return unit;
}

} //end namespace spatial
} //end namespace desteer
