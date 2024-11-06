#include "delimiter.hpp"
#include <iostream>
#include "streamGuard.hpp"
std::istream& lazareva::operator>>(std::istream& in, Delimiter&& exp)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    StreamGuard s_guard(in);
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
