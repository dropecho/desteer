#pragma once
#include "desteer/controller/ISteeringController.hpp"

namespace desteer{
namespace controller{

/*
enum EBEHAVIOR_FLAG
{
    EBF_ARRIVE  = 0x01,
    EBF_EVADE   = 0x02,
    EBF_FLEE    = 0x04,
    EBF_HIDE    = 0x08,
    EBF_SEEK    = 0x10,
    EBF_PURSUIT = 0x20,
    EBF_WANDER  = 0x40,
    EBF_AVOID   = 0x80
}
*/
class SimpleSteeringController : public ISteeringController
{
    private:
        entity::IMobileEntity *         _mob;

        int behaviorFlags;

  /*      ArriveBehavior  * _arriveBehavior;
        EvadeBehavior   * _evadeBehavior;
        FleeBehavior    * _fleeBehavior;
        HideBehavior    * _hideBehavior;
        SeekBehavior    * _seekBehavior;
        PursuitBehavior * _pursuitBehavior;
        WanderBehavior  * _wanderBehavior;
        ObstacleAvoidanceBehavior * _obsAvoidBehavior;
*/

    public:
        SimpleSteeringController(entity::IMobileEntity *vehicle);
        irr::core::vector3df Calculate();

//        void SetBehaviorFlag(EBEHAVIOR_FLAG flag, bool active);


    };

}//end ns controller
}//end ns desteer
