#pragma once
 
#include <stl/string>
#include <mce.h>

class ScreenContext;

class Font {
    public:
        void draw(ScreenContext&, stl::string const&, float, float, mce::Color const&, bool, mce::MaterialPtr*, int, float);
        void drawShadow(ScreenContext&, stl::string const&,float,float,mce::Color const&,bool,mce::MaterialPtr*,float);
        float getBaseFontHeight() const;
        float getTextHeight(stl::string const&, float);
        void calculateTextWidths(stl::string const&, stl::vector<int>&);
};

class FontRepository {
    public:

};

class FontHandle {
    public:
        FontHandle();
        Font* getFont() const;
};