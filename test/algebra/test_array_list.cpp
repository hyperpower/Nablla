#include "gtest/gtest.h"
#include <iostream>

#include "algebra/array/array_list.hpp"

using namespace carpio;


template<class ARR>
inline void _ShowFirstElements(const ARR& arr, int n){
    ASSERT(n < arr.size());
    for(int i = 0; i< n; i++){
        std::cout << arr[i] << ", ";  
    }
}
template<class ARR>
inline void _ShowLastElements(const ARR& arr, int n){
    ASSERT(n < arr.size());
    auto size = arr.size();
    for(int i = size - n; i< size; i++){
        std::cout << arr[i];  
        if(i < size - 1){
            std::cout << ", ";
        }
    }
}

template<class ARR>
inline void _ShowArrayInShort(const ARR& arr, int n){
    _ShowFirstElements(arr, 3);
    std::cout << "... ";
    _ShowLastElements(arr, 3);
    std::cout << std::endl;
}

TEST(algebra, assgin){
    std::cout << "TEST algebra: arraylist assgin" << std::endl;
    ArrayListV_<double> arr(10);
    arr.assign(1.0);
    for(auto& v : arr){
        EXPECT_TRUE(v == 1.0);
    }
    std::cout << "arr  = ";
    _ShowArrayInShort(arr, 3);
}

TEST(algebra, add){
    std::cout << "TEST algebra: arraylist add" << std::endl;
    ArrayListV_<double> arr(10);
    arr.assign(1.0);
    std::cout << "arr.size = " << arr.size() << std::endl;
    std::cout << "arr  = ";
    _ShowArrayInShort(arr, 3);
    ArrayListV_<double> arr2(10);
    arr2.assign(2.0);
    std::cout << "arr2 = ";
    _ShowArrayInShort(arr2, 3);
    auto res = arr + arr2;
    std::cout << "res  = arr + arr2" << std::endl;
    std::cout << "res  = ";
    _ShowArrayInShort(res, 3);
    EXPECT_EQ(res[0], 3);
}