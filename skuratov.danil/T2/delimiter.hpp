#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace skuratov
{
	struct DelimiterI
	{
		char expected;
	};
	std::istream& operator>>(std::istream& in, DelimiterI&& exp);
}

#endif
