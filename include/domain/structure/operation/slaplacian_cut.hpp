#ifndef _S_LAPLACIANCUT_HPP
#define _S_LAPLACIANCUT_HPP

#include "slaplacian.hpp"


namespace carpio{

template<St DIM, class FIELD, class GRID, class ORDER>
struct SLaplacianFieldOperation_<DIM, FIELD, GRID, SGhostRegularSubdivision_<DIM> ,ORDER>{
    typedef FIELD Field;
    typedef BoundaryIndex BI;
public:
    void operator()(Field& res, const Field& f, const Vt& t, const BI&) const{
        std::cout << "Ghost Regular Subdivision1" << std::endl;
    };
    ~SLaplacianFieldOperation_(){};
};

}


#endif