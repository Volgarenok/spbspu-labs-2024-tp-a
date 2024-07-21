#include "dataStruct.hpp"
#include <iostream>
#include <iomanip>
#include "delimiter.hpp"
#include "streamGuard.hpp"

namespace lazareva {

std::istream& operator>>(std::istream& in, double& value) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }
    StreamGuard s_guard(in);
    in >> value;
    in >> Delimiter{'d'};
    return in;
}

std::istream& operator>>(std::istream& in, long long& value) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }
    StreamGuard s_guard(in);
    in >> value;
    in >> Delimiter{'l'} >> Delimiter{'l'};
    return in;
}

std::istream& operator>>(std::istream& in, std::string& value) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }
    StreamGuard s_guard(in);
    in >> Delimiter{'"'};
    std::getline(in, value, '"');
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }
    StreamGuard s_guard(in);
    in >> Delimiter{'('};
    for (int b = 0; b < 3; b++) {
        in >> Delimiter{':'} >> Delimiter{'k'} >> Delimiter{'e'} >> Delimiter{'y'};
        int i = 0;
        in >> i;
        if (i == 1) {
            in >> data.key1; 
        } else if (i == 2) {
            in >> data.key2; 
        } else if (i == 3) {
            in >> data.key3; 
        } else {
            in.setstate(std::ios::failbit);
        }
    }
    in >> Delimiter{':'} >> Delimiter{')'};
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    std::ostream::sentry guard(out);
    if (!guard) {
        return out;
    }
    StreamGuard s_guard(out);
    out << std::fixed;
    out << "(:key1 " << std::setprecision(1) <<  data.key1 << "d:key2 " << data.key2 << "ll:key3 \"" << data.key3 << "\":)";
    return out;
}

}
