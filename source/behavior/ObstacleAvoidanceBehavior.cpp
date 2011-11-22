#include "desteer/behavior/ObstacleAvoidanceBehavior.hpp"

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
    float detectLength = _mob->Velocity().getLength();
    for(ConstEntityIterator currentObs = _obstacles.begin(); currentObs != _obstacles.end(); ++currentObs)
    {
        localPos = _mob->transformWorldVectToLocal((*currentObs)->Position());
        float curRadius = (*currentObs)->Radius();

        bool inFront = localPos.Z >= 0;
        bool near = (localPos.Z - curRadius) < detectLength;

        if(inFront && near)
        {
            bool intersecting = (fabs(localPos.X) - (curRadius) < _mob->Radius());
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
        localPos = _mob->transformWorldVectToLocal(closestHitObstacle->Position());
        vector3df steeringForce = vector3df(0,0,0);

        f32 maxForce = _mob->MaxForce();
        steeringForce.X = localPos.X >= 0 ? -maxForce * 9000 : maxForce * 9000;
        steeringForce.Z = -maxForce + (-maxForce * 1/distToClosest);
        return _mob->transformLocalVectToWorld(steeringForce);
    }
    return vector3df(0,0,0);
}
