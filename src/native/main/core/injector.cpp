
#include "engine/JniInjector.h"
#include "../shared_headers/VtableHelper.h"

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