#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <map>
#include <set>
#include <iostream>

namespace novokhatskiy
{
	class Dictionary
	{
	public:
		Dictionary() = default;
		~Dictionary() = default;

		friend std::istream& operator>>(std::istream& in, Dictionary& dict);
		friend std::ostream& operator<<(std::ostream& out, const Dictionary& dict);

	private:
		using val_t = std::pair< std::string, std::set< std::string > >;
		std::map< std::string, val_t > dict_;
	};
	std::istream& operator>>(std::istream& in, Dictionary& dict);
	std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
}

#endif
