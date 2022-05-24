#pragma once

#include <stl/string>
#define stl std::__ndk1

namespace mce {
    class UUID {
        public:
        void operator!=(mce::UUID const&)const;
        void operator<(mce::UUID const&)const; 
        void seedFromString(stl::string const&);
        mce::UUID fromString(stl::string const&);
        stl::string asString()const; 
        bool isEmpty() const; 
    };
}