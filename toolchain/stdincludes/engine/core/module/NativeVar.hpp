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
		TypeBuilder* set(const T& v){
            constexpr std::size_t size = sizeof(T);
            buffer.resize(size);
            *reinterpret_cast<T*>(buffer.data()) = v;
            return this;
        }
        template<typename T>
        const T& get(){
            return *reinterpret_cast<T*>(buffer.data());
        }
};

class NativeType {
    public:
        virtual jobject getJava(JNIEnv*,TypeBuilder*,NativeVar*) = 0;
        virtual TypeBuilder* getCpp(JNIEnv*,jobject,NativeVar*) = 0;
};

class NativeVar {
    private:
        TypeBuilder* value = nullptr;
        jobject jValue = NULL;
        static std::map<std::string, NativeType*> types;
    public:
        static jclass PointerClass, Double, Long, NativeVarClass;
        static jmethodID getPointerPointerClass, constructorDouble, doubleValue, constructorLong, longValue, NativeVarConstructor;
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