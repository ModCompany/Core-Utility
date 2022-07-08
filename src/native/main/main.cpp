
#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <stl/string>
#define stl std::__ndk1

#include <type/Json.h>
#include <horizon/types.h>
#include <horizon/item.h>
#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/id_conversion_map.h>
typedef int content_id_t;
#include <core/JavaClass.h>
#include <core/entity/CustomEntity.h>
#include <core/module/ToolTip.h>
#include <core/module/hook_java.h>
#include <core/module/NativeAPI.h>
#include <core/JavaClass.h>
#include <core/JniHook.h>
#include <core/Global.h>
#include <core/effect_registry.h>
#include <core/module/BlockLegacy.h>
#include <core/world/FlatWorldOverrided.h>
#include <core/NativeSaver.h>
#include <client/MinecraftGame.h>
#include <client/ui/Container.h>
#include <client/Sound.h>
#include <core/scales.h>

#include <Core.h>
#include <innercore/global_context.h>






//variables


Core::FilePathManager *file_path_manager;
FlatWorldOverrided *flat_world_overrided;


//global environments for .cpp files
Core::FileSystemImpl* Global::_system_impl;
PlayScreenController* Global::_world_controller;
LevelListCache* Global::_world_cache;
class CoreUtility : public Module
{
public:
	CoreUtility(const char *id) : Module(id){};
	static jclass callback_class;

	virtual void initialize()
	{
		Logger::debug("Core Utility", "Initialize core");
		DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
		Logger::flush();

		JNIEnv *env;
		ATTACH_JAVA(env, JNI_VERSION_1_6)
		{
			jclass a = env->FindClass("com/core/api/NativeCallback");
			CoreUtility::callback_class = reinterpret_cast<jclass>(env->NewGlobalRef(a));
		}

		JavaClass::init();
		CustomEntity::init();
		ToolTip::init();
		NativeAPI::init();
		HookJava::init();
		BlockLegacyApi::init();
		//NativeSaver::init();

		HookManager::addCallback(
			SYMBOL("mcpe", "_ZN36EnchantingContainerManagerController13enchantResultEi"), 
			LAMBDA((HookManager::CallbackController * controller, EnchantingContainerManagerController * a, int b), {
				int id = IdConversion::dynamicToStatic(a->_getItem0(ContainerEnumName::Enchant).getId(), IdConversion::ITEM);
				JavaCallbacks::invokeControlledCallback(CoreUtility::callback_class, "onEnchant", "(I)V", controller, 0, id);
				return controller->call<void>(a, b);
			}, 
		), HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe", "_ZN20PlayScreenControllerC2ENSt6__ndk110shared_ptrI15PlayScreenModelEE20PlayScreenDefaultTabRKNS0_12basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"), LAMBDA((HookManager::CallbackController * controller, PlayScreenController * a, void *b, void *c), {
			Global::_world_controller = a;
		}, ),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe", "_ZN14LevelListCacheC2ER18LevelStorageSourceONSt6__ndk18functionIFbvEEE"), LAMBDA((HookManager::CallbackController * controller, LevelListCache * self, void *path), {
			Global::_world_cache = self;
		}, ),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe", "_ZN4Core14FileSystemImplC2ENS_14FileAccessTypeENSt6__ndk110shared_ptrINS_15FileStorageAreaEEENS_16TransactionFlagsENS3_INS_23FlatFileManifestTrackerEEE"), LAMBDA((HookManager::CallbackController * controller, Core::FileSystemImpl* self,void* a,void* b,void* c,void* d), {
			Global::_system_impl = self;
		}, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

	}
};

jclass CoreUtility::callback_class;


#include <level/Generator.h>
#include <level/Level.h>
#include <Core.h>

class CoreGeneration : public Module
{
public:
	CoreGeneration(Module *parent, const char *id) : Module(parent, id){};

	virtual void initialize(){
		/*HookManager::addCallback(SYMBOL("mcpe", "_ZN25FlatWorldGeneratorOptionsC2ERKN4Json5ValueERK12BlockPalette"), LAMBDA((HookManager::CallbackController * controller, void *a, Json::Value const &json, void *settings), {
									 Json::Value root{};

									 root["biome_id"] = 1;

									 Json::Value layers{};
									 Json::Value layer{};
									 layer["block_name"] = "minecraft:dirt";
									 layer["count"] = 2;

									 layers.append(layer);
									 root["block_layers"] = layers;
									 root["encoding_version"] = 5;

									 Logger::debug("FlatWorld", "%s", root.toStyledString().c_str());
									 Logger::flush();

									 Logger::flush();
									 if (flat_world_overrided->overrided)
									 {
										 return controller->call<bool>(a, flat_world_overrided->value, settings);
									 }
									 return controller->call<bool>(a,root,settings);
									 
								 }, ),
								 HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);*/

							

		 
	}
};

MAIN
{
	Module *main_module = new CoreUtility("core_utility");
	new CoreGeneration(main_module, "core_utility.generation");
	new SoundModule(main_module, "core_utility.sound");
	new ScalesModule();
}



#include <client/ClientIntance.h>

