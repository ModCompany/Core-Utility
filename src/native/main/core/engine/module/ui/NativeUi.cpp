#include <core/module/ui/NativeUi.h>
#include <java.h>
#include <innercore_callbacks.h>
#include <core/JavaClass.h>
#include <hook.h>
#include <symbol.h>
#include <core/VtableHelper.h>
#include <core/scales.h>
#include <logger.h>

std::vector<NativeUi*> NativeUi::opens;
jclass NativeUi::JavaElement, NativeUi::JavaImageElement, NativeUi::JavaTextElement;
std::vector<Font*> NativeUi::fonts;
jmethodID NativeUi::getTypeElement, NativeUi::getMaterialElement, NativeUi::getXElement, NativeUi::getYElement, NativeUi::getWidthElement, NativeUi::getHeigthElement, NativeUi::getTextureElement, NativeUi::getTextureHeigthElement, NativeUi::getTextureWidthElement, NativeUi::getSizeElement, NativeUi::getTextElement, NativeUi::getFontTypeElement, NativeUi::getShadowOffsetElement, NativeUi::isShadowElement;

void ElementImage::render(ScreenContext& ctx){
    ScalesModule::blit(&ctx, x, y, w, h, texture, t_w, t_h, 1, material);
}

void ElementFont::render(ScreenContext& ctx){
    //mce::MaterialPtr material = mce::RenderMaterialGroup::common.getMaterial(HashedString(this->material.c_str()));
    ctx.shaderColor->setColor(mce::Color { 1.0f, 1.0f, 1.0f, 1.0f });
    Font* font;
    if(font_type < NativeUi::fonts.size())
        font = NativeUi::fonts[font_type];
    else
        font = NativeUi::fonts[NativeUi::fonts.size() - 1];
    if(isShadow)
        font->drawShadow(ctx, std::__ndk1::string(text.c_str()), x + shadow_offset, y + shadow_offset, {0, 0, 0, 1}, true, nullptr, 0); //А это тень :/
    font->draw(ctx, std::__ndk1::string(text.c_str()), x, y, {1, 1, 1, 1}, true, nullptr, -size, 0); //0 это расстояние между строк оказывается :D, окей спасибо

}


NativeUi::NativeUi(){
    _open = false;
}

NativeUi::~NativeUi(){

}

void NativeUi::setElements(std::vector<Element*> elements){
    this->elements = elements;
}

void NativeUi::render(ScreenContext& ctx){
    for(int i = 0;i < opens.size();i++)
        for(int a = 0;a < opens[i]->elements.size();a++)
            opens[i]->elements[a]->render(ctx);
}

bool NativeUi::isOpen() const {
    return this->_open;
}

void NativeUi::open(NativeUi* ui){
    ui->_open = true;
    opens.push_back(ui);
}

