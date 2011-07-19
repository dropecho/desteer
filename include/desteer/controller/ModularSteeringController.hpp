#pragma once
#include "ISteeringController.hpp"
#include "desteer/Types.hpp"
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/behavior/ISteeringBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{
namespace controller{

/*!
    This is a concrete implementation of a modular steering controller.
    It takes in steering behaviors at runtime, and will sum/accumulate the steering forces from those.
*/
class ModularSteeringController : ISteeringController
{
private:
    boost::shared_ptr<entity::IMobileEntity> _mob;
    BehaviorGroup _behaviors;

public:
    /*!
        @\param mob The entity is controller is supplying with a calculated steering force.
    */
    ModularSteeringController(boost::shared_ptr<entity::IMobileEntity> mob);
    irr::core::vector3df Calculate();

    void AddBehavior(boost::shared_ptr<behavior::ISteeringBehavior> behavior);

};

} //end ns controller
} //end ns desteer
