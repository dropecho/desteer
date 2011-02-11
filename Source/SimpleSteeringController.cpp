#include "desteer/controller/SimpleSteeringController.hpp"
#include "desteer/Types.hpp"

using namespace irr;
using namespace core;
using namespace desteer;
using namespace controller;
using namespace entity;

SimpleSteeringController::SimpleSteeringController(IMobileEntity* mob)
{
    _mob = mob;

/*    _isSeeking = false;
    _isFleeing = false;
    _isWandering = false;
    _isPursuing = false;
    _isEvading = false;
    _isAvoidingObstacles = false;
    _isArriving = false;*/
}

irr::core::vector3df SimpleSteeringController::Calculate()
{
    irr::core::vector3df steeringForce = vector3df(0,0,0);
    float maxForceSQ = (_mob->MaxForce() * _mob->MaxForce());

    return steeringForce;
};

