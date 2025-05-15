#include <core/module/ActorDamageCause.h>
#include <hook.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <java.h>

#include <logger.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>
#include <vector>

std::map<int,jobject> RegisterDamageCause::types;
jclass RegisterDamageCause::JavaClass;
jmethodID RegisterDamageCause::DeadMessage;

#define stl std

stl::pair<stl::string, stl::vector<stl::string>> getDeadMessage(ActorDamageSource* source, stl::string text, Actor* actor){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        jstring arg = JavaClass::toString(env, text);
        jstring str = (jstring) env->CallObjectMethod(
            RegisterDamageCause::types.find((int) source->getCause())->second, RegisterDamageCause::DeadMessage,
            (jlong) source, arg, (jlong) actor
        );
        stl::string result = JavaClass::toStlString(env, str);
        env->DeleteLocalRef(arg);
        env->DeleteLocalRef(str);
        return stl::pair<stl::string, stl::vector<stl::string>>(result, stl::vector<stl::string>({text}));
    }
}

void RegisterDamageCause::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        RegisterDamageCause::JavaClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/entity/ActorDamageCause")));
        RegisterDamageCause::DeadMessage = env->GetMethodID(RegisterDamageCause::JavaClass, "getDeadMessage", "(JLjava/lang/String;J)Ljava/lang/String;");
    }
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN5Actor4hurtERK17ActorDamageSourceibb"), 
        LAMBDA((void* item, ActorDamageSource& source, int damage, bool v, bool b), {
            if(RegisterDamageCause::types.find((int) source.getCause()) == RegisterDamageCause::types.end())
                return;
            VtableHelper helper(&source);
            helper.resize();
            helper.patch("_ZTV17ActorDamageSource", "_ZNK17ActorDamageSource15getDeathMessageENSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEP5Actor", (void*) &getDeadMessage);
        }, ), HookManager::CALL | HookManager::LISTENER
    );
}

void RegisterDamageCause::registerType(int type, jobject value){
    RegisterDamageCause::types[type] = value;
}

export(void, entity_ActorDamageCause_registerCause, jint type, jobject value) {
    RegisterDamageCause::registerType((int) type, env->NewGlobalRef(value));
}