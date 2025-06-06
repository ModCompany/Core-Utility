#pragma once

#include <string>
#include <string>
#include <vector>


// std::__ndk1::string
using stl_string = std::__ndk1::basic_string<char>;

// std::__ndk1::vector
template<typename _Tp>
using stl_vector = std::__ndk1::vector<_Tp>; 

inline std::string to_std(std::__ndk1::string const& s) {
    return std::string(s.data());
} 

inline std::__ndk1::string to_stl(std::string const& s) {
    return std::__ndk1::string(s.data());
}

