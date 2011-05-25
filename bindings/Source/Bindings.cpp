// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/DESteer/Bindings.hpp"
#include "Bindings/DESteer/Protos.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

//using namespace desteer;

namespace Bindings { namespace DESteer {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_desteer = Namespace::global(type_sys).subspace("desteer");

    //LM_CLASS(ns_desteer, PhysicsAnimator)
    //LM_BASE(PhysicsAnimator, btMotionState)
    //LM_CONSTR(PhysicsAnimator,, btTransform const&, btTransform const&)

    //LM_STATIC_FUNC(ns_desteer, Bindings::DESteer, add_protos)
}

}}
