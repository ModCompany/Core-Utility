#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <stl/string>
#define stl std::__ndk1

#include <innercore/common.h>

#include <core/Overrided.h>

OverridedItem::OverridedName::OverridedData::OverridedData(int id, std::string name){
	this->name[id] = name;
};

void OverridedItem::OverridedName::addNameForId(int id, int data, std::string name){
	if(OverridedName::isExist(id)){
		auto it = items.find(id);
		it->second.name[data] = name;
	}else{
		items.insert(std::pair<int, OverridedName::OverridedData>(id,OverridedName::OverridedData(data,name)));
	}

};

stl::string OverridedItem::OverridedName::getNameForId(int id, int data){
	auto it = items.find(id);
	return to_stl(it->second.name[data]);
	
};

bool OverridedItem::OverridedName::isExist(int id){
	if(items.count(id) > 0){
		return true;
	}else return false;
};

void OverridedItem::OverridedArmor::addArmorForId(int id,float value){
	items[id] = value;
};

float OverridedItem::OverridedArmor::getArmorForId(int id){
	return items[id];
};

bool OverridedItem::OverridedArmor::isExist(int id){
	if(items.count(id) > 0){
		return true;
	}else return false;
};

std::map<int, OverridedItem::OverridedName::OverridedData> OverridedItem::OverridedName::items;
std::map<int, float> OverridedItem::OverridedArmor::items;
