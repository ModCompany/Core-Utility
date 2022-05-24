#pragma once

class OverridedName {
	public:
	static std::map<int, std::string> names;
	static void addNameForId(int id, std::string name);
	static stl::string getNameForId(int id);
	static bool isExist(int id);
};


