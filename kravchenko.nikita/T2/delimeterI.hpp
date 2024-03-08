#ifndef DELIMETER_I_HPP
#define DELIMETER_I_HPP

#include <istream>

namespace delimeterI
{
	struct DelimeterI
	{
		char expected;
	};
	std::istream& operator>>(std::istream& in, DelimeterI&& exp);
}

#endif