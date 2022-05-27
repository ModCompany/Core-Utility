#include <mod.h>
#include <java.h>

#include <map>
#include <vector>
#include <string>

#include <stl/string>
#include <logger.h>
#include <hook.h>
#include <symbol.h>
#include <core/module/ToolTip.h>

struct Item {};
class Level;
namespace ItemRegistry {
    Item* getItemById(int);
};
struct ItemStackBase {
    short getId() const;
    short getAuxValue() const;
    bool isBlock() const;
};

namespace IdConversion {
    enum Scope {
        ITEM, 
        BLOCK
    };

    int dynamicToStatic(int dynamicId, Scope scope);
    int staticToDynamic(int staticId, Scope scope);
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
    return result;
}
void ToolTip::addToolTip(int id, int data, std::string name){
    ToolTip* key = new ToolTip(id, data);
    if(tool_tips.find(key) == tool_tips.end())
        tool_tips[key] = {name};
    else
        tool_tips[key].push_back(name);
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
void ToolTip::init(){
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb"), 
        LAMBDA((Item* item, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool b), {
            ToolTip* key_tip = new ToolTip(IdConversion::dynamicToStatic(stack.getId(), IdConversion::Scope::ITEM), stack.getAuxValue());
            std::vector<std::string> tips = ToolTip::get(key_tip);
            for(int i = 0;i < tips.size();i++)
                text += "\n"+std::__ndk1::string(tips[i].c_str());
            delete key_tip;
        }, ), HookManager::RETURN | HookManager::LISTENER
    );
}

class ToolTipModule : public Module {
	public:
        ToolTipModule(): Module("ToolTip") {};
        virtual void initialize(){
            
        }
};

//Артём, тот метод иногда выдовал какуя-то хуйню)
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

export(void,item_ToolTip_addToolTip, jint id, jint data, jstring name) {
    ToolTip::addToolTip((int) id, (int) data, toString(env, name));
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