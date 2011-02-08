#pragma once
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/behavior/SteeringBehaviors.hpp"

namespace desteer {
namespace entity {

class IrrlichtMobileEntity : public IMobileEntity
{
private:
	irr::scene::ISceneNode* _node;

	behavior::SteeringBehaviors *_steering;
public:
    IrrlichtMobileEntity(){};
    IrrlichtMobileEntity(irr::scene::ISceneNode* node,
                         irr::core::vector3df position = irr::core::vector3df(0,0,0),
                         irr::f32 mass = 1,
                         irr::f32 maxSpeed = 50,
                         irr::f32 maxForce = 50)
                         {
                             _node = node;
                             SetPosition(position);
                             SetMass(mass);
                             SetMaxSpeed(maxSpeed);
                             SetMaxForce(maxForce);
                         };


	inline irr::scene::ISceneNode* Node() { return _node; };
	inline void SetNode(irr::scene::ISceneNode *node) { _node = node; };

    virtual irr::core::vector3df Position() const;
	virtual void SetPosition(irr::core::vector3df position);

	virtual irr::core::aabbox3df BoundingBox() const;
	//an approximation of the radius of the bounding box.
	virtual irr::f32 Radius() const;

	virtual irr::core::vector3df PredictFuturePosition(const float predictionTime) const { return irr::core::vector3df(0,0,0); };

	virtual irr::core::vector3df SideVector() const;
	virtual void SetSideVector(irr::core::vector3df side);

	virtual irr::core::vector3df ForwardVector() const;
	virtual void SetForwardVector(irr::core::vector3df forward);

    virtual irr::core::vector3df transformWorldVectToLocal(irr::core::vector3df vec);
	virtual irr::core::vector3df transformLocalVectToWorld(irr::core::vector3df vec);

    void SetSteering(behavior::SteeringBehaviors *container){ _steering = container;};
	virtual void Update(irr::f32 timeElapsed);
};

}//end namespace entity
}//end namespace desteer
