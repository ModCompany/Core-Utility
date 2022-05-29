#include <core/module/hook_java.h>
#include <innercore_callbacks.h>
#include <core/JavaClass.h>
#include <logger.h>

#include <hook.h>
#include <symbol.h>

jclass HookJava::HOOK;
jclass HookJava::DATA;
jmethodID HookJava::ID;
jmethodID HookJava::ID_INTAS;
std::map<std::string, ReturnType*> HookJava::types;
std::map<std::string, jstring> HookJava::cache;

void HookJava::regiserReturnType(std::string name, ReturnType* type){
    types[name] = type;
}

void* HookJava::getConvertType(JNIEnv* env, std::string type, jobject obj){
    return types.find(type)->second->getConvertType(env, obj);
}

std::vector<Hook*> HookJava::getHooks(JNIEnv* env){
    const jmethodID getJsons = env->GetStaticMethodID(HookJava::HOOK, "getJsons", "()[Lcom/core/api/module/JsonData;");
    const jmethodID getSymbol = env->GetMethodID(HookJava::DATA, "getSymbol", "()Ljava/lang/String;");
    const jmethodID getCallback = env->GetMethodID(HookJava::DATA, "getCallback", "()Ljava/lang/String;");
    const jmethodID getPriority = env->GetMethodID(HookJava::DATA, "getPriority", "()Ljava/lang/String;");
    const jmethodID getReturn = env->GetMethodID(HookJava::DATA, "getReturn", "()Ljava/lang/String;");

	const jobjectArray array = (jobjectArray) env->CallStaticObjectMethod(HookJava::HOOK, getJsons);

    std::vector<Hook*> hooks;
    for(int i=0;i<env->GetArrayLength(array);i++) {
        jobject json = env->GetObjectArrayElement(array, i);
        jstring symbol = (jstring) env->CallObjectMethod(json, getSymbol);
        jstring callback = (jstring) env->CallObjectMethod(json, getCallback);
        jstring priority = (jstring) env->CallObjectMethod(json, getPriority);
        jstring returnType = (jstring) env->CallObjectMethod(json, getReturn);
        hooks.push_back(new Hook(
            JavaClass::toString(env, symbol),
            JavaClass::toString(env, callback),
            JavaClass::toString(env, priority),
            JavaClass::toString(env, returnType)
        ));
    }
    return hooks;
}

class Controller {
    private:
        HookManager::CallbackController* controller;
        bool isResultV;
        jobject result;
    public:
        Controller(HookManager::CallbackController* controller){
            this->controller = controller;
            isResultV = false;
        }
        void replace(){
            controller->replace();
        }
        bool isResult(){
            return isResultV;
        }
        void setIsResult(bool v){
            isResultV = v;
        }
        void setResult(jobject v){
            result = v;
        }
        jobject getResultHook(){
            return result;
        }
};

class ReturnInt : public ReturnType {
    public:
        void* getConvertType(JNIEnv* env, jobject v) override {
            return (void*) (int) (env->CallIntMethod(v, HookJava::ID_INTAS));
        }
};

void HookJava::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_2){
		HookJava::HOOK = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/Hook")));
        HookJava::DATA = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/JsonData")));
        HookJava::ID = env->GetStaticMethodID(HookJava::HOOK, "hook", "(JJLjava/lang/String;Ljava/lang/String;)V");
        jclass Double = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Double")));
        HookJava::ID_INTAS = env->GetMethodID(Double, "intValue", "()I");

        HookJava::regiserReturnType("int", new ReturnInt());
        
        std::vector<Hook*> hooks = HookJava::getHooks(env);
        for(int i = 0;i < hooks.size();i++){
            Hook* hook = hooks[i];
            HookJava::getJavaString(env, hook->callback); HookJava::getJavaString(env, hook->returnType);
            int v = HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER;
            if(hook->priority == "post")
                v = HookManager::RETURN | HookManager::LISTENER | HookManager::CONTROLLER;
            HookManager::addCallback(
                SYMBOL("mcpe",hook->symbol.c_str()), 
                LAMBDA((HookManager::CallbackController* controller, void* self),{
                    Controller* ctr = new Controller(controller);
                    env->CallStaticVoidMethod(HookJava::HOOK, HookJava::ID, (jlong) ctr, (jlong) self, HookJava::getJavaString(env, hook->callback), HookJava::getJavaString(env, hook->returnType));
                    if(ctr->isResult() && hook->returnType != "void"){
                        Logger::debug("TEST", "%i", (int) HookJava::getConvertType(env, hook->returnType, ctr->getResultHook()));
                        return HookJava::getConvertType(env, hook->returnType, ctr->getResultHook());
                    }
                    delete ctr;
                },hook, env
            ), v);
        }
	}
}

export(void,module_Hook_replace, jlong ptr) {
    ((Controller*) ptr)->replace();
}

export(void,module_Hook_setIsResult, jlong ptr, jboolean v) {
    ((Controller*) ptr)->setIsResult(v == JNI_TRUE);
}

export(void,module_Hook_setResult, jlong ptr, jobject v) {
    ((Controller*) ptr)->setResult(env->NewGlobalRef(v));
}