void NativeUi::close(NativeUi* ui){
    ui->_open = false;
    for(int i = 0;i < opens.size();i++){
        NativeUi* obj = opens[i];
        if(obj == ui){
            opens.erase(opens.begin() + i);
            return;
        }
    }
}
#include <logger.h>
#include <client/ui/ResourceLocation.h>
void NativeUi::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        NativeUi::JavaElement = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/ui/types/Element")));
        NativeUi::getTypeElement = env->GetMethodID(NativeUi::JavaElement, "getType", "()Ljava/lang/String;");
        NativeUi::getMaterialElement = env->GetMethodID(NativeUi::JavaElement, "getMaterial", "()Ljava/lang/String;");
        NativeUi::getXElement = env->GetMethodID(NativeUi::JavaElement, "getX", "()F");
        NativeUi::getYElement = env->GetMethodID(NativeUi::JavaElement, "getY", "()F");

        NativeUi::JavaImageElement = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/ui/types/ImageElement")));
        NativeUi::getWidthElement = env->GetMethodID(NativeUi::JavaImageElement, "getWidth", "()I");
        NativeUi::getHeigthElement = env->GetMethodID(NativeUi::JavaImageElement, "getHeigth", "()I");
        NativeUi::getTextureElement = env->GetMethodID(NativeUi::JavaImageElement, "getTexture", "()Ljava/lang/String;");
        NativeUi::getTextureWidthElement = env->GetMethodID(NativeUi::JavaImageElement, "getTextureWidth", "()I");
        NativeUi::getTextureHeigthElement = env->GetMethodID(NativeUi::JavaImageElement, "getTextureHeigth", "()I");

        NativeUi::JavaTextElement = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/ui/types/TextElement")));
        NativeUi::getSizeElement = env->GetMethodID(NativeUi::JavaTextElement, "getSize", "()I");
        NativeUi::getFontTypeElement = env->GetMethodID(NativeUi::JavaTextElement, "getFontType", "()I");
        NativeUi::getShadowOffsetElement = env->GetMethodID(NativeUi::JavaTextElement, "getShadowOffset", "()I");
        NativeUi::isShadowElement = env->GetMethodID(NativeUi::JavaTextElement, "isShadow", "()Z");
        NativeUi::getTextElement = env->GetMethodID(NativeUi::JavaTextElement, "getText", "()Ljava/lang/String;");
        
        HookManager::addCallback(
            SYMBOL("mcpe", "_ZN3mce11RenderGraph6renderER13ScreenContextRK17FrameRenderObject"), 
            LAMBDA((void* self, ScreenContext& ctx), {
                NativeUi::render(ctx);
            }, ), HookManager::RETURN | HookManager::LISTENER
        );
        HookManager::addCallback(
            SYMBOL("mcpe", "_ZN4FontC2ERN3mce12TextureGroupE"), 
            LAMBDA((Font* self), {
                NativeUi::fonts.push_back(self);
            }, ), HookManager::RETURN | HookManager::LISTENER
        );
    }
}

std::vector<Element*> getElements(JNIEnv* env, jobjectArray arr){
    int size = env->GetArrayLength(arr);
    std::vector<Element*> elements;
    for(int i = 0;i < size;i++){
        jobject object = env->GetObjectArrayElement(arr, i);
        std::string type = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getTypeElement));
        if(type == "image"){
            ElementImage* element = new ElementImage();
            element->x = (float) env->CallFloatMethod(object, NativeUi::getXElement);
            element->y = (float) env->CallFloatMethod(object, NativeUi::getYElement);
            element->w = (int) env->CallIntMethod(object, NativeUi::getWidthElement);
            element->h = (int) env->CallIntMethod(object, NativeUi::getHeigthElement);
            element->t_w = (int) env->CallIntMethod(object, NativeUi::getTextureWidthElement);
            element->t_h = (int) env->CallIntMethod(object, NativeUi::getTextureHeigthElement);
            element->texture = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getTextureElement));
            element->material = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getMaterialElement));
            elements.push_back(element);
        }else if(type == "text"){
            ElementFont* element = new ElementFont();
            element->x = (float) env->CallFloatMethod(object, NativeUi::getXElement);
            element->y = (float) env->CallFloatMethod(object, NativeUi::getYElement);
            element->size = (int) env->CallIntMethod(object, NativeUi::getSizeElement);
            element->text = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getTextElement));
            element->material = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getMaterialElement));
            element->isShadow = env->CallBooleanMethod(object, NativeUi::isShadowElement) == JNI_TRUE;
            element->shadow_offset = (int) env->CallIntMethod(object, NativeUi::getShadowOffsetElement);
            element->font_type = (int) env->CallIntMethod(object, NativeUi::getFontTypeElement);
            elements.push_back(element);
        }
    }
    return elements;
}

export(jlong,engine_ui_NativeUi_init, jobjectArray arr) {
    NativeUi* ui = new NativeUi();
    ui->setElements(getElements(env, arr));
    return (jlong) ui;
}
export(jboolean,engine_ui_NativeUi_isOpen, jlong ptr) {
    return ((NativeUi*) ptr)->isOpen() ? JNI_TRUE : JNI_FALSE;
}
export(void,engine_ui_NativeUi_open, jlong ptr) {
    NativeUi::open((NativeUi*) ptr);
}

export(void,engine_ui_NativeUi_setElements, jlong ptr, jobjectArray arr) {
    ((NativeUi*) ptr)->setElements(getElements(env, arr));
}

export(void,engine_ui_NativeUi_free, jlong ptr) {
    ((NativeUi*) ptr)->~NativeUi();
}

export(void,engine_ui_NativeUi_close, jlong ptr) {
    NativeUi::close((NativeUi*) ptr);
}

