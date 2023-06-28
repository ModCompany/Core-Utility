#pragma once

#include <mod.h>

class ScreenContext;

class ScalesModule {
    public:
        static void blit(ScreenContext* ctx, float x, float y, float width, float height, std::string texture, float textureWidth, float textureHeight, float alpha, std::string);
        static void initialize();
};