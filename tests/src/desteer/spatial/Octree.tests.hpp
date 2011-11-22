#include "desteer/spatial/octree.hpp"
#include <iostream>
#include <tut/tut.hpp>
namespace tut
{

class TestEntity : public desteer::entity::IBaseEntity
{
    private:
        irr::core::vector3df _position;
        float _radius;

    public:
        TestEntity(irr::core::vector3df position = irr::core::vector3df(0,0,0), float radius = 0)
        {
            _position = position;
            _radius = radius;
        }

        virtual irr::core::vector3df Position() const {return _position;};
        virtual void SetPosition(irr::core::vector3df position) {_position = position;};
        virtual float Radius() const {return _radius;};

        virtual void Update(float timeElapsed){};
};

struct octree_test_data
{
    desteer::spatial::Octree *octree;
    octree_test_data()
    {
        octree = new desteer::spatial::Octree(8,1);
    }

    void Clear()
    {
        delete octree;
        octree = new desteer::spatial::Octree(8,1);
    }
};

typedef test_group<octree_test_data> octree_tg;
typedef octree_tg::object octree_tests;

octree_tg octree_test_suite("Octree Tests");

template<>
template<>
void octree_tests::test<1>()
{
    set_test_name("When adding an index to an empty octree");
    Clear();

    TestEntity* entity = new TestEntity();
    octree->Insert(entity);

    ensure_equals("Index count should be incremented to 1",octree->IndicesCount(),1);
}

template<>
template<>
void octree_tests::test<2>()
{
    set_test_name("When adding two indices");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);

    TestEntity* entity2 = new TestEntity(irr::core::vector3df(0,0,1));
    octree->Insert(entity2);

    ensure_equals("Tree should have split, so top node should not be leaf",octree->IsLeaf(),false);
    ensure_equals("Index count should now be 0",octree->IndicesCount(),0);
    ensure_equals("Index count with children should now be 2",octree->IndicesCountWithChildren(),2);
}

template<>
template<>
void octree_tests::test<3>()
{
    set_test_name("When adding one index and then removing it.");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);
    octree->Remove(entity1);

    ensure_equals("Index count should now be 0",octree->IndicesCount(),0);
}

template<>
template<>
void octree_tests::test<4>()
{
    set_test_name("When adding two indices and then removing one");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);

    TestEntity* entity2 = new TestEntity(irr::core::vector3df(0,0,1));
    octree->Insert(entity2);
    octree->Remove(entity2);

    ensure_equals("Index count should now be 1",octree->IndicesCount(),1);
    ensure_equals("Index count with children should now be 1",octree->IndicesCountWithChildren(),1);
    ensure_equals("Tree should have pruned, so top node should be leaf",octree->IsLeaf(),true);
}

template<>
template<>
void octree_tests::test<5>()
{
    set_test_name("When adding two indices in different octants and checking neighbors");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);

    TestEntity* entity2 = new TestEntity(irr::core::vector3df(0,0,1));
    octree->Insert(entity2);

    ensure_equals("Should only have 1 neighbor, itself.",octree->GetNeighbors(entity1).size(),1);
}

template<>
template<>
void octree_tests::test<6>()
{
    set_test_name("When adding two indices in same octant and checking neighbors");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);

    TestEntity* entity2 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity2);

    ensure_equals("Should have 2 neighbors, including itself.",octree->GetNeighbors(entity1).size(),2);
}

template<>
template<>
void octree_tests::test<7>()
{
    set_test_name("When adding two indices in same octant and checking neighbors after one has moved to a new octant without recalculating indices");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);

    TestEntity* entity2 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity2);

    entity1->SetPosition(irr::core::vector3df(0,0,1));

    ensure_equals("Should have no neighbors.",octree->GetNeighbors(entity1).size(),0);
}

template<>
template<>
void octree_tests::test<8>()
{
    set_test_name("When adding two indices in same octant and checking neighbors after one has moved to a new octant and indices have been recalculated");
    Clear();

    TestEntity* entity1 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity1);

    TestEntity* entity2 = new TestEntity(irr::core::vector3df(1,0,0));
    octree->Insert(entity2);

    entity1->SetPosition(irr::core::vector3df(0,0,1));
    octree->RecalculateIndices();

    ensure_equals("Should have 1 neighbors.",octree->GetNeighbors(entity1).size(),1);
}
}
