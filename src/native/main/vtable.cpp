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

#include "shared_headers/VtableHelper.h"
#include "shared_headers/OverridedName.h"

VtableHelper::VtableHelper(void* a){
		original = a;
		vtable = *(void***) a;
};

void** VtableHelper::get(){
		return vtable;
};

void VtableHelper::resize(){
		const int new_size = 512;
		const int offset = 4;
		void** vtable_old = this->vtable;
		vtable = (void**) malloc((new_size + offset) * sizeof(void*));
		memcpy(this->vtable, vtable_old - offset, (new_size + offset) * sizeof(void*));
		this->vtable += offset;
		*(void***) this->original = vtable;
}	

void VtableHelper::patch(const char* table, const char* symbol, void* func){
		int index = getVtableOffset(table, symbol);
		this->get()[index] = func;
};

void* VtableHelper::getAdreess(const char* table, const char* symbol){
		return SYMBOL(table, symbol);
};

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

