#include "dataIO.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace serter
{
std::istream& operator>>(std::istream& in, DelimiterIO&& val)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    char ch = 0;
    in >> ch;
    if (in && ch != std::tolower(val.val) && ch != std::toupper(val.val))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& val)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::getline(in >> DelimiterIO{'"'}, val.val, '"');
    in >> DelimiterIO{ ':' };
    return in;
}

std::istream& operator>>(std::istream& in, DoubleIO&& val)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    int mantissa = 0;
    int number = 0;
    int power = 0;
    in >> mantissa >> DelimiterIO{'.'} >> number >> DelimiterIO{'E'} >> power;
    val.val = (mantissa * 1.0 + number * 0.01) * std::pow(10, power);
    in >> DelimiterIO{ ':' };
    return in;
}

std::istream& operator>>(std::istream& in, UnsignedllIO&& val)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    unsigned long long number = 0;
    char c = 0;
    in >> LabelIO{"0b"};
    while (in >> c)
    {
        if (c == '0' || c == '1')
        {
            number = (number << 1) + (c - '0');
        }
        else
        {
            break;
        }
    }
    if (c == ':')
    {
        val.val = number;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LabelIO && val)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    for (size_t i = 0; i < val.val.length(); i++)
    {
        in >> DelimiterIO{val.val[i]};
    }
    return in;
}

std::string fromULLtoBinary(unsigned long long value)
{
    if (value == 0)
    {
        return "0";
    }
    std::string binary;
    while (value > 0)
    {
        binary.insert(0, std::to_string(value % 2));
        value /= 2;
    }
    return binary;
}

std::string fromDoubleToScientific(double val)
{
    int exp = 0;
    while (std::abs(val) < 1)
    {
        val *= 10;
        exp--;
    }
    while (std::abs(val) >= 10)
    {
        val /= 10;
        exp++;
    }
    int num = static_cast<int>(std::round(val * 10));
    std::string result = std::to_string(num);
    result.insert(1, 1, '.');
    result += 'e';
    if (exp >= 0)
    {
        result += '+';
    }
    return result + std::to_string(exp);
}
} // namespace serter
