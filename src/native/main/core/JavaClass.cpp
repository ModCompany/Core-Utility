
#include <string>
#include <logger.h>
#include <core/JavaClass.h>

JavaClass::JavaClass(JNIEnv* a, jobject b){
    env = a;
    object = b;
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

