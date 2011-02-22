//
// This is a pure virtual class that is the base of all steering behaviors.
// These are used in conjunction with the ModularSteeringController or custom steering controllers
// based off the ISteeringController.
//

#pragma once
#include "desteer/entity/IMobileEntity.hpp"

namespace desteer{
namespace behavior{

class ISteeringBehavior
{
    public:
        virtual ~ISteeringBehavior();
        virtual irr::core::vector3df Calculate() = 0;
        virtual void SetMobile(entity::IMobileEntity * mob) = 0;

};//end class ISteeringBehavior

} //end ns behavior
} //end ns desteer
