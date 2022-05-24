#pragma once


class JniInjector {
    public:
    enum JniInjectorTypes {
        
    };
    JniInjector(void*);
    JniInjector(long);
    int getIntResult(const char*, const char*);
    float getFloatResult(const char*, const char*);
    void call(const char*,const char*);
    private:

    void* table;
};