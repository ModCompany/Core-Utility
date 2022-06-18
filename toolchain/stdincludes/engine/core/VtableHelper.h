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

	template<typename A,typename ... B> A call(const char* symbol,B&&...args){
		void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
		auto a = (A(*)(void*,B&&...)) dlsym(handle, symbol);
		return a(this->original,std::forward(args)...);
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
		BLOCK,
		INJECTOR
	};
	static std::map<int, void**> item_tables;
	static std::map<int, void**> block_tables;
	static std::map<long, void**> injector_tables;
	static void addTable(VtableType, int, void**);
	static void addTable(VtableType, int, void*);
	static void addTable(long, void*);
	static void addTable(long, void**);
	static void** getTable(VtableType, int);
	static void** getItemTable(int);
	static void** getBlockTable(int);
	static void** getInjectorTable(long);
	static bool isExist(VtableType, int);
	static bool isExist(long);
	~VtableCache();
};

class VtablePatcher {
	public:
	VtableCache::VtableType type;
	VtableHelper helper;
	int id;

	VtablePatcher(VtableCache::VtableType,int, void*);
	VtablePatcher(long, void*);
	void patch(const char*, const char*, void*);
	void replace(const char*, const char*,const char*);
	template<typename...A> void call(int, A...);
};