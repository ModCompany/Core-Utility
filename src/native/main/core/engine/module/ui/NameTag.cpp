#include <core/module/ui/NameTag.hpp>
#include <client/ui/NameTagRender.hpp>
#include <hook.h>
#include <symbol.h>
#include <logger.h>
#include <nativejs.h>
#include <vector>

float _x = 0, _y = 0, _z = 0;
void* _hz;
void* _base;
const mce::Color* color;
const Vec3* pos;

void NameTagAPI::render(ScreenContext& ctx){
    if(_x != 0){
        BaseActorRenderer base;
        auto a = (void(*)(BaseActorRenderer*, void*, Tessellator&, stl::string, stl::vector<int>, const Vec3&, const mce::Color&, bool)) SYMBOL("mcpe", "_ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEb");
        const Vec3 v1 = *pos; const mce::Color v2 = *color;
        //a(&base,nullptr,*ctx.tessellator, stl::string("Белевич где двери"), stl::vector<int>({34}), v1, v2, false);
        //BaseActorRenderer base;
        //base.extractRenderTextObjects(*ctx.tessellator, stl::string("Белевич где двери"), stl::vector<int>({34}), *pos, *color, false);
        //base.extractRenderTextObjects(*ctx.tessellator, stl::string("Test NameTag"), 1, Vec3(_x, _y, _z), mce::Color::WHITE, true);
    }
}


JS_EXPORT(HelperCoreUtility, renderNameTag, "V(FFF)", (float x, float y, float z){
    _x = x;
    _y = y;
    _z = z;
});



void NameTagAPI::init(){
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRendererD2Ev"),
        LAMBDA((void* self),{
            Logger::debug("BaseActorRenderer", "_ZN17BaseActorRendererD2Ev");
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRendererD0Ev"),
        LAMBDA((void* self),{
            Logger::debug("BaseActorRenderer", "_ZN17BaseActorRendererD0Ev");
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRendererC1Ev"),
        LAMBDA((void* self),{
            Logger::debug("BaseActorRenderer", "_ZN17BaseActorRendererC1Ev");
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRenderer24_extractRenderTextObjectER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK4Vec3RKN3mce5ColorEPNSE_11MaterialPtrESJ_SH_"),
        LAMBDA((void* self, Tessellator&, stl::string const& text, int v1, Vec3 const&, mce::Color const&),{
            Logger::debug("BaseActorRenderer", "_extractRenderTextObject %s %i", text.c_str(), v1);
        },),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK4Vec3RKN3mce5ColorEb"),
        LAMBDA((void* self, Tessellator&, stl::string const& text, int v1, Vec3 const&, mce::Color const&, bool v2),{
            Logger::debug("BaseActorRenderer", "extractRenderTextObjects %s %i %i", text.c_str(), v1, v2);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRenderer24_extractRenderTextObjectER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEPNSJ_11MaterialPtrESO_SM_"),
        LAMBDA((void* self, int, Tessellator&, stl::string const& text, stl::vector<int> const& arr, Vec3 const&, mce::Color const&, mce::MaterialPtr*, mce::MaterialPtr*, mce::Color const&),{
            Logger::debug("CE", "hook");
            Logger::debug("BaseActorRenderer", "_extractRenderTextObject2 %s %i", text.c_str(), arr.size());
            for(int i = 0;i < arr.size();i++)
                Logger::debug("vector", "%i", arr[i]);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN19LevelRendererPlayer14renderNameTagsER13ScreenContextRK14ViewRenderDataRK29NameTagRenderObjectCollectionR4Font"),
        LAMBDA((ScreenContext& ctx, ViewRenderData const& view, void*, Font& font),{
            if(_x == 0) return;
            BaseActorRenderer base;
            //auto a = (void(*)(void*, void*, Tessellator&, stl::string, stl::vector<int>, const Vec3&, const mce::Color&, bool)) SYMBOL("mcpe", "_ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEb");
            //a(&base,nullptr, *ctx.tessellator, stl::string("ArtemOn где текстуры"), stl::vector<int>({34}), Vec3(_x, _y, _z), *color, false);
           // BaseActorRenderer::renderText(ctx, view, base, font);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEb"),
        LAMBDA((HookManager::CallbackController* ctr, BaseActorRenderer* self, void* hz, Tessellator& tes, stl::string const& text, stl::vector<int> const& arr, Vec3 const& pos_, mce::Color const& color_, bool v),{
            stl::string res = stl::string("Белевич где двери");
            if(text != res){
                auto a = (void(*)(void*, void*, Tessellator&, stl::string, stl::vector<int>, const Vec3&, const mce::Color&, bool)) SYMBOL("mcpe", "_ZN17BaseActorRenderer24extractRenderTextObjectsER11TessellatorRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS2_6vectorIiNS6_IiEEEERK4Vec3RKN3mce5ColorEb");
                a(self,hz,tes, res, stl::vector<int>({34}), Vec3(pos_.x, pos_.y+2, pos_.z), color_, false);
                ctr->replace();
            }
            _base = self;
            _hz = hz;
            color = &color_;
            pos = &pos_;
            Logger::debug("CE", "hook");
            Logger::debug("BaseActorRenderer", "extractRenderTextObjects2 hz: %p %p, string: %s, size: %i, bool: %i %p",self, hz, text.c_str(), arr.size(), v, color);
            for(int i = 0;i < arr.size();i++)
                Logger::debug("vector", "%i", arr[i]);
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
    );
}