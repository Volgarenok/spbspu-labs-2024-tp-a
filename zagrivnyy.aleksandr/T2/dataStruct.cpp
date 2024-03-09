#include "dataStruct.hpp"

#include "delimiter.hpp"

std::istream &zagrivnyy::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = zagrivnyy::DelimiterI;

  in >> del{"("};

  const size_t KEYS_TO_READ = 3;
  for (size_t i = 0; i < KEYS_TO_READ && in; ++i)
  {
    // TODO: Implement key reading
  }

  return in;
}

std::ostream &zagrivnyy::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 '" << data.key1 << "':key2 #c(" << data.key2.real() << " " << data.key2.imag() << "):key3 \""
      << data.key3 << "\":)";

  return out;
}
