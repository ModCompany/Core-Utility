#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <string>
#define stl std

#include <innercore/common.h>

#include <mce.h>
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

OverridedItem::OverridedColor::OverridedData::OverridedData(int id,mce::Color color){
	this->colors[id] = color;
}

void OverridedItem::OverridedColor::addColorForId(int id,int data,mce::Color color){
	if(OverridedColor::isExist(id)){
		auto it = items.find(id);
		it->second.colors[data] = color;
	}else{
		items.insert(std::pair<int, OverridedColor::OverridedData>(id,OverridedColor::OverridedData(data,color)));
	}
}

bool OverridedItem::OverridedColor::isExist(int id){
	if(items.count(id) > 0){
		return true;
	}else return false;
}

mce::Color OverridedItem::OverridedColor::getColor(int id,int data){
	auto it = items.find(id);
	return it->second.colors[data];
}

std::map<int, float> OverridedItem::OverridedArmor::items;
std::map<int, OverridedItem::OverridedName::OverridedData> OverridedItem::OverridedName::items;
std::map<int,OverridedItem::OverridedColor::OverridedData> OverridedItem::OverridedColor::items;