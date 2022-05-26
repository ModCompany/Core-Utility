
#include <java.h>
#include <core/JniInjector.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>

JniInjector::JniInjector(void* a){
    this->table = a;
};

JniInjector::JniInjector(long pointer){
    this->table = (void*) pointer;
};

int JniInjector::getIntResult(const char* table, const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<int>(table,symbol);
}

float JniInjector::getFloatResult(const char* table, const char* symbol){
    VtableHelper helper (this->table);
    return helper.call<float>(table,symbol);
}

void JniInjector::call(const char* table, const char* symbol){
    VtableHelper helper(this->table);
    return helper.call<void>(table,symbol);
}

export(jlong, Injector_init_injector, jlong ptr){
    return (jlong) new JniInjector(ptr);
}

export(jint, Injector_getIntResult, jlong ptr, jstring a,jstring b){
    const char* table = JavaClass::release(env,a);
    const char* address = JavaClass::release(env,b);
    return ((JniInjector*) ptr)->getIntResult(table,address);
}

export(jint, Injector_getFloatResult, jlong ptr, jstring a,jstring b){
    const char* table = JavaClass::release(env,a);
    const char* address = JavaClass::release(env,b);
    return ((JniInjector*) ptr)->getFloatResult(table,address);
}

export(void, Injector_call, jlong ptr, jstring a, jstring b){
    const char* table = JavaClass::release(env,a);
    const char* address = JavaClass::release(env,b);
    return ((JniInjector*) ptr)->call(table,address);
}