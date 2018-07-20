#pragma once

#include "stdafx.h"
#include <string>
#include "LinearAllocator.h"

namespace tmp
{
	typedef std::basic_string<char, std::char_traits<char>, CustomAllocator::LinearAllocator>
		tmpstring;
	

}

