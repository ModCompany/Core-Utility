#pragma once

#include <mce.h>
#include <horizon/types.h>
#include <string>

class ShaderColor {
    public:
    void makeClean() const;
    mce::Color* getColor() const;
    bool isDirty() const;
    void setColor(mce::Color const&);
};

#include <ui/Tessellator.h>

class ScreenContext {
    public:
        char filler1[48];
        ShaderColor* shaderColor;

        inline Tessellator* getTessellator() {
            return (*(Tessellator**)((unsigned char *) (this) + 176));
        }
};

class RenderMesh {
    public:
        void prepareForRender();
        void rebuildNormals();
        void translate(float, float, float);
        void* tessellate(Tessellator&, Vec3, mce::Color const&, bool, bool, bool);
        static void endTessellationAndRenderImmediately(ScreenContext&, Tessellator&, void*, std::string const&);
        void* renderImmediatelyNoCache(ScreenContext&, Tessellator&, void*, std::string const&, Vec3, mce::Color const&, bool, bool, bool);
};