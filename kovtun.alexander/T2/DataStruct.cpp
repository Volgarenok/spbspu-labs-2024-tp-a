#include "DataStruct.hpp"

std::istream & kovtun::operator>>(std::istream & in, kovtun::DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  kovtun::IOScopeGuard scopeGuard(in);

  using dl = kovtun::DelimiterI;
  using stub = kovtun::KeyI;
  using dLit = kovtun::DoubleLitI;
  using cLit = kovtun::CharLitI;
  using str = kovtun::StringI;

  DataStruct _data;
  int key = 0;

  in >> dl{'('};
  for (int i = 0; i < 3; i++)
  {
    in >> stub{key};

    if (key == 1)
    {
      in >> dLit{_data.key1};
    }
    else if (key == 2)
    {
      in >> cLit{_data.key2};
    }
    else if (key == 3)
    {
      in >> str{_data.key3};
    }
  }
  in >> dl{':'} >> dl{')'};

  if (in)
  {
    data = _data;
  }

  return in;
}

std::ostream & kovtun::operator<<(std::ostream & out, const kovtun::DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  kovtun::IOScopeGuard scopeGuard(out);

  out << "(:key1 " << data.key1 << 'd';
  out << ":key2 " << '\'' << data.key2 << '\'';
  out << ":key3 " << '\"' << data.key3 << '\"';
  out << ":)"; // :)

  return out;
}
