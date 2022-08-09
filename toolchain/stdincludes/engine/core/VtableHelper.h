#pragma once

#include <type_traits>
#include <cstdint>
#include <vector>
#include <iostream>
#include <vtable.h>
#include <cstring>
#include <symbol.h>


template<unsigned N>
class ArgsBuffer {
    char pad[N];
};
class ArgsBufferBuilder {
	private:
    	std::vector<unsigned char> buffer;
	public:
		template<typename T>
		void add(const T& v) {
			//static_assert(std::is_trivially_copyable<T>::value, "");
			
			constexpr std::size_t size = sizeof(T);
			constexpr std::size_t align = alignof(T);
			auto mask = align - 1;
			auto offset = ( buffer.size() + mask ) & ( ~mask );
			buffer.resize( offset + size );
			*reinterpret_cast<T*>( buffer.data() + offset ) = v;
		}

		inline const std::size_t size() const { return buffer.size(); }
		inline const unsigned char* data() const { return buffer.data(); }
};

class VtableHelper {
	public:
		void** vtable;
		void* original;
		VtableHelper();
		VtableHelper(void*);
		void resize();
		void patch(const char*, const char*, void*);
		void patch(const char*, const char*, const char*, void*);

    public:
		template<typename A, unsigned N >
		A callWithArgsBufferN(void* func, const unsigned char* buffer) {
			auto* f = (A (*) (ArgsBuffer<N>)) func;
			return f(*(ArgsBuffer<N>*) buffer);
		}
		template<typename A>
		A call(const char* symbol, ArgsBufferBuilder buff, bool virt, const char* vtableName, const char* lib){
			void* func;
			if(virt)
				func = VTableManager::get_method(this->original, getVtableOffset(vtableName, symbol));
			else
				func = SYMBOL(lib, symbol);
				//func = dlsym(dlopen("libminecraftpe.so", RTLD_LAZY), symbol);
			auto size = buff.size();
			if (size <= 8) {
				return callWithArgsBufferN<A, 8>(func, buff.data());
			} else if (size <= 32) {
				return callWithArgsBufferN<A, 32>(func, buff.data());
			} else if (size <= 128) {
				return callWithArgsBufferN<A, 128>(func, buff.data());
			} else if (size <= 512) {
				return callWithArgsBufferN<A, 512>(func, buff.data());
			} else if (size <= 2048) {
				return callWithArgsBufferN<A, 1024>(func, buff.data());
			}
			//auto a = (A(*)(void*,B&&...)) dlsym(handle, symbol);
			//return a(this->original,std::forward<B>(args)...);
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
	void replace(const char*, const char*, const char*,const char*);
	template<typename...A> void call(int, A...);
};