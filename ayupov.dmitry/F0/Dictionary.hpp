#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <set>
#include <unordered_map>

namespace ayupov
{
	struct ARDictionary
	{
		std::unordered_map< std::string, std::set< std::string > > dictionary;

	};
}
#endif
