#include "desteer/behavior/HideBehavior.hpp"

using namespace desteer;
using namespace behavior;
using namespace entity;

using namespace irr;
using namespace core;

HideBehavior::HideBehavior(IMobileEntity* target,EntityGroup & obstacles)
{
    _obstacles = obstacles;
    _target = target;

    _hideDistanceFromObj = 20;
    _evadeBehavior = new EvadeBehavior(NULL);
    _arriveBehavior = new ArriveBehavior(vector3df(0,0,0));
}

void HideBehavior::SetMobile(IMobileEntity * mob)
{
    _mob = mob;
}

void HideBehavior::SetTarget(IMobileEntity * target)
{
    _target = target;
}

vector3df HideBehavior::GetHidingPosition(const IBaseEntity *obstacle, const vector3df& targetPos)
{
    vector3df toHidingSpotNorm = (obstacle->Position() - targetPos).normalize();
    vector3df toHidingSpot = toHidingSpotNorm * (obstacle->Radius() + _hideDistanceFromObj);
    return toHidingSpot + obstacle->Position();
}

vector3df HideBehavior::Calculate()
{
    float distToClosest = 16415876;
    vector3df BestHidingSpot;

    for(EntityIterator currentObs = _obstacles.begin(); currentObs != _obstacles.end(); ++currentObs)
    {
        vector3df HidingSpot = GetHidingPosition((*currentObs),_target->Position());
        float sqDist = (HidingSpot - _mob->Position()).getLengthSQ();

        if(sqDist < distToClosest)
        {
            distToClosest = sqDist;
            BestHidingSpot = HidingSpot;
        }
    }

    if(distToClosest == 16415876)
    {
        _evadeBehavior->SetTarget(_target);
        return _evadeBehavior->Calculate();
    }

    _arriveBehavior->SetTarget(BestHidingSpot);
    return _arriveBehavior->Calculate();
}

