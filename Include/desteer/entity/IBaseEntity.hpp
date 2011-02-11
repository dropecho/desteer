#include "irrlicht/irrlicht.h"
#pragma once

namespace desteer {
namespace entity {

class IBaseEntity{
public:
	virtual irr::core::vector3df Position() const = 0;
	virtual void SetPosition(irr::core::vector3df position) = 0;

	virtual irr::core::aabbox3df BoundingBox() const = 0;
	virtual float Radius() const = 0;

	virtual void Update(float timeElapsed) = 0;
};

}//end namespace entity
}//end namespace desteer
