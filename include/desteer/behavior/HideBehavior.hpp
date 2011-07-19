#pragma once
#include "ISteeringBehavior.hpp"
#include "desteer/Types.hpp"
#include "desteer/behavior/EvadeBehavior.hpp"
#include "desteer/behavior/ArriveBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace behavior{

class HideBehavior : public ISteeringBehavior
{
private:
    boost::shared_ptr<entity::IMobileEntity> _mob;
    boost::shared_ptr<entity::IMobileEntity> _target;

    float _hideDistanceFromObj;

    EntityGroup _obstacles;

    boost::shared_ptr<EvadeBehavior>  _evadeBehavior;
    boost::shared_ptr<ArriveBehavior> _arriveBehavior;

    irr::core::vector3df GetHidingPosition(const irr::core::vector3df& targetPos, const boost::shared_ptr<entity::IBaseEntity> obstacle);
public:
    HideBehavior(boost::shared_ptr<entity::IMobileEntity> target, EntityGroup & obstacles, float hideDistanceFromObstacle = 20);
    irr::core::vector3df Calculate();
    void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
    void SetTarget(boost::shared_ptr<entity::IMobileEntity> target);
    void SetObstacles(EntityGroup &obstacles);
};

} //end ns behavior
} //end ns desteer

