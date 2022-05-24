#pragma once

enum UIProfile { 
    pe,classic 
};

class Options { 
    public: 
    UIProfile getUIProfile() const; 
}; 
