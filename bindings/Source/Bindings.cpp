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

#include "Bindings/DESteer/ScriptedBaseEntity.hpp"
#include "Bindings/DESteer/ScriptedMobileEntity.hpp"

#include "desteer/Types.hpp"
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/controller/SimpleSteeringController.hpp"

using namespace LikeMagic;

using namespace desteer;
using namespace desteer::entity;
using namespace desteer::controller;
using namespace desteer::behavior;

namespace Bindings { namespace DESteer {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_desteer = Namespace::global(type_sys).subspace("desteer");

    LM_CLASS(ns_desteer, BehaviorGroup)
    LM_CLASS(ns_desteer, BehaviorIterator)
    LM_CLASS(ns_desteer, MobGroup)
    LM_CLASS(ns_desteer, MobIterator)
    LM_CLASS(ns_desteer, EntityGroup)
    LM_CLASS(ns_desteer, EntityIterator)

    auto ns_entity = ns_desteer.subspace("entity");

    LM_CLASS(ns_entity, IBaseEntity)

    LM_FUNC(IBaseEntity,
        (Position)
        (SetPosition)
        (Radius)
        (Update)
    )

    LM_CLASS(ns_entity, IEntitySpace)

    LM_FUNC(IEntitySpace,
        (SideVector)
        (SetSideVector)
        (ForwardVector)
        (SetForwardVector)
        (transformWorldVectToLocal)
        (transformLocalVectToWorld)
    )

    LM_CLASS(ns_entity, IMobileEntity)
    LM_BASE(IMobileEntity, IBaseEntity)
    LM_BASE(IMobileEntity, IEntitySpace)

    LM_FUNC(IMobileEntity,
        (SetSteering)
        (Mass)
        (SetMass)
        (MaxForce)
        (SetMaxForce)
        (MaxSpeed)
        (SetMaxSpeed)
        (Velocity)
    )

    LM_CLASS(ns_entity, ScriptedBaseEntity)
    LM_BASE(ScriptedBaseEntity, IBaseEntity)
    LM_CONSTR(ScriptedBaseEntity,,)

    LM_BLOCK(ScriptedBaseEntity,
        (Position)
        (SetPosition)
        (Radius)
        (Update)
    )

    LM_CLASS(ns_entity, ScriptedEntitySpace)
    LM_BASE(ScriptedEntitySpace, IEntitySpace)
    LM_CONSTR(ScriptedEntitySpace,,)

    LM_BLOCK(ScriptedEntitySpace,
        (SideVector)
        (SetSideVector)
        (ForwardVector)
        (SetForwardVector)
        (transformWorldVectToLocal)
        (transformLocalVectToWorld)
    )

    LM_CLASS(ns_entity, ScriptedMobileEntity)
    LM_BASE(ScriptedMobileEntity, IMobileEntity)
    LM_CONSTR(ScriptedMobileEntity,,)

    LM_BLOCK(ScriptedMobileEntity,

        // IBaseEntity
        (Position)
        (SetPosition)
        (Radius)
        (Update)

        // IEntitySpace
        (SideVector)
        (SetSideVector)
        (ForwardVector)
        (SetForwardVector)
        (transformWorldVectToLocal)
        (transformLocalVectToWorld)

        // IMobileEntity
        (SetSteering)
        (Mass)
        (SetMass)
        (MaxForce)
        (SetMaxForce)
        (MaxSpeed)
        (SetMaxSpeed)
        (Velocity)
    )

    auto ns_controller = ns_desteer.subspace("controller");

    LM_CLASS(ns_controller, ISteeringController)
    LM_FUNC(ISteeringController, (Calculate))

    LM_CLASS(ns_controller, SimpleSteeringController)
    LM_BASE(SimpleSteeringController, ISteeringController)
    LM_CONSTR(SimpleSteeringController,, entity::IMobileEntity*)

    LM_FUNC(SimpleSteeringController,
        (SetBehaviorFlag)
        (SetSeekTarget)
        (SetArriveTarget)
        (SetHideTarget)
        (SetPursuitTarget)
        (SetObstacles)
    )

    auto ns_behavior = ns_desteer.subspace("behavior");

}

}}
