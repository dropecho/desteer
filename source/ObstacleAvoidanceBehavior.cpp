#include "desteer/behavior/ObstacleAvoidanceBehavior.hpp"

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
    float detectLength = 40 + (_mob->Velocity().getLength()/1.5); //_mob->MaxSpeed() / 5

    for(EntityIterator currentObs = _obstacles.begin(); currentObs != _obstacles.end(); ++currentObs)
    {
        localPos = _mob->transformWorldVectToLocal((*currentObs)->Position());
        float curRadius = (*currentObs)->Radius();

        bool inFront = localPos.Z >= 0;
        bool near = localPos.Z < detectLength;

        if(inFront && near)
        {
            bool intersecting = (fabs(localPos.X) - (curRadius * .75) < _mob->Radius());
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

        float multiplier = 1.0 + ( detectLength - localPos.Z ) / detectLength;
        float distToEdge = ( closestHitObstacle->Radius() - localPos.Z );
        //steeringForce.X = distToEdge * multiplier;
        //steeringForce.Z = distToEdge * .02;

        steeringForce.X = (localPos.X - _mob->Radius()) + _mob->Radius();
        steeringForce.Z = distToEdge;
        return _mob->transformLocalVectToWorld(steeringForce);
    }
    return vector3df(0,0,0);
}
