#include "dataStruct.hpp"
#include <string>
#include <bitset>
#include "delimiters.hpp"

bool babinov::DataStruct::operator>(const DataStruct& right) const
{
  if (key1 != right.key1)
  {
    return key1 > right.key1;
  }
  if (key2 != right.key2)
  {
    return key2 > right.key2;
  }
  return key3 > right.key3;
}

bool babinov::DataStruct::operator<(const DataStruct& right) const
{
  return (right > *this);
}

bool babinov::DataStruct::operator>=(const DataStruct& right) const
{
  return !(*this < right);
}

bool babinov::DataStruct::operator<=(const DataStruct& right) const
{
  return !(right < *this);
}

bool babinov::DataStruct::operator==(const DataStruct& right) const
{
  return ((right <= *this) && (*this <= right));
}

bool babinov::DataStruct::operator!=(const DataStruct& right) const
{
  return !(*this == right);
}

std::string toBin(unsigned long long dec)
{
  std::bitset< 64 > bin(dec);
  std::string strBin = bin.to_string();
  strBin.erase(0, strBin.find_first_not_of('0'));
  return strBin;
}

std::istream& babinov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using charDel = CharDelimiterI;
    using strDel = StringDelimiterI;
    using dProc = DataProcessor;

    const int N_KEYS = 3;
    int iKey = 0;
    DataStruct temp{0, 0, ""};
    in >> charDel{'('};
    for (int i = 0; in && (i < N_KEYS); ++i)
    {
      in >> strDel{":key"} >> iKey >> dProc{temp, iKey};
    }
    in >> strDel{":)"};
    if (in)
    {
      data = temp;
    }
  }
  return in;
}

std::ostream& babinov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << "(:key1 " << data.key1 << "ull";
    out << ":key2 " << "0b" << toBin(data.key2);
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}

std::istream& babinov::operator>>(std::istream& in, DataProcessor&& proc)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using caseDel = StringCaseDelimiterI;
    using charDel = CharDelimiterI;
    if (proc.key == 1)
    {
      unsigned long long num = 0;
      in >> num >> caseDel{"ull"};
      if (in)
      {
        proc.dataStruct.key1 = num;
      }
    }
    else if (proc.key == 2)
    {
      BinaryNumber bin{};
      in >> caseDel{"0b"} >> bin;
      if (in)
      {
        proc.dataStruct.key2 = bin.toUll();
      }
    }
    else if (proc.key == 3)
    {
      std::string str = "";
      in >> charDel{'"'};
      std::getline(in, str, '"');
      proc.dataStruct.key3 = str;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

unsigned long long babinov::BinaryNumber::toUll() const
{
  return std::bitset< 64 >(value).to_ullong();
}

std::istream& babinov::operator>>(std::istream& in, BinaryNumber& bin)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    std::string number = "";
    char digit = 0;
    in >> digit;
    while (((digit == '0') || (digit == '1')) && in)
    {
      number += digit;
      in >> digit;
    }
    if (!number.length())
    {
      in.setstate(std::ios::failbit);
    }
    else if (in)
    {
      in.putback(digit);
    }
    bin.value = number;
  }
  return in;
}
