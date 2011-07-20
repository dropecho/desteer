#pragma once
#include "desteer/controller/ISteeringController.hpp"

//Include all basic behaviors.
#include "desteer/behavior/SeekBehavior.hpp"
#include "desteer/behavior/FleeBehavior.hpp"
#include "desteer/behavior/WanderBehavior.hpp"
#include "desteer/behavior/PursuitBehavior.hpp"
#include "desteer/behavior/EvadeBehavior.hpp"
#include "desteer/behavior/ArriveBehavior.hpp"
#include "desteer/behavior/HideBehavior.hpp"
#include "desteer/behavior/ObstacleAvoidanceBehavior.hpp"
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <string>

namespace desteer
{
namespace controller
{

enum EBEHAVIOR_FLAG
{
    EBF_ARRIVE  = 0x01,
    EBF_EVADE   = 0x02,
    EBF_FLEE    = 0x04,
    EBF_HIDE    = 0x08,
    EBF_SEEK    = 0x10,
    EBF_PURSUIT = 0x20,
    EBF_WANDER  = 0x40,
    EBF_AVOID   = 0x80
};

class SimpleSteeringController : public ISteeringController
{
private:
    boost::shared_ptr<desteer::entity::IMobileEntity>     _mob;
    irr::core::vector3df        _seekTarget;
    irr::core::vector3df        _arriveTarget;
    irr::core::vector3df        _fleeTarget;

    boost::shared_ptr<desteer::entity::IMobileEntity>     _evadeTarget;
    boost::shared_ptr<desteer::entity::IMobileEntity>     _hideTarget;
    boost::shared_ptr<desteer::entity::IMobileEntity>     _pursuitTarget;
    boost::shared_ptr<EntityGroup>    _obstacles;

    unsigned int _behaviorFlags;

    boost::shared_ptr<desteer::behavior::ArriveBehavior>  _arriveBehavior;
    boost::shared_ptr<desteer::behavior::EvadeBehavior>   _evadeBehavior;
    boost::shared_ptr<desteer::behavior::FleeBehavior>    _fleeBehavior;
    boost::shared_ptr<desteer::behavior::HideBehavior>    _hideBehavior;
    boost::shared_ptr<desteer::behavior::SeekBehavior>    _seekBehavior;
    boost::shared_ptr<desteer::behavior::PursuitBehavior> _pursuitBehavior;
    boost::shared_ptr<desteer::behavior::WanderBehavior>  _wanderBehavior;
    boost::shared_ptr<desteer::behavior::ObstacleAvoidanceBehavior> _obsAvoidBehavior;


public:
    SimpleSteeringController(boost::shared_ptr<desteer::entity::IMobileEntity> vehicle);
    irr::core::vector3df Calculate();

    void SetBehaviorFlag(EBEHAVIOR_FLAG flag, bool active);

    void SetSeekTarget(irr::core::vector3df target);
    void SetArriveTarget(irr::core::vector3df target);
    void SetHideTarget(boost::shared_ptr<desteer::entity::IMobileEntity> target);
    void SetPursuitTarget(boost::shared_ptr<desteer::entity::IMobileEntity> target);

    void SetObstacles(boost::shared_ptr<desteer::EntityGroup> obstacles);

    virtual ~SimpleSteeringController(){
    }
};

}//end ns controller
}//end ns desteer
