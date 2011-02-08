#include "DESteer/behavior/SteeringBehaviors.hpp"
#include "DESteer/Types.hpp"

using namespace irr;
using namespace core;
using namespace desteer;
using namespace behavior;
using namespace entity;

SteeringBehaviors::SteeringBehaviors(IMobileEntity* mob)
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

irr::core::vector3df SteeringBehaviors::Calculate()
{
    irr::core::vector3df steeringForce = vector3df(0,0,0);
    irr::f32 maxForceSQ = (_mob->MaxForce() * _mob->MaxForce());

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

vector3df SteeringBehaviors::Seek(const vector3df& target)
{
    vector3df desiredVelocity = (target - _mob->Position()).normalize() * _mob->MaxSpeed();
    return (desiredVelocity - _mob->Velocity());
}

vector3df SteeringBehaviors::Flee(const vector3df& target)
{
    if(target.getDistanceFromSQ(_mob->Position()) < _fleeDistance * _fleeDistance)
    {
        vector3df desiredVelocity = ( _mob->Position() - target).normalize() * _mob->MaxSpeed();
        return (desiredVelocity - _mob->Velocity());
    }
    return vector3df(0,0,0);
}

vector3df SteeringBehaviors::Wander()
{
    f32 wanderRadius = 30;
    f32 wanderDistance = 30;
    f32 wanderJitter = 10 * RandomClamped();

    _wanderTarget += vector3df(RandomClamped() * wanderJitter,0,RandomClamped() * wanderJitter);
    (_wanderTarget.normalize()) *= wanderRadius;

    realWanderTarget = _mob->transformLocalVectToWorld(_wanderTarget + vector3df(0,0,wanderDistance));;
    return realWanderTarget - _mob->Position();
}

vector3df SteeringBehaviors::Arrive(const vector3df& targetPos)
{
    vector3df target = targetPos - _mob->Position();

    f32 distanceToTarget = target.getLength();

    if(distanceToTarget < _arriveTolerance)
    {
        return (vector3df(0,0,0) - (_mob->Velocity() * _mob->MaxForce()));
    }

    if(distanceToTarget > ROUNDING_ERROR_f32 )
    {
        //.6 is medium decelleration
        f32 speed = distanceToTarget / .9;

        //truncate speed to max
        speed = min_(speed, _mob->MaxSpeed());

        return (target * (speed/distanceToTarget)) - _mob->Velocity();
    }

    return vector3df(0,0,0);
}

vector3df SteeringBehaviors::Pursue(const IMobileEntity * target)
{
    vector3df toTarget = target->Position() - _mob->Position();
    irr::f32 heading = _mob->ForwardVector().dotProduct(target->ForwardVector());

    //if target forward and mob forward are within 18 degs, just seek.
    if((toTarget.dotProduct( _mob->ForwardVector()) > 0) && (heading < 0.95)) //acos(0.95) = 18 degs
    {
        return Seek(target->Position());
    }

    f32 lookAheadTime = toTarget.getLengthSQ() / ( _mob->MaxSpeed() + target->Velocity().getLengthSQ() );

    return Seek( target->Position() + (target->Velocity() * lookAheadTime));
}

vector3df SteeringBehaviors::Evade(const IMobileEntity * target)
{
    vector3df toTarget = target->Position() - _mob->Position();

    f32 lookAheadTime = toTarget.getLength() / ( _mob->MaxSpeed() + target->Velocity().getLength() );
    return Flee(target->Position() + (target->Velocity() * lookAheadTime));
}

vector3df SteeringBehaviors::AvoidObstacles(const EntityGroup &obstacles)
{
    IBaseEntity* closestHitObstacle = NULL;
    vector3df localPos = vector3df(0,0,0);
    f32 distToClosest = 16487654;
    f32 detectLength = 40 + (_mob->Velocity().getLength()/1.5); //_mob->MaxSpeed() / 5

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

        f32 multiplier = 1.0 + ( detectLength - localPos.Z ) / detectLength;
        f32 distToEdge = ( closestHitObstacle->Radius() - localPos.Z );
        steeringForce.X = distToEdge * multiplier;
        steeringForce.Z = distToEdge * .02;

        return _mob->transformLocalVectToWorld(steeringForce);
    }
    return vector3df(0,0,0);
}


vector3df SteeringBehaviors::GetHidingPosition(const IBaseEntity *obstacle, const vector3df& targetPos)
{
    vector3df toHidingSpotNorm = (obstacle->Position() - targetPos).normalize();
    vector3df toHidingSpot = toHidingSpotNorm * (obstacle->Radius() + _hideDistanceFromObj);
    return toHidingSpot + obstacle->Position();
}

vector3df SteeringBehaviors::Hide(const IMobileEntity* target, const EntityGroup &obstacles)
{
    f32 distToClosest = 16415876;
    vector3df BestHidingSpot;

    for(EntityIterator currentObs = obstacles.begin(); currentObs != obstacles.end(); ++currentObs)
    {
        vector3df HidingSpot = GetHidingPosition((*currentObs),target->Position());
        f32 sqDist = (HidingSpot - _mob->Position()).getLengthSQ();

        if(sqDist < distToClosest)
        {
            distToClosest = sqDist;
            BestHidingSpot = HidingSpot;
        }
    }

    return distToClosest == 16415876 ? Evade(target) : Arrive(BestHidingSpot);
}
