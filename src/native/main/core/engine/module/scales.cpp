#include <hook.h>
#include <symbol.h>
#include <logger.h>
#include <java.h>

#include <map>

#include <client/ui/ScreenContext.h>
#include "mcpe/MinecraftUIRenderContext.hpp"
#include "mcpe/UIControl.hpp"
#include "mcpe/Player.hpp"
#include "mcpe/ClientInstance.hpp"

#include <core/scales.h>

#include <core/JavaClass.h>

const int SCALE_MAX = 20;
const int SCALE_SIZE = 8;

class HudHungerRenderer {};
class RectangleArea {};

class Scales;

namespace GlobalContext {
	LocalPlayer* getLocalPlayer();
};

class ScalesData {
	private:
		Scales* scale;
		int value;
	public:
		void reset(){
			value = 20;
		}
		ScalesData(Scales* _scale){
			scale = _scale;
			reset();
		}
		int getValue(){
			return value;
		}
		void setValue(int _value){
			if(_value > SCALE_MAX)
				_value = SCALE_MAX;
			else if(_value < 0)
				_value = 0;
			value = _value;
		}
		Scales* getScale(){
			return scale;
		}
};

struct ScalePlayer {
	std::map<std::string, ScalesData*> scales;
	ScalePlayer(){
		scales = std::map<std::string, ScalesData*>();
	}
};

class Scales {
	private:
		static std::map<std::string, Scales*> scales;
		static std::map<std::string, ScalePlayer*> scales_player;

		std::string full;
		std::string helf;
		std::string empty;
		std::string name;
		bool left;
		bool reset;
		bool display;
	public:
		Scales(std::string _name, std::string _full, std::string _helf, std::string _empty, bool _left, bool _reset, bool _display){
			scales.emplace(_name, this);
			name = _name;
			full = _full;
			helf = _helf;
			empty = _empty;
			left = _left;
			reset = _reset;
			display = _display;
		}

		std::string getName(){
			return name;
		}

		bool isLeft(){
			return left;
		}

		bool isReset(){
			return reset;
		}

		std::string getFull(){
			return full;
		}

		void setFull(std::string _full){
			full = _full;
		}

		std::string getHelf(){
			return helf;
		}

		void setHelf(std::string _helf){
			helf = _helf;
		}

		std::string getEmpty(){
			return empty;
		}

		void setDisplay(bool _display){
			display = _display;
		}
		bool isDisplay(){
			return display;
		}

		void setEmpty(std::string _empty){
			empty = _empty;
		}

		static bool isScale(std::string name){
			return scales.find(name) != scales.end();
		}

		static std::vector<std::string> getScales(){
			std::vector<std::string> keys;
			for(auto it = scales.begin(); it != scales.end(); ++it)
      			keys.push_back(it->first);
		
			return keys;
		}

		static std::vector<std::string> getAllPlayers(){
			std::vector<std::string> keys;
			for(auto it = scales_player.begin(); it != scales_player.end(); ++it)
      			keys.push_back(it->first);
			return keys;
		}

		static Scales* getScaleByName(std::string name){
			return scales.at(name);
		}

		static ScalesData* getPlayerScale(std::string entity, std::string name){
			if(scales_player.find(entity) == scales_player.end())
				scales_player.emplace(entity, new ScalePlayer());
			ScalePlayer* _scales = scales_player.at(entity);
			if(_scales->scales.find(name) == _scales->scales.end())
				_scales->scales.emplace(name, new ScalesData(scales.at(name)));
			return _scales->scales.at(name);
		}
};

std::map<std::string, ScalePlayer*> Scales::scales_player;
std::map<std::string, Scales*> Scales::scales;

