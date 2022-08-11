#include <java.h>
#include <innercore_callbacks.h>
#include <core/module/NativeVar.h>
#include <core/JavaClass.h>
#include <vector>

std::map<std::string, NativeType*> NativeVar::types;
jclass NativeVar::PointerClass, NativeVar::Double, NativeVar::Long;
jmethodID NativeVar::getPointerPointerClass, NativeVar::constructorDouble, NativeVar::doubleValue, NativeVar::constructorLong, NativeVar::longValue;

template<typename T>
TypeBuilder* TypeBuilder::set(const T& v){
    constexpr std::size_t size = sizeof(T);
	buffer.resize(size);
	*reinterpret_cast<T*>(buffer.data()) = v;
    return this;
}
template<typename T>
const T TypeBuilder::get(){
    return *reinterpret_cast<T*>(buffer.data());
}

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

class NativeTypeLong : public NativeType {
    public:
        jobject getJava(JNIEnv* env, TypeBuilder* value, NativeVar* self) override {
            return env->NewObject(NativeVar::Long, NativeVar::constructorLong, (jlong)  value->get<long long>());
        }
        TypeBuilder* getCpp(JNIEnv* env, jobject value, NativeVar* self) override {
            return TypeBuilder().set<long long>((long long) ((jlong) env->CallLongMethod(value, NativeVar::longValue)));
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
    NativeVar::registerType("ptr", new NativeTypeLong());
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
        env->DeleteGlobalRef(this->value);
    }
}

void NativeVar::setType(std::string type){
    this->type = type;
}

jobject NativeVar::get(JNIEnv* env) {
    return value;
}
void NativeVar::set(JNIEnv* env, jobject value){
    env->DeleteGlobalRef(this->value);
    this->value = env->NewGlobalRef(value);
}
TypeBuilder* NativeVar::getCpp(JNIEnv* env) {
    return NativeVar::types.find(this->type)->second->getCpp(env,value,this);
}
void NativeVar::setCpp(JNIEnv* env, TypeBuilder* value){
    env->DeleteGlobalRef(this->value);
    this->value = env->NewGlobalRef(NativeVar::types.find(this->type)->second->getJava(env,value,this));
}
void NativeVar::setFinalize(bool value){
    this->isFinalize = value;
}





inline NativeVar* getPointer(JNIEnv* env, jobject obj){
    return (NativeVar*) getPointerClass(env, obj);
}

#define _export(TYPE, CLZ, ...) extern "C" JNIEXPORT TYPE JNICALL Java_com_core_api_##CLZ (JNIEnv* env, jobject self, ##__VA_ARGS__)

_export(jlong,engine_NativeVar_init) {
    return (jlong) new NativeVar();
}
_export(void,engine_NativeVar_setType, jstring type) {
    getPointer(env, self)->setType(JavaClass::toString(env, type));
}
_export(jobject,engine_NativeVar_get) {
    return getPointer(env, self)->get(env);
}
_export(void,engine_NativeVar_free) {
    NativeVar* var = getPointer(env, self);
    if(var->isFinalize)
        delete var;
}
_export(void,engine_NativeVar_setFinalize, jboolean value) {
    getPointer(env, self)->setFinalize(value == JNI_TRUE);
}
_export(void,engine_NativeVar_set, jobject value) {
    getPointer(env, self)->set(env, value);
}
_export(void,engine_NativeVar_finalize, jobject value) {
    NativeVar* var = getPointer(env, self);
    if(var->isFinalize)
        delete var;
}