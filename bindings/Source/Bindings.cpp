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

using namespace LikeMagic;

using namespace desteer;
using namespace desteer::entity;

namespace Bindings { namespace DESteer {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_desteer = Namespace::global(type_sys).subspace("desteer");
    auto ns_entity = ns_desteer.subspace("entity");

    LM_CLASS(ns_entity, IBaseEntity)

    LM_CLASS(ns_entity, IEntitySpace)

    LM_CLASS(ns_entity, IMobileEntity)
    LM_BASE(IMobileEntity, IBaseEntity)
    LM_BASE(IMobileEntity, IEntitySpace)

    LM_CLASS(ns_entity, ScriptedBaseEntity)
    LM_BASE(ScriptedBaseEntity, IBaseEntity)
    LM_CONSTR(ScriptedBaseEntity,,)

    LM_CLASS(ns_entity, ScriptedMobileEntity)
    LM_BASE(ScriptedMobileEntity, IMobileEntity)
    LM_CONSTR(ScriptedMobileEntity,,)

}

}}
