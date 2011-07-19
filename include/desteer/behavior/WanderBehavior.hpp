#pragma once
#include "ISteeringBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace behavior{

class WanderBehavior : public ISteeringBehavior
{
private:
    boost::shared_ptr<entity::IMobileEntity> _mob;

    float _wanderRadius;
    float _wanderDistance;
    float _wanderJitter;

public:
    WanderBehavior(float wanderRadius = 10, float wanderDistance = 20, float wanderJitter = 10 );
    irr::core::vector3df Calculate();
    void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
    virtual ~WanderBehavior(){}
};

} //end ns behavior
} //end ns desteer

