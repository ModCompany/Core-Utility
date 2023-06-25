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
        TypeBuilder(){}
        TypeBuilder(std::vector<unsigned char> buffer): buffer(buffer){}

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
/*
T - тип c++
value - значение 
type = подерживаемый NativeVar, текстовый тип
*/
#define newJavaNativeVar(T, env, value, type) env->NewGlobalRef(env->NewObject(NativeVar::NativeVarClass, NativeVar::NativeVarConstructor, (jlong) new NativeVar(env, (new TypeBuilder())->set<T>(value), type)))

/*
Класс упрощает использование NativeVar из C++
*/
template<typename T>
class NativeVarHelper {
    private:
        NativeVar* native_var;
        TypeBuilder* builder;
    public:
        NativeVarHelper(NativeVar* native_var): native_var(native_var){
            this->builder = native_var->getCpp(NULL);
        }

        T get() const {
            return builder->get<T>();
        }

        void set(T v){
            JNIEnv* env;
            ATTACH_JAVA(env, JNI_VERSION_1_6){
                native_var->setCpp(env, builder->set<T>(v));
            }
        }
};

/*
Аналоги NativeVarHelper, хз нахуя, но пусть будут
*/
#define VarGet(T, native_var) native_var->getCpp(NULL)->get<T>()
#define VarSet(T, native_var, value)({JNIEnv* env;                          \
    ATTACH_JAVA(env, JNI_VERSION_1_6){                                      \
        native_var->setCpp(env, native_var->getCpp(NULL)->set<T>(value));   \
    }})