#include "formats.hpp"
#include "Delimeter.hpp"
#include "streamGuard.hpp"

std::istream& feofanova::operator>>(std::istream& in,dbllit&& dest)
{
    std::istream::sentry guard(in);
    if (guard)
    {
        StreamGuard sGuard(in);
        in >> std::noskipws;
        in >> dest.value >> IgnoreCaseDelimeter{ "d" };
    }
    return in;
}

std::istream& feofanova::operator>>(std::istream& in, ullbin&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> dest.value;
    char suffix[3] = "";
    in.read(suffix, 2);
    suffix[2] = '\0';
    if (in && std::strcmp(suffix, "ll") && (std::strcmp(suffix, "LL")))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& feofanova::operator>>(std::istream& in, String&& dest)
{
    std::istream::sentry guard(in);
    if (guard)
    {
        StreamGuard sGuard(in);
        dest.str .clear();
        char c = '\0';
        in >> std::noskipws;
        using Delimeter = delimeter_t;
        in >> Delimeter{ '\"'};
        while ((in >> c) && (c != '"'))
        {
            if (c == '\\')
            {
                in >> c;
            }
            dest.str.push_back(c);
        }
    }
    return in;
}
