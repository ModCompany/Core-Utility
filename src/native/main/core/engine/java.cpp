
#include <string>
#include <logger.h>
#include <core/JavaClass.h>

JavaClass::JavaClass(JNIEnv* a, jobject b){
    env = a;
    object = b;
}

std::string JavaClass::getClassName(){
    jclass clz = this->env->GetObjectClass(object);
    jmethodID mid = this->env->GetMethodID(clz, "getClass", "()Ljava/lang/Class;");
    jobject obj2 = env->CallObjectMethod(object, mid);
    jclass clz2 = env->GetObjectClass(obj2);
    jmethodID mid2 = env->GetMethodID(clz2, "getName", "()Ljava/lang/String;");
    jstring strObj = (jstring)env->CallObjectMethod(obj2, mid2);
    const char* str = env->GetStringUTFChars(strObj, NULL);
    env->ReleaseStringUTFChars(strObj, str);
    return std::string(str);
}

int JavaClass::getInt(const char* value){
    jclass clz = this->env->GetObjectClass(object);
    jfieldID a = this->env->GetFieldID(clz, value, "I");
    return (int) env->GetIntField(object, a);
}

float JavaClass::getFloat(const char* value){
    jclass clz = this->env->GetObjectClass(object);
    jfieldID a = this->env->GetFieldID(clz, value, "F");
    return this->env->GetFloatField(this->object, a);
}

bool JavaClass::getBool(const char* value){
    jclass clz = this->env->GetObjectClass(object);
    jfieldID a = this->env->GetFieldID(clz, value, "Z");
    return this->env->GetBooleanField(this->object, a);
}

const char* JavaClass::getString(const char* value){
    jclass clz = env->GetObjectClass(object);
    jfieldID a = env->GetFieldID(clz, value, "Ljava/lang/String;");
    jstring b = (jstring) env->GetObjectField(this->object, a);
    const char* string;
    const char* c;
    string = env->GetStringUTFChars(b, 0);

    c = string;

    env->ReleaseStringUTFChars(b, string);
   
    return c;
}

const char* JavaClass::release(JNIEnv* env,jstring value){
    const char* a = env->GetStringUTFChars(value, 0);
    const char* b;
    b = a;
    env->ReleaseStringUTFChars(value, a);
    return b;
}

std::string JavaClass::toString(JNIEnv* env,jstring jStr){
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