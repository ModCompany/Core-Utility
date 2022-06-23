#pragma once

class HashedString {
    public:
        HashedString(char const*);
        char const* c_str() const;
};