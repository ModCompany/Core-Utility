#pragma once

#include <mod.h>

class ScreenContext;

class ScalesModule : public Module {
    public:
        ScalesModule(): Module("core_utility.Scales") {};
        static void blit(ScreenContext* ctx, float x, float y, float width, float height, std::string texture, float textureWidth, float textureHeight, float alpha);
        virtual void initialize();
};