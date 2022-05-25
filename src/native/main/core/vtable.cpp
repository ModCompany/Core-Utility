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

#include <core/VtableHelper.h>

VtableHelper::VtableHelper(void* a){
	original = a;
	vtable = *(void***) a;
};

void** VtableHelper::get(){
	return vtable;
};

void* VtableHelper::getTop(){
	return original;
}
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

template<typename A> A VtableHelper::call(const char* table, const char* symbol){
	auto a = (A(*)(void*)) SYMBOL(table, symbol);
	return a(this->original);
};

std::map<int, void**> VtableCache::block_tables;
std::map<int, void**> VtableCache::item_tables;

void VtableCache::addTable(VtableType type,int id, void** table){
	if(type == VtableType::ITEM) item_tables[id] = table;
	if(type == VtableType::BLOCK) block_tables[id] = table;
};
void VtableCache::addTable(VtableType type,int id, void* table){
	if(type == VtableType::ITEM) item_tables[id] = *(void***) table;
	if(type == VtableType::BLOCK) block_tables[id] = *(void***) table;
};
void** VtableCache::getItemTable(int id){
	if(item_tables.count(id)) return item_tables[id];
};
void** VtableCache::getBlockTable(int id){
	if(block_tables.count(id)) return block_tables[id];
};

bool VtableCache::isExist(VtableType type, int id){
	if(type == VtableType::ITEM){
		if(item_tables.count(id)) return true;
		return false;
	}
	if(type == VtableType::BLOCK){
		if(block_tables.count(id)) return true;
		return false;
	}
}

void VtablePatcher::patch(VtableType type,int id, void* a){
	if(VtableCache::isExist(type, id)){
		VtableHelper helper (a);
		
	}else{

	}
}