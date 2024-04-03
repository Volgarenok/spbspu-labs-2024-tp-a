#include "dataStruct.hpp"
#include "streamGuard.hpp"

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
