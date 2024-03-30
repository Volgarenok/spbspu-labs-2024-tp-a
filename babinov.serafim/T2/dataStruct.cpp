#include "dataStruct.hpp"
#include <string>
#include <bitset>
#include "delimiters.hpp"

bool babinov::DataStruct::operator<(const DataStruct& right) const
{
  if (key1 != right.key1)
  {
    return key1 < right.key1;
  }
  if (key2 != right.key2)
  {
    return key2 < right.key2;
  }
  return key3 < right.key3;
}

std::string toBin(unsigned long long dec)
{
  std::bitset< 64 > bin(dec);
  std::string strBin = bin.to_string();
  return '0' + strBin.substr(strBin.find('1'));
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
      std::bitset< 64 > bin(0);
      in >> caseDel{"0b"} >> bin;
      if (in)
      {
        proc.dataStruct.key2 = bin.to_ullong();
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
