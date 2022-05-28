#pragma once

#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <string>

class JniHook {
    public:
    enum ReturnData {
        Int = 0,
        Float = 1,
        String = 2,
    };

    class HookDataBase {
        public:
        ReturnData type;


        ReturnData getType(){
            return type;
        };
    };

    template<typename A> class HookData : public HookDataBase {
        
        A data;
        std::string symbol;
        HookData(ReturnData type,std::string a,A b) : symbol(a), data(b){
            this->type = type;
        }

        A getData(){
            return data;
        }
    };

    static std::map<std::string, HookDataBase> hooks;

    static void init_all(){
        std::map<std::string, HookDataBase>::iterator it = hooks.begin();
        while(it!=hooks.end()){
            HookDataBase base = it->second;
            HookDataBase* a = &base;
            ReturnData type = it->second.getType();
            if(type==ReturnData::Int){
   
            }
            if(type==ReturnData::Float){

            }
            if(type==ReturnData::String){

            }
        }
    };

};