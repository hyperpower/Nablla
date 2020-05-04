#ifndef _DOMAIN_DEFINE_HPP_
#define _DOMAIN_DEFINE_HPP_

#include "type_define.hpp"

namespace carpio{
    
#define FOR_EACH_DIM for(St d=0;d<DIM;++d)

enum CellType{
	_NORMAL_ = 0,
	_GHOST_  = 1,
	_CUT_    = 2
};

}
#endif
