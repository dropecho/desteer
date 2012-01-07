#include "desteer/VectorTransformer.hpp"
#include "desteer/spatial/octree.hpp"
#include <iostream>
#include <tut/tut.hpp>
namespace tut
{

struct octree_get_octant_test_data {};
typedef test_group<octree_get_octant_test_data> octree_get_octant_tg;
typedef octree_get_octant_tg::object octree_get_octant_tests;

octree_get_octant_tg octree_get_octant_test_suite("Get Octree Octant From Vector Tests");

template<>
template<>
void octree_get_octant_tests::test<1>()
{
    irr::core::vector3df vec = irr::core::vector3df(0,0,0);

    ensure_equals("vec(0,0,0) should be in octant 0",desteer::spatial::GetOctreeOctant(vec) , 0);
}
template<>
template<>
void octree_get_octant_tests::test<2>()
{
    irr::core::vector3df vec = irr::core::vector3df(1,0,0);

    ensure_equals("vec(1,0,0) should be in octant 0",desteer::spatial::GetOctreeOctant(vec),0);
}
template<>
template<>
void octree_get_octant_tests::test<3>()
{
    irr::core::vector3df vec = irr::core::vector3df(0,1,0);

    ensure_equals("vec(0,1,0) should be in octant 0",desteer::spatial::GetOctreeOctant(vec) ,0);
}
template<>
template<>
void octree_get_octant_tests::test<4>()
{
    irr::core::vector3df vec = irr::core::vector3df(0,0,1);

    ensure_equals("vec(0,0,1) should be in octant 0",desteer::spatial::GetOctreeOctant(vec), 0);
}
template<>
template<>
void octree_get_octant_tests::test<5>()
{
    irr::core::vector3df vec = irr::core::vector3df(-1,0,0);

    ensure_equals("vec(-1,0,0) should be in octant 1",desteer::spatial::GetOctreeOctant(vec), 1);
}
template<>
template<>
void octree_get_octant_tests::test<6>()
{
    irr::core::vector3df vec = irr::core::vector3df(0,0,-1);

    ensure_equals("vec(0,0,-1) should be in octant 3",desteer::spatial::GetOctreeOctant(vec), 2);
}
template<>
template<>
void octree_get_octant_tests::test<7>()
{
    irr::core::vector3df vec = irr::core::vector3df(-1,0,-1);

    ensure_equals("vec(-1,0,-1) should be in octant 3",desteer::spatial::GetOctreeOctant(vec) , 3);
}
template<>
template<>
void octree_get_octant_tests::test<8>()
{
    irr::core::vector3df vec = irr::core::vector3df(0,-1,0);

    ensure_equals("vec(0,-1,0) should be in octant 2",desteer::spatial::GetOctreeOctant(vec), 4);
}
template<>
template<>
void octree_get_octant_tests::test<9>()
{
    irr::core::vector3df vec = irr::core::vector3df(-1,-1,0);

    ensure_equals("vec(-1,0,-1) should be in octant 5",desteer::spatial::GetOctreeOctant(vec) , 5);
}
template<>
template<>
void octree_get_octant_tests::test<10>()
{
    irr::core::vector3df vec = irr::core::vector3df(0,-1,-1);

    ensure_equals("vec(0,-1,-1) should be in octant 6",desteer::spatial::GetOctreeOctant(vec) , 6);
}
template<>
template<>
void octree_get_octant_tests::test<11>()
{
    irr::core::vector3df vec = irr::core::vector3df(-1,-1,-1);

    ensure_equals("vec(-1,-1,-1) should be in octant 7",desteer::spatial::GetOctreeOctant(vec) , 7);
}

template<>
template<>
void octree_get_octant_tests::test<12>()
{
    irr::core::vector3df origin = irr::core::vector3df(1,0,1);
    irr::core::vector3df vec = irr::core::vector3df(1,0,1);

    ensure_equals("at origin of (1,0,1) vec(1,0,1) should be in octant 0",desteer::spatial::GetOctreeOctant(vec,origin) , 0);
}

template<>
template<>
void octree_get_octant_tests::test<13>()
{
    irr::core::vector3df origin = irr::core::vector3df(1,0,1);
    irr::core::vector3df vec = irr::core::vector3df(0,0,0);

    ensure_equals("at origin of (1,0,1) vec(0,0,0) should be in octant 3",desteer::spatial::GetOctreeOctant(vec,origin) , 3);
}

template<>
template<>
void octree_get_octant_tests::test<14>()
{
    irr::core::vector3df origin = irr::core::vector3df(-1,0,-1);
    irr::core::vector3df vec = irr::core::vector3df(-1,0,-1);

    ensure_equals("at origin of (1,0,1) vec(1,0,1) should be in octant 0",desteer::spatial::GetOctreeOctant(vec,origin) , 0);
}

template<>
template<>
void octree_get_octant_tests::test<15>()
{
    irr::core::vector3df origin = irr::core::vector3df(-1,0,-1);
    irr::core::vector3df vec = irr::core::vector3df(0,0,0);

    ensure_equals("at origin of (1,0,1) vec(0,0,0) should be in octant 0",desteer::spatial::GetOctreeOctant(vec,origin) , 0);
}

}

