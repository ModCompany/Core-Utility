#pragma once

#include <stl/string>
#include <horizon/types.h>
#include <mce.h>
#include <ui/Tessellator.h>
#include <client/ui/ScreenContext.h>

#define stl std::__ndk1
//ItemFrameRenderer::extractText
/*
class BaseActorRenderer {
: public ActorShaderManager
    public:
        //Fields
        char filler_BaseActorRenderer[UNKNOW_SIZE];
    public:
        //Virtual Tables
        virtual ~BaseActorRenderer();// _ZN17BaseActorRendererD2Ev
        virtual ~BaseActorRenderer();// _ZN17BaseActorRendererD0Ev
        public:
        //Methods
        BaseActorRenderer();// _ZN17BaseActorRendererC1Ev
        void _extractRenderTextObject(Tessellator&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, int, Vec3 const&, mce::Color const&, mce::MaterialPtr*, mce::MaterialPtr*, mce::Color const&);// _ZN17BaseActorRenderer24_extractRenderTextObjectER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK4Vec3RKN3mce5ColorEPNSE_11MaterialPtrESJ_SH_
        void extractRenderTextObjects(Tessellator&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, int, Vec3 const&, mce::Color const&, bool);// _ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK4Vec3RKN3mce5ColorEb

        void _extractRenderTextObject(Tessellator&, stl::string const&, stl::vector<int> const&, Vec3 const&, mce::Color const&, mce::MaterialPtr*, mce::MaterialPtr*, mce::Color const&);// _ZN17BaseActorRenderer24_extractRenderTextObjectER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEPNSJ_11MaterialPtrESO_SM_
        void extractRenderTextObjects(Tessellator&, stl::string const&, stl::vector<int> const&, Vec3 const&, mce::Color const&, bool);// _ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEb

        void getDepthTestedNameTagMat();// _ZN17BaseActorRenderer24getDepthTestedNameTagMatEv
        
        
        void getDepthTestedNameTextMat();// _ZN17BaseActorRenderer25getDepthTestedNameTextMatEv
        void renderText(ScreenContext&, ViewRenderData const&, NameTagRenderObject const&, Font&);// _ZN17BaseActorRenderer10renderTextER13ScreenContextRK14ViewRenderDataRK19NameTagRenderObjectR4Font
        public:
        //Objects
        static BaseActorRenderer * NAME_TAG_COLOR;// _ZN17BaseActorRenderer14NAME_TAG_COLORE
};//BaseActorRenderer
*/
class ActorShaderManager {
    public:
        ActorShaderManager();
};
class ViewRenderObject {
    public:
};

class ViewRenderData {
    public:
};

class Font {

};

class NameTagRenderObject;

class BaseActorRenderer : public ActorShaderManager {
    public:
        BaseActorRenderer();
        void _extractRenderTextObject(Tessellator&, stl::string const&, int, Vec3 const&, mce::Color const&, mce::MaterialPtr *, mce::MaterialPtr *, mce::Color const&);

        void* extractRenderTextObjects(Tessellator&, stl::string const&, int, Vec3 const&, mce::Color const&, bool);
        void* extractRenderTextObjects(Tessellator&, stl::string const&, stl::vector<int> const&, Vec3 const&, mce::Color const&, bool);

        static void renderText(ScreenContext&, ViewRenderData const&, NameTagRenderObject const&, Font&);

        static mce::Color const& NAME_TAG_COLOR;
};
class NameTagRenderObject : public BaseActorRenderer {
    public:
};