// author: Yiang Lu
// Date created: 9/Oct/2019
#pragma once
#include <iostream>

class Comparable
{
public:
	
	virtual bool isEqualTo(const Comparable& rhs) const = 0;
	friend std::ostream& operator<< (std::ostream& ostr, Comparable& comparable)
	{
		return comparable.print(ostr, comparable);
	}
private:
	virtual std::ostream& print(std::ostream& ostr, const Comparable& comparable) const = 0;
};
