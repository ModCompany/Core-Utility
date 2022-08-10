#include <core/module/ActorDamageCause.h>
#include <hook.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <java.h>

#include <logger.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>
#include <stl/vector>

std::map<int,jobject> RegisterDamageCause::types;
jclass RegisterDamageCause::JavaClass;
jmethodID RegisterDamageCause::DeadMessage;

std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeadMessage(ActorDamageSource* source, std::__ndk1::string text, Actor* actor){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        jstring str = (jstring) env->CallObjectMethod(
            RegisterDamageCause::types.find((int) source->getCause())->second, RegisterDamageCause::DeadMessage,
            (jlong) source, JavaClass::toString(env, std::string(text.c_str())), (jlong) actor
        );
        std::__ndk1::string result = JavaClass::toStlString(env, str);
        env->DeleteLocalRef(str);
        return std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>>(result, std::__ndk1::vector<std::__ndk1::string>({text}));
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