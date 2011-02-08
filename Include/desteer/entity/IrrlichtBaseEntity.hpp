#include "desteer/entity/IBaseEntity.hpp"
#include "Irrlicht/Irrlicht.h"

namespace desteer{
namespace entity {

class IrrlichtBaseEntity : public IBaseEntity
{
private:
    irr::scene::ISceneNode *_node;

public :
    IrrlichtBaseEntity(irr::scene::ISceneNode * node) {_node = node;}

    virtual irr::scene::ISceneNode* Node() const {return _node;}

	virtual irr::core::vector3df Position() const {return _node->getPosition();};
	virtual void SetPosition(irr::core::vector3df position) {_node->setPosition(position);};

	virtual irr::core::aabbox3df BoundingBox() const {return _node->getBoundingBox();};
	virtual irr::f32 Radius() const {return (_node->getBoundingBox().getExtent().getLength() / 2);};

	virtual void Update(irr::f32 timeElapsed) {return;};
};

}//end namespace entity
}//end namespace desteer
