#pragma once
 
#include <stl/string>
#include <mce.h>

class ScreenContext;

class Font {
    public:
        void draw(ScreenContext&, std::__ndk1::string const&, float, float, mce::Color const&, bool, mce::MaterialPtr*, int, float);
};