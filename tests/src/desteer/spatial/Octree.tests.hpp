#include "desteer/Util.hpp"
#include <iostream>
#include <tut/tut.hpp>
namespace tut
{

struct octree_test_data {};
typedef test_group<octree_test_data> octree_tg;
typedef octree_tg::object octree_tests;

octree_tg octree_test_suite("Octree Tests");

template<>
template<>
void octree_tests::test<1>()
{
    set_test_name("with heading on postive z-axis");

    //setup a local coords system with heading along positive z-axis
    irr::core::vector3df forward = irr::core::vector3df(0,0,1);
    irr::core::vector3df side = irr::core::vector3df(1,0,0);

    //position of local coords in world coords
    irr::core::vector3df pos = irr::core::vector3df(0,0,0);

    //input for transformation
    irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

    //correct output for transformation
    irr::core::vector3df localVec = irr::core::vector3df(1,0,0);

    irr::core::vector3df transformedVec = VectorTransformer::VectorTransformWorldToLocal(worldVec,forward,side,pos);

    //ensure_equals("<1,0,0> => <0,0,1>", transformedVec ,localVec);
    ensure(transformedVec == localVec);
}
}
