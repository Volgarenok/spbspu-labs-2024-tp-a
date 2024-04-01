#ifndef FORMATS_HPP
#define FORMATS_HPP
#include <iostream>
#include <string>

namespace feofanova
{
    struct dbllit
    {
        double& value;
    };
    std::istream& operator>>(std::istream& in, dbllit&& num);

    struct ullbin
    {
        unsigned long long& value;
    };
    std::istream& operator>>(std::istream& in, ullbin&& num);

    struct String
    {
        std::string& str;
    };
    std::istream& operator>>(std::istream& in, String&& num);
}
#endif
