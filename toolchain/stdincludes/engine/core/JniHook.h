#pragma once

#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <string>
#include <stl/string>
#define stl std::__ndk1

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

        HookDataBase(ReturnData data){
            this->type = data;
        }
        ReturnData getType(){
            return type;
        };
    };

    template<typename A> class HookData : public HookDataBase {
        public:
        A data;
        std::string symbol;
        HookData(ReturnData type,std::string a,A b) :HookDataBase(type), symbol(a), data(b){}

        A getValue(){
            return data;
        }
        std::string getSymbol(){
            return symbol;
        }
    };

    static std::map<std::string, HookDataBase*> hooks;

    static void init_all(){
        std::map<std::string, HookDataBase*>::iterator it = hooks.begin();
        while(it!=hooks.end()){
            HookDataBase* base = it->second;

            ReturnData type = it->second->getType();
            if(type==ReturnData::Int){
                HookData<int>* data = reinterpret_cast<HookData<int>*>(base);
                HookManager::addCallback(SYMBOL("mcpe", data->getSymbol().data()), LAMBDA((HookManager::CallbackController* controller,void* self), {
                    return controller->call<int>(self, data->getValue());
                }, data), HookManager::CONTROLLER | HookManager::RETURN | HookManager::LISTENER);
            }
            if(type==ReturnData::Float){
                HookData<float>* data = reinterpret_cast<HookData<float>*>(base);
                HookManager::addCallback(SYMBOL("mcpe", data->getSymbol().data()), LAMBDA((HookManager::CallbackController* controller,void* self), {
                    return controller->call<float>(self, data->getValue());
                }, data), HookManager::CONTROLLER | HookManager::RETURN | HookManager::LISTENER);
            }
            if(type==ReturnData::String){
                HookData<stl::string>* data = reinterpret_cast<HookData<stl::string>*>(base);
                HookManager::addCallback(SYMBOL("mcpe", data->getSymbol().data()), LAMBDA((HookManager::CallbackController* controller,void* self), {
                    return controller->call<stl::string>(self, data->getValue());
                }, data), HookManager::CONTROLLER | HookManager::RETURN | HookManager::LISTENER);
            }
        }
    };

};