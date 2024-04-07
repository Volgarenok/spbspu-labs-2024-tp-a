#include "DataStruct"


std::istream& stepanchenko::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = DelimeterI;
  using strDel = StringDelimeterI;
  size_t keyAmount = 3;

  in >> del{ '(' } >> del{ ':' };
  while (in && key_amount > 0)
  {
    char num = 0;
    in >> strDel{ "key" };
    in >> num;
    switch (num)
    {
    case '1':
      in >> LongLongI{ data.key1_ };
      break;
    case '2':
      in >> CharI{ data.key2_ };
      break;
    case '3':
      in >> StringI{ data.key3_ };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
    --keyAmount;
    in >> del{ ':' };
  }
  in >> del{ ')' };

  return in;
}

std::ostream& stepanchenko::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return in;
  }
  out << "(:key1 " << data.key1_ << "ull" 
      << ":key2 '" << data.key2_
      << "':key3 " << data.key3_ << ":)";

  return out;
}
