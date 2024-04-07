#include "delimeter.hpp"
#include "dataStruct.hpp"
#include <iostream>

std::istream & isaychev::operator>>(std::istream & in, DelimChI && sym)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != sym.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, DelimStrI && seq)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  bool isRight = true;
  for (int i = 0; seq.exp[i] != '\0'; ++i)
  {
    in >> c;
    if (seq.exp[i] != c)
    {
      isRight = false;
    }
  }
  if (!isRight)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, DataTypeI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }

  using dc = DelimChI;
  using ds = DelimStrI;

  char c = 0;
  std::string data = "";

  in >> c;
  if (c == '1')
  {
    in >> dc{' '};
    std::getline(in, data,':');
    try
    {
      dest.ref.key1 = std::stoll(data);
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
    }
  }
  else if (c == '2')
  {
    in >> ds{" #c("};
    std::getline(in, data,')');
    size_t b = 0;
    double real = 0, imag = 0;
    try
    {
      real = std::stod(data, &b);
      imag = std::stod(data.substr(b));
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
    }
    dest.ref.key2 = {real, imag};
    in >> dc{':'};
  }
  else if (c == '3')
  {
    in >> ds{" \""};
    std::getline(in, data, '"');
    in >> dc{':'};
    dest.ref.key3 = data;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

/*std::istream & isaychev::operator>>(std::istream & in, LongLongI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }

  
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, ComplexI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream & isaychev::operator>>(std::istream & in, StringI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}*/
