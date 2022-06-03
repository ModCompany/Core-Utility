
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

		HookManager::addCallback(SYMBOL("mcpe","_ZN36EnchantingContainerManagerController13enchantResultEi"), LAMBDA((HookManager::CallbackController* controller, EnchantingContainerManagerController* a,int b),{

			int id = IdConversion::dynamicToStatic(a->_getItem0(ContainerEnumName::Enchant).getId(), IdConversion::ITEM);
			
			JavaCallbacks::invokeControlledCallback(CoreUtility::callback_class, "onEnchant", "(I)V", controller, 0,id);

			return controller->call<void>(a,b);
		},),HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);


		HookManager::addCallback(SYMBOL("mcpe","_ZNK9Dimension15getDefaultBiomeEv"), LAMBDA((HookManager::CallbackController* controller, void* a,void* b,void* c),{

			return 31;
		},),HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

		HookManager::addCallback(SYMBOL("mcpe","_ZN20ActorDefinitionGroup29loadActorDefinitionIdentifierERKN4Json5ValueERK10SemVersionRNSt6__ndk112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE"), LAMBDA((HookManager::CallbackController* controller, Json::Value const& b,void* c,stl::string& d),{

			//Logger::debug("Test",b.toStyledString().data());
			//Logger::debug("Test",d.data());
			return controller->call<void>(b,c,d);
		},),HookManager::CALL |  HookManager::LISTENER | HookManager::REPLACE | HookManager::CONTROLLER | HookManager::RESULT);

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





