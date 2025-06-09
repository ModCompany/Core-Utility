#pragma once

#include <string>
#include <api/HashedString.h>
#define stl std

namespace mce {
    class UUID {
        public:
            void operator!=(mce::UUID const&)const;
            void operator<(mce::UUID const&)const; 
            void seedFromString(stl::string const&);
            mce::UUID fromString(stl::string const&);
            stl::string asString()const; 
            bool isEmpty() const; 
    };

    class Color {
        public:
            float r, g, b, a;
            static Color fromHexString(stl::string const&);
            static Color const& WHITE;
            static Color const& BLACK;
            stl::string const& toHexString() const;         
    };

    enum class PrimitiveMode : uint8_t {
	};

    class RenderMaterialGroupBase {

    };

    class MaterialPtr {
        public:
            char filler[512];
            MaterialPtr(RenderMaterialGroupBase&, HashedString const&);
            HashedString& getHashKey() const;
            HashedString& getHashedName() const;
    };

    class RenderMaterialGroup : public RenderMaterialGroupBase {
        public:
            char filer[16];
            RenderMaterialGroupBase* base;
            static RenderMaterialGroup common;
            static RenderMaterialGroup switchable;
            mce::MaterialPtr getMaterial(HashedString const&);
    };

    class TexturePtr {
        public:
            static TexturePtr NONE;
            char filler[40];
            TexturePtr(TexturePtr const&);
            TexturePtr& operator=(TexturePtr const&);
    };
}