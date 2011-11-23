#include "desteer/spatial/Octree.hpp"
#include <algorithm>

using namespace desteer;
using namespace spatial;
using namespace entity;
using namespace irr;
using namespace core;
using namespace std;

Octree::Octree(unsigned short int maxDepth, unsigned int maxIndices, float size, unsigned short int depth, vector3df origin)
{
    _maxDepth = maxDepth;
    _maxIndices = maxIndices;
    _depth = depth;
    _size = size;
    _origin = origin;

    _children = 0;
}

Octree::~Octree()
{
    // be sure to not leak memory by deleting all the way down if there are children.
    if(_children){
        for(int i = 0; i < 8; ++i)
        {
            delete _children[i];
        }
    }

    delete[] _children;
}

void Octree::Insert(IBaseEntity *item)
{
    if(IsLeaf())
    {
        _indices.push_back(item);
        Grow();
    }
    else
    {
        InsertIntoChild(item);
    }
}

void Octree::InsertIntoChild(entity::IBaseEntity* item)
{
    if((item->Radius() * 2) < _size)
    {
        // Determine which child to add index to, and add it to node.
        unsigned short int octant = GetOctreeOctant(item->Position(),_origin);
        _children[octant]->Insert(item);

        EntityIterator it = find(_indices.begin(),_indices.end(),item);
        if(it != _indices.end())
        {
            _indices.erase(it);
        }
    }
}

void Octree::Grow()
{
    if(ShouldSplit())
    {
        _children = new Octree*[8];

        //Actually build the children.
        for(unsigned short int i = 0; i < 8; ++i)
        {
            //Calculate new child origin that is based off parent origin
            irr::core::vector3df childOrigin = (GetUnitVectorForOctant(i) * (_size / 4)) + _origin;

            //Create the child.
            _children[i] = new Octree(_maxDepth, _maxIndices, _size / 2.0f, _depth + 1, childOrigin);
        }

        EntityGroup indices = _indices;

        //Go through my indices, and put them in my children.
        for(EntityIterator it = indices.begin(); it != indices.end(); ++it)
        {
            InsertIntoChild(*it);
        }
    }
}

bool Octree::Remove(IBaseEntity *item)
{
    // If this is a leaf node, delete it from here.
    if(IsLeaf())
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
    // Otherwise, ask children to delete it.
    else
    {
        for(int i = 0; i < 8; ++i)
        {
            if(_children[i]->Remove(item))
            {
                Prune();
                return true;
            }
        }
    }
    return false;
}

void Octree::Prune()
{
    if(CanPruneLeafs())
    {
        for(int i = 0; i < 8; ++i)
        {
            for(EntityIterator it = _children[i]->GetIndices().begin(); it != _children[i]->GetIndices().end(); ++it)
            {
                _indices.push_back(*it);
            }
            delete _children[i];
        }
        delete [] _children;
        _children = 0;
    }
}

unsigned int Octree::IndicesCount()
{
    return _indices.size();
}

unsigned int Octree::IndicesCountWithChildren()
{
    if(IsLeaf())
    {
        return IndicesCount();
    }

    unsigned int totalIndicesInChildren = 0;
    for(int i = 0; i < 8; ++i)
    {
        totalIndicesInChildren += _children[i]->IndicesCountWithChildren();
    }
    return totalIndicesInChildren + IndicesCount();
}

bool Octree::CanPruneLeafs()
{
    if(IsLeaf())
    {
        return false;
    }

    return IndicesCountWithChildren() <= _maxIndices;

}

bool Octree::ShouldSplit()
{
    return IsFull() && _depth < _maxDepth;
}

bool Octree::IsFull()
{
    //Is full it is not a leaf(meaning its split already),
    //or the number of indices is greater than the max index allowance.
    return !IsLeaf() || (IndicesCount() > _maxIndices);
}

bool Octree::IsLeaf()
{
    //Either it is as deep as it can go in the tree, or it is a leaf without children.
    return _depth == _maxDepth || !_children;
}

void Octree::RecalculateIndices()
{
    EntityGroup allIndices = GetIndicesWithChildren();

    for(EntityIterator it = allIndices.begin(); it != allIndices.end(); ++it)
    {
        UpdateIndex(*it);
    }
}

void Octree::UpdateIndex(IBaseEntity* item)
{
    EntityGroup neighbors = GetNeighbors(item);
    if(find(neighbors.begin(),neighbors.end(),item) == neighbors.end()
       || item->Radius() > (_size / pow(2,_maxDepth))
       || item->Radius() * 2 < _size)
    {
        Remove(item);
        Insert(item);
    }
}

EntityGroup Octree::GetIndicesWithChildren()
{
    if(IsLeaf())
    {
        return _indices;
    }

    EntityGroup indices = _indices;
    for(int i = 0; i < 8; ++i)
    {
        EntityGroup childIndices = _children[i]->GetIndicesWithChildren();
        indices.insert(indices.end(),childIndices.begin(),childIndices.end());
    }
    return indices;

}

EntityGroup& Octree::GetIndices()
{
    return _indices;
}

EntityGroup Octree::GetNeighbors(IBaseEntity* item)
{
    if(IsLeaf() || item->Radius() * 2 > _size)
    {
        return _indices;
    }
    else
    {
        unsigned int octant = GetOctreeOctant(item->Position(), _origin);
        EntityGroup indices = _indices;
        EntityGroup childIndices = _children[octant]->GetNeighbors(item);
        indices.insert(indices.end(),childIndices.begin(),childIndices.end());
        return indices;
    }
}
