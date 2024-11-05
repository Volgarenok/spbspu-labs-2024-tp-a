#include "datastruct.hpp"
#include <iostream>
#include "delimeters.hpp"
#include "streamguard.hpp"

std::istream &petuhov::operator>>(std::istream &in, petuhov::DataStruct &data)
{
  petuhov::StreamGuard guard(in);
  petuhov::DelimiterIO del;
  petuhov::UllLiteralIO ull1{data.key1};
  petuhov::UllLiteralIO ull2{data.key2};
  petuhov::StringIO str{data.key3};

  in >> del >> ull1 >> del >> ull2 >> del >> str >> del;
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

