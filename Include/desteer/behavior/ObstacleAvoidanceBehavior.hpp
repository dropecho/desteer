#pragma once
#include "ISteeringBehavior.hpp"
#include "desteer/Types.hpp"

namespace desteer{
namespace behavior{

class ObstacleAvoidanceBehavior : ISteeringBehavior
{
private:
    entity::IMobileEntity * _mob;

    EntityGroup _obstacles;

public:
    ObstacleAvoidanceBehavior(EntityGroup & obstacles);
    irr::core::vector3df Calculate();
    void SetMobile(entity::IMobileEntity * mob);
};

} //end ns behavior
} //end ns desteer
