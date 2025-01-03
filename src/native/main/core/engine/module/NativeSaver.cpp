#include <innercore_callbacks.h>
#include <java.h>
#include <core/NativeSaver.h>
#include <symbol.h>
#include <hook.h>
jclass NativeSaver::NativeSaverClass;
jmethodID NativeSaver::readID;
jmethodID NativeSaver::saveID;
class CompoundTag {};

void NativeSaver::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        NativeSaver::NativeSaverClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/NativeSaver")));
        NativeSaver::readID = env->GetStaticMethodID(NativeSaver::NativeSaverClass, "readCallback", "(JJ)V");
        NativeSaver::saveID = env->GetStaticMethodID(NativeSaver::NativeSaverClass, "saveCallback", "(JJ)V");
        /*HookManager::addCallback(
            SYMBOL("mcpe", "_ZN5Actor4saveER11CompoundTag"), 
            LAMBDA((void* self, CompoundTag const& tag), {
                JNIEnv* env;
                ATTACH_JAVA(env, JNI_VERSION_1_6){
                    env->CallStaticVoidMethod(
                        NativeSaver::NativeSaverClass, NativeSaver::saveID, 
                        (jlong) self,
                        (jlong) &tag
                    );
                }
            }, 
        ), HookManager::CALL | HookManager::LISTENER);*/
        /*HookManager::addCallback(
            SYMBOL("mcpe", "_ZN5Actor4loadERK11CompoundTagR14DataLoadHelper"), 
            LAMBDA((void* self, CompoundTag& tag), {
                JNIEnv* env;
                ATTACH_JAVA(env, JNI_VERSION_1_6){
                    env->CallStaticVoidMethod(
                        NativeSaver::NativeSaverClass, NativeSaver::readID, 
                        (jlong) self,
                        (jlong) &tag
                    );
                }
            }, 
        ), HookManager::CALL | HookManager::LISTENER);*/
    }
}