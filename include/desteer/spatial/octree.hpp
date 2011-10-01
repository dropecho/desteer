#pragma once
#include "desteer/entity/IBaseEntity.hpp"
#include <vector>

namespace desteer{
namespace spatial{

class octree
{
private:
    std::vector<entity::IBaseEntity *> _indices;
    //octree[8] _children;
    int _maxDepth;
    int _maxIndices;
    float _size;
public:
    octree(int maxDepth = 8, int maxIndices = 36, float size = 256.0f);
    void insert(entity::IBaseEntity* item);
    void remove(entity::IBaseEntity* item);

    void recalculateIndices();
    entity::IBaseEntity* findNeighbors(entity::IBaseEntity* item);
};


} //end namespace spatial
} //end namespace desteer
