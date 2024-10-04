#include <tuple>
#include <algorithm>
#include <sstream>
#include <cctype>
#include "DataStruct.hpp"

namespace kumekova
{
    namespace
    {

        constexpr size_t KeyCount = 3;
        constexpr size_t KeyLength = 4;
        constexpr size_t SpaceLength = 1;
        constexpr size_t PrefixLength = 2;
        constexpr size_t SuffixLength = 3;

        bool parse(const std::string& part, DataStruct& dataStruct)
        {
            constexpr auto ValueOffset = KeyLength + SpaceLength;

            const auto partLength = part.size();
            if (partLength < ValueOffset) {
                return false;
            }

            const std::string keyStr(part.data(), KeyLength);
            const std::string valueStr(part.data() + ValueOffset, partLength - ValueOffset);

            if (keyStr == "key3") {
                dataStruct.key3 = valueStr.substr(1, valueStr.size() - 2); // Убираем кавычки
                return true;
            }

            const auto valueLength = valueStr.size();

            if (keyStr == "key2" && valueLength > SuffixLength) {
                if (valueStr.substr(valueLength - 3) == "ULL") {
                    dataStruct.key2 = std::strtoull(valueStr.data(), nullptr, 10);
                    return true;
                }
                else {
                    return false;
                }
            }

            if (keyStr == "key1" && valueLength > SuffixLength) {
                const auto prefix = valueStr.substr(0, PrefixLength);
                if (prefix == "0x" || prefix == "0X") {
                    dataStruct.key1 = std::strtoull(valueStr.data(), nullptr, 16);
                    return true;
                }
                else {
                    return false;
                }
            }

            return false;
        }

        void printHex(std::ostream& stream, const KeyType value)
        {
            stream << std::uppercase << std::hex << std::showbase << value
                << std::nouppercase << std::dec << std::noshowbase;
        }

    }

    std::istream& operator>>(std::istream& stream, DataStruct& dataStruct)
    {
        std::string line;
        std::getline(stream, line);

        if (line.empty()) {
            return stream; // Игнорируем пустые строки
        }

        size_t from = line.find("key1");
        if (from == std::string::npos) {
            return stream; // Пропускаем строки без ключа key1
        }

        for (size_t i = 0; i < KeyCount; ++i) {
            from = line.find(':', from) + 1;
            const auto to = line.find(':', from);
            if (to == std::string::npos || !parse(std::string(line.c_str() + from, to - from), dataStruct)) {
                stream.setstate(std::ios::failbit); // Устанавливаем failbit если парсинг не удался
                return stream;
            }
            from = to;
        }

        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct)
    {
        stream << "(:key1 0x" << std::hex << dataStruct.key1 << ":key2 ";
        printHex(stream, dataStruct.key2);
        return stream << ":key3 \"" << dataStruct.key3 << "\"):)";
    }

    bool operator<(const DataStruct& lhs, const DataStruct& rhs)
    {
        return std::make_tuple(lhs.key1, lhs.key2, lhs.key3.size()) <
            std::make_tuple(rhs.key1, rhs.key2, rhs.key3.size());
    }

}
