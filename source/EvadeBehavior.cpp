#include "desteer/behavior/EvadeBehavior.hpp"

using namespace desteer;
using namespace behavior;
using namespace entity;

using namespace irr;
using namespace core;
using boost::shared_ptr;

EvadeBehavior::EvadeBehavior(shared_ptr<IMobileEntity> target)
{
    _target = target;
    shared_ptr<FleeBehavior> fleeBehavior(new FleeBehavior(vector3df(0,0,0)));
    _fleeBehavior = fleeBehavior;
}

vector3df EvadeBehavior::Calculate()
{
    vector3df toTarget = _target->Position() - _mob->Position();

    float lookAheadTime = toTarget.getLength() / ( _mob->MaxSpeed() + _target->Velocity().getLength() );

    _fleeBehavior->SetTarget(_target->Position() + (_target->Velocity() * lookAheadTime));
    return _fleeBehavior->Calculate();
}

void EvadeBehavior::SetMobile(shared_ptr<entity::IMobileEntity> mob)
{
    _mob = mob;
}

void EvadeBehavior::SetTarget(shared_ptr<IMobileEntity> target)
{
    _target = target;
}
