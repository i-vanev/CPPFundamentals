
#include "stdafx.h"

#include "LinearAllocator.h"

#include <utility>
#include "stdio.h"
#include <iostream>
#include <memory>

namespace CustomAllocator 
{

LinearAllocator::LinearAllocator(size_t size, void* start) : Allocator(size, start), _current_pos(start)
{
	assert(size > 0);
}

LinearAllocator::~LinearAllocator()
{
	_current_pos = nullptr;
}

void* LinearAllocator::allocate(size_t size, uint8_t alignment)
{
	assert(size != 0);
	uint8_t adjustment = Allocator::AlignForwardAdjustment(_current_pos, alignment);

	if (_used_memory + adjustment + size > _size) return nullptr;

	uint8_t* aligned_address = (uint8_t*)_current_pos + adjustment;
	_current_pos = (void*)(aligned_address + size);
	_used_memory += size + adjustment;
	_num_allocations++;

	return (void*)aligned_address;
}

void LinearAllocator::deallocate(void* p)
{
	assert(false && "Use clear() instead");
}

void LinearAllocator::clear()
{
	_num_allocations = 0;
	_used_memory = 0;
	_current_pos = _start;
}



}