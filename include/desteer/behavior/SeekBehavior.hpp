#pragma once
#include "ISteeringBehavior.hpp"

#include <boost/smart_ptr.hpp>

namespace desteer
{
namespace behavior
{

class SeekBehavior : public ISteeringBehavior
{
private:
    irr::core::vector3df _target;
    boost::shared_ptr<entity::IMobileEntity> _mob;
public:
    SeekBehavior(irr::core::vector3df target = irr::core::vector3df(0,0,0), boost::shared_ptr<entity::IMobileEntity> mob = boost::shared_ptr<entity::IMobileEntity>());
    void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
    void SetTarget(irr::core::vector3df target);
    void SetTarget(boost::shared_ptr<entity::IMobileEntity> target)
    {
        return;
    };
    irr::core::vector3df Calculate();
    virtual ~SeekBehavior(){}
};

} //end ns behavior
} //end ns desteer
