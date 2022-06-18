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

VtableHelper::VtableHelper(){

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

std::map<int, void**> VtableCache::block_tables;
std::map<int, void**> VtableCache::item_tables;
std::map<long, void**> VtableCache::injector_tables;

void VtableCache::addTable(VtableType type,int id, void** table){
	if(type == VtableType::ITEM) item_tables[id] = table;
	if(type == VtableType::BLOCK) block_tables[id] = table;
};

void VtableCache::addTable(VtableType type,int id, void* table){
	if(type == VtableType::ITEM) item_tables[id] = *(void***) table;
	if(type == VtableType::BLOCK) block_tables[id] = *(void***) table;
};

void VtableCache::addTable(long pointer, void** table){
	injector_tables[pointer] = table;
};

void VtableCache::addTable(long pointer, void* table){
	injector_tables[pointer] = *(void***) table;
};

void** VtableCache::getItemTable(int id){
	if(item_tables.count(id)) return item_tables[id];
};
void** VtableCache::getBlockTable(int id){
	if(block_tables.count(id)) return block_tables[id];
};

void** VtableCache::getInjectorTable(long table){
	if(injector_tables.count(table)) return injector_tables[table];
}

void** VtableCache::getTable(VtableType type, int id){
	if(type==VtableType::ITEM && item_tables.count(id)) return item_tables[id];
	if(type==VtableType::BLOCK && block_tables.count(id)) return block_tables[id];	
	return nullptr;
}

bool VtableCache::isExist(VtableType type, int id){
	if(type == VtableType::ITEM){
		if(item_tables.count(id)) return true;
		return false;
	}
	if(type == VtableType::BLOCK){
		if(block_tables.count(id)) return true;
		return false;
	}
};

bool VtableCache::isExist(long pointer){
	if(injector_tables.count(pointer)) return true;
	return false;
};

VtablePatcher::VtablePatcher(VtableCache::VtableType type,int id, void* table){
	this->type = type;
	this->helper = VtableHelper(table);
	if(VtableCache::isExist(type,id)){
		this->helper.vtable = VtableCache::getTable(type, id);
	}else this->helper.resize();
};

VtablePatcher::VtablePatcher(long pointer, void* table){
	this->type = VtableCache::VtableType::INJECTOR;
	this->helper = VtableHelper(table);
	if(VtableCache::isExist(pointer)){
		this->helper.vtable = VtableCache::getInjectorTable(pointer);
	}else this->helper.resize();
};

void VtablePatcher::patch(const char* table, const char* symbol, void* func){
	this->helper.patch(table,symbol,func);
};

void VtablePatcher::replace(const char* table, const char* symbol, const char* replace){
	void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
	this->helper.patch(table,symbol,dlsym(handle, replace));
};