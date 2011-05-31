#include "SimpleSteeringController.hpp"

class FluentSimpleController : private SimpleSteeringController
{
public:
    FluentSimpleController();
    FluentSimpleController(entity::IMobileEntity *vehicle);
    irr::core::vector3df Calculate();

    FluentSimpleController & WithSeek(){
        SetBehaviorFlag(EBF_SEEK,true);
        return this;
    };
    FluentSimpleController & WithSeek(irr::core::vector3df target){
        SetSeekTarget(target);
        return this.WithSeek();
    };
    FluentSimpleController & WithArrive(){
        SetBehaviorFlag(EBF_ARRIVE,true);
        return this;
    };
    FluentSimpleController & WithArrive(irr::core::vector3df target){
        SetArriveTarget(target);
        return this.WithArrive();
    };
}
