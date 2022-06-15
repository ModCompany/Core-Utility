#pragma once


class OverridedName {
	public:
	class OverridedData {
		public:
		std::map<int, std::string> name;
		OverridedData(int, std::string);
	};
	static std::map<int, OverridedName::OverridedData> items;
	static void addNameForId(int, int, std::string);
	static stl::string getNameForId(int, int);
	static bool isExist(int);
};


