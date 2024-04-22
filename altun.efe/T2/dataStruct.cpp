#include "dataStruct.hpp"
#include <iomanip>
#include "streamGuard.hpp"
#include "delimiter.hpp"


std::istream& altun::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  using del = Delimiter;
  int dnumber = 0;
  in >> del{'('};
  int max_keys = 3;
  for (int i = 0; i < max_keys; i++)
  {
    in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
    in >> dnumber;
    if (dnumber == 1)
    {
      in >> data.key1 >> del{'d'};
    }
