#include "DataStruct.hpp"
#include <iomanip>
#include <bitset>
#include "streamGuard.hpp"
#include "Delimeter.hpp"

std::istream& feofanova::operator>>(std::istream& in, LitI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.value >> IgnoreCaseDelimeter{ "d" };
}

std::istream& feofanova::operator>>(std::istream& in, BinI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using Delimeter = DelimeterI;
  in >> Delimeter{ '0' } >> Delimeter{ 'b' };
  if (in)
  {
    char binary[64]{};
    char c;
    size_t i = 0;
    while (in.get(c))
    {
      if (std::isdigit(c))
      {
        binary[i] = c;
        ++i;
      }
      else
      {
        in.putback(c);
        break;
      }
    }
    dest.value = std::stoull(binary, nullptr, 2);
  }
  return in;
}


std::istream& feofanova::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using Delimeter = DelimeterI;
  in >> Delimeter{ '\"' };
  std::getline(in, dest.str, '\"');
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, BinO&& src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  std::string binary = "";
  if (src.value)
  {
    binary = std::bitset<64>(src.value).to_string();
    binary.erase(0, binary.find_first_not_of('0'));
  }
  return out << ('0' + binary);
}

std::istream& feofanova::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  DataStruct temp{ 0, 0, "" };
  using del = DelimeterI;
  int keys_cout = 3;
  in >> del{ '(' };
  int i = 0;
  while ((in) && (i != keys_cout))
  {
    in >> del{ ':' } >> del{ 'k' } >> del{ 'e' } >> del{ 'y' };
    int key_num = 0;
    in >> key_num;
    if (key_num == 1)
    {
      in >> LitI{ temp.key1 };
      i++;
    }
    else if (key_num == 2)
    {
      in >> BinI{ temp.key2 };
      i++;
    }
    else if (key_num == 3)
    {
      in >> StringI{ temp.key3 };
      i++;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{ ':' } >> del{ ')' };
  data = temp;
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard s_guard(out);
  out << "(:key1 " << std::setprecision(1) << std::fixed << data.key1 << "d" << ':';
  using ullbin = feofanova::BinO;
  out << "key2 0b" << ullbin{data.key2};
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}

bool feofanova::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  return key3.size() < other.key3.size();
}
