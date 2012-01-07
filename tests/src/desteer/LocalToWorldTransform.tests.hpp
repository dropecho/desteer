#include "desteer/VectorTransformer.hpp"
#include <iostream>
#include <tut/tut.hpp>

using namespace desteer;

namespace tut
{
	struct util_local_to_world_data{};
	typedef test_group<util_local_to_world_data> util_local_to_world_tg;
	typedef util_local_to_world_tg::object local_to_world_tests;

	util_local_to_world_tg util_local_to_world_test_suite("Util - Local to World Vector Transformations");

	template<>
	template<>
	void local_to_world_tests::test<1>()
	{
	    set_test_name("with heading on postive x-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(1,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

	template<>
	template<>
	void local_to_world_tests::test<2>()
	{
	    set_test_name("with heading on negative z-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,-1);
        irr::core::vector3df side = irr::core::vector3df(1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(0,0,1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

	template<>
	template<>
	void local_to_world_tests::test<3>()
	{
	    set_test_name("with heading on postive z-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(0,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}


	template<>
	template<>
	void local_to_world_tests::test<4>()
	{
	    set_test_name("with heading on negative x-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(-1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,-1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(0,0,1);
        irr::core::vector3df localVec = irr::core::vector3df(0,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

	template<>
	template<>
	void local_to_world_tests::test<5>()
	{
	    set_test_name("with heading on postive x-axis with position offset (1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(1,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(0,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

	template<>
	template<>
	void local_to_world_tests::test<6>()
	{
	    set_test_name("with heading on postive x-axis with position offset (-1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(-1,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(2,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

    template<>
	template<>
	void local_to_world_tests::test<7>()
	{
	    set_test_name("with heading on postive x-axis with position offset (0,0,1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,1);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(1,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

    template<>
	template<>
	void local_to_world_tests::test<8>()
	{
	    set_test_name("with heading on postive x-axis with position offset (0,0,-1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,-1);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(1,0,1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

    template<>
	template<>
	void local_to_world_tests::test<9>()
	{
	    set_test_name("with heading on postive z-axis with position offset (1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(1,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(0,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

    template<>
	template<>
	void local_to_world_tests::test<10>()
	{
	    set_test_name("with heading on postive z-axis with position offset (-1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(-1,0,0);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(0,0,-2);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

    template<>
	template<>
	void local_to_world_tests::test<11>()
	{
	    set_test_name("with heading on postive z-axis with position offset (0,0,1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,1);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(-1,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}

	template<>
	template<>
	void local_to_world_tests::test<12>()
	{
	    set_test_name("with heading on postive z-axis with position offset (0,0,-1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,-1);

        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);
        irr::core::vector3df localVec = irr::core::vector3df(1,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::LocalToWorld(localVec,forward,side,pos);

        ensure(transformedVec == worldVec);
	}
}

