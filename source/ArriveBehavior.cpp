#include "desteer/behavior/ArriveBehavior.hpp"

using namespace desteer;
using namespace behavior;
using namespace irr;
using namespace core;
using namespace entity;

ArriveBehavior::ArriveBehavior(vector3df target,IMobileEntity * mob ,float arriveTolerance, float decceleration)
{
    _target = target;
    _mob = mob;
    _arriveTolerance = arriveTolerance;
    _decceleration = decceleration;
}

vector3df ArriveBehavior::Calculate()
{
    vector3df toTarget = _target - _mob->Position();


    float distanceToTarget = toTarget.getLength();
    float currentSpeed = _mob->Velocity().getLength();

    float timeToStop = currentSpeed / _mob->MaxForce();
    float timeToTarget = distanceToTarget / currentSpeed;

    if(distanceToTarget < _mob->Radius())
    {
        return vector3df(0,0,0) - (_mob->Velocity() * (_mob->Radius() + _arriveTolerance));
    }

    if(timeToStop >= timeToTarget)
    {
        return toTarget + ( toTarget - (_mob->Velocity() / timeToTarget));
    }

    if(distanceToTarget > ROUNDING_ERROR_f32)
    {
        float speed = distanceToTarget / _decceleration;

        speed = min_(speed, _mob->MaxSpeed());

        return (toTarget * (speed/distanceToTarget)) - _mob->Velocity();
    }

    return vector3df(0,0,0);
}

void ArriveBehavior::SetMobile(IMobileEntity * mob)
{
    _mob = mob;
}

void ArriveBehavior::SetTarget(vector3df target)
{
    _target = target;
}
