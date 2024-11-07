#pragma once
#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>
#include <string>
namespace lazareva
{
    struct Dbl
    {
        double& value;
    };
    std::istream& operator>>(std::istream& in, Dbl&& num);

    struct Sll
    {
        unsigned long long value;
    };
    std::ostream& operator<<(std::ostream& out, Sll&& src);

    struct String
    {
        std::string& str;
    };
    std::istream& operator>>(std::istream& in, String&& num);

    struct DataStruct
    {
        double key1;
        long long key2;
        std::string key3;
    };

    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);

};

#endif;
