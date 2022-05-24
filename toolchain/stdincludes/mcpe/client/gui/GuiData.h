#pragma once

#include <stl/string.h>
#define stl std::__ndk1

class GuiData {
public:
    void displayClientMessage(stl::string const&);
    void showTipMessage(stl::string const&);
    void setNowPlaying(stl::string const&);
    void displaySystemMessage(stl::string const&);
};

