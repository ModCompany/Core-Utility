#include <java.h>
#include <innercore_callbacks.h>
#include <core/module/NativeVar.hpp>
#include <core/JavaClass.h>
#include <vector>
#include <logger.h>

std::map<std::string, NativeType*> NativeVar::types;
jclass NativeVar::PointerClass, NativeVar::Double, NativeVar::Long, NativeVar::NativeVarClass;
jmethodID NativeVar::getPointerPointerClass, NativeVar::constructorDouble, NativeVar::doubleValue, NativeVar::constructorLong, NativeVar::longValue, NativeVar::NativeVarConstructor;

class NativeTypeInt : public NativeType {
    public:
        jobject getJava(JNIEnv* env, TypeBuilder* value, NativeVar* self) override {
            return env->NewObject(NativeVar::Double, NativeVar::constructorDouble, (jdouble) ((double) value->get<int>()));
        }
        TypeBuilder* getCpp(JNIEnv* env, jobject value, NativeVar* self) override {
            return TypeBuilder().set<int>((int) ((double) env->CallDoubleMethod(value, NativeVar::doubleValue)));
        }
};

class NativeTypeDouble : public NativeType {
    public:
        jobject getJava(JNIEnv* env, TypeBuilder* value, NativeVar* self) override {
            return env->NewObject(NativeVar::Double, NativeVar::constructorDouble, (jdouble) value->get<double>());
        }
        TypeBuilder* getCpp(JNIEnv* env, jobject value, NativeVar* self) override {
            return TypeBuilder().set<double>((double) env->CallDoubleMethod(value, NativeVar::doubleValue));
        }
};

class NativeTypeFloat : public NativeType {
    public:
        jobject getJava(JNIEnv* env, TypeBuilder* value, NativeVar* self) override {
            return env->NewObject(NativeVar::Double, NativeVar::constructorDouble, (jfloat) ((float) value->get<int>()));
        }
        TypeBuilder* getCpp(JNIEnv* env, jobject value, NativeVar* self) override {
            return TypeBuilder().set<float>((float) ((jfloat) env->CallDoubleMethod(value, NativeVar::doubleValue)));
        }
};

class NativeTypePtr : public NativeType {
    public:
        jobject getJava(JNIEnv* env, TypeBuilder* value, NativeVar* self) override {
            return env->NewGlobalRef(env->NewObject(NativeVar::Long, NativeVar::constructorLong, (jlong) value->get<long long>()));
        }
        TypeBuilder* getCpp(JNIEnv* env, jobject value, NativeVar* self) override {
            return (new TypeBuilder())->set<long long>((long long) ((jlong) env->CallLongMethod(value, NativeVar::longValue)));
        }
};
#include <stl/string>
class NativeTypeString : public NativeType {
    public:
        jobject getJava(JNIEnv* env, TypeBuilder* value, NativeVar* self) override {
            return (jobject) env->NewStringUTF(value->get<std::__ndk1::string>().c_str());
        }
        TypeBuilder* getCpp(JNIEnv* env, jobject value, NativeVar* self) override {
            return TypeBuilder().set<std::__ndk1::string>(JavaClass::toStlString(env, (jstring) value));
        }
};

void NativeVar::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        NativeVar::PointerClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/PointerClass")));
        NativeVar::NativeVarClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/NativeVar")));
        NativeVar::NativeVarConstructor = env->GetMethodID(NativeVar::NativeVarClass, "<init>", "(J)V");
        NativeVar::getPointerPointerClass = env->GetMethodID(PointerClass, "getPointer", "()J");
        NativeVar::Double = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Double")));
        NativeVar::constructorDouble = env->GetMethodID(NativeVar::Double, "<init>", "(D)V");
        NativeVar::doubleValue = env->GetMethodID(NativeVar::Double, "doubleValue", "()D");

        NativeVar::Long = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Long")));
        NativeVar::constructorLong = env->GetMethodID(NativeVar::Long, "<init>", "(J)V");
        NativeVar::longValue = env->GetMethodID(NativeVar::Long, "longValue", "()J");
    }

    NativeVar::registerType("int", new NativeTypeInt());
    NativeVar::registerType("float", new NativeTypeFloat());
    NativeVar::registerType("double", new NativeTypeDouble());
    NativeVar::registerType("ptr", new NativeTypePtr());
    NativeVar::registerType("stl::string", new NativeTypeString());
}

