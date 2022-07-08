#pragma once
#include <mce.h>
class OverridedItem {
	public:
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
	class OverridedArmor {
		public:
		static std::map<int, float> items;
		static void addArmorForId(int,float);
		static float getArmorForId(int);
		static bool isExist(int);
	};
	class OverridedColor {
		public:
		class OverridedData {
			public:
			std::map<int,mce::Color> colors;
			OverridedData(int,mce::Color);
		};
		static std::map<int, OverridedColor::OverridedData> items;
		static void addColorForId(int,int,mce::Color);
		static mce::Color getColor(int,int);
		static bool isExist(int);
	};
};



