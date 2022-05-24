#pragma once

class AttributeInstance {   
    public:
    char filler[76-0]; // 0
    float value; // 76
    float getMaxValue() const;
    void setMaxValue(float);
    
};
