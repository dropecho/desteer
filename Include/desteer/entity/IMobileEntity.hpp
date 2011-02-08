#include "Irrlicht/Irrlicht.h"
#include "desteer/entity/IBaseEntity.hpp"
#include "desteer/entity/IEntitySpace.hpp"
#pragma once

namespace desteer {
namespace entity {

class IMobileEntity : public IBaseEntity, public IEntitySpace
{
protected:
	irr::f32 _mass;
	irr::f32 _maxForce;
	irr::f32 _maxSpeed;
	irr::f32 _maxTurnRate;

	irr::core::vector3df _velocity;

public:
	inline irr::f32 Mass() const { return _mass; };
	inline void SetMass(irr::f32 mass) { _mass = mass; };

	inline irr::f32 MaxForce() const { return _maxForce; };
	inline void SetMaxForce(irr::f32 maxForce) { _maxForce = maxForce; };

	inline irr::f32 MaxSpeed() const { return _maxSpeed; };
	inline void SetMaxSpeed(irr::f32 maxSpeed) { _maxSpeed = maxSpeed; };

	inline irr::f32 MaxTurnRate() const { return _maxTurnRate; };
	inline void SetMaxTurnRate(irr::f32 maxTurnRate) { _maxTurnRate = maxTurnRate; };

    virtual irr::core::vector3df Velocity() const {return _velocity;};
};

}//end namespace entity
}//end namespace desteer

