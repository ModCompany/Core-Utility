#include <core/module/hook_java.h>
#include <innercore_callbacks.h>
#include <logger.h>

#include <hook.h>
#include <symbol.h>

jclass HookJava::HOOK;
jclass HookJava::DATA;
jmethodID HookJava::ID;

std::string toString2(JNIEnv* env, jstring jStr) {
	if (!jStr)
		return "";
	const jclass stringClass = env->GetObjectClass(jStr);
	const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
	const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));
	size_t length = (size_t) env->GetArrayLength(stringJbytes);
	jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
	std::string ret = std::string((char *)pBytes, length);
	env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
	env->DeleteLocalRef(stringJbytes); env->DeleteLocalRef(stringClass);
	return ret;
}

std::vector<Hook*> HookJava::getHooks(JNIEnv* env){
    const jmethodID getJsons = env->GetStaticMethodID(HookJava::HOOK, "getJsons", "()[Lcom/core/api/module/JsonData;");
    const jmethodID getSymbol = env->GetMethodID(HookJava::DATA, "getSymbol", "()Ljava/lang/String;");
    const jmethodID getCallback = env->GetMethodID(HookJava::DATA, "getCallback", "()Ljava/lang/String;");

	const jobjectArray array = (jobjectArray) env->CallStaticObjectMethod(HookJava::HOOK, getJsons);

    std::vector<Hook*> hooks;
    for(int i=0;i<env->GetArrayLength(array);i++) {
        jobject json = env->GetObjectArrayElement(array, i);
        jstring symbol = (jstring) env->CallObjectMethod(json, getSymbol);
        jstring callback = (jstring) env->CallObjectMethod(json, getCallback);
        hooks.push_back(new Hook(toString2(env, symbol), toString2(env, callback)));
    }
    return hooks;
}

void HookJava::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
		HookJava::HOOK = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/Hook")));
        HookJava::DATA = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/JsonData")));
        HookJava::ID = env->GetStaticMethodID(HookJava::HOOK, "hook", "(JLjava/lang/String;)V");
        
        std::vector<Hook*> hooks = HookJava::getHooks(env);
        for(int i = 0;i < hooks.size();i++){
            Hook* hook = hooks[i];
            HookManager::addCallback(
                SYMBOL("mcpe",hook->symbol.c_str()), 
                LAMBDA((HookManager::CallbackController* controller, void* self),{
                    JNIEnv* env;
                    ATTACH_JAVA(env, JNI_VERSION_1_6){
                        env->CallStaticVoidMethod(HookJava::HOOK, HookJava::ID, (jlong) self, env->NewStringUTF(hook->callback.c_str()));
                    }
                },hook,
            ), HookManager::RETURN | HookManager::LISTENER | HookManager::CONTROLLER);
        }
	}
}