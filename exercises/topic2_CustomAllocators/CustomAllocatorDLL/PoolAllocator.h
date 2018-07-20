#pragma once

#include "CustomBaseAllocatorDLL.h" 

namespace CustomAllocator {

	class PoolAllocator : public Allocator
	{
	public:

		PoolAllocator(size_t objectSize, uint8_t objectAlignment, size_t size, void* mem);
		~PoolAllocator();
		void* allocate(size_t size, uint8_t alignment) override;
		void deallocate(void* p) override;

	private:

		PoolAllocator(const PoolAllocator&);

		//Prevent copies because it might cause errors 
		PoolAllocator& operator=(const PoolAllocator&); size_t _objectSize;

		uint8_t _objectAlignment;
		void** _free_list;
	};

}