#pragma once
#include "ISteeringBehavior.hpp"

namespace desteer{
namespace behavior{

class SeekBehavior : ISteeringBehavior
{
    private:
        irr::core::vector3df _target;
        entity::IMobileEntity * _mob;
    public:
        SeekBehavior(irr::core::vector3df target);
        void SetMobile(entity::IMobileEntity * mob);
        irr::core::vector3df Calculate();
};

} //end ns behavior
} //end ns desteer
