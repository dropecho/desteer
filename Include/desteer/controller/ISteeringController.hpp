#pragma once
#include "irrvector/vector3d.h"
#include "desteer/Types.hpp"
#include "desteer/entity/IMobileEntity.hpp"

namespace desteer{
namespace controller{

class ISteeringController
{
    public:
    virtual ~ISteeringController();
    virtual irr::core::vector3df Calculate() = 0;
};

} //end ns controller
} //end ns desteer
