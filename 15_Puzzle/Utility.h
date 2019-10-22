// Author: Yiang Lu
// Date created: 20/Oct/2019
#pragma once

typedef unsigned long long ull;

inline int GetNumberLength(ull number) // get the digits for a positive integer
{
	int length = 0;
	while (number)
	{
		number /= 10;
		length++;
	}
	return length;
}
