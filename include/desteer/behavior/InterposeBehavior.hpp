#include "ISteeringBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{ namespace behavior{

class InterposeBehavior : ISteeringBehavior
{
private:
    boost::shared_ptr<entity::IMobileEntity> _vehicle1;
    boost::shared_ptr<entity::IMobileEntity> _vehicle2;

    boost::shared_ptr<entity::IMobileEntity> _mob;
public:
    InterposeBehavior(boost::shared_ptr<entity::IMobileEntity> mob, boost::shared_ptr<entity::IMobileEntity> vehicle1, entity::IMobileEntity *vehicle2)
    : _vehicle1(vehicle1), _vehicle2(vehicle2), _mob(mob){}

    virtual irr::core::vector3df Calculate();
    virtual void SetMobile(boost::shared_ptr<entity::IMobileEntity> mob);

};

}   //end namespace behavior
}   //end namespace desteer
