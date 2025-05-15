#pragma once
#include <cstdint>
#include <cassert>

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <typeinfo>
#include <core/VtableHelper.h>

#define stl std

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
            return *(int*)((char*) table + this->offset); 
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

        float getFloat(){
            return *(float*)((char*) table + this->offset);
        }

        float getFloat(int a){
            return *(float*)((char*) table + a);
        }

        void* get(){
            long ptr = this->getPointer();
            return (void*) ptr;
        };

        void* get(int a){
            long ptr = this->getPointer(a);
            return (void*) ptr;
        };

        void free(){
            this->~DataOffset();
        };
        
        int setOffset(int offset){
            this->offset = offset;
        };

        void setBool(bool value){
            *(bool*)((char*) table + this->offset) = value;
        };

        void setBool(int offset,bool value){
            *(bool*)((char*) table + offset) = value;
        };

        void setInt(int value){
            *(int*)((char*) table + this->offset) = value;
        };

        void setInt(int offset,int value){
            *(int*)((char*) table + offset) = value;
        };

        void setFloat(float value){
            *(float*)((char*) table + this->offset) = value;
        };

        void setFloat(int offset,float value){
            *(float*)((char*) table + offset) = value;
        };

        void setPointer(long long value){
            *(long long*)((char*) table + this->offset) = value;
        };

        void setPointer(int offset,long long value){
            *(long long*)((char*) table + offset) = value;
        };

        void setString(int offset, stl::string value){
            *(stl::string*)((char*) table + offset) = value;    
        };

        void setString(stl::string value){
            *(stl::string*)((char*) table + this->offset) = value;    
        };
        ~DataOffset(){

        }
    };
        bool isDebug = false;
        void* table;
        long pointer;
        std::vector<std::string> types;
        std::string lib;
        JniInjector(void*);
        JniInjector(long long);

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

        ~JniInjector(){
            if(isDebug) Logger::debug("JniInjector-Debug", "delete injector");
        };
};