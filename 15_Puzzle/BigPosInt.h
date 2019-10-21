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
	const int baseLength = util::GetNumberLength(~(util::size_t)0) / 2; // number of digits for each slots
	const util::size_t base = pow(10, baseLength); // max number for each slots
	BigPosInt() {};
	BigPosInt(util::size_t value);
	BigPosInt(const BigPosInt& value);

	virtual void operator= (util::size_t num);
	virtual void operator= (const BigPosInt& num);
	virtual BigPosInt operator+(const BigPosInt& rhs) const;
	virtual void operator+=(const BigPosInt& rhs);
	virtual BigPosInt operator*(unsigned int num) const;
	virtual void operator*=(unsigned int num);
	virtual bool operator==(const BigPosInt& num) const;

	friend std::ostream& operator<<(std::ostream& ostr, const BigPosInt& num);

protected:
	vector<util::size_t> number;

};

