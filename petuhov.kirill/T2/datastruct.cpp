#include "datastruct.hpp"
#include <iostream>
#include "delimiters.hpp"
#include "streamguard.hpp"

std::istream &petuhov::operator>>(std::istream &in, petuhov::DataStruct &dest)
{
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }

  petuhov::DataStruct input;
  using sep = petuhov::DelimiterIO;
  using oct = petuhov::UllOctIO;
  using hex = petuhov::UllHexIO;
  using str = petuhov::StringIO;

  in >> sep{'('};
  if (in.fail()) {
    std::cerr << "Failed to read opening bracket\n";
    return in;
  }

  for (size_t i = 0; i < 3; ++i)
  {
    std::string key;

    in >> sep{':'};
    in >> key;

    if (in.fail()) {
      std::cerr << "Failed to read key\n";
      return in;
    }

    if (key == "key1") {
      in >> oct{input.key1};
      if (in.fail()) {
        std::cerr << "Failed to read key1 (ULL OCT)\n";
        return in;
      }
    }
    else if (key == "key2") {
      in >> hex{input.key2};
      if (in.fail()) {
        std::cerr << "Failed to read key2 (ULL HEX)\n";
        return in;
      }
    }
    else if (key == "key3") {
      in >> str{input.key3};
      if (in.fail()) {
        std::cerr << "Failed to read key3 (String)\n";
        return in;
      }
    }
  }

  in >> sep{':'};
  in >> sep{')'};

  if (!in.fail()) {
    dest = input;
  }

  return in;
}

std::ostream &petuhov::operator<<(std::ostream &out, const petuhov::DataStruct &data)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }

  petuhov::StreamGuard guard(out);

  out << "(:key1 0" << std::oct << data.key1;
  out << ":key2 0x" << std::uppercase << std::hex << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";

  return out;
}

bool petuhov::operator<(const petuhov::DataStruct &lhs, const petuhov::DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2) {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.size() < rhs.key3.size();
}

