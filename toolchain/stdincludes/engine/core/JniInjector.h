#pragma once
#include <cstdint>
#include <cassert>

#include <stl/string>
#include <stl/vector>
#include <stl/map>
#include <functional>
#include <typeinfo>
#include <core/VtableHelper.h>

#define stl std::__ndk1

class JniInjector {
    public:
    class DataOffset {
        public:

        long table;
        int offset;
        DataOffset(void* table,int offset) : table((long)table), offset(offset) {};
        DataOffset(void* table) : table((long) table), offset(0) {};
        DataOffset(long table,int offset) : table(table), offset(offset) {};
        DataOffset(long table) : table(table), offset(0) {};

        stl::string& getString(){
            return *(stl::string*)((char*) table + this->offset); 
        };

        stl::string& getString(int a){
            return *(stl::string*)((char*) table + a); 
        };

        int getInt(){
            return *(int*)((void*) table + this->offset); 
        };

        int getInt(int a){
            return *(int*)((char*) table + a); 
        };

        bool getBool(){
            return *(bool*)((char*) table + this->offset); 
        };

        bool getBool(int a){
            return *(bool*)((char*) table + a);
        };

        long getPointer(){
            return *(long*)((char*) table + this->offset); 
        };

        long getPointer(int a){
            return *(long*)((char*) table + a); 
        };

        void* get(){
            long ptr = this->getPointer();
            return (void*) ptr;
        };

        void* get(int a){
            long ptr = this->getPointer(a);
            return (void*) ptr;
        };

        int setOffset(int offset){
            this->offset = offset;
        };
    };

        void* table;
        long pointer;
        std::vector<std::string> types;
        JniInjector(void*);
        JniInjector(long);

        void replaceResult(const char*,const char*,void*);
        void setArgsType(std::vector<std::string> types);
        template<typename T>
        T call(const char*, ArgsBufferBuilder, bool, const char*);

        DataOffset* getOffset(int offset){
            return new DataOffset(this->table,offset);
        };

        DataOffset* getOffset(){    
            return new DataOffset(this->table);
        };

        DataOffset* getOffset(const char* a,const char* b){
        };

        void free();
        void replace(const char*,const char*,const char*);
};