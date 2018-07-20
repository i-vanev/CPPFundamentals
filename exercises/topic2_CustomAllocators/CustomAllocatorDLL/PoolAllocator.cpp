#include "stdafx.h"
#include "PoolAllocator.h"

namespace CustomAllocator {

	PoolAllocator::PoolAllocator(size_t objectSize, uint8_t objectAlignment, size_t size, void* mem) : 
		Allocator(size, mem), _objectSize(objectSize), _objectAlignment(objectAlignment)
	{
		assert(objectSize >= sizeof(void*));
		/*
		//Should calculate the adjustment needed to keep object correctly aligned
		uint8_t adjustment;// = Allocator::AlignForwardAdjustment(mem, objectAlignment);
		//_free_list = (void**)pointer_math::add(mem, adjustment)
		size_t numObjects = (size - adjustment) / objectSize;
		void** p = _free_list;

		//Then initialize free blocks list
		for (int i = 0; i < numObjects - 1; i++)
		{
			//*p = pointer_math::add(p, objectSize);
			p = (void**)*p;
		}

		*p = nullptr;*/
	}

	PoolAllocator::~PoolAllocator()
	{
		_free_list = nullptr;
	}

	void* PoolAllocator::allocate(size_t size, uint8_t alignment)
	{
		//assert that the size and alignment are in check
		assert(size == _objectSize && alignment == _objectAlignment);
		if (_free_list == nullptr) return nullptr;
		void* p = _free_list;
		_free_list = (void**)(*_free_list);
		_used_memory += size;
		_num_allocations++;
		return p;
		//allocate the next free block with the same size

		//
	}

	void PoolAllocator::deallocate(void* p)
	{
		*((void**)p) = _free_list;
		_free_list = (void**)p;
		_used_memory -= _objectSize;
		_num_allocations--;
	}
}