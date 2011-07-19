#include "desteer/behavior/PursuitBehavior.hpp"

using namespace desteer;
using namespace behavior;
using namespace entity;

using namespace irr;
using namespace core;
using boost::shared_ptr;


PursuitBehavior::PursuitBehavior(shared_ptr<IMobileEntity> target)
{
    _target = target;
    shared_ptr<SeekBehavior> seekBehavior(new SeekBehavior(vector3df(0,0,0)));
    _seekBehavior = seekBehavior;
}

vector3df PursuitBehavior::Calculate()
{
    vector3df toTarget = _target->Position() - _mob->Position();
    float heading = _mob->ForwardVector().dotProduct(_target->ForwardVector());

    //if target forward and mob forward are within 18 degs, just seek.
    if((toTarget.dotProduct( _mob->ForwardVector()) > 0) && (heading < 0.95)) //acos(0.95) = 18 degs
    {
        _seekBehavior->SetTarget(_target->Position());
        return _seekBehavior->Calculate();
    }

    float lookAheadTime = toTarget.getLengthSQ() / ( _mob->MaxSpeed() +_target->Velocity().getLengthSQ() );

    _seekBehavior->SetTarget( _target->Position() + (_target->Velocity() * lookAheadTime));
    return _seekBehavior->Calculate();
}

void PursuitBehavior::SetMobile(shared_ptr<entity::IMobileEntity> mob)
{
    _mob = mob;

    _seekBehavior->SetMobile(_mob);
}

void PursuitBehavior::SetTarget(shared_ptr<entity::IMobileEntity> target)
{
    _target = target;
}
