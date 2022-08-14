#include <core/module/ui/NativeUi.h>
#include <java.h>
#include <innercore_callbacks.h>
#include <core/JavaClass.h>
#include <hook.h>
#include <symbol.h>
#include <core/VtableHelper.h>
#include <core/scales.h>

std::vector<NativeUi*> NativeUi::opens;
jclass NativeUi::JavaElement, NativeUi::JavaImageElement;
jmethodID NativeUi::getTypeElement, NativeUi::getXElement, NativeUi::getYElement, NativeUi::getWidthElement, NativeUi::getHeigthElement, NativeUi::getTextureElement;

void ElementImage::render(ScreenContext& ctx){
    ScalesModule::blit(&ctx, x, y, w, h, texture, w, h, 1);
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
void NativeUi::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        NativeUi::JavaElement = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/ui/types/Element")));
        NativeUi::getTypeElement = env->GetMethodID(NativeUi::JavaElement, "getType", "()Ljava/lang/String;");
        NativeUi::getXElement = env->GetMethodID(NativeUi::JavaElement, "getX", "()I");
        NativeUi::getYElement = env->GetMethodID(NativeUi::JavaElement, "getY", "()I");

        NativeUi::JavaImageElement = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/engine/ui/types/ImageElement")));
        NativeUi::getWidthElement = env->GetMethodID(NativeUi::JavaImageElement, "getWidth", "()I");
        NativeUi::getHeigthElement = env->GetMethodID(NativeUi::JavaImageElement, "getHeigth", "()I");
        NativeUi::getTextureElement = env->GetMethodID(NativeUi::JavaImageElement, "getTexture", "()Ljava/lang/String;");
       
        HookManager::addCallback(
            SYMBOL("mcpe", "_ZN19ScreenContextHelper30makeScreenContextAlphaOverrideER13ScreenContextf"), 
            LAMBDA((void* self, ScreenContext& ctx), {
                Logger::debug("Test-pre", "NativeUi::render");
                NativeUi::render(ctx);
                Logger::debug("Test-post", "NativeUi::render");
            }, ), HookManager::RETURN | HookManager::LISTENER
        );
    }
}

export(jlong,engine_ui_NativeUi_init, jobjectArray arr) {
    int size = env->GetArrayLength(arr);
    std::vector<Element*> elements;
    for(int i = 0;i < size;i++){
        jobject object = env->GetObjectArrayElement(arr, i);
        std::string type = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getTypeElement));
        if(type == "image"){
            ElementImage* element = new ElementImage();
            element->h = (int) env->CallIntMethod(object, NativeUi::getXElement);
            element->y = (int) env->CallIntMethod(object, NativeUi::getYElement);
            element->w = (int) env->CallIntMethod(object, NativeUi::getWidthElement);
            element->h = (int) env->CallIntMethod(object, NativeUi::getTextureElement);
            element->texture = JavaClass::toString(env, (jstring) env->CallObjectMethod(object, NativeUi::getTextureElement));
            elements.push_back(element);
        }
    }
    NativeUi* ui = new NativeUi();
    ui->setElements(elements);
    return (jlong) ui;
}
export(jboolean,engine_ui_NativeUi_isOpen, jlong ptr) {
    return ((NativeUi*) ptr)->isOpen() ? JNI_TRUE : JNI_FALSE;
}
export(void,engine_ui_NativeUi_open, jlong ptr) {
    NativeUi::open((NativeUi*) ptr);
}

export(void,engine_ui_NativeUi_close, jlong ptr) {
    NativeUi::close((NativeUi*) ptr);
}