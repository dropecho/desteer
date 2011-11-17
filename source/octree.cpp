#include "desteer/spatial/octree.hpp"


using namespace desteer;
using namespace spatial;
using namespace entity;

using namespace std;

octree::octree(unsigned int maxDepth, unsigned int maxIndices, float size)
{
    _maxDepth = maxDepth;
    _maxIndices = maxIndices;
    _size = size;
    _children = 0;
}

octree::~octree()
{
    // be sure to not leak memory by deleting all the way down if there are children.
    if(_children){
        for(int i = 0; i < 8; ++i)
        {
            delete _children[i];
        }
    }
}

void octree::insert(IBaseEntity *item)
{
    // If already split, add item to a leaf node...
    if(isSplit())
    {
        // Determine which node to add index to.

        // Add index to correct node;
    }
    // else simply add it here.
    else
    {
        // Split the tree when it has too many indices.
        if(_indices.size() == _maxIndices)
        {
            _children = new octree*[8];
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

bool octree::remove(IBaseEntity *item)
{

    // If the tree has split parse the children recursively until its removed.
    if(isSplit())
    {
        for(int i = 0; i < 8; ++i)
        {
            bool breakOut = _children[i]->remove(item);
            if(breakOut)
            {
                return true;
            }
        }
    }
    // Otherwise, just delete it from this node.
    else
    {
        for(EntityIterator it = _indices.begin(); it != _indices.end(); ++it)
        {
            if(*it == item)
            {
                _indices.erase(it);
                return true;
            }
        }
    }

    return false;
}

int octree::indicesCount()
{
    return _indices.size();
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

EntityGroup octree::findNeighbors(IBaseEntity* item)
{
    EntityGroup e;
    return e;
}
