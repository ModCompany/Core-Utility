#pragma once

enum UIProfile { 
    pe,classic 
};
enum DebugHudOptions {};

class Options { 
    public: 
    UIProfile getUIProfile() const; 
    void setDevRenderMobInfoState(bool);
    void setDevRenderBoundingBoxes(bool);
    void setDevRenderPaths(bool);
    void setRenderDebug(DebugHudOptions);
}; 
