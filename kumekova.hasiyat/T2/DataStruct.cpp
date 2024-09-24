#include <algorithm>
#include <tuple>

#include "DataStruct.hpp"

namespace kumekova
{
namespace
{

constexpr size_t KeyCount = 3;
constexpr size_t KeyLength = 4; // "keyX"
constexpr size_t SpaceLength = 1; // " "
constexpr size_t PrefixLength = 2; // "0x"
constexpr size_t SuffixLength = 3; // "ULL"

bool parse(const std::string& part, DataStruct& dataStruct)
{
  constexpr auto ValueOffset = KeyLength + SpaceLength;

  const auto partLength = part.size();
  if (partLength < ValueOffset) {
    return false;
  }

  const std::string keyStr(part.data(), KeyLength);
  const std::string valueStr(part.data() + ValueOffset, partLength - ValueOffset);

  if (std::equal(keyStr.begin(), keyStr.end(), "key3", [](char a, char b) { 
    return std::tolower(a) == std::tolower(b); })) {
        dataStruct.key3 = valueStr;
        return true;
    }

  const auto valueLength = valueStr.size();
   if (std::equal(keyStr.begin(), keyStr.end(), "key2", [](char a, char b) { 
     return std::tolower(a) == std::tolower(b); }) && valueLength > PrefixLength) {
        if (std::tolower(valueStr[0]) == '0' && std::tolower(valueStr[1]) == 'x') {
            dataStruct.key2 = std::strtoull(valueStr.data(), nullptr, 16);
            return true;
        }
    }
  
 if (std::equal(keyStr.begin(), keyStr.end(), "key1", [](char a, char b) { return std::tolower(a) == std::tolower(b); }) && valueLength > SuffixLength) {
        const auto suffix = valueStr.substr(valueLength - SuffixLength);

        if (std::all_of(suffix.begin(), suffix.end(), [](char c) { return std::tolower(c) == 'u' || std::tolower(c) == 'l'; })) {
            const auto trimmed = valueStr.substr(0, valueLength - SuffixLength);
            dataStruct.key1 = std::strtoull(trimmed.data(), nullptr, 10);
            return true;
        }
    }

    return false;
}

void printHex(std::ostream& stream, const KeyType value)
{
  stream
    << std::uppercase << std::hex << std::showbase
    << value
    << std::nouppercase << std::dec << std::noshowbase;
}

} // namespace

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct)
{
  constexpr auto NoPos = std::string::npos;
  constexpr auto FailBit = std::ios::failbit;

  std::string line;
  std::getline(stream, line);

  size_t from = line.find(':');
  if (from == NoPos) {
    stream.setstate(FailBit);
    return stream;
  }

  for (size_t i = 0; i < KeyCount; ++i) {
    ++from;
    const auto to = line.find(':', from);
    if (to == NoPos || !parse(std::string(line.c_str() + from, to - from), dataStruct)) {
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
  return
    std::make_tuple(lhs.key1, lhs.key2, lhs.key3.size()) <
    std::make_tuple(rhs.key1, rhs.key2, rhs.key3.size());
}

}
