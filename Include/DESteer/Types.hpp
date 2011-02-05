#include <vector>
#include <iterator>

namespace desteer{

typedef std::vector<IMobileEntity*> MobGroup;
typedef MobGroup::const_iterator MobIterator;

typedef std::vector<IBaseEntity*> EntityGroup;
typedef EntityGroup::const_iterator EntityIterator;

}
