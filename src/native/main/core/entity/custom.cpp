#include <core/entity/CustomEntity.h>
#include <core/entity/Entity.h>
#include <level/api/BlockSource.h>
#include <innercore/global_context.h>
#include <level/api/Vec3.h>
#include <type/ActorType.h>
#include <entity/ActorDefinitionIdentifier.h>

#include <hook.h>
#include <symbol.h>
#include <logger.h>
#include <innercore_callbacks.h>
#include <type/AutomaticID.h>
#include <core/JavaClass.h>
std::map<std::string, Entity*> CustomEntity::customs;
std::map<std::string, bool> CustomEntity::ticks;
jclass CustomEntity::customEntity;

Actor* CustomEntity::getEntityByName(std::string name){
    
}

bool CustomEntity::isTick(std::string name){
    if(ticks.find(name) == ticks.end())
        return false;
    return ticks[name];
}

void CustomEntity::setTick(std::string name, bool value){
    ticks[name] = value;
}

void CustomEntity::spawnEnity(BlockSource* region, Vec3* pos, std::string name){
    region->addEntity(pos, new EntityEmpty(*(region->getLevel())));
}

class ActorFactory;

void CustomEntity::init(){
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_2) {
        jclass localClass = env->FindClass("com/core/api/entity/CustomEntity");
        CustomEntity::customEntity = reinterpret_cast<jclass>(env->NewGlobalRef(localClass));
    }

    HookManager::addCallback(
        SYMBOL("mcpe","_ZN5Actor4tickER11BlockSource"), 
        LAMBDA((HookManager::CallbackController* controller, Actor* thas, BlockSource& region),{
            if(CustomEntity::isTick(std::string(thas->getActorIdentifier()->getFullName().c_str())))
                JavaCallbacks::invokeControlledCallback(CustomEntity::customEntity, "tickEntity", "(J)V", controller, 0, (jlong) thas->getUniqueID()->id);
	    },
    ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

    /*HookManager::addCallback(
        SYMBOL("mcpe","_ZN12ActorFactory21registerEntityMappingERK9ActorTypebRKPFNSt6__ndk110unique_ptrI5ActorNS3_14default_deleteIS5_EEEEP20ActorDefinitionGroupRK25ActorDefinitionIdentifierEN6nonstd13optional_lite8optionalIiEE"),
        LAMBDA((ActorFactory* thas, ActorType const& type, bool v, stl::unique_ptr<Actor> (* const&)(ActorDefinitionGroup*, ActorDefinitionIdentifier const&), nonstd::optional_lite::optional<int>),{
            
	    },
    ), HookManager::CALL | HookManager::LISTENER  | HookManager::RESULT);*/
}

std::string toString(JNIEnv* env, jstring jStr) {
	if (!jStr)
		return "";
	const jclass stringClass = env->GetObjectClass(jStr);
	const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
	const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));
	size_t length = (size_t) env->GetArrayLength(stringJbytes);
	jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
	std::string ret = std::string((char *)pBytes, length);
	env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
	env->DeleteLocalRef(stringJbytes); env->DeleteLocalRef(stringClass);
	return ret;
}

export(void,api_entity_CustomEntity_setTick,jstring name, jboolean value) {
        CustomEntity::setTick(JavaClass::toString(env,name),(bool)(value == JNI_TRUE));
}

