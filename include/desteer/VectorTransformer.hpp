#pragma once
#include "Types.hpp"
#include "irrvector/matrix4.h"

namespace desteer {

class VectorTransformer
{
    public:

    static irr::core::vector3df WorldToLocal(irr::core::vector3df vec, entity::IMobileEntity * _mob)
    {
        return WorldToLocal(vec,_mob->ForwardVector(), _mob->SideVector(), _mob->Position());
    }

    static irr::core::vector3df WorldToLocal(irr::core::vector3df vec,
                                                            irr::core::vector3df forward,
                                                            irr::core::vector3df side,
                                                            irr::core::vector3df pos)
    {
        irr::core::matrix4 mat;
        mat.setRotation(forward,side);
        irr::core::vector3df transformedVec = vec - pos;
        mat.transformVect(transformedVec);
        return transformedVec;
    }

    static irr::core::vector3df LocalToWorld(irr::core::vector3df vec, entity::IMobileEntity * _mob)
    {
        return LocalToWorld(vec,_mob->ForwardVector(), _mob->SideVector(), _mob->Position());
    }

    static irr::core::vector3df LocalToWorld(irr::core::vector3df vec,
                                                            irr::core::vector3df forward,
                                                            irr::core::vector3df side,
                                                            irr::core::vector3df pos)
    {
        irr::core::matrix4 mat;
        mat.setRotation(forward,side);
        mat.makeInverse();
        mat.transformVect(vec);
        return vec + pos;
    }
};

}
