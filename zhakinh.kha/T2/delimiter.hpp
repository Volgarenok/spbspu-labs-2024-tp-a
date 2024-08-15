#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <string>
#include <iostream>

namespace zhakha
{
    struct delimiterStr
    {
        std::string expected;
    };

    std::istream& operator>>(std::istream& in, delimiterStr&& exp);

    struct delimiterChar
    {
        char expected;
    };

    std::istream& operator>>(std::istream& in, delimiterChar&& exp);
}

#endif
