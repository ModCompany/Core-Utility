#pragma once

#include <string>
#include <jni.h>
#include <map>

class NativeVar;

template<unsigned N>
class Type {
    char pad[N];
};

class TypeBuilder {
	private:
    	std::vector<unsigned char> buffer;
	public:
		template<typename T>
		TypeBuilder* set(const T& v);
        template<typename T>
        const T get();
};

class NativeType {
    public:
        virtual jobject getJava(JNIEnv*,TypeBuilder*,NativeVar*) = 0;
        virtual TypeBuilder* getCpp(JNIEnv*,jobject,NativeVar*) = 0;
};

/*
Не большая инструкция по использованию NativeVar
TypeBuilder не обходимо удалять из памяти в ручную!!!
Ну а дальше сами разберётесь :D, удачи
*/

class NativeVar {
    private:
        jobject value;
        static std::map<std::string, NativeType*> types;
    public:
        static jclass PointerClass, Double, Long;
        static jmethodID getPointerPointerClass, constructorDouble, doubleValue, constructorLong, longValue;
        std::string type;
        bool isFinalize;
        static void init();
        static void registerType(std::string, NativeType*);
        NativeVar();
        NativeVar(std::string);
        NativeVar(JNIEnv*, jobject, std::string);
        NativeVar(JNIEnv*, TypeBuilder*, std::string);
        ~NativeVar();

        void setType(std::string);

        jobject get(JNIEnv*);
        void set(JNIEnv*,jobject);
        TypeBuilder* getCpp(JNIEnv*);
        void setCpp(JNIEnv*, TypeBuilder*);
        void setFinalize(bool);
};

inline void* getPointerClass(JNIEnv* env, jobject obj){
    return (void*) env->CallLongMethod(obj, NativeVar::getPointerPointerClass);
}