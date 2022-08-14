#pragma once
#include <jni.h>
#include <vector>
#include <string>
#include <client/ui/ScreenContext.h>
#include <client/ui/Font.h>

class Element {
    public:
        int x, y;
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
        int size;
        std::string text;
        virtual void render(ScreenContext&) override;
};

class NativeUi {
    private:
        std::vector<Element*> elements;
        bool _open;
        static std::vector<NativeUi*> opens; 
    public:
        static Font* font;
        static jclass JavaElement, JavaImageElement, JavaTextElement;
        static jmethodID getTypeElement, getMaterialElement, getXElement, getYElement, getWidthElement, getHeigthElement, getTextureElement, getTextureHeigthElement, getTextureWidthElement, getSizeElement, getTextElement;
        static void init();
        static void render(ScreenContext&);
        static void open(NativeUi*);
        static void close(NativeUi*);

        
        NativeUi();
        ~NativeUi();
        void setElements(std::vector<Element*> elements);
        bool isOpen() const;
};