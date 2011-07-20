#ifndef SIMPLESTEERINGCONTROLLERFACTORY_H
#define SIMPLESTEERINGCONTROLLERFACTORY_H
#include <boost/smart_ptr.hpp>
#include "desteer/controller/SimpleSteeringController.hpp"
#include "desteer/entity/IMobileEntity.hpp"

class SimpleSteeringControllerFactory
{
public:
    static boost::shared_ptr<desteer::controller::SimpleSteeringController> CreateController(boost::shared_ptr<desteer::entity::IMobileEntity> mob)
    {
        boost::shared_ptr<desteer::controller::SimpleSteeringController> controller(new desteer::controller::SimpleSteeringController(mob));
        mob->SetSteering(controller);
        return controller;
    }
protected:
private:
};

#endif // SIMPLESTEERINGCONTROLLERFACTORY_H
