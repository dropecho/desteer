#pragma once
#include "ISteeringBehavior.hpp"
#include "desteer/Types.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace behavior{

class ObstacleAvoidanceBehavior : public ISteeringBehavior
{
private:
    boost::shared_ptr<entity::IMobileEntity> _mob;

    EntityGroup _obstacles;

public:
    ObstacleAvoidanceBehavior(EntityGroup & obstacles);
    irr::core::vector3df Calculate();
    void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);
    void SetObstacles(EntityGroup &obstacles);
    virtual ~ObstacleAvoidanceBehavior(){}
};

} //end ns behavior
} //end ns desteer
