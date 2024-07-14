#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP

#include <iostream>

namespace zhakha
{
	struct StreamGuard
	{
	public:
		StreamGuard(std::basic_ios< char >& s);
		~StreamGuard();

	private:
		std::basic_ios< char >& s_;
		std::streamsize precision_;
		std::basic_ios< char >::fmtflags flags_;
	};
}
#endif