void ScalesModule::blit(ScreenContext* ctx, float x, float y, float width, float height, std::string texture, float textureWidth, float textureHeight, float alpha, std::string m){
	mce::MaterialPtr material = mce::RenderMaterialGroup::common.getMaterial(HashedString(m.c_str()));
	float maxU = width / textureWidth;
	float maxV = height / textureHeight;
	ctx->tessellator->begin(4, false);
	ctx->tessellator->vertexUV(x, y + height, 0.0f, 0.0f, maxV);
	ctx->tessellator->vertexUV(x + width, y + height, 0.0f, maxU, maxV);
	ctx->tessellator->vertexUV(x + width, y, 0.0f, maxU, 0.0f);
	ctx->tessellator->vertexUV(x, y, 0.0f, 0.0f, 0.0f);
	ctx->shaderColor->setColor(mce::Color { 1.0f, 1.0f, 1.0f, alpha });
	RenderMesh::endTessellationAndRenderImmediately(*ctx, *ctx->tessellator, &material, texture);
	ctx->shaderColor->setColor(mce::Color { 1.0f, 1.0f, 1.0f, 1.0f });
}
void ScalesModule::initialize(){
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
	HookManager::addCallback(
		SYMBOL("mcpe", "_ZN17HudHungerRenderer6renderER24MinecraftUIRenderContextR15IClientInstanceR9UIControliR13RectangleArea"),
		LAMBDA((HudHungerRenderer* renderer, MinecraftUIRenderContext& renderContext, ClientInstance& client, UIControl& control, int someInt, RectangleArea& area), {
			Vec2* pos = control.getPosition();
			Options* options = client.getOptionsVTABLE();
			std::vector<std::string> keys = Scales::getScales();
			int y_left = 0;
			int y_right = 0;
			LocalPlayer* player = GlobalContext::getLocalPlayer();
			if(player->getAirSupply() != 300 && player->getAirSupply() >= 0)
				if(options->getUIProfile() != 0)
					y_right+=SCALE_SIZE+2;
				else
					y_right-=SCALE_SIZE+2;
			if(player->getCountArmor() > 0)
				if(options->getUIProfile() != 0)
					y_left+=SCALE_SIZE+2;
				else
					y_left-=SCALE_SIZE+2;
			for(int i = 0;i < keys.size();i++){
				std::string key = keys[i];
				ScalesData* data = Scales::getPlayerScale(player->getNameTagVTABLE(), key);
				Scales* scale = data->getScale();
				if(!scale->isDisplay())
					continue;
				int x_bonus = 0;
				int y = pos->y-SCALE_SIZE+y_right;
				if(options->getUIProfile() != 0)
					if(scale->isLeft())
						y = pos->y+SCALE_SIZE+y_left;
					else
						y = pos->y+SCALE_SIZE+y_right;
				int x = pos->x - SCALE_SIZE;

				if(scale->isLeft()){
					if(options->getUIProfile() == 0){
						x_bonus = -101;
						y = pos->y-SCALE_SIZE+y_left;
					}else{
						x = SCALE_SIZE*9+3;
						y = pos->y+SCALE_SIZE+y_left;
					}
						
				}
				int v = data->getValue();
				int fill = 0;
				if(scale->isLeft())
					fill = SCALE_MAX;
				for(int j = 0;j < 10;j++){
					std::string texture = scale->getFull();
					if(scale->isLeft()){
						if(fill - 1 == v)
							texture = scale->getHelf();
						else if(fill - 2 >= v)
							texture	= scale->getEmpty();
						fill-=2;
					}else{
						if(fill + 1 == v)
							texture = scale->getHelf();
						else if(fill + 2> v)
							texture	= scale->getEmpty();
						fill+=2;
					}
						
					ScalesModule::blit(renderContext.getScreenContext(), x + x_bonus - SCALE_SIZE*j, y, SCALE_SIZE, SCALE_SIZE, texture, SCALE_SIZE, SCALE_SIZE, options->getInterfaceOpacity(), "ui_textured_and_glcolor");
				}
				if(options->getUIProfile() == 0){
					if(scale->isLeft())
						y_left-=SCALE_SIZE;
					else
						y_right-=SCALE_SIZE;
				}else{
					if(scale->isLeft())
						y_left+=SCALE_SIZE;
					else
						y_right+=SCALE_SIZE;
				}
			}
		}, ), HookManager::RETURN | HookManager::LISTENER
	);
}

