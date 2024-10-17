#include "DataStruct.h"
#include <bitset>
#include <iostream>
#include "StreamGuard.h"
#include "HelperStructsIO.h"
#include "TypeStructures.h"

namespace stepanov
{
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        DataStruct input;
        using sep = DelimeterIO;
        in >> sep{ '(' };
        in >> sep{ ':' };
        for (int i = 0; i < 3; ++i)
        {
            using oct = OctUnsignedLongLongIO;
            using bin = BinUnsignedLongLongIO;
            using str = StringIO;
            std::string key = "";
            in >> key;

            if (key == "key1")
            {
                unsigned long long temp;
                in >> oct{ temp };
                input.key1_ = temp;
            }
            else if (key == "key2")
            {
                unsigned long long temp;
                in >> bin{ temp };
                input.key2_ = temp;
            }
            else if (key == "key3")
            {
                in >> str{ input.key3_ };
            }
            in >> sep{ ':' };
        }
        in >> sep{ ')' };

        if (in) dest = input;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry) return out;

        StreamGuard format(out);
        out << "(";
        out << ":key1 " << (src.key1_ & 0x1FFF);
        std::string binary = std::bitset<64>(src.key2_).to_string();
        size_t pos = binary.find('1');
        if (pos != std::string::npos) {
            binary = binary.substr(pos);
        }
        else {
            binary = "0";
        }
        out << ":key2 0b" << binary;
        out << ":key3 \"" << src.key3_ << '"';
        out << ":)";
        return out;
    }

    bool operator<(const DataStruct& first, const DataStruct& second)
    {
        if (first.key1_ != second.key1_) return first.key1_ < second.key1_;
        if (first.key2_ != second.key2_) return first.key2_ < second.key2_;
        return first.key3_ < second.key3_;
    }
}
