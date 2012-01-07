#include "desteer/behavior/ObstacleAvoidanceBehavior.hpp"
#include "desteer/VectorTransformer.hpp"
#include <cstdio>
using namespace desteer;
using namespace behavior;
using namespace entity;

using namespace irr;
using namespace core;

ObstacleAvoidanceBehavior::ObstacleAvoidanceBehavior(EntityGroup & obstacles)
{
    _obstacles = obstacles;
}

void ObstacleAvoidanceBehavior::SetMobile(IMobileEntity * mob)
{
    _mob = mob;
}

void ObstacleAvoidanceBehavior::SetObstacles(EntityGroup &obstacles)
{
    _obstacles = obstacles;
}

vector3df ObstacleAvoidanceBehavior::Calculate()
{
    IBaseEntity* closestHitObstacle = NULL;
    vector3df localPos = vector3df(0,0,0);
    float distToClosest = 16487654;
    float currentSpeed = _mob->Velocity().getLength();
    float detectLength = currentSpeed; //* (_mob->MaxForce() / currentSpeed);
    for(ConstEntityIterator currentObs = _obstacles.begin(); currentObs != _obstacles.end(); ++currentObs)
    {
        localPos = VectorTransformer::WorldToLocal((*currentObs)->Position(), _mob);
        float curRadius = (*currentObs)->Radius();

        bool inFront = localPos.X >= 0;
        bool near = (localPos.X - curRadius) < detectLength;

        if(inFront && near)
        {
            bool intersecting = (fabs(localPos.Z) - (curRadius) < _mob->Radius());
            if(intersecting)
            {
                if(localPos.getLength() < distToClosest)
                {
                    closestHitObstacle = (*currentObs);
                    distToClosest = localPos.getLength();
                }
            }
        }
    }

    if(closestHitObstacle)
    {
        localPos = VectorTransformer::WorldToLocal(closestHitObstacle->Position(),_mob);
        vector3df steeringForce = vector3df(0,0,0);
        float maxForce = _mob->MaxForce();
        steeringForce.Z = localPos.Z >= 0 ? -maxForce : maxForce;
        //steeringForce.X = -maxForce + (-maxForce * 1/distToClosest);
        return VectorTransformer::LocalToWorld(steeringForce,_mob);
    }
    return vector3df(0,0,0);
}
