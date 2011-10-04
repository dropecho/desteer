#include "desteer/spatial/octree.hpp"

using namespace desteer;
using namespace spatial;
using namespace entity;

using namespace std;

octree::octree(int maxDepth, int maxIndices, float size)
{
//    _children = 0;
}

void octree::insert(IBaseEntity *item)
{
    //If already split, add item to a leaf node...
    if(isSplit)
    {
        // Determine which node to add index to.

        // Add index to correct node;
    }
    // else simply add it here.
    else
    {
        // Split the tree when it has too many indices.
        if(_indices.size() +1 >= _maxIndices)
        {
            //_children = octree[8];
            // Recurse back onto this, as the chilren should now be existant.
            insert(item);
        }
        //just add the item if its still below the max.
        else
        {
            _indices.push_back(item);
        }
    }
}

void octree::remove(IBaseEntity *item)
{

}

void octree::recalculateIndices()
{

}

bool octree::isSplit()
{
    for(int i = 0; i < 8; ++i)
    {
        if(_children[i])
        {
            return true;
        }
    }

    return false;
}

IBaseEntity* octree::findNeighbors(IBaseEntity* item)
{

}
