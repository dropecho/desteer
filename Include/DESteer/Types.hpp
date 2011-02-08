#pragma once
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/behavior/ISteeringBehavior.hpp"
#include <vector>
#include <iterator>

namespace desteer{

typedef std::vector<behavior::ISteeringBehavior *> BehaviorGroup;
typedef std::vector<behavior::ISteeringBehavior *>::const_iterator BehaviorIterator;

typedef std::vector<entity::IMobileEntity*> MobGroup;
typedef MobGroup::const_iterator MobIterator;

typedef std::vector<entity::IBaseEntity*> EntityGroup;
typedef EntityGroup::const_iterator EntityIterator;

}
