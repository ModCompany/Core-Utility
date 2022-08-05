#include <core/module/NativeAPI.h>
#include <core/JavaClass.h>

jclass NativeAPI::JNativeAPI;
jclass NativeAPI::PARAMETER;
jmethodID NativeAPI::constructorParameterLong;
jmethodID NativeAPI::constructorParameterInt;
jmethodID NativeAPI::constructorParameterFloat;
jmethodID NativeAPI::constructorParameterString;
jmethodID NativeAPI::getParameterLong;
jmethodID NativeAPI::getParameterInt;
jmethodID NativeAPI::getParameterFloat;
jmethodID NativeAPI::getParameterString;

jobject NativeAPI::createHookParameter(JNIEnv* env, jlong v, jstring t){
    return env->NewObject(NativeAPI::PARAMETER, NativeAPI::constructorParameterLong, v, t);
}
jobject NativeAPI::createHookParameter(JNIEnv* env, jint v, jstring t){
    return env->NewObject(NativeAPI::PARAMETER, NativeAPI::constructorParameterInt, v, t);
}
jobject NativeAPI::createHookParameter(JNIEnv* env, jfloat v, jstring t){
    return env->NewObject(NativeAPI::PARAMETER, NativeAPI::constructorParameterFloat, v, t);
}
jobject NativeAPI::createHookParameter(JNIEnv* env, jstring v, jstring t){
    return env->NewObject(NativeAPI::PARAMETER, NativeAPI::constructorParameterString, v, t); 
}

void* NativeAPI::getPointerHookParameter(JNIEnv* env, jobject obj){
    return (void*) env->CallLongMethod(obj, NativeAPI::getParameterLong);
}

long NativeAPI::getLongHookParameter(JNIEnv* env, jobject obj){
    return (long) env->CallLongMethod(obj, NativeAPI::getParameterLong);
}

int NativeAPI::getIntHookParameter(JNIEnv* env, jobject obj){
    return (int) env->CallIntMethod(obj, NativeAPI::getParameterInt);
}

float NativeAPI::getFloatHookParameter(JNIEnv* env, jobject obj){
    return (float) env->CallFloatMethod(obj, NativeAPI::getParameterFloat);
}

std::string NativeAPI::getStringHookParameter(JNIEnv* env, jobject obj){
    return JavaClass::toString(env, (jstring) env->CallObjectMethod(obj, NativeAPI::getParameterString));
}

void NativeAPI::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_2){
        NativeAPI::JNativeAPI = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/NativeAPI")));
        NativeAPI::PARAMETER = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/types/Parameter")));
        NativeAPI::constructorParameterLong = env->GetMethodID(NativeAPI::PARAMETER, "<init>", "(JLjava/lang/String;)V");
        NativeAPI::constructorParameterInt = env->GetMethodID(NativeAPI::PARAMETER, "<init>", "(ILjava/lang/String;)V");
        NativeAPI::constructorParameterFloat = env->GetMethodID(NativeAPI::PARAMETER, "<init>", "(FLjava/lang/String;)V");
        NativeAPI::constructorParameterString = env->GetMethodID(NativeAPI::PARAMETER, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
        
        NativeAPI::getParameterLong = env->GetMethodID(NativeAPI::PARAMETER, "getPointer", "()J");
        NativeAPI::getParameterInt = env->GetMethodID(NativeAPI::PARAMETER, "getInt", "()I");
        NativeAPI::getParameterFloat = env->GetMethodID(NativeAPI::PARAMETER, "getFloat", "()F");
        NativeAPI::getParameterString = env->GetMethodID(NativeAPI::PARAMETER, "getString", "()Ljava/lang/String;");
    }
}

#include <java.h>
#include <innercore/id_conversion_map.h>
#include <entity/Entity.h>
#include <type/AutomaticID.h>
#include <horizon/types.h>
#include <innercore/global_context.h>
#include <level/Level.h>

export(jint,module_NativeAPI_dynamicToStatic, jint id, jint type) {
    return (jint) IdConversion::dynamicToStatic((int) id, (IdConversion::Scope) ((int) type));
}
export(jint,module_NativeAPI_staticToDynamic, jint id, jint type) {
    return (jint) IdConversion::staticToDynamic((int) id, (IdConversion::Scope) ((int) type));
}
export(jlong,module_NativeAPI_getActorID, jlong ptr) {
    return (jlong) ((Actor*) ptr)->getUniqueID()->getId();
}
export(jint,module_NativeAPI_getXBlockPos, jlong ptr) {
    return (jint) ((BlockPos*) ptr)->x;
}
export(jint,module_NativeAPI_getYBlockPos, jlong ptr) {
    return (jint) ((BlockPos*) ptr)->y;
}
export(jint,module_NativeAPI_getZBlockPos, jlong ptr) {
    return (jint) ((BlockPos*) ptr)->z;
}
export(jlong,module_NativeAPI_getActorById, jlong ptr) {
    return (jlong) GlobalContext::getServerLevel()->fetchEntity((long long) ptr, true);
}