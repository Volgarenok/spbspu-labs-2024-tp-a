#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <cstddef>
#include <string>

namespace vyzhanov
{
    struct DataStruct
    {
        size_t key1_;
        size_t key2_;
        std::string key3_;
    };
    std::istream& operator>>(std::istream&, DataStruct&);
    std::ostream& operator<<(std::ostream&, const DataStruct&);
    bool operator<(const DataStruct&, const DataStruct&);
}

#endif
