#include "DataStruct.hpp"
#include <iomanip>
#include "streamGuard.hpp"
#include "Delimeter.hpp"
#include "formats.hpp"

std::istream& feofanova::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  DataStruct temp{ 0, 0, "" };
  using del = delimeter_t;
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
      in >> dbllit{ temp.key1 };
      i++;
    }
    else if (key_num == 2)
      {
        in >> ullbin{ temp.key2 };
        i++;
      }
      else if (key_num == 3)
      {
        in >> String{ temp.key3 };
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
};

std::ostream& feofanova::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard s_guard(out);
  out << std::setprecision(1) << std::fixed << "(";
  out << ":key1 " << data.key1 << "d";
  out << ":key2 0b" << toBinary(data.key2);
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
};

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
};
