#pragma once

#include <stl/string>
#include <stl/vector>
#include <stl/map>
#include <functional>
#include <typeinfo>

#define stl std::__ndk1

class JniInjector {
    public:
    enum JniInjectorTypes {
        
    };

    struct JniBase {
        JniInjectorTypes types;
    };

    template<typename A> class JniValue : public JniBase {
        public:
        A value;

        JniValue(A a){
            this->value = a;
        };

        operator A() const {
            return this->value;
        };

        A getValue(){
            return this->value;
        };
    };

    void* table;
    long pointer;
    JniInjector(void*);
    JniInjector(long);

    void replaceResult(const char*,const char*,int64_t);
    void call(const char*);
    void free();

    template<typename...A> void call(A...a){
        stl::vector<stl::string> types = getTypes(a...);
        stl::map<int, JniBase> args;
        
        for(auto& item : types){

            if(item=="NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"){
                //getArg(std::forward<A>(a)...);
                //std::string
            }
            if(item=="i"){
                //getArg(std::forward<A>(a)...);               
                //int
            }
            if(item=="d"){
                //getArg(std::forward<A>(a)...);                
                //double
            }
            if(item=="b"){
                //getArg(std::forward<A>(a)...);                
                //bool
            }
            if(item=="PKc"){
                //char
                //getArg(std::forward<A>(a)...);
            }
            Logger::debug("InjectorCaller", "Call %s", item.c_str());
            Logger::flush();
        }
    };

    template<class... T> stl::vector<stl::string> getTypes(T...a) {
        return {typeid(T).name()...};
    };

    template<typename A> A getArg(A a){
        return a;
    };

    int getIntResult(const char*);
    float getFloatResult(const char*);
    bool getBoolResult(const char*);
    void* getPointerResult(const char*);
    stl::string& getStringResult(const char*);
    void replace(const char*,const char*,const char*);


    private:


};