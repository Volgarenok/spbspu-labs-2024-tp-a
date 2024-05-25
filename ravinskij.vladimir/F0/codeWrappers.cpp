#include "codeWrappers.hpp"
#include <iostream>
#include <scopeGuard.hpp>
#include <delimeters.hpp>

namespace rav = ravinskij;
std::ostream& rav::operator<<(std::ostream& out, rav::WriteWrapper&& wrapper)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << wrapper.symbol << '-';
    for (bool bit: wrapper.code)
    {
        out << bit;
    }
    return out;
}

std::istream& rav::operator>>(std::istream& in, rav::ReadWrapper&& wrapper)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    wrapper.symbol = in.get();
    in >> CharDelimeter{'-'};
    char bit = 0;
    in >> std::noskipws;
    while (bit != '\n')
    {
        in >> bit;
        wrapper.code.push_back(static_cast< bool >(bit - '0'));
    }
    wrapper.code.pop_back();
    in >> std::skipws;
    return in;
}
