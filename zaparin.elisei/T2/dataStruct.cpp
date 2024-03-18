#include"dataStruct.hpp"

#include"delimeter.hpp"

std::istream& zaparin::operator>>(std::istream& in, zaparin::DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  in >> del{ "(" };
  size_t keysCount = 0;
  DataStruct temp{ 0, {0, 0}, " " };

  while (in && keysCount < 3)
  {
    size_t keyType = 0;
    in >> del{ ":key" } >> keyType;

    switch (keyType)
    {
    case 1:
      in >> del{ " 0b" } >> data.key1;
    }
  }
}