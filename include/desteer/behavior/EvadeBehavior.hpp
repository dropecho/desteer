#pragma once
#include "desteer/behavior/ISteeringBehavior.hpp"
#include "desteer/behavior/FleeBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace behavior{

class EvadeBehavior : public ISteeringBehavior
{
    private:
    boost::shared_ptr<entity::IMobileEntity> _mob;
    boost::shared_ptr<entity::IMobileEntity> _target;

    boost::shared_ptr<FleeBehavior> _fleeBehavior;

public:
    EvadeBehavior(boost::shared_ptr<entity::IMobileEntity> target = boost::shared_ptr<entity::IMobileEntity>());
    irr::core::vector3df Calculate();
    void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
    void SetTarget(boost::shared_ptr<entity::IMobileEntity> target);
    virtual ~EvadeBehavior(){}
};


} //end ns behavior
} //end ns desteer
