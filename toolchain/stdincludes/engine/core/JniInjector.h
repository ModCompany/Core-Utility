#pragma once

#include <stl/string>
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
    long getPointerResult(const char*);
    stl::string getStringResult(const char*);
    void replaceResult(const char*,const char*,void*);
    void call(const char*);
   /* template<typename A,typename...B> callArgs(const char* symbol, B...b){
        Logger::debug("Mod-Test", "Pointer of table: %p", (long) this->table);
        VtableHelper helper(this->table);
        return helper.call<A>(symbol,b...);
    }*/
    void callJava(const char*, jobject);
    void callJava(const char*, jobject,jobject);
    void callJava(const char*, jobject,jobject,jobject);
    private:


};