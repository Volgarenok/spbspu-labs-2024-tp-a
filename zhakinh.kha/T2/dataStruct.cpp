﻿#include "datastruct.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

namespace zhakha {

    // Operator <
    bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
        if (lhs.key1 != rhs.key1) {
            return lhs.key1 < rhs.key1;
        }
        if (lhs.key2 != rhs.key2) {
            return lhs.key2 < rhs.key2;
        }
        return lhs.key3.size() < rhs.key3.size();
    }

    // Operator >>
    std::istream& operator>>(std::istream& in, DataStruct& data) {
        std::istream::sentry guard(in);
        if (!guard) {
            return in;
        }
        StreamGuard s_guard(in);

        DataStruct temp;
        using del = Delimiter;

        in >> del{ '(' };
        for (int i = 0; i < 3; ++i) {
            in >> del{ ':' } >> del{ 'k' } >> del{ 'e' } >> del{ 'y' };
            int key_num = 0;
            in >> key_num;

            if (key_num == 1) {
                double value = 0;
                in >> value;
                temp.key1 = value; // Khởi tạo data.key1
                in >> del{ 'd' };
            }
            else if (key_num == 2) {
                long long num = 0;
                unsigned long long denom;
                in >> num >> del{ ':' } >> denom;
                temp.key2 = { num, denom }; // Khởi tạo data.key2
                in >> del{ 'l' } >> del{ 'l' };
            }
            else if (key_num == 3) {
                std::string value = "";
                in >> del{ '"' };
                std::getline(in, value, '\"');
                data.key3 = value;
            }
            else {
                // Xử lý trường hợp key_num không hợp lệ
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        in >> del{ ':' } >> del{ ')' };

        data = temp;
        return in;
    }

    // Operator <<
    std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        std::ostream::sentry guard(out);
        if (!guard) {
            return out;
        }
        StreamGuard s_guard(out);

        out << std::fixed;
        out << "(:key1 " << std::setprecision(1) << data.key1 << "d:key2 (" << data.key2.first << ":" << data.key2.second << "):key3 \"" << data.key3 << "\":)";
        return out;
    }

} // namespace zhakha
