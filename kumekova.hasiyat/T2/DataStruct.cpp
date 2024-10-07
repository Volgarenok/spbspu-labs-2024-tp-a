#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <complex>
#include <cmath>
#include <exception>
#include <istream>
#include <ostream>

#include "DataStruct.hpp"

namespace kumekova
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c{ '0' };
        in >> c;
        if (in && c != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, ComplexDoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        double real = 0.0;
        double imag = 0.0;

        in >> DelimiterIO{ '(' } >> real >> imag >> DelimiterIO{ ')' };
        if (in)
        {
            dest.ref = std::complex<double>(real, imag);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.num;
    }

    std::istream& operator>>(std::istream& in, ULLOCTIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::oct >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using sep = DelimiterIO;
            using ULL = ULLOCTIO;
            using cmp = ComplexDoubleIO;
            using str = StringIO;

            in >> sep{ '(' };
            bool flag1 = false, flag2 = false, flag3 = false;
            while (true)
            {
                if (flag1 && flag2 && flag3) break;
                std::string key;
                char c;
                in >> c;
                if (!in) break;

                if (c == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> ULL{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> sep{ '#' } >> sep{ 'c' } >> cmp{ input.key2 };
                        flag2 = true;
                    }
                    else if (key == "key3")
                    {
                        in >> str{ input.key3 };
                        flag3 = true;
                    }
                }
            }
            in >> sep{ ':' } >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(";
        out << ":key1 " << "0" << std::oct << src.key1;
        out << ":key2 " << std::fixed << std::setprecision(1) << "#c(" << src.key2.real() << " " << src.key2.imag() << ")";
        out << ":key3 \"" << src.key3 << '"';
        out << ":)";
        return out;
    }

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second)
    {
        double Re_first = ds_first.key2.real(),
            Re_second = ds_second.key2.real(),
            Im_first = ds_first.key2.imag(),
            Im_second = ds_second.key2.imag(),
            R_first = sqrt(pow(Re_first, 2) + pow(Im_first, 2)),
            R_second = sqrt(pow(Re_second, 2) + pow(Im_second, 2));

        if (ds_first.key1 < ds_second.key1)
        {
            return true;
        }
        else if (ds_first.key1 == ds_second.key1)
        {
            if (R_first < R_second)
            {
                return true;
            }
            else if (R_first == R_second)
            {
                return ds_first.key3.length() < ds_second.key3.length();
            }
        }
        return false;
    }

    iofmtguard::iofmtguard(std::basic_ios<char>& s) :
        stream(s),
        original_fill(s.fill()),
        original_precision(s.precision()),
        original_format(s.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        stream.fill(original_fill);
        stream.precision(original_precision);
        stream.flags(original_format);
    }
}
