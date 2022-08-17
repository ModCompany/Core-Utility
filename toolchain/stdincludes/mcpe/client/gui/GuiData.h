#pragma once

#include <stl/string.h>
#include <horizon/types.h>
#define stl std::__ndk1

class GuiData {
public:
    void displayClientMessage(stl::string const&);
    void showTipMessage(stl::string const&);
    void displaySystemMessage(stl::string const&);
    void setTitle(stl::string const&);
    void setSubtitle(stl::string const&);
    void setFilteredText(stl::string const&);
    void setActionBarMessage(stl::string const&);
    Vec2* getScreenSizeData() const;
    float getGuiScale() const;
    float setGuiScale(float);
};

