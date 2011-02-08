#include "Irrlicht/Irrlicht.h"
#include "desteer/entity/IBaseEntity.hpp"
#include "desteer/entity/IEntitySpace.hpp"
#pragma once

namespace desteer {
namespace entity {

class IMobileEntity : public IBaseEntity, public IEntitySpace
{
protected:
	float _mass;
	float _maxForce;
	float _maxSpeed;
	float _maxTurnRate;

	irr::core::vector3df _velocity;

public:
	inline float Mass() const { return _mass; };
	inline void SetMass(float mass) { _mass = mass; };

	inline float MaxForce() const { return _maxForce; };
	inline void SetMaxForce(float maxForce) { _maxForce = maxForce; };

	inline float MaxSpeed() const { return _maxSpeed; };
	inline void SetMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; };

	inline float MaxTurnRate() const { return _maxTurnRate; };
	inline void SetMaxTurnRate(float maxTurnRate) { _maxTurnRate = maxTurnRate; };

    virtual irr::core::vector3df Velocity() const {return _velocity;};
};

}//end namespace entity
}//end namespace desteer

