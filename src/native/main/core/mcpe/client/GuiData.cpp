#include <innercore_callbacks.h>
#include <java.h>
#include <nativejs.h>



#include <core/JavaClass.h>
#include <client/ClientIntance.h>
#include <client/gui/GuiData.h>
#include <innercore/global_context.h>

export(void, mcpe_client_GuiData_setTitle,jlong pointer,jstring title){
    return ((GuiData*) pointer)->setTitle(JavaClass::toStlString(env,title));
}

export(void, mcpe_client_GuiData_setSubtitle,jlong pointer,jstring title){
    return ((GuiData*) pointer)->setSubtitle(JavaClass::toStlString(env,title));    
}

export(void, mcpe_client_GuiData_setActionMessage,jlong pointer,jstring message){
    return ((GuiData*) pointer)->setActionBarMessage(JavaClass::toStlString(env,message));    

}

