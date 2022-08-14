#pragma once

#include <stl/string>
#include <api/HashedString.h>
#define stl std::__ndk1

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
            Color fromHexString(stl::string const&);
            static Color const& WHITE;
            static Color const& BLACK;
            stl::string const& toHexString() const;         
    };

    class MaterialPtr {
        public:
            char filler[8];
            HashedString& getHashKey() const;
            HashedString& getHashedName() const;
    };

    class RenderMaterialGroup {
        public:
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