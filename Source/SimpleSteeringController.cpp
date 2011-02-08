#include "DESteer/controller/SimpleSteeringController.hpp"
#include "DESteer/Types.hpp"

using namespace irr;
using namespace core;
using namespace desteer;
using namespace controller;
using namespace entity;

SimpleSteeringController::SimpleSteeringController(IMobileEntity* mob)
{
    _mob = mob;
    _seekTarget     = irr::core::vector3df(0,0,0);
    _arriveTarget   = irr::core::vector3df(0,0,0);
    _wanderTarget   = irr::core::vector3df(0,0,0);
    _fleeTarget     = irr::core::vector3df(0,0,0);

    _isSeeking = false;
    _isFleeing = false;
    _isWandering = false;
    _isPursuing = false;
    _isEvading = false;
    _isAvoidingObstacles = false;
    _isArriving = false;
    _fleeDistance = 128;
    _hideDistanceFromObj = 20;
}

irr::core::vector3df SimpleSteeringController::Calculate()
{
    irr::core::vector3df steeringForce = vector3df(0,0,0);
    float maxForceSQ = (_mob->MaxForce() * _mob->MaxForce());

    if(_isAvoidingObstacles)
    {
        steeringForce += AvoidObstacles(_obstacles);

        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isHiding)
    {
        steeringForce += Hide(_hideTarget,_obstacles);
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isSeeking)
    {
        steeringForce += Seek(_seekTarget);
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isArriving)
    {
        steeringForce += Arrive(_arriveTarget);
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isFleeing)
    {
        steeringForce += Flee(_fleeTarget);
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isPursuing)
    {
        steeringForce += Pursue(_pursuitTarget);
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isEvading)
    {
        steeringForce += Evade(_evadeTarget);
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }
    if(_isWandering)
    {
        steeringForce += Wander();
        if(steeringForce.getLengthSQ() > maxForceSQ)
        {
            steeringForce.setLength(_mob->MaxForce());
            return steeringForce;
        }
    }

    return steeringForce;
};

f64 RandomClamped()
{
    return ((rand()%10000) - 5000) * .0001;
}

vector3df SimpleSteeringController::Seek(const vector3df& target)
{

}

vector3df SimpleSteeringController::Flee(const vector3df& target)
{

}

vector3df SimpleSteeringController::Wander()
{
    //_wanderJitter *= RandomClamped();

    _wanderTarget += vector3df(RandomClamped() * _wanderJitter,0,RandomClamped() * _wanderJitter);
    (_wanderTarget.normalize()) *= _wanderRadius;

    return _mob->transformLocalVectToWorld(_wanderTarget + vector3df(0,0,_wanderDistance)) - _mob->Position();
}

vector3df SimpleSteeringController::Arrive(const vector3df& targetPos)
{
    vector3df target = targetPos - _mob->Position();

    float distanceToTarget = target.getLength();

    if(distanceToTarget < _arriveTolerance)
    {
        return (vector3df(0,0,0) - (_mob->Velocity() * _mob->MaxForce()));
    }

    if(distanceToTarget > ROUNDING_ERROR_f32 )
    {
        //.6 is medium decelleration
        float speed = distanceToTarget / .9;

        //truncate speed to max
        speed = min_(speed, _mob->MaxSpeed());

        return (target * (speed/distanceToTarget)) - _mob->Velocity();
    }

    return vector3df(0,0,0);
}

vector3df SimpleSteeringController::Pursue(const IMobileEntity * target)
{
    vector3df toTarget = target->Position() - _mob->Position();
    float heading = _mob->ForwardVector().dotProduct(target->ForwardVector());

    //if target forward and mob forward are within 18 degs, just seek.
    if((toTarget.dotProduct( _mob->ForwardVector()) > 0) && (heading < 0.95)) //acos(0.95) = 18 degs
    {
        return Seek(target->Position());
    }

    float lookAheadTime = toTarget.getLengthSQ() / ( _mob->MaxSpeed() + target->Velocity().getLengthSQ() );

    return Seek( target->Position() + (target->Velocity() * lookAheadTime));
}

vector3df SimpleSteeringController::Evade(const IMobileEntity * target)
{
    vector3df toTarget = target->Position() - _mob->Position();

    float lookAheadTime = toTarget.getLength() / ( _mob->MaxSpeed() + target->Velocity().getLength() );
    return Flee(target->Position() + (target->Velocity() * lookAheadTime));
}

vector3df SimpleSteeringController::AvoidObstacles(const EntityGroup &obstacles)
{
    IBaseEntity* closestHitObstacle = NULL;
    vector3df localPos = vector3df(0,0,0);
    float distToClosest = 16487654;
    float detectLength = 40 + (_mob->Velocity().getLength()/1.5); //_mob->MaxSpeed() / 5

    for(EntityIterator currentObs = obstacles.begin(); currentObs != obstacles.end(); ++currentObs)
    {
        localPos = _mob->transformWorldVectToLocal((*currentObs)->Position());

        bool inFront = localPos.Z >= 0;
        bool nearby = localPos.Z < detectLength;

        if(inFront && nearby)
        {
            bool intersecting = (fabs(localPos.X) - ((*currentObs)->Radius() * .75) < _mob->Radius());
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
        vector3df steeringForce = vector3df(0,0,0);

        float multiplier = 1.0 + ( detectLength - localPos.Z ) / detectLength;
        float distToEdge = ( closestHitObstacle->Radius() - localPos.Z );
        steeringForce.X = distToEdge * multiplier;
        steeringForce.Z = distToEdge * .02;

        return _mob->transformLocalVectToWorld(steeringForce);
    }
    return vector3df(0,0,0);
}

vector3df SimpleSteeringController::GetHidingPosition(const IBaseEntity *obstacle, const vector3df& targetPos)
{
    vector3df toHidingSpotNorm = (obstacle->Position() - targetPos).normalize();
    vector3df toHidingSpot = toHidingSpotNorm * (obstacle->Radius() + _hideDistanceFromObj);
    return toHidingSpot + obstacle->Position();
}

vector3df SimpleSteeringController::Hide(const IMobileEntity* target, const EntityGroup &obstacles)
{
    float distToClosest = 16415876;
    vector3df BestHidingSpot;

    for(EntityIterator currentObs = obstacles.begin(); currentObs != obstacles.end(); ++currentObs)
    {
        vector3df HidingSpot = GetHidingPosition((*currentObs),target->Position());
        float sqDist = (HidingSpot - _mob->Position()).getLengthSQ();

        if(sqDist < distToClosest)
        {
            distToClosest = sqDist;
            BestHidingSpot = HidingSpot;
        }
    }

    return distToClosest == 16415876 ? Evade(target) : Arrive(BestHidingSpot);
}
