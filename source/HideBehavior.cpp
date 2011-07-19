#include "desteer/behavior/HideBehavior.hpp"

using namespace desteer;
using namespace behavior;
using namespace entity;

using namespace irr;
using namespace core;
using boost::shared_ptr;

HideBehavior::HideBehavior(shared_ptr<IMobileEntity> target,EntityGroup & obstacles, float hideDistanceFromObstacle)
{
    _obstacles = obstacles;
    _target = target;

    _hideDistanceFromObj = hideDistanceFromObstacle;
    shared_ptr<EvadeBehavior> evadeBehavior(new EvadeBehavior(shared_ptr<IMobileEntity>()));
    _evadeBehavior = evadeBehavior;
    shared_ptr<ArriveBehavior> arriveBehavior(new ArriveBehavior(vector3df(0,0,0)));
    _arriveBehavior = arriveBehavior;

    _evadeBehavior->SetMobile(_mob);
    _arriveBehavior->SetMobile(_mob);
}

void HideBehavior::SetMobile(shared_ptr<IMobileEntity> mob)
{
    _mob = mob;

    _evadeBehavior->SetMobile(_mob);
    _arriveBehavior->SetMobile(_mob);
}

void HideBehavior::SetTarget(shared_ptr<IMobileEntity> target)
{
    _target = target;
}

void HideBehavior::SetObstacles(EntityGroup &obstacles)
{
    _obstacles = obstacles;
}

vector3df HideBehavior::GetHidingPosition(const vector3df& targetPos,const shared_ptr<IBaseEntity> obstacle)
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
        vector3df HidingSpot = GetHidingPosition(_target->Position(),(*currentObs));
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