extern "C" {
	JNIEXPORT jlong JNICALL Java_com_core_api_module_Scales_registerScale
	(JNIEnv* env, jclass, jstring name, jstring full, jstring helf, jstring empty, jboolean left, jboolean reset, jboolean display) {
		return (jlong) new Scales(
			JavaClass::toString(env, name),
			JavaClass::toString(env, full),
			JavaClass::toString(env, helf),
			JavaClass::toString(env, empty),
			(bool)(left == JNI_TRUE),
			(bool)(reset == JNI_TRUE),
			(bool)(display == JNI_TRUE)
		);
	}
	JNIEXPORT jlong JNICALL Java_com_core_api_module_Scales_getScale
	(JNIEnv* env, jclass, jstring name) {
		return (jlong) Scales::getScaleByName(JavaClass::toString(env, name));
	}
	JNIEXPORT jint JNICALL Java_com_core_api_module_Scales_isScale
	(JNIEnv* env, jclass, jstring name) {
		return (jint) ((int) Scales::isScale(JavaClass::toString(env, name)));
	}
	JNIEXPORT jstring JNICALL Java_com_core_api_module_Scales_getFull
	(JNIEnv* env, jclass, jlong scale) {
		return JavaClass::toString(env, ((Scales*) scale)->getFull());
	}
	JNIEXPORT void JNICALL Java_com_core_api_module_Scales_setFull
	(JNIEnv* env, jclass, jlong scale, jstring name) {
		((Scales*) scale)->setFull(JavaClass::toString(env, name));
	}
	JNIEXPORT jstring JNICALL Java_com_core_api_module_Scales_getHelf
	(JNIEnv* env, jclass, jlong scale) {
		return JavaClass::toString(env, ((Scales*) scale)->getHelf());
	}
	JNIEXPORT void JNICALL Java_com_core_api_module_Scales_setHelf
	(JNIEnv* env, jclass, jlong scale, jstring name) {
		((Scales*) scale)->setHelf(JavaClass::toString(env, name));
	}
	JNIEXPORT jstring JNICALL Java_com_core_api_module_Scales_getEmpty
	(JNIEnv* env, jclass, jlong scale) {
		return JavaClass::toString(env, ((Scales*) scale)->getEmpty());
	}
	JNIEXPORT jint JNICALL Java_com_core_api_module_Scales_isLeft
	(JNIEnv* env, jclass, jlong scale) {
		return (jint) ((int) ((Scales*) scale)->isLeft());
	}
	JNIEXPORT jint JNICALL Java_com_core_api_module_Scales_isReset
	(JNIEnv* env, jclass, jlong scale) {
		return (jint) ((int) ((Scales*) scale)->isReset());
	}
	JNIEXPORT jint JNICALL Java_com_core_api_module_Scales_isDisplay
	(JNIEnv* env, jclass, jlong scale) {
		return (jint) ((int) ((Scales*) scale)->isDisplay());
	}
	JNIEXPORT void JNICALL Java_com_core_api_module_Scales_setDisplay
	(JNIEnv* env, jclass, jlong scale, jboolean v) {
		((Scales*) scale)->setDisplay(v == JNI_TRUE);
	}
	JNIEXPORT jstring JNICALL Java_com_core_api_module_Scales_getName
	(JNIEnv* env, jclass, jlong scale) {
		return JavaClass::toString(env, ((Scales*) scale)->getName());
	}
	JNIEXPORT void JNICALL Java_com_core_api_module_Scales_setEmpty
	(JNIEnv* env, jclass, jlong scale, jstring name) {
		((Scales*) scale)->setEmpty(JavaClass::toString(env, name));
	}
	JNIEXPORT jlong JNICALL Java_com_core_api_module_Scales_getScalePlayer
	(JNIEnv* env, jclass, jstring ent, jstring name) {
		return (jlong) Scales::getPlayerScale(JavaClass::toString(env, ent), JavaClass::toString(env, name));
	}
	JNIEXPORT void JNICALL Java_com_core_api_module_Scales_setValuePlayer
	(JNIEnv* env, jclass, jlong scale, jint value) {
		((ScalesData*) scale)->setValue((int) value);
	}
	JNIEXPORT jint JNICALL Java_com_core_api_module_Scales_getValuePlayer
	(JNIEnv* env, jclass, jlong scale) {
		return (jint) (((ScalesData*) scale)->getValue());
	}
	JNIEXPORT jlong JNICALL Java_com_core_api_module_Scales_getScaleType
	(JNIEnv* env, jclass, jlong scale) {
		return (jlong) (((ScalesData*) scale)->getScale());
	}
	JNIEXPORT void JNICALL Java_com_core_api_module_Scales_resetScale
	(JNIEnv* env, jclass, jlong scale) {
		((ScalesData*) scale)->reset();
	}
	JNIEXPORT jobjectArray JNICALL Java_com_core_api_module_Scales_getScales
	(JNIEnv* env, jclass) {
		std::vector<std::string> scales = Scales::getScales();
		jobjectArray array = env->NewObjectArray(scales.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
		for(int i = 0;i < scales.size();i++)
			env->SetObjectArrayElement(array,i,env->NewStringUTF(scales[i].c_str()));  
		return array;
	}
	JNIEXPORT jobjectArray JNICALL Java_com_core_api_module_Scales_getPlayers
	(JNIEnv* env, jclass) {
		std::vector<std::string> scales = Scales::getAllPlayers();
		jobjectArray array = env->NewObjectArray(scales.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
		for(int i = 0;i < scales.size();i++)
			env->SetObjectArrayElement(array,i,env->NewStringUTF(scales[i].c_str()));  
		return array;
	}
}
