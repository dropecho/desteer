#include "Irrlicht/Irrlicht.h"
#pragma once

namespace desteer {

class IBaseEntity{
public:
	virtual irr::core::vector3df Position() const = 0;
	virtual void SetPosition(irr::core::vector3df position) = 0;

	virtual irr::core::aabbox3df BoundingBox() const = 0;
	virtual irr::f32 Radius() const = 0;

	virtual void Update(irr::f32 timeElapsed) = 0;
};

}//end namespace desteer
