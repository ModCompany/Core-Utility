#pragma once
#include <jni.h>
#include <vector>
#include <string>
#include <client/ui/ScreenContext.h>
#include <client/ui/Font.h>

class Element {
    public:
        float x, y;
        std::string material;
        virtual void render(ScreenContext&) = 0;
};

class ElementImage : public Element {
    public:
        int w, h, t_w, t_h;
        std::string texture;
        virtual void render(ScreenContext&) override;
};

class ElementFont : public Element {
    public:
        int size, font_type, shadow_offset;
        bool isShadow;
        std::string text;
        virtual void render(ScreenContext&) override;
};

class ElementMesh : public Element {
    public:
        float z;
        std::string texture;
        RenderMesh* mesh;
        virtual void render(ScreenContext&) override;
};

class NativeUi {
    private:
        std::vector<Element*> elements;
        bool _open;
        static std::vector<NativeUi*> opens; 
        jobject self;
    public:
        static std::vector<Font*> fonts;
        static jclass JavaElement, JavaImageElement, JavaTextElement, JavaNativeUi, JavaMeshElement;
        static jmethodID getZElement, getTextureMeshElement, getMeshElement, touchUi, getTypeElement, getMaterialElement, getXElement, getYElement, getWidthElement, getHeigthElement, getTextureElement, getTextureHeigthElement, getTextureWidthElement, getSizeElement, getTextElement, getFontTypeElement, getShadowOffsetElement, isShadowElement;
        static void init();
        static void render(ScreenContext&);
        static bool touch(int type, float x, float y, int i1, bool b1, bool b2, bool b3);
        static void open(NativeUi*);
        static void close(NativeUi*);

        
        NativeUi(jobject);
        ~NativeUi();
        void setElements(std::vector<Element*> elements);
        bool isOpen() const;
};