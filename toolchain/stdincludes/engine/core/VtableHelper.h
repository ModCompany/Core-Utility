#pragma once

class VtableHelper {
	public:
	void** vtable;
	void* original;

	VtableHelper(void*);
	void resize();
	void patch(const char*, const char*, void*);

    public:

	template<typename A> A call(const char*, const char*);
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

	static void** getItemTable(int);
	static void** getBlockTable(int);
	static bool isExist(VtableType, int);
};

class VtablePatcher {
	public:
	VtablePatcher(VtableCache::VtableType, void*);
	void patch(const char*, const char*, void*);
	void patch(VtableCache::VtableType, int, void*);
};