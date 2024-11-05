#include "delimiters.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include "streamguard.hpp"

std::istream &petuhov::operator>>(std::istream &in, DelimiterIO &&del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = '\0';
  in >> c;

  if (in && (c != del.expected))
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}


std::istream &petuhov::operator>>(std::istream &in, StringIO &&str)
{
  std::istream::sentry sentry(in);
  if(!sentry)
  {
    return in;
  }

  petuhov::StreamGuard guard(in);

  in >> DelimiterIO{'\"'};
  std::getline(in, str.ref, '\"');

  return in;
}

std::ostream &petuhov::operator<<(std::ostream &out, StringIO &&str)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  petuhov::StreamGuard guard(out);

  out << '\"' << str.ref << '\"';
  return out;
}

std::istream &petuhov::operator>>(std::istream &in, UllHexIO &&ullhex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  StreamGuard guard(in);

  in >> DelimiterIO{'0'} >> DelimiterIO{'x'} >> std::hex >> ullhex.ref;
  return in;
}

std::ostream &petuhov::operator<<(std::ostream &out, UllHexIO &&ullhex)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  StreamGuard guard(out);

  out << "0x" << std::uppercase << std::hex << ullhex.ref;
  return out;
}

std::istream &petuhov::operator>>(std::istream &in, UllOctIO &&ulloct)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  StreamGuard guard(in);

  in >> DelimiterIO{'0'} >> std::oct >> ulloct.ref;
  return in;
}

std::ostream &petuhov::operator<<(std::ostream &out, UllOctIO &&ulloct)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  StreamGuard guard(out);

  out << "0" << std::oct << ulloct.ref;
  return out;
}
