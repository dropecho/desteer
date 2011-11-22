#include "desteer/Util.hpp"
#include "desteer/spatial/octree.hpp"
#include <iostream>
#include <tut/tut.hpp>
namespace tut
{

struct octree_get_unit_vec_for_octant_test_data {};
typedef test_group<octree_get_unit_vec_for_octant_test_data> octree_get_unit_vec_for_octant_tg;
typedef octree_get_unit_vec_for_octant_tg::object octree_get_unit_vec_for_octant_tests;

octree_get_unit_vec_for_octant_tg octree_get_unit_vec_for_octant_test_suite("Get Octant's Unit Vector Tests");

template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<1>()
{
    set_test_name("octant 0 should have a unit vector of (1,1,1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(0) == irr::core::vector3df(1,1,1));
}

template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<2>()
{
    set_test_name("octant 1 should have a unit vector of (-1,1,1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(1) == irr::core::vector3df(-1,1,1));
}
template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<3>()
{
    set_test_name("octant 2 should have a unit vector of (1,1,-1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(2) == irr::core::vector3df(1,1,-1));
}
template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<4>()
{
    set_test_name("octant 3 should have a unit vector of (-1,1,-1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(3) == irr::core::vector3df(-1,1,-1));
}
template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<5>()
{
    set_test_name("octant 4 should have a unit vector of (1,-1,1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(4) == irr::core::vector3df(1,-1,1));
}
template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<6>()
{
    set_test_name("octant 5 should have a unit vector of (-1,-1,1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(5) == irr::core::vector3df(-1,-1,1));
}
template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<7>()
{
    set_test_name("octant 6 should have a unit vector of (1,-1,-1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(6) == irr::core::vector3df(1,-1,-1));
}
template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<8>()
{
    set_test_name("octant 7 should have a unit vector of (-1,-1,-1)");
    ensure(desteer::spatial::GetUnitVectorForOctant(7) == irr::core::vector3df(-1,-1,-1));
}

template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<9>()
{
    set_test_name("in octree size 512, origin of octant 0 should be (128,128,128)");
    irr::core::vector3df expectedOrigin = irr::core::vector3df(128,128,128);

    irr::core::vector3df actualOrigin = desteer::spatial::GetUnitVectorForOctant(0) * (512 / 4);

    ensure(actualOrigin == expectedOrigin);
}

template<>
template<>
void octree_get_unit_vec_for_octant_tests::test<10>()
{
    set_test_name("in octree size 512, origin of octant 7 should be (-128,-128,-128)");
    irr::core::vector3df expectedOrigin = irr::core::vector3df(-128,-128,-128);

    irr::core::vector3df actualOrigin = desteer::spatial::GetUnitVectorForOctant(7) * (512 / 4);

    ensure(actualOrigin == expectedOrigin);
}
}

