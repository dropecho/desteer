//
// This is a concrete implementation of a modular steering controller.
// It takes in steering behaviors at runtime, and will sum/accumulate the steering forces from those.
//

#pragma once
#include "ISteeringController.hpp"
#include "desteer/Types.hpp"
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/behavior/ISteeringBehavior.hpp"

namespace desteer{
namespace controller{

class ModularSteeringController : ISteeringController
{
private:
    entity::IMobileEntity * _mob;
    BehaviorGroup _behaviors;

public:
    ModularSteeringController(entity::IMobileEntity * mob);
    irr::core::vector3df Calculate();

    void AddBehavior(behavior::ISteeringBehavior * behavior);

};

} //end ns controller
} //end ns desteer
