#pragma once

#include <stl/string>
#include <stl/vector>
#include <functional>
#define stl std::__ndk1

class JniInjector {
    public:
    enum JniInjectorTypes {
        
    };
    void* table;
    JniInjector(void*);
    JniInjector(long);
    int getIntResult(const char*);
    float getFloatResult(const char*);
    bool getBoolResult(const char*);
    void* getPointerResult(const char*);
    stl::string getStringResult(const char*);
    void replaceResult(const char*,const char*,void*);
    void call(const char*);
    private:


};