#include "desteer/controller/SimpleSteeringController.hpp"

#include "desteer/Types.hpp"

using namespace irr;
using namespace core;
using namespace desteer;
using namespace behavior;
using namespace controller;
using namespace entity;
using boost::shared_ptr;
using boost::weak_ptr;

SimpleSteeringController::SimpleSteeringController(shared_ptr<IMobileEntity> mob)
{
    _mob = mob;
    _arriveTarget   = vector3df(0,0,0);
    _seekTarget     = vector3df(0,0,0);
    _fleeTarget     = vector3df(0,0,0);

    _evadeTarget    = shared_ptr<IMobileEntity>();
    _hideTarget     = shared_ptr<IMobileEntity>();
    _pursuitTarget  = shared_ptr<IMobileEntity>();

    _behaviorFlags  = 0;

    shared_ptr<SeekBehavior> seekBehavior(new SeekBehavior(_seekTarget,mob));
    _seekBehavior       = seekBehavior;

    shared_ptr<ArriveBehavior> arriveBehavior(new ArriveBehavior(_seekTarget,mob,.08));
    _arriveBehavior     = arriveBehavior;

    shared_ptr<FleeBehavior> fleeBehavior(new FleeBehavior(_fleeTarget));
    _fleeBehavior       = fleeBehavior;

    shared_ptr<HideBehavior> hideBehavior(new HideBehavior(_hideTarget,_obstacles));
    _hideBehavior       = hideBehavior;

    shared_ptr<WanderBehavior> wanderBehavior(new WanderBehavior());
    _wanderBehavior     = wanderBehavior;

    shared_ptr<EvadeBehavior> evadeBehavior(new EvadeBehavior(_evadeTarget));
    _evadeBehavior      = evadeBehavior;

    shared_ptr<PursuitBehavior> pursuitBehavior(new PursuitBehavior(_pursuitTarget));
    _pursuitBehavior    = pursuitBehavior;

    shared_ptr<ObstacleAvoidanceBehavior> obsAvoidBehavior(new ObstacleAvoidanceBehavior(_obstacles));
    _obsAvoidBehavior   = obsAvoidBehavior;


    _seekBehavior->SetMobile(_mob);
    _arriveBehavior->SetMobile(_mob);
    _fleeBehavior->SetMobile(_mob);
    _hideBehavior->SetMobile(_mob);
    _wanderBehavior->SetMobile(_mob);
    _evadeBehavior->SetMobile(_mob);
    _pursuitBehavior->SetMobile(_mob);
    _obsAvoidBehavior->SetMobile(_mob);

}

irr::core::vector3df SimpleSteeringController::Calculate()
{
    irr::core::vector3df steeringForce = vector3df(0,0,0);
    float maxForceSQ = (_mob->MaxForce() * _mob->MaxForce());

    if(_behaviorFlags & EBF_AVOID)
    {
        _obsAvoidBehavior->SetObstacles(_obstacles);
        steeringForce += _obsAvoidBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    if(_behaviorFlags & EBF_HIDE)
    {
        _hideBehavior->SetTarget(_hideTarget);
        _hideBehavior->SetObstacles(_obstacles);
        steeringForce += _hideBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    if(_behaviorFlags & EBF_PURSUIT)
    {
        _pursuitBehavior->SetTarget(_pursuitTarget);
        steeringForce += _pursuitBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    if(_behaviorFlags & EBF_EVADE)
    {
        _evadeBehavior->SetTarget(_evadeTarget);
        steeringForce += _evadeBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    if(_behaviorFlags & EBF_SEEK)
    {
        _seekBehavior->SetTarget(_seekTarget);
        steeringForce += _seekBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    if(_behaviorFlags & EBF_ARRIVE)
    {
        _arriveBehavior->SetTarget(_arriveTarget);
        steeringForce += _arriveBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    if(_behaviorFlags & EBF_WANDER)
    {
        steeringForce += _wanderBehavior->Calculate();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    return steeringForce;
};

void SimpleSteeringController::SetSeekTarget(vector3df target)
{
    _seekTarget = target;
}

void SimpleSteeringController::SetArriveTarget(vector3df target)
{
    _arriveTarget = target;
}

void SimpleSteeringController::SetHideTarget(shared_ptr<entity::IMobileEntity> target)
{
    _hideTarget = target;
}

void SimpleSteeringController::SetPursuitTarget(shared_ptr<entity::IMobileEntity> target)
{
    _pursuitTarget = target;
}

void SimpleSteeringController::SetObstacles(boost::shared_ptr<EntityGroup> obstacles)
{
    _obstacles = obstacles;
}

void SimpleSteeringController::SetBehaviorFlag(EBEHAVIOR_FLAG flag, bool active)
{
    _behaviorFlags = active ? _behaviorFlags | flag :  _behaviorFlags ^ flag;
}
