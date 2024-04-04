#include "dataStructure.hpp"

#include <iomanip>
#include <ios>
#include <tuple>
#include "delimiters.hpp"
#include "inputFormatters.hpp"
#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, DataStructure& value)
{
  using namespace ibragimov;
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    int keysAmount = 3;
    bool isInputed[3] = {false, false, false};
    int keyId = 0;
    in >> std::noskipws;
    in >> DelimiterI< CaseSensitive >{"("};
    while ((in) && (keysAmount != 0))
    {
      in >> DelimiterI< CaseSensitive >{":key"} >> keyId >> std::ws;
      if ((keyId == 1) && (isInputed[keyId - 1] == false))
      {
        in >> DoubleLitI{value.key1};
      }
      else if ((keyId == 2) && (isInputed[keyId - 1] == false))
      {
        in >> ComplexLspI{value.key2};
      }
      else if ((keyId == 3) && (isInputed[keyId - 1] == false))
      {
        in >> StringI{value.key3};
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      isInputed[keyId - 1] = true;
      --keysAmount;
    }
    in >> DelimiterI< CaseSensitive >{":)"};
  }
  return in;
}

std::ostream& ibragimov::operator<<(std::ostream& out, const DataStructure& value)
{
  using namespace ibragimov;
  StreamGuard sGuard(out);
  out << std::fixed << std::setprecision(1);
  out << "(:key1 " << value.key1 << "d";
  out << ":key2 " << "#c(" << value.key2.real() << ' ' << value.key2.imag() << ")";
  out << ":key3 " << std::quoted(value.key3) << ":)";
  return out;
}

bool ibragimov::operator<(const DataStructure& l, const DataStructure& r)
{
  return std::forward_as_tuple(l.key1, std::abs(l.key2), l.key3.size()) < std::forward_as_tuple(l.key1, std::abs(l.key2), r.key3.size());
}