void NativeVar::registerType(std::string name, NativeType* type){
    NativeVar::types[name] = type;
}

NativeVar::NativeVar(): type("int"){
    this->setFinalize(true);
}
NativeVar::NativeVar(JNIEnv* env, jobject value, std::string type){
    this->type = type;
    set(env, value);
    this->setFinalize(true);
}
NativeVar::NativeVar(JNIEnv* env, TypeBuilder* value, std::string type){
    this->type = type;
    setCpp(env, value);
    this->setFinalize(true);
}
NativeVar::NativeVar(std::string type): type(type){
    this->setFinalize(true);
}
NativeVar::~NativeVar(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        env->DeleteGlobalRef(this->jValue);
    }
    delete this->value;
}

void NativeVar::setType(std::string type){
    this->type = type;
}

jobject NativeVar::get(JNIEnv* env) {
    return this->jValue;
}
void NativeVar::set(JNIEnv* env, jobject value){
    if(this->value != nullptr){
        env->DeleteGlobalRef(this->jValue);
        delete this->value;
    }
    this->jValue = value;
    this->value = NativeVar::types.find(this->type)->second->getCpp(env, value, this);
}
TypeBuilder* NativeVar::getCpp(JNIEnv* env) {
    Logger::debug("CoreUtility", "%p", this->value->get<void*>());
    return this->value;
}
void NativeVar::setCpp(JNIEnv* env, TypeBuilder* value){
    Logger::debug("CoreUtility", "setCpp %i", (this->value != nullptr && this->value != value));
    if(this->value != nullptr && this->value != value){
        env->DeleteGlobalRef(this->jValue);
        delete this->value;
       
    }
    Logger::debug("CoreUtility", "prePrint");
    Logger::debug("CoreUtility", "%p", value->get<void*>());
    this->jValue = NativeVar::types.find(this->type)->second->getJava(env, value, this);
    this->value = value;
}
void NativeVar::setFinalize(bool value){
    this->isFinalize = value;
}





#define _export(TYPE, CLZ, ...) extern "C" JNIEXPORT TYPE JNICALL Java_com_core_api_##CLZ (JNIEnv* env, jobject self, ##__VA_ARGS__)

_export(jlong,engine_NativeVar_init) {
    return (jlong) new NativeVar();
}
_export(void,engine_NativeVar_nativeSetType, jlong ptr, jstring type) {
    ((NativeVar*) ptr)->setType(JavaClass::toString(env, type));
}
_export(jobject,engine_NativeVar_nativeGet, jlong ptr) {
    return ((NativeVar*) ptr)->get(env);
}
_export(void,engine_NativeVar_nativeFree, jlong ptr) {
    NativeVar* var = ((NativeVar*) ptr);
    if(var->isFinalize)
        delete var;
}
_export(void,engine_NativeVar_nativeSetFinalize, jlong ptr, jboolean value) {
    ((NativeVar*) ptr)->setFinalize(value == JNI_TRUE);
}
_export(void,engine_NativeVar_nativeSet, jlong ptr, jobject value) {
    ((NativeVar*) ptr)->set(env, env->NewGlobalRef(value));
}

_export(void,engine_NativeVar_nativeFinalize, jlong ptr, jobject value) {
    NativeVar* var = ((NativeVar*) ptr);
    if(var->isFinalize)
        delete var;
}


_export(void,Boot_nativeVarMath, jlong ptr) {
    NativeVar* var = ((NativeVar*) ptr);
    Logger::debug("CoreUtility", "NativeVar test, status: 4");
    TypeBuilder* value = var->getCpp(env);
    Logger::debug("CoreUtility", "NativeVar test, status: 5");
    var->setCpp(env, value->set<long long>(value->get<long long>() - 100));
}