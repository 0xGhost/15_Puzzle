// Author: Yiang Lu
// Date created: 20/Oct/2019
#include "BigPosInt.h"
#include <iomanip>
#include "Utility.h"

#define max(a,b) a>b?a:b

BigPosInt::BigPosInt(ull value)
{
	*this = value;
}

BigPosInt::BigPosInt(const BigPosInt& value)
{
	*this = value;
}

void BigPosInt::operator=(ull num)
{
	while (num > 0)
	{
		number.push_back(num % base);
		num /= base;
	}
}

void BigPosInt::operator=(const BigPosInt& num)
{
	this->number = num.number;
}

BigPosInt BigPosInt::operator+(const BigPosInt& rhs) const
{
	BigPosInt result = rhs;
	bool carry = false;
	for (int i = 0; i < (max(number.size(), rhs.number.size())) || carry; i++)
	{
		if (i == result.number.size()) // result size is not enough
			result.number.push_back(0);
		result.number[i] += carry + (i < number.size() ? number[i] : 0);
		carry = result.number[i] >= base;
		if (carry) // check carry bit
			result.number[i] -= base;
	}
	return result;
}

void BigPosInt::operator+=(const BigPosInt& rhs)
{
	*this = *this + rhs;
}

BigPosInt BigPosInt::operator*(unsigned int num) const
{
	BigPosInt result = *this;
	for (ull i = 0, carry = 0; i < result.number.size() || carry; i++)
	{
		if (i == (int)result.number.size()) // result size is not enough
			result.number.push_back(0);
		ull current = result.number[i] * (ull)num + carry;
		carry = (ull)(current / base);
		result.number[i] = (ull)(current % base);
	}
	while (!result.number.empty() && !result.number.back()) // delelte 0s in the front of a number; eg: 001000 -> 1000
		result.number.pop_back();
	return result;
}

void BigPosInt::operator*=(unsigned int num)
{
	*this = *this * num;
}

bool BigPosInt::operator==(const BigPosInt& num) const
{
	if (num.number.size() != number.size())
		return false;
	for (unsigned int i = 0; i < number.size(); i++)
	{
		if (number[i] != num.number[i])
		{
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& ostr, const BigPosInt& num)
{
	ostr << (num.number.empty() ? 0 : num.number.back()); // print the first part without fill 0 in the front
	for (int i = num.number.size() - 2; i >= 0; i--)
		ostr << std::setw(num.baseLength) << std::setfill('0') << num.number[i]; // print the last and fill 0 for empty digits
	return ostr;
}
