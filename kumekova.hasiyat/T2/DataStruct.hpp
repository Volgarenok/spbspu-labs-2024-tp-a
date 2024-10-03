#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

namespace kumekova {

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    DataStruct() : key1(0), key2(0), key3("") {} // default constructor
    DataStruct(unsigned long long key1, unsigned long long key2, const std::string& key3)
        : key1(key1), key2(key2), key3(key3) {}
};
std::istream& operator>>(std::istream& stream, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct);
bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}
#endif
