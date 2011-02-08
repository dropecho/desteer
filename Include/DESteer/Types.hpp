#include <vector>
#include <iterator>

namespace desteer{

typedef std::vector<entity::IMobileEntity*> MobGroup;
typedef MobGroup::const_iterator MobIterator;

typedef std::vector<entity::IBaseEntity*> EntityGroup;
typedef EntityGroup::const_iterator EntityIterator;

}
