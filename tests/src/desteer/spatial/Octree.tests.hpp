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
    set_test_name("");


    ensure(true);
}
}
