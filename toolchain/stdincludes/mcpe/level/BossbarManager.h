#pragma once

#include <type/Json.h>

#include <string.h>
#define stl std

class BossbarManager {
    public:
    void add(stl::string const&, Json::Value const&);
    void remove(stl::string const&);
};