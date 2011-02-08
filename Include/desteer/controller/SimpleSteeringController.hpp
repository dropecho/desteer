#pragma once
#include "desteer/controller/ISteeringController.hpp"

namespace desteer{
namespace controller{

class SimpleSteeringController : public ISteeringController
{
    private:

        irr::core::vector3df    _seekTarget;
        irr::core::vector3df    _arriveTarget;
        irr::core::vector3df    _fleeTarget;
        irr::core::vector3df    _wanderTarget;
        entity::IMobileEntity *         _hideTarget;
        entity::IMobileEntity *         _pursuitTarget;
        entity::IMobileEntity *         _evadeTarget;
        EntityGroup             _obstacles;

        //Vehicle Controlled by these steering behaviors.
        entity::IMobileEntity *         _mob;

        //Tweaking values
        float _fleeDistance;
        float _arriveTolerance;
        float _hideDistanceFromObj;

        float _wanderRadius;
        float _wanderDistance;
        float _wanderJitter;

        irr::core::vector3df Seek(const irr::core::vector3df& target);
        irr::core::vector3df Flee(const irr::core::vector3df& target);
        irr::core::vector3df Arrive(const irr::core::vector3df& target);
        irr::core::vector3df Wander();
        irr::core::vector3df Pursue(const entity::IMobileEntity * target);
        irr::core::vector3df Evade(const entity::IMobileEntity * target);
        irr::core::vector3df AvoidObstacles(const EntityGroup &obstacles);
        irr::core::vector3df GetHidingPosition(const entity::IBaseEntity *obstacle, const irr::core::vector3df& targetPos);
        irr::core::vector3df Hide(const entity::IMobileEntity* target, const EntityGroup &obstacles);

        bool _isSeeking;
        bool _isFleeing;
        bool _isWandering;
        bool _isPursuing;
        bool _isEvading;
        bool _isArriving;
        bool _isAvoidingObstacles;
        bool _isHiding;

    public:
        SimpleSteeringController(entity::IMobileEntity *vehicle);
        irr::core::vector3df Calculate();

        void ToggleSeek()   { _isSeeking    = !_isSeeking; }
        void ToggleArrive() { _isArriving   = !_isArriving; }
        void ToggleFlee()   { _isFleeing    = !_isFleeing; }
        void ToggleWander() { _isWandering  = !_isWandering; }
        void TogglePersue() { _isPursuing   = !_isPursuing; }
        void ToggleEvade()  { _isEvading    = !_isEvading; }
        void ToggleAvoidObstacles() { _isAvoidingObstacles = !_isAvoidingObstacles; }

        void SeekOn(irr::core::vector3df target)    { _seekTarget      = target; _isSeeking    = true;}
        void ArriveOn(irr::core::vector3df target)  { _arriveTarget    = target; _isArriving   = true;}
        void PursuitOn(entity::IMobileEntity* target)       { _pursuitTarget   = target; _isPursuing   = true;}
        void EvadeOn(entity::IMobileEntity* target)         { _evadeTarget     = target; _isEvading    = true;}
        void HideOn(entity::IMobileEntity* target)          { _hideTarget      = target; _isHiding     = true;}
        void AvoidObstaclesOn(EntityGroup &obstacles) { _obstacles = obstacles;  _isAvoidingObstacles = true;}

        void SetObstacles(EntityGroup &obstacles) {_obstacles = obstacles;}

        //Tweaking Values
        void SetArriveTolerance(float tolerance)         { _arriveTolerance      = tolerance; }
        void SetFleeDistance(float distance)             { _fleeDistance         = distance; }
        void SetHideDistanceFromObject(float distance)   {_hideDistanceFromObj   = distance;}
    };

}//end ns controller
}//end ns desteer
