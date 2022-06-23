#pragma once
#include <mce.h>

class Tessellator {
    public:
        mce::MaterialPtr& material;
        void triggerIntercept(mce::MaterialPtr const&, mce::TexturePtr const&);
};