#include <java.h>
#include <innercore_callbacks.h>
#include <core/module/NativeVar.h>
#include <core/JavaClass.h>

std::map<std::string, NativeType*> NativeVar::types;

class NativeTypeInt : public NativeType {
    public:
        jobject getJava(char* value) const override {
            return reinterpret_cast<jobject>((jint) ((int) value));
        }
        char* getCpp(jobject value) const override {
            return (char*) ((int) reinterpret_cast<jint>(value));
        }
};

jclass PointerClass;
jmethodID getPointerPointerClass;
void NativeVar::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        PointerClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/PointerClass")));
        getPointerPointerClass = env->GetMethodID(PointerClass, "getPointer", "()J");
    }

    NativeVar::registerType("int", new NativeTypeInt());
}

void NativeVar::registerType(std::string name, NativeType* type){
    NativeVar::types[name] = type;
}


NativeVar::NativeVar(): type("int"){
    this->setFinalize(true);
}
NativeVar::NativeVar(JNIEnv* env, jobject value, std::string type): type(type){
    set(env, value);
    this->setFinalize(true);
}
NativeVar::NativeVar(JNIEnv* env, char* value, std::string type): type(type){
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

jobject NativeVar::get(JNIEnv* env) const {
    return value;
}
void NativeVar::set(JNIEnv* env, jobject value){
    this->value = env->NewGlobalRef(value);
}
char* NativeVar::getCpp(JNIEnv* env) const {
    auto it = NativeVar::types.begin();
    while(it != NativeVar::types.end()){
        if(it->first == this->type)
            return it->second->getCpp(value);
        it++;
    }
}
void NativeVar::setCpp(JNIEnv* env, char* value){
    auto it = NativeVar::types.begin();
    while(it != NativeVar::types.end()){
        Logger::debug(value, "%s %s %i", this->type.c_str(), it->first.c_str(), it->first == this->type);
        if(it->first == this->type){
            this->value = env->NewGlobalRef(it->second->getJava(value));
            break;
        }
        it++;
    }
}
void NativeVar::setFinalize(bool value){
    this->isFinalize = value;
}






inline NativeVar* getPointer(JNIEnv* env, jobject obj){
    return (NativeVar*) env->CallLongMethod(obj, getPointerPointerClass);
}
#define _export(TYPE, CLZ, ...) extern "C" JNIEXPORT TYPE JNICALL Java_com_core_api_##CLZ (JNIEnv* env, jobject self, ##__VA_ARGS__)

_export(void,engine_NativeVar_registerType, jstring name, jobject type) {
    
}
_export(jlong,engine_NativeVar_init) {
    return (jlong) new NativeVar(env, (char*) 556, "int");
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
        var->~NativeVar();
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
        var->~NativeVar();
}