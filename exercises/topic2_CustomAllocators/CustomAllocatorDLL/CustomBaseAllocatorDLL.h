#pragma once

#ifdef CUSTOMALLOC_EXPORTS  
#define CUSTOMALLOC_API __declspec(dllexport)   
#else  
#define CUSTOMALLOC_API __declspec(dllimport)   
#endif

#include "stdafx.h"
#include <assert.h>
#include "malloc.h"
#include <string>

namespace CustomAllocator {

class CUSTOMALLOC_API Allocator
{
public:
	 Allocator(size_t size, void* start) {
		_start = start;
		_size = size;
		_used_memory = 0;
		_num_allocations = 0;
	}

	virtual ~Allocator()
	{
		assert(_num_allocations == 0 && _used_memory == 0);
		_start = nullptr; _size = 0;
	}

	virtual void* allocate(size_t size, uint8_t alignment = 4) = 0;
	virtual void deallocate(void* p) = 0;
	void* getStart() const { return _start; }
	size_t getSize() const { return _size; }
	size_t getUsedMemory() const { return _used_memory; }
	size_t getNumAllocations() const { return _num_allocations; }

	uint8_t AlignForwardAdjustment(const void* address, uint8_t alignment)
	{
		uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));

		if (adjustment == alignment)
			return 0;

		return adjustment;
	}

protected:

	void* _start;
	size_t _size;
	size_t _used_memory;
	size_t _num_allocations;
};

	template <class T> T* allocateNew(Allocator& allocator) {
		return new(allocator.allocate(sizeof(T), __alignof(T))) T;
	}

	template <class T> T* allocateNew(Allocator& allocator, const T& t) {
		return new(allocator.allocate(sizeof(T), __alignof(T))) T(t);
	}

	template <class T> void deallocateDelete(Allocator& allocator, T& object) {
		object.~T();
		allocator.deallocate(&object);
	}

	template <class T> T* allocateArray(Allocator& allocator, size_t length) {
		assert(length != 0);

		//The header actually represents the extra space needed to store the array length in the bytes before the array
		char headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0) headerSize += 1;

		T* p = ((T*)allocator.allocate(sizeof(T)*(length + headerSize), __alignof(T))) + headerSize;
		*(((size_t*)p) - 1) = length;

		for (size_t i = 0; i < length; i++)
			new (&p) T;

		return p;
	}

	template <class T> void deallocateArray(Allocator& allocator, T* array)
	{
		assert(array != nullptr);
		size_t length = *((size_t*)array - 1);

		for (size_t i = 0; i < length; i++) array.~T();

		//Calculate how much additional memory was allocated to store the length before the array
		char headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0) headerSize += 1;

		allocator.deallocate(array - headerSize);
	}

}
