#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <cstddef>
#include <string>

namespace vyzhanov
{
    struct DataStruct
    {
        size_t key1;
        size_t key2;
        std::string key3;
    };
    std::istream& operator>>(std::istream&, DataStruct&);
    std::ostream& operator<<(std::ostream&, const DataStruct&);
    bool operator<(const DataStruct&, const DataStruct&);
}

#endif
