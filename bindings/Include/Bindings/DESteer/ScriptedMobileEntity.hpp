#pragma once
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/controller/SimpleSteeringController.hpp"

namespace desteer {
namespace entity {

class ScriptedMobileEntity : public LikeMagic::MarkableObjGraph, public IMobileEntity
{
public:
    ScriptFunc(0, irr::core::vector3df, Position,                       const,)
    ScriptFunc(1, void,                 SetPosition,                /* not const */,    (irr::core::vector3df))
    ScriptFunc(0, float,                Radius,                         const,)
    ScriptFunc(1, void,                 Update,                     /* not const */,    (float))
    ScriptFunc(0, irr::core::vector3df, PredictFuturePosition,          const,          (const float))
    ScriptFunc(0, irr::core::vector3df, SideVector,                     const,)
	ScriptFunc(1, void,                 SetSideVector,              /* not const */,    (irr::core::vector3df))
	ScriptFunc(0, irr::core::vector3df, ForwardVector,                  const,)
	ScriptFunc(1, void,                 SetForwardVector,           /* not const */,    (irr::core::vector3df))
    ScriptFunc(0, irr::core::vector3df, transformWorldVectToLocal,  /* not const */,    (irr::core::vector3df))
	ScriptFunc(0, irr::core::vector3df, transformLocalVectToWorld,  /* not const */,    (irr::core::vector3df))
	ScriptFunc(1, void,                 SetSteering,                /* not const */,    (controller::ISteeringController*))
};

}//end namespace entity
}//end namespace desteer
