#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

namespace serter
{
    struct DataStruct
    {
        double key1;
        unsigned long long key2;
        std::string key3;
    };

    std::istream& operator>>(std::istream& in, DataStruct& value);
    std::ostream& operator<<(std::ostream& out, const DataStruct& value);

    bool operator<(const DataStruct& value1, const DataStruct& value2);
}

#endif // DATASTRUCT_HPP

