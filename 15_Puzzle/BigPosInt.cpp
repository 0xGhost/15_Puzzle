// Author: Yiang Lu
// Date created: 20/Oct/2019
#include "BigPosInt.h"
#include <iomanip>
#include "Utility.h"

#define max(a,b) a>b?a:b

BigPosInt::BigPosInt(util::size_t value)
{
	*this = value;
}

BigPosInt::BigPosInt(const BigPosInt& value)
{
	*this = value;
}

void BigPosInt::operator=(util::size_t num)
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
		if (i == result.number.size())
			result.number.push_back(0);
		result.number[i] += carry + (i < number.size() ? number[i] : 0);
		carry = result.number[i] >= base;
		if (carry)
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
	for (util::size_t i = 0, carry = 0; i < result.number.size() || carry; i++)
	{
		if (i == (int)result.number.size())
			result.number.push_back(0);
		util::size_t current = result.number[i] * (util::size_t)num + carry;
		carry = (util::size_t)(current / base);
		result.number[i] = (util::size_t)(current % base);
		//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
	}
	while (!result.number.empty() && !result.number.back())
		result.number.pop_back();
	//trim();
	return result;
}

void BigPosInt::operator*=(unsigned int num)
{
	for (util::size_t i = 0, carry = 0; i < number.size() || carry; i++)
	{
		if (i == number.size())
			number.push_back(0);
		util::size_t current = number[i] * (util::size_t)num + carry;
		carry = (util::size_t)(current / base);
		number[i] = (util::size_t)(current % base);
		//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
	}
	while (!number.empty() && !number.back())
		number.pop_back();
	//trim();

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
