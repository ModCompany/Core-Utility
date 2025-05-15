#pragma once

#include <type/Json.h>
#include <string>

#define stl std
class FlatWorldOverrided {
    public:
    Json::Value value;
    bool overrided = false;
    FlatWorldOverrided(char const* json){
        value = Json::Value(Json::StaticString(json));
        overrided = true;
    }

    operator Json::Value const() {
        return value;
    }
};