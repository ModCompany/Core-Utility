#pragma once
 
#include <stl/string>
#include <mce.h>

class ScreenContext;

class Font {
    public:
        void draw(ScreenContext&, std::__ndk1::string const&, float, float, mce::Color const&, bool, mce::MaterialPtr*, int, float);
        void drawShadow(ScreenContext&, std::__ndk1::string const&,float,float,mce::Color const&,bool,mce::MaterialPtr*,float);
        float getBaseFontHeight() const;
};

class FontRepository {
    public:

};

class FontHandle {
    public:
    Font* getFont() const;
};