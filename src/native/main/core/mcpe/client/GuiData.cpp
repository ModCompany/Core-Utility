#include <innercore_callbacks.h>
#include <java.h>
#include <nativejs.h>



#include <core/JavaClass.h>
#include <client/ClientIntance.h>
#include <client/gui/GuiData.h>
#include <innercore/global_context.h>

export(void, mcpe_client_GuiData_setGuiScale,jlong pointer,jfloat value){
    ((GuiData*) pointer)->setGuiScale((float) value);
}

export(jfloat, mcpe_client_GuiData_getGuiScale,jlong pointer){
    return (jfloat) ((GuiData*) pointer)->getGuiScale();
}

export(jfloat, mcpe_client_GuiData_getWindowWidth,jlong pointer){
    GuiData* data = (GuiData*) pointer;
    return data->getScreenSizeData()->x / data->getGuiScale();
}

export(jfloat, mcpe_client_GuiData_getWindowHeigth,jlong pointer){
    GuiData* data = (GuiData*) pointer;
    return data->getScreenSizeData()->y / data->getGuiScale();
}

export(jfloat, mcpe_client_GuiData_getDisplayWidth,jlong pointer){
    GuiData* data = (GuiData*) pointer;
    return data->getScreenSizeData()->x;
}

export(jfloat, mcpe_client_GuiData_getDisplayHeigth,jlong pointer){
    GuiData* data = (GuiData*) pointer;
    return data->getScreenSizeData()->y;
}

export(void, mcpe_client_GuiData_setTitle,jlong pointer,jstring title){
    return ((GuiData*) pointer)->setTitle(JavaClass::toStlString(env,title));
}

export(void, mcpe_client_GuiData_setSubtitle,jlong pointer,jstring title){
    return ((GuiData*) pointer)->setSubtitle(JavaClass::toStlString(env,title));    
}

export(void, mcpe_client_GuiData_setActionMessage,jlong pointer,jstring message){
    return ((GuiData*) pointer)->setActionBarMessage(JavaClass::toStlString(env,message));    

}

