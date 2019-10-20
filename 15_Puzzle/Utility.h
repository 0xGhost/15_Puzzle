#pragma once

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

inline unsigned long long Factorial(int start, int end)
{
	unsigned long long factorial = 1;
	for (int i = start; i <= end; ++i)
	{
		factorial *= i;
	}
	return factorial;
}