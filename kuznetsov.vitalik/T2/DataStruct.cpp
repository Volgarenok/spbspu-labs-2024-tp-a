#include "DataStruct.hpp"

std::ostream& kuznetsov::operator<<(std::ostream& out, const DataStruct& data)
{
    std::ostream::sentry guard(out);
    if (!guard)
    {
        return out;
    }
    out << "(:key1 " << data.key1 << "ull";
    out << ":key2 #c(" << data.key2.real() << " " << data.key2.imag() << ")";
    out << ":key3 \"" << data.key3 << "\":)\n";
    return out;
}
