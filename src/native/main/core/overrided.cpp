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

#include <core/OverridedName.h>

void OverridedName::addNameForId(int id, std::string name){
	names[id] = name;
};

stl::string OverridedName::getNameForId(int id){
	return to_stl(names[id]);
};

bool OverridedName::isExist(int id){
	if(names.count(id) > 0){
		return true;
	}else return false;
};

std::map<int, std::string> OverridedName::names;
