#ifndef _S_GHOST_HPP_
#define _S_GHOST_HPP_

#include "domain/domain_define.hpp"
#include "domain/structure/structure_define.hpp"
#include "domain/structure/index.hpp"

namespace carpio{

template<St DIM>
class SGhost_ {
public:
    typedef SIndex_<DIM> Index;
    typedef SGrid_<DIM>  Grid;

    SGhost_(){

    }
    virtual ~SGhost_(){
    }
    virtual std::string type() const{
    	return "SGhost";
    }
	virtual St type(const Index& idx) const{//SHOULD_NOT_REACH; return 0;
    }

    virtual Grid& grid() {
        // return Grid();
    }

    virtual const Grid& grid() const {
        // return Grid();
    }

    virtual bool is_ghost(const Index& index) const{
        SHOULD_NOT_REACH; return false;};
    virtual bool is_not_ghost(const Index& index) const{
        SHOULD_NOT_REACH; return false;
    };
    virtual bool is_boundary(
            const Index& index,
            const St&    a,
            const St&    o) const{
                SHOULD_NOT_REACH; return false;
            };
    virtual bool is_cut(
    		const Index& index) const{
                SHOULD_NOT_REACH; return false;
            };
    virtual bool is_normal(const Index& index) const{
        SHOULD_NOT_REACH; return false;
    };


    virtual int boundary_id(const Index& indexc,
                            const Index& indexg,
                            const St&  axe,
                            const St& ori) const{
                                SHOULD_NOT_REACH; return 0;
                            };
    virtual Index boundary_index(const Index& indexc,
                                 const Index& indexg,
                                 const St&    axe,
                                 const St&    ori) const{
                                     SHOULD_NOT_REACH; return 0;
                                 };
    virtual St size_normal() const{
        SHOULD_NOT_REACH; return 0;
    }
    virtual St size_not_ghost() const{
        SHOULD_NOT_REACH; return 0;
    }
};


}



#endif
