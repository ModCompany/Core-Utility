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

        void* table;
        int offset;
        DataOffset(void* table,int offset) : table(table), offset(offset) {};
        DataOffset(void* table) : table(table), offset(0) {};

        void* getOffset(){
            void** _offset = (void**) this->table + this->offset;
            return (void*) _offset;
        };

        void* getOffset(int a){
            void** _offset = (void**) this->table + a;
            return (void*) _offset;
        };

        stl::string& getString(){
            stl::string* string = (stl::string*) this->getOffset();
            return *string;

        };
        int getInt(){
            return (int) this->getOffset();
        };

        int getInt(int a){
            return (int) this->getOffset(a);
        };

        bool getBool(){
            return (bool) this->getOffset();
        };

        bool getBool(int a){
            return (bool) this->getOffset(a);
        };

        long getPointer(){
            return (long) this->getOffset(); 
        };

        long getPointer(int a){
            return (long) this->getOffset(a); 
        };

        void* get(){
            return (void*) this->getOffset();
        };

        void* get(int a){
            return (void*) this->getOffset(a);
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
            DataOffset _offset = DataOffset(this->table,offset);
            return &_offset;
        };

        DataOffset* getOffset(){
            DataOffset _offset = DataOffset(this->table);
            return &_offset;
        };

        DataOffset* getOffset(const char* a,const char* b){
        };

        void free();
        void replace(const char*,const char*,const char*);
};