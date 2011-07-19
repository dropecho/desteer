#pragma once

#include <vector>
#include <iterator>
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/behavior/ISteeringBehavior.hpp"
#include <boost/smart_ptr.hpp>

namespace desteer{

typedef std::vector<boost::shared_ptr<desteer::behavior::ISteeringBehavior> > BehaviorGroup;
typedef BehaviorGroup::const_iterator BehaviorIterator;

typedef std::vector<boost::shared_ptr<desteer::entity::IMobileEntity> > MobGroup;
typedef MobGroup::const_iterator MobIterator;

typedef std::vector<boost::shared_ptr<desteer::entity::IBaseEntity> > EntityGroup;
typedef EntityGroup::const_iterator EntityIterator;

}
