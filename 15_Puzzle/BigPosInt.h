// Author: Yiang Lu
// Date created: 20/Oct/2019
#pragma once
#include <vector>
#include <iostream>
#include "Utility.h"

using std::vector;

class BigPosInt
{
public:
	const int baseLength = GetNumberLength((~(size_t)0)) - 1; // number of digits for each slots
	const size_t base = pow(10, baseLength); // max number for each slots
	BigPosInt() {};
	BigPosInt(size_t value);
	BigPosInt(const BigPosInt& value);

	virtual void operator= (size_t num);
	virtual void operator= (const BigPosInt& num);
	virtual BigPosInt operator+(const BigPosInt& rhs) const;
	virtual void operator+=(const BigPosInt& rhs);
	virtual BigPosInt operator*(int num) const;

	friend std::ostream& operator<<(std::ostream& ostr, const BigPosInt& num);

protected:
	vector<size_t> number;

};

