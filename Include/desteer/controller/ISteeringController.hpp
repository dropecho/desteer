#pragma once
#include "irrlicht/irrlicht.h"
#include "desteer/Types.hpp"
#include "desteer/entity/IMobileEntity.hpp"

namespace desteer{
namespace controller{

class ISteeringController
{
    public:
    virtual irr::core::vector3df Calculate() = 0;
};

} //end ns controller
} //end ns desteer
