#pragma once
#include "desteer/entity/IBaseEntity.hpp"
#include "desteer/Types.hpp"
#include <vector>

namespace desteer{
namespace spatial{

class octree
{
private:
    EntityGroup _indices;
    octree** _children;
    unsigned int _maxDepth;
    unsigned int _maxIndices;
    float _size;
public:
    octree(unsigned int maxDepth = 8, unsigned int maxIndices = 36, float size = 256.0f);
    ~octree();
    void insert(entity::IBaseEntity* item);
    bool remove(entity::IBaseEntity* item);
    bool isSplit();

    int indicesCount();

    void recalculateIndices();
    EntityGroup findNeighbors(entity::IBaseEntity* item);
};


} //end namespace spatial
} //end namespace desteer
