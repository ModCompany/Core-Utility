
#include <java.h>
#include <core/JniInjector.h>
#include <core/VtableHelper.h>
#include <core/JavaClass.h>
#include <functional>
#include <core/module/hook_java.h>
#include <type/Json.h>


JniInjector::JniInjector(void* a){
    this->table = a;
};

JniInjector::JniInjector(long pointer){
    Logger::debug("Mod-Test", "Pointer of table: %p", pointer);
    this->table = (void*) pointer;
    this->pointer = pointer;
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

stl::string& JniInjector::getStringResult(const char* symbol){
    VtableHelper helper(this->table);
    return helper.call<stl::string&>(symbol);
}

void JniInjector::call(const char* symbol){
    Logger::debug("Mod-Test", "Pointer of table: %p", (long) this->table);
    VtableHelper helper(this->table);
    return helper.call<void>(symbol);
}

void JniInjector::replaceResult(const char* table,const char* symbol, int64_t lambda){
    VtableHelper helper(this->table);
    helper.resize();
    helper.patch(table,symbol, (void*) lambda);
}

void JniInjector::replace(const char* table, const char* symbol, const char* replace){
    VtablePatcher patcher(this->pointer,this->table);
    patcher.replace(table,symbol,replace);
}

void JniInjector::free(){
    delete this;
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
    //bool b = ((JniInjector*) ptr)->getBoolResult(JavaClass::toString(env,a).data());
    JniInjector* injector = (JniInjector*) ptr;
    bool b = injector->getBoolResult(JavaClass::toString(env,a).data());
    Logger::debug("Injector", "%i", b);
    Logger::flush();
    return b;
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

export(void, Injector_free, jlong ptr){
    return ((JniInjector*) ptr)->free();
}

#include <vector>
#include <hook.h>
/* ЗАМОРОЖЕННО ДО ЛУЧШИХ ВРЕМЁН ДА ИЛЬЯ?
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



export(void, Injector_callArgs, jlong ptr,jstring a,jstring b,jobject object){
    JniInjector* injector = (JniInjector*) ptr;
    
    injector->replaceResult(JavaClass::toString(env,a).data(),JavaClass::toString(env,b).data(),LAMBDA((void* self),{
        return "test";
    }));

}

export(void, Injector_replace, jlong ptr,jstring table,jstring symbol,jstring replace){
    JniInjector* injector = (JniInjector*) ptr;
    injector->replace(JavaClass::toString(env,table).data(),JavaClass::toString(env,symbol).data(),JavaClass::toString(env,replace).data());
}