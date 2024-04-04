#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& timchishina::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  in >> del{'('};
  for (int i = 0; i < 3; i++)
  {
    int num = 0;
    in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
    in >> num;
    if (num == 1)
    {
      in >> data.key1 >> del{'l'} >> del{'l'};
    }
    else if (num == 2)
    {
      in >> std::oct >> data.key2;
    }
    else if (num == 3)
    {
      std::getline(in >> del{'\"'}, data.key3, '\"');
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{':'} >> del{')'};
  return in;
}

std::ostream & timchishina::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard streamG(out);
  out << "(:key1 " << data.key1 << "ll";
  out << ":key2 " << std::oct << data.key2;
  out << ":key3 \"" << data.key3 << "\":)"; 
  return out;
}
