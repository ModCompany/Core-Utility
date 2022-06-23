
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
#include <client/ui/Container.h>
#include <client/Sound.h>
#include <core/module/ToolTip.h>
#include <core/module/hook_java.h>
#include <core/module/NativeAPI.h>
#include <core/JavaClass.h>

#include <core/JniHook.h>
#include <Core.h>
#include <client/MinecraftGame.h>
#include <core/effect_registry.h>
#include <core/module/BlockLegacy.h>
class PlayScreenController {
	public:
	void repopulateLevels();
	int _getLocalWorldsCount() const;
};
struct BlockLegacy {
	int getBlockItemId() const;
};

struct Block {
	BlockLegacy* getBlockLegacy() const;
};

PlayScreenController* model;
LevelListCache* cache;
Core::FilePathManager* file_path_manager;


class CoreUtility : public Module {
public:
	CoreUtility(const char* id): Module(id) {};
	static jclass callback_class;

	virtual void initialize() {	
		Logger::debug("Core Utility", "Initialize core");
		DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
		Logger::flush();

		JNIEnv* env;
		ATTACH_JAVA(env, JNI_VERSION_1_6){
			jclass a = env->FindClass("com/core/api/NativeCallback");
			CoreUtility::callback_class = reinterpret_cast<jclass>(env->NewGlobalRef(a));
		}

		JavaClass::init();
		CustomEntity::init();
		ToolTip::init();
		NativeAPI::init();
		HookJava::init();
		BlockLegacyApi::init();

		HookManager::addCallback(SYMBOL("mcpe","_ZN36EnchantingContainerManagerController13enchantResultEi"), LAMBDA((HookManager::CallbackController* controller, EnchantingContainerManagerController* a,int b),{

			int id = IdConversion::dynamicToStatic(a->_getItem0(ContainerEnumName::Enchant).getId(), IdConversion::ITEM);
			
			JavaCallbacks::invokeControlledCallback(CoreUtility::callback_class, "onEnchant", "(I)V", controller, 0,id);

			return controller->call<void>(a,b);
		},),HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe","_ZN20PlayScreenControllerC2ENSt6__ndk110shared_ptrI15PlayScreenModelEE20PlayScreenDefaultTabRKNS0_12basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"), LAMBDA((HookManager::CallbackController* controller, PlayScreenController* a,void* b,void* c),{

			model = a;

		},),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
		HookManager::addCallback(SYMBOL("mcpe","_ZN14LevelListCache11_addToCacheERKN4Core4PathE"), LAMBDA((HookManager::CallbackController* controller, LevelListCache* self,Core::Path const& path),{

			Logger::debug("CoreTest",path.path.data());
			Logger::flush();
		},),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe","_ZN14LevelListCacheC2ER18LevelStorageSourceONSt6__ndk18functionIFbvEEE"), LAMBDA((HookManager::CallbackController* controller, LevelListCache* self,void* path),{
			cache = self;
		},),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe","_ZN4Core15FilePathManagerC2ERKNS_4PathEb"), LAMBDA((HookManager::CallbackController* controller, Core::FilePathManager* self,void* path,bool c),{
			file_path_manager = self;
		},),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
		

		
    }	
};

jclass CoreUtility::callback_class;

class CoreItems : public Module {
public:
	CoreItems(Module* parent, const char* id) : Module(parent, id) {};
	virtual void initialize(){
		Logger::debug("Core Utility", "Initialize CoreItems for working with mods");
		Logger::flush();
	}
};

class WorldGenerator {
	public:
	Json::Value root;

};

class RandomScatteredLargeFeature;

class FlatWorldGenerator {
	public:

	template<typename A> void addHardcodedSpawnsForFeature();
};
class CoreGeneration : public Module {
	public:
	CoreGeneration(Module* parent, const char* id) : Module(parent, id) {};

	virtual void initialize(){
		
		HookManager::addCallback(SYMBOL("mcpe", "_ZN25FlatWorldGeneratorOptions5_loadERKN4Json5ValueERK12BlockPalette"),LAMBDA((HookManager::CallbackController* controller,void* a,Json::Value const& json, void* settings),{
			Json::Value root{};

			root["biome_id"]          = 1;

			Json::Value layers {};
			Json::Value layer {};
			layer["block_name"] = "minecraft:dirt";
			layer["count"] = 80;

			layers.append(layer);
			root["block_layers"] = layers;
			root["encoding_version"]  = 5;

			Json::Value structure {};
			Json::Value str{};
			Json::Value option{};
			option["size"] = 32;
			option["distance"] = 9;
			option["structure_name"] = "village";
			option["feature_name"] = "minecraft:village";			
			structure.append(option);
			root["structure_options"] = structure;

			Logger::debug("FlatWorld", "%s", root.toStyledString().c_str());
			Logger::flush();
			return controller->call<bool>(a,root,settings);

		},),HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);


	}
};


MAIN {
	Module* main_module = new CoreUtility("core_utility");
	//new CoreItems(main_module, "core_utility.items");
	//new CoreGeneration(main_module, "core_utility.generation");
	new SoundModule(main_module, "core_utility.sound");


}	



#include <innercore/global_context.h>


#include <client/ClientIntance.h>



JS_MODULE_VERSION(PlayScreen,1);

JS_EXPORT(PlayScreen, refresh,"V()", (JNIEnv* env){

	  for(int x = 29; x!=-1; x--){
		if(MobEffect::mMobEffects[x--]!=nullptr){
			auto a = MobEffect::mMobEffects[x];
			Logger::debug("CoreTest",a->getIconName().data());
			Logger::flush();
		}
	  }
});