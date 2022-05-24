#pragma once

#include <type/Json.h>

#include <stl/string.h>
#define stl std::__ndk1

class BossbarManager {
    public:
    void add(stl::string const&, Json::Value const&);
    void remove(stl::string const&);
};