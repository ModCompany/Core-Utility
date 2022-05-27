
#include <java.h>
#include <core/JniInjector.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>

std::string to(JNIEnv* env, jstring jStr) {
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

JniInjector::JniInjector(void* a){
    this->table = a;
};

JniInjector::JniInjector(long pointer){
    Logger::debug("Mod-Test", "Pointer of table: %p", pointer);
    this->table = (void*) pointer;
};

int JniInjector::getIntResult(const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<int>(symbol);
}

float JniInjector::getFloatResult(const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<float>(symbol);
}

bool JniInjector::getBoolResult(const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<bool>(symbol);
}

void JniInjector::call(const char* symbol){
    Logger::debug("Mod-Test", "Pointer of table: %p", (long) this->table);
    VtableHelper helper(this->table);
    return helper.call<void>(symbol);
}

export(jlong, Injector_init_1injector, jlong ptr){
    return (jlong) new JniInjector(ptr);
}

export(jint, Injector_getIntResult, jlong ptr,jstring a){
    return ((JniInjector*) ptr)->getIntResult(to(env,a).data());
}

export(jfloat, Injector_getFloatResult, jlong ptr,jstring a){
    return ((JniInjector*) ptr)->getFloatResult(to(env,a).data());
}

export(jboolean, Injector_getBoolResult, jlong ptr,jstring a){
    return ((JniInjector*) ptr)->getBoolResult(to(env,a).data());
}

export(void, Injector_call, jlong ptr,jstring b){

    Logger::debug("Mod-Test", to(env,b).data());
    return ((JniInjector*) ptr)->call(to(env,b).data());
}