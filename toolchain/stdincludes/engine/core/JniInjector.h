#pragma once

#include <stl/string>
#include <stl/vector>
#include <stl/map>
#include <functional>
#include <typeinfo>
#include <core/VtableHelper.h>

#define stl std::__ndk1

class JniInjector {
    public:
        void* table;
        long pointer;
        std::vector<std::string> types;
        JniInjector(void*);
        JniInjector(long);

        void replaceResult(const char*,const char*,void*);
        void setArgsType(std::vector<std::string> types);
        template<typename T>
        T call(const char*, ArgsBufferBuilder);
        void free();
        void replace(const char*,const char*,const char*);
};