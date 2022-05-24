#pragma once

class VtableHelper {
	public:
	void** vtable;
	void* original;

	VtableHelper(void* a);
	void resize();
	void patch(const char* table, const char* symbol, void* func);

    public:
	void* getAdreess(const char* table, const char* symbol);
    void* getTop();
    void** get();

};