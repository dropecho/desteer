#pragma once
#include "ISteeringBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace behavior{

class FleeBehavior : public ISteeringBehavior
{
    private:
        irr::core::vector3df _target;
        boost::shared_ptr<entity::IMobileEntity> _mob;

        float _fleeDistance;
    public:
        FleeBehavior(irr::core::vector3df target, float fleeDistance = -1);
        void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
        void SetTarget(irr::core::vector3df target);
        irr::core::vector3df Calculate();
        virtual ~FleeBehavior(){}
};

} //end ns behavior
} //end ns desteer

