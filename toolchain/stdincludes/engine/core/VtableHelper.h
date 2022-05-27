#pragma once

#include <vtable.h>
#include <cstring>


class VtableHelper {
	public:
	void** vtable;
	void* original;
	VtableHelper();
	VtableHelper(void*);
	void resize();
	void patch(const char*, const char*, void*);

    public:

	template<typename A> A call(const char* symbol){
		void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
		auto a = (A(*)(void*)) dlsym(handle, symbol);
		return a(this->original);
	};
    void* getTop();
    void** get();
	public:

	static void* getAdreess(const char*, const char*);
};

class VtableCache {
	public:
	enum VtableType {
		ITEM,
		BLOCK
	};
	static std::map<int, void**> item_tables;
	static std::map<int, void**> block_tables;

	static void addTable(VtableType, int, void**);
	static void addTable(VtableType, int, void*);
	static void** getTable(VtableType, int);
	static void** getItemTable(int);
	static void** getBlockTable(int);
	static bool isExist(VtableType, int);
};

class VtablePatcher {
	public:
	VtableCache::VtableType type;
	VtableHelper helper;
	int id;

	VtablePatcher(VtableCache::VtableType,int, void*);
	void patch(const char*, const char*, void*);
	template<typename...A> void call(int, A...);
};