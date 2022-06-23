
#include <java.h>
#include <core/JniInjector.h>
#include <core/JavaClass.h>
#include <functional>
#include <core/module/hook_java.h>
#include <type/Json.h>
#include <hook.h>

JniInjector::JniInjector(void* a){
    this->table = a;
    this->types = std::vector<std::string>();
};

JniInjector::JniInjector(long pointer){
    Logger::debug("Mod-Test", "Pointer of table: %p", pointer);
    this->table = (void*) pointer;
    this->pointer = pointer;
    this->types = std::vector<std::string>();
};

void JniInjector::setArgsType(std::vector<std::string> types){
    this->types = types;
}

template<typename T>
T JniInjector::call(const char* symbol, ArgsBufferBuilder args, bool virt, const char* table){
    VtableHelper helper(this->table);
    return helper.call<T>(symbol, args, virt, table);
}

void JniInjector::replace(const char* table, const char* symbol, const char* replace){
    VtablePatcher patcher(this->pointer,this->table);
    patcher.replace(table,symbol,replace);
}

void JniInjector::free(){
    delete this;
}

template<typename T>
T callInjector(JNIEnv* env, JniInjector* injector, jstring symbol, jobjectArray arr, bool virt, jstring table){
    return injector->call<T>(JavaClass::toString(env,symbol).data(), HookJava::getParameters(env, injector->table, injector->types, arr), virt, JavaClass::toString(env,table).data());
}

export(jlong, Injector_init_1injector, jlong ptr){
    return (jlong) new JniInjector(ptr);
}

export(jint, Injector_getIntResult, jlong ptr, jstring a, jobjectArray arr, jboolean virt, jstring table){
    return (jint) callInjector<int>(env, (JniInjector*) ptr, a, arr, (bool) (virt == JNI_TRUE), table);
}

export(jfloat, Injector_getFloatResult, jlong ptr,jstring a, jobjectArray arr, jboolean virt, jstring table){
    return (jfloat) callInjector<float>(env, (JniInjector*) ptr, a, arr, (bool) (virt == JNI_TRUE), table);
}

export(jint, Injector_getBoolResult, jlong ptr,jstring a, jobjectArray arr, jboolean virt, jstring table){
    return (jint) ((int) callInjector<bool>(env, (JniInjector*) ptr, a, arr, (bool) (virt == JNI_TRUE), table));
}

export(jlong, Injector_getPointerResult, jlong ptr,jstring a, jobjectArray arr, jboolean virt, jstring table){
    return (jlong) callInjector<void*>(env, (JniInjector*) ptr, a, arr, (bool) (virt == JNI_TRUE), table);
}

export(jstring, Injector_getStringResult, jlong ptr,jstring a, jobjectArray arr, jboolean virt, jstring table){
    return env->NewStringUTF(callInjector<stl::string&>(env, (JniInjector*) ptr, a, arr, (bool) (virt == JNI_TRUE), table).c_str());
}

export(void, Injector_call, jlong ptr, jstring a, jobjectArray arr, jboolean virt, jstring table){
    callInjector<void*>(env, (JniInjector*) ptr, a, arr, (bool) (virt == JNI_TRUE), table);
}

export(void, Injector_free, jlong ptr){
    return ((JniInjector*) ptr)->free();
}


export(void, Injector_setArgsType, jlong ptr, jobjectArray arr){
    std::vector<std::string> types;
    for(int i=0;i<env->GetArrayLength(arr);i++)
        types.push_back(JavaClass::toString(env,(jstring) env->GetObjectArrayElement(arr, i)));
    ((JniInjector*) ptr)->setArgsType(types);
}


/* ЗАМОРОЖЕННО ДО ЛУЧШИХ ВРЕМЁН ДА ИЛЬЯ? Да-да
export(jobject, Injector_replace, jlong ptr,jstring a,jstring b, jobject value, jobjectArray arr){
    jobject func = env->NewGlobalRef(value);
    std::vector<std::string>* types = new std::vector<std::string>();
    for(int j=0;j<env->GetArrayLength(arr);j++)
        types->push_back(JavaClass::toString(env,(jstring) env->GetObjectArrayElement(arr, j)));
    JniInjector* injector = ((JniInjector*) ptr);
    JavaClass* java = new JavaClass(env, NULL);
    auto newFunc = ([java, types, env, func](void* a){
        Logger::debug("TEST", "table");
        java->runJsFunction(func, HookJava::getParameters(env, *types, {}, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
        
        Logger::debug("TEST", "end run");
        return stl::string("popa");
    });
    injector->replaceResult(JavaClass::toString(env,a).data(), JavaClass::toString(env,b).data(), LAMBDA((void* a, void* b), {
        Logger::debug("TEST", "table");
        java->runJsFunction(func, HookJava::getParameters(env, *types, {}, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
        
        Logger::debug("TEST", "end run");
        return stl::string("popa");
    }, java, types, env, func));
    return NULL;
}*/


export(void, Injector_replace, jlong ptr,jstring table,jstring symbol,jstring replace){
    JniInjector* injector = (JniInjector*) ptr;
    injector->replace(JavaClass::toString(env,table).data(),JavaClass::toString(env,symbol).data(),JavaClass::toString(env,replace).data());
}