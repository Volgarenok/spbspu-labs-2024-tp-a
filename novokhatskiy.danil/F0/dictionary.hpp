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
		using val_t = std::pair< std::string, std::set< std::string > >;
		Dictionary() = default;
		~Dictionary() = default;
		//void addValue(val_t&& val);
		val_t& getValue(const std::string& name);
		void remove(const std::string& word);
		void find(const std::string& word, std::ostream& out) const;
		size_t size() const noexcept;
		std::map< std::string, val_t > getDict() const;
		friend std::istream& operator>>(std::istream& in, Dictionary& dict);
		friend std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
	private:
		std::map< std::string, val_t > dict_;
	};
	std::istream& operator>>(std::istream& in, Dictionary& dict);
	std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
}

#endif
