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