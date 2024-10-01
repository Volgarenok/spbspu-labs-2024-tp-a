#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
    std::list<kumekova::DataEntry> entries{};
    while (!std::cin.eof())
    {
        using InputIterator = std::istream_iterator<kumekova::DataEntry>;
        std::copy(InputIterator{ std::cin }, InputIterator{}, std::back_inserter(entries));
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    entries.sort();
    using OutputIterator = std::ostream_iterator<kumekova::DataEntry>;
    std::copy(entries.cbegin(), entries.cend(), OutputIterator{ std::cout, "\n" });
    return 0;
}
