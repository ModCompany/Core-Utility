#pragma once
#include <jni.h>
#include <vector>
#include <string>
#include <client/ui/ScreenContext.h>

class Element {
    public:
        int x, y;
        virtual void render(ScreenContext&) = 0;
};

class ElementImage : public Element {
    public:
        int w, h;
        std::string texture;
        virtual void render(ScreenContext&) override;
};

class NativeUi {
    private:
        std::vector<Element*> elements;
        bool _open;
        static std::vector<NativeUi*> opens; 
    public:
        static jclass JavaElement, JavaImageElement;
        static jmethodID getTypeElement, getXElement, getYElement, getWidthElement, getHeigthElement, getTextureElement;
        static void init();
        static void render(ScreenContext&);
        static void open(NativeUi*);
        static void close(NativeUi*);

        
        NativeUi();
        ~NativeUi();
        void setElements(std::vector<Element*> elements);
        bool isOpen() const;
};