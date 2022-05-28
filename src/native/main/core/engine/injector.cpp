
#include <java.h>
#include <core/JniInjector.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>
#include <functional>

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

long JniInjector::getPointerResult(const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<long>(symbol);
}

stl::string JniInjector::getStringResult(const char* symbol){
    VtableHelper helper(this->table);
    return helper.call<stl::string>(symbol);
}

void JniInjector::call(const char* symbol){
    Logger::debug("Mod-Test", "Pointer of table: %p", (long) this->table);
    VtableHelper helper(this->table);
    return helper.call<void>(symbol);
}

void JniInjector::replaceResult(const char* table,const char* symbol, void* lambda){
    VtableHelper helper(this->table);
    helper.resize();
    helper.patch(table,symbol,lambda);
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

export(jboolean, Injector_getPointerResult, jlong ptr,jstring a){
    return ((JniInjector*) ptr)->getPointerResult(to(env,a).data());
}

export(jstring, Injector_getStringResult, jlong ptr,jstring a){
    return env->NewStringUTF(((JniInjector*) ptr)->getStringResult(to(env,a).data()).c_str());
}

export(void, Injector_call, jlong ptr,jstring b){
    Logger::debug("Mod-Test", to(env,b).data());
    return ((JniInjector*) ptr)->call(to(env,b).data());
}

int replace(int value){
    return value;
}
export(void, Injector_replace, jlong ptr,jstring a,jstring b,int value){

    ((JniInjector*) ptr)->replaceResult(to(env,a).data(),to(env,b).data(),(void*) replace(value));

}