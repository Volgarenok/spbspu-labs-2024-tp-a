#include <algorithm>
#include <tuple>
#include <cctype>
#include <cstdlib>
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
        if (part.empty()) {
            std::cerr << "Error: Empty key-value part in the input." << std::endl;
            return false;
        }

        constexpr auto ValueOffset = KeyLength + SpaceLength;
        const auto partLength = part.size();
        if (partLength < ValueOffset) {
            std::cerr << "Error: Malformed key-value part in the input: " << part << std::endl;
            return false;
        }

        const std::string keyStr(part.data(), KeyLength);
        const std::string valueStr(part.data() + ValueOffset, partLength - ValueOffset);

        if (keyStr == "key3") {
            dataStruct.key3 = valueStr;
            return true;
        }

        if (keyStr == "key2" && valueStr.size() > PrefixLength) {
            if (valueStr[0] == '0' && std::tolower(valueStr[1]) == 'x') {
                dataStruct.key2 = std::strtoull(valueStr.data(), nullptr, 16);
                return true;
            }
            std::cerr << "Error: Invalid key2 format in the input: " << valueStr << std::endl;
        }

        if (keyStr == "key1" && valueStr.size() > SuffixLength) {
            const auto suffix = valueStr.substr(valueStr.size() - SuffixLength);
            if (suffix == "ULL") {
                const auto trimmed = valueStr.substr(0, valueStr.size() - SuffixLength);
                dataStruct.key1 = std::strtoull(trimmed.data(), nullptr, 10);
                return true;
            }
            std::cerr << "Error: Invalid key1 format in the input: " << valueStr << std::endl;
        }

        return false;
    }

    void printHex(std::ostream& stream, const KeyType value)
    {
        stream << std::uppercase << std::hex << std::showbase
               << value << std::nouppercase << std::dec << std::noshowbase;
    }
}

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct)
{
    constexpr auto NoPos = std::string::npos;
    constexpr auto FailBit = std::ios::failbit;

    std::string line;
    std::getline(stream, line);

    if (line.empty()) {
        std::cerr << "Error: Empty input line." << std::endl;
        stream.setstate(FailBit);
        return stream;
    }

    size_t from = line.find(':');
    if (from == NoPos) {
        std::cerr << "Error: Could not find the first colon in the input line: " << line << std::endl;
        stream.setstate(FailBit);
        return stream;
    }

    for (size_t i = 0; i < KeyCount; ++i) {
        ++from;
        const auto to = line.find(':', from);
        if (to == NoPos || !parse(std::string(line.c_str() + from, to - from), dataStruct)) {
            std::cerr << "Error: Failed to parse key-value pair in the input: " << line << std::endl;
            stream.setstate(FailBit);
            return stream;
        }
        from = to;
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct)
{
    stream << "(:key1 " << dataStruct.key1 << "ULL:key2 ";
    printHex(stream, dataStruct.key2);
    return stream << ":key3 " << dataStruct.key3 << ":)";
}

bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    return std::make_tuple(lhs.key1, lhs.key2, lhs.key3.size()) <
           std::make_tuple(rhs.key1, rhs.key2, rhs.key3.size());
}
}
