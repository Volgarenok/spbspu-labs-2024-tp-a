#include "dataStructure.hpp"

#include <iomanip>
#include <ios>
#include <tuple>
#include "inputFormatters.hpp"
#include "label.hpp"
#include "strategies.hpp"
#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, DataStructure& ds)
{
  using namespace ibragimov;
  using namespace formatters;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard sGuard(in);
  in >> std::noskipws;
  in >> LabelI< CaseSensitive >{"("};
  int keysAmount = 3;
  bool isInputed[3] = {false, false, false};
  while ((in) && (keysAmount != 0))
  {
    int keyId = 0;
    in >> LabelI< CaseSensitive >{":key"} >> keyId >> std::ws;
    if ((keyId == 1) && (isInputed[keyId - 1] == false))
    {
      in >> DoubleLitI{ds.key1};
    }
    else if ((keyId == 2) && (isInputed[keyId - 1] == false))
    {
      in >> ComplexLspI{ds.key2};
    }
    else if ((keyId == 3) && (isInputed[keyId - 1] == false))
    {
      in >> StringI{ds.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    isInputed[keyId - 1] = true;
    --keysAmount;
  }
  in >> LabelI< CaseSensitive >{":)"};
  return in;
}
std::ostream& ibragimov::operator<<(std::ostream& out, const DataStructure& ds)
{
  using namespace ibragimov;
  StreamGuard sGuard(out);
  out << std::fixed << std::setprecision(1);
  out << "(:key1 " << ds.key1 << "d";
  out << ":key2 " << "#c(" << ds.key2.real() << ' ' << ds.key2.imag() << ")";
  out << ":key3 " << std::quoted(ds.key3) << ":)";
  return out;
}
bool ibragimov::operator<(const DataStructure& l, const DataStructure& r)
{
  return std::forward_as_tuple(l.key1, std::abs(l.key2), l.key3.size())
      < std::forward_as_tuple(r.key1, std::abs(r.key2), r.key3.size());
}
