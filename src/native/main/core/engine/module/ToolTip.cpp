#include <mod.h>
#include <java.h>
#include <innercore_callbacks.h>

#include <map>
#include <vector>
#include <string>

#include <stl/string>
#include <logger.h>
#include <hook.h>
#include <symbol.h>
#include <core/module/ToolTip.h>

#include <vtable.h>
#include <core/JavaClass.h>
class ItemStackBase;
class Level {};
struct Item {
    virtual void appendFormattedHovertext(ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool b) const;
    virtual void* buildDescriptionName(ItemStackBase const& stack);
};
namespace ItemRegistry {
    Item* getItemById(int);
};
struct ItemStackBase {
    short getId() const;
    short getAuxValue() const;
    bool isBlock() const;
    Item* getItem() const;
    bool isNull() const;
    int getDamageValue() const;
};



std::map<ToolTip*, std::vector<std::string>> ToolTip::tool_tips;
std::vector<std::string> ToolTip::get(ToolTip* key){
    for(auto it = tool_tips.begin(); it != tool_tips.end(); ++it){
        ToolTip* tip = it->first;
        if(tip->id == key->id && (tip->data == -1 || tip->data == key->data))
            return it->second;
    }
    return std::vector<std::string>();
}
std::vector<std::string> ToolTip::get(int id, int data){
    ToolTip* tip = new ToolTip(id, data);
    std::vector<std::string> result = get(tip);
    delete tip;
    tip = nullptr;
    return result;
}
void ToolTip::addToolTip(int id, int data, std::string name){
    ToolTip* key = new ToolTip(id, data);
    std::vector<std::string> result = get(key);
    result.push_back(name);
    tool_tips[key] = result;
}
void ToolTip::clearToolTips(){
    for(auto it = tool_tips.begin(); it != tool_tips.end(); ++it)
        it->second.clear();
}
void ToolTip::clearToolTip(int id, int data){
    ToolTip* tip = new ToolTip(id, data);
    get(tip).clear();
    delete tip;
}
namespace GlobalContext {
    Level* getLevel();
};
namespace ItemRegistry {
    Item* getItemById(int id);
};
#include <innercore/id_conversion_map.h>

#include <core/VtableHelper.h>
std::vector<int> ToolTip::items_dynamic;

#include <logger.h>

jclass ToolTipClass, ItemStack;
jmethodID pre, post, constructorItemStack;
std::map<int, bool> enablesPre;
std::map<int, bool> enablesPost;

void ToolTip::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        ToolTipClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/item/ToolTip")));
        ItemStack = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/mcpe/item/ItemStack")));

        pre = env->GetStaticMethodID(ToolTipClass, "generateBuildDynamicToolTipPre", "(Lcom/core/api/mcpe/item/ItemStack;)Ljava/lang/String;");
        post = env->GetStaticMethodID(ToolTipClass, "generateBuildDynamicToolTipPost", "(Lcom/core/api/mcpe/item/ItemStack;)Ljava/lang/String;");
        constructorItemStack = env->GetMethodID(ItemStack, "<init>", "(J)V");
    }
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb"), 
        LAMBDA((Item* item, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool b), {
            int id = IdConversion::dynamicToStatic(stack.getId(), IdConversion::Scope::ITEM);
            if(stack.isNull() || id == 0)
                return;
            JNIEnv* env;
            ATTACH_JAVA(env, JNI_VERSION_1_6){
                jobject itemStack;
                if(enablesPre.find(id) != enablesPre.end() || enablesPost.find(id) != enablesPost.end())
                    itemStack = env->NewLocalRef(env->NewObject(ItemStack, constructorItemStack, (jlong) &stack));
                if(enablesPre.find(id) != enablesPre.end()){
                    jstring str = (jstring) env->CallStaticObjectMethod(
                        ToolTipClass, pre, 
                        itemStack
                    );
                    std::__ndk1::string res = JavaClass::toStlString(env, str);
                    env->DeleteLocalRef(str);
                    if(res != "")
                        text += "\n"+res;
                }

                ToolTip* key_tip = new ToolTip(id, stack.getAuxValue());
                std::vector<std::string> tips = ToolTip::get(key_tip);
                for(int i = 0;i < tips.size();i++)
                    text += "\n"+std::__ndk1::string(tips[i].c_str());

                if(enablesPost.find(id) != enablesPost.end()){
                    jstring str = (jstring) env->CallStaticObjectMethod(
                        ToolTipClass, post, 
                        itemStack
                    );
                    
                    std::__ndk1::string res = JavaClass::toStlString(env, str);
                    env->DeleteLocalRef(str);
                    if(res != "")
                        text += "\n"+res;
                }
                if(enablesPre.find(id) != enablesPre.end() || enablesPost.find(id) != enablesPost.end())
                    env->DeleteLocalRef(itemStack);
                delete key_tip;
                key_tip = nullptr;
            }
        }, ), HookManager::RETURN | HookManager::LISTENER
    );
}
export(void,item_ToolTip_enablePre, jint id, jboolean value){
    enablesPre[(int) id] = value == JNI_TRUE;
}
export(void,item_ToolTip_enablePost, jint id, jboolean value){
    enablesPost[(int) id] = value == JNI_TRUE;
}
export(void,item_ToolTip_addToolTip, jint id, jint data, jstring name) {
    ToolTip::addToolTip((int) id, (int) data, JavaClass::toString(env, name));
}
export(void,item_ToolTip_clearToolTips) {
    ToolTip::clearToolTips();
}
export(void,item_ToolTip_clearToolTip, jint id, jint data) {
    ToolTip::clearToolTip((int) id, (int) data);
}
export(jobjectArray,item_ToolTip_getToolTips, jint id, jint data) {
    std::vector<std::string> datas = ToolTip::get((int) id, (int) data);
	jobjectArray array = env->NewObjectArray(datas.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
	for(int i = 0;i < datas.size();i++)
		env->SetObjectArrayElement(array,i,env->NewStringUTF(datas[i].c_str()));  
	return array;
}