#pragma once


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
    void call(const char*);
    private:


};