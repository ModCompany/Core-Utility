#pragma once

#include <string>

class HashedString {
    public:
        HashedString(char const*);
        std::string const& getString() const;
        char const* c_str() const;
};