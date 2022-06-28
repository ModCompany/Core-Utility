#pragma once

struct ToolTip {
    public:
        int id, data;
        static std::vector<int> items_dynamic;
        static std::map<ToolTip*, std::vector<std::string>> tool_tips;
        ToolTip(int id, int data): id(id), data(data){}
        
        static std::vector<std::string> get(ToolTip* key);
        static std::vector<std::string> get(int id, int data);
        static void addToolTip(int id, int data, std::string name);
        static void clearToolTips();
        static void clearToolTip(int id, int data);
        static void init();
};