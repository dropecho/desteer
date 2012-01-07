#include "desteer/VectorTransformer.hpp"
#include <iostream>
#include <tut/tut.hpp>

using namespace desteer;

namespace tut
{
	struct util_world_to_local_data{};
	typedef test_group<util_world_to_local_data> util_world_to_local_tg;
	typedef util_world_to_local_tg::object object;

	util_world_to_local_tg util_world_to_local_test_suite("Util - World to Local Vector Transformations");

	template<>
	template<>
	void object::test<1>()
	{
	    set_test_name("with heading on postive x-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(1,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<1,0,0> => <0,0,1>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

	template<>
	template<>
	void object::test<2>()
	{
	    set_test_name("with heading on negative z-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,-1);
        irr::core::vector3df side = irr::core::vector3df(1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(0,0,1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<1,0,0> => <0,0,1>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

	template<>
	template<>
	void object::test<3>()
	{
	    set_test_name("with heading on postive z-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(0,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <0,0,5> => <0,0,-4>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}


	template<>
	template<>
	void object::test<4>()
	{
	    set_test_name("with heading on negative x-axis");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(-1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,-1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(0,0,1);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(0,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,1> => <-1,0,0>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

	template<>
	template<>
	void object::test<5>()
	{
	    set_test_name("with heading on postive x-axis with position offset (1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(1,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(0,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

	template<>
	template<>
	void object::test<6>()
	{
	    set_test_name("with heading on postive x-axis with position offset (-1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(-1,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(2,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

    template<>
	template<>
	void object::test<7>()
	{
	    set_test_name("with heading on postive x-axis with position offset (0,0,1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,1);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(1,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

    template<>
	template<>
	void object::test<8>()
	{
	    set_test_name("with heading on postive x-axis with position offset (0,0,-1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(1,0,0);
        irr::core::vector3df side = irr::core::vector3df(0,0,1);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,-1);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(1,0,1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

    template<>
	template<>
	void object::test<9>()
	{
	    set_test_name("with heading on postive z-axis with position offset (1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(1,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(0,0,0);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

    template<>
	template<>
	void object::test<10>()
	{
	    set_test_name("with heading on postive z-axis with position offset (-1,0,0)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(-1,0,0);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(0,0,-2);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

    template<>
	template<>
	void object::test<11>()
	{
	    set_test_name("with heading on postive z-axis with position offset (0,0,1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,1);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(-1,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}

	template<>
	template<>
	void object::test<12>()
	{
	    set_test_name("with heading on postive z-axis with position offset (0,0,-1)");

        //setup a local coords system with heading along positive z-axis
        irr::core::vector3df forward = irr::core::vector3df(0,0,1);
        irr::core::vector3df side = irr::core::vector3df(-1,0,0);

        //position of local coords in world coords
        irr::core::vector3df pos = irr::core::vector3df(0,0,-1);

        //input for transformation
        irr::core::vector3df worldVec = irr::core::vector3df(1,0,0);

        //correct output for transformation
        irr::core::vector3df localVec = irr::core::vector3df(1,0,-1);

        irr::core::vector3df transformedVec = VectorTransformer::WorldToLocal(worldVec,forward,side,pos);

        //ensure_equals("<0,0,1> @ <1,0,-1> => <0,0,2>", transformedVec ,localVec);
        ensure(transformedVec == localVec);
	}
}

