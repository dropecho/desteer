#pragma once
#include "desteer/behavior/ISteeringBehavior.hpp"
#include "desteer/behavior/SeekBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace behavior{

class PursuitBehavior : public ISteeringBehavior
{
    private:
    boost::shared_ptr<entity::IMobileEntity> _mob;
    boost::shared_ptr<entity::IMobileEntity> _target;

    boost::shared_ptr<SeekBehavior> _seekBehavior;

public:
    PursuitBehavior(boost::shared_ptr<entity::IMobileEntity> target);
    irr::core::vector3df Calculate();
    void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
    void SetTarget(boost::shared_ptr<entity::IMobileEntity> target);
};


} //end ns behavior
} //end ns desteer
