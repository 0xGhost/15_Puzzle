#pragma once
//#include "BigPosInt.h"
class BigPosInt;
namespace util
{
	typedef unsigned long long size_t;

	inline int GetNumberLength(size_t number)
	{
		int length = 0;
		while (number)
		{
			number /= 10;
			length++;
		}
		return length;
	}
}