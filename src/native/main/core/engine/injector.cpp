
#include <java.h>
#include <core/JniInjector.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>
#include <functional>



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

void* JniInjector::getPointerResult(const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<void*>(symbol);
}

stl::string JniInjector::getStringResult(const char* symbol){
    VtableHelper helper(this->table);
    stl::string str = helper.call<stl::string>(symbol);
    Logger::debug("TEST", str.c_str());
    Logger::flush();
    return str;
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
    return ((JniInjector*) ptr)->getIntResult(JavaClass::toString(env,a).data());
}

export(jfloat, Injector_getFloatResult, jlong ptr,jstring a){
    return ((JniInjector*) ptr)->getFloatResult(JavaClass::toString(env,a).data());
}

export(jboolean, Injector_getBoolResult, jlong ptr,jstring a){
    return ((JniInjector*) ptr)->getBoolResult(JavaClass::toString(env,a).data());
}

export(jlong, Injector_getPointerResult, jlong ptr,jstring a){
    return (jlong) ((JniInjector*) ptr)->getPointerResult(JavaClass::toString(env,a).data());
}

export(jstring, Injector_getStringResult, jlong ptr,jstring a){
    return env->NewStringUTF(((JniInjector*) ptr)->getStringResult(JavaClass::toString(env,a).data()).c_str());
}

export(void, Injector_call, jlong ptr,jstring b){
    Logger::debug("Mod-Test", JavaClass::toString(env,b).data());
    return ((JniInjector*) ptr)->call(JavaClass::toString(env,b).data());
}

int replace(int value){
    return value;
}

export(void, Injector_replace, jlong ptr,jstring a,jstring b,int value){
    ((JniInjector*) ptr)->replaceResult(JavaClass::toString(env,a).data(),JavaClass::toString(env,b).data(),(void*) replace(value));
}

export(void, Injector_callArgs, jlong ptr, jstring a,jobject object){
    JavaClass first (env,object);
    Logger::debug("Mod-Test","%i",first.getInt("args_count"));

    Logger::flush();

}