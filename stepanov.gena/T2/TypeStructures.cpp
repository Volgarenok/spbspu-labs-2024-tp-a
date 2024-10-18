#include "TypeStructures.h"
#include <bitset>
#include <stack>
#include <iomanip>
#include <string>
#include <iostream>
#include "StreamGuard.h"
#include "HelperStructsIO.h"

namespace stepanov
{
  BinUnsignedLongLongIO::BinUnsignedLongLongIO(unsigned long long& ref):
    ref_(ref)
  {}

  StringIO::StringIO(std::string& ref):
    ref_(ref)
  {}

  OctUnsignedLongLongIO::OctUnsignedLongLongIO(unsigned long long& ref):
    ref_(ref)
  {}

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    StreamGuard format(in);
    in >> DelimeterIO{'\"'};
    std::getline(in,dest.ref_,'\"');
    return in;
  }

  std::ostream & operator<<(std::ostream & out, StringIO && dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    StreamGuard guard(out);

    out << std::quoted(dest.ref_, '\"');

    return out;
  }

  std::istream & operator>>(std::istream & in, BinUnsignedLongLongIO && dest)
  {
    std::istream::sentry sentryGuard(in);
    if (!sentryGuard)
    {
      return in;
    }

    unsigned long long dataCopy = dest.ref_;
    dest.ref_ = 0;

    StreamGuard guard(in);

    in >> DelimeterIO{'0'} >> DelimeterIO{'b'};

    in >> std::noskipws;

    std::stack< char > reverseStr;

    std::string str;
    std::getline(in, str, ':');

    for (size_t i = 0; str[i] != '\0'; ++i)
    {
      try
      {
        reverseStr.push(str[i]);
      }
      catch (...)
      {
        dest.ref_ = dataCopy;
        throw;
      }
    }

    unsigned long long pow = 1;
    size_t size = reverseStr.size();

    for (size_t i = 0; i < size; ++i)
    {
      dest.ref_ += (reverseStr.top() - '0') * pow;
      pow *= 2;
      try
      {
        reverseStr.pop();
      }
      catch (...)
      {
        dest.ref_ = dataCopy;
        throw;
      }
    }

    return in;
  }

  std::ostream & operator<<(std::ostream & out, BinUnsignedLongLongIO && dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    StreamGuard guard(out);

    out << "0b";

    std::stack< char > reverseBin;

    unsigned long long num = dest.ref_;

    for (size_t i = 0; (num > 0); ++i)
    {
      reverseBin.push(('0' + (num % 2)));
      num /= 2;
    }

    out << '0';

    size_t size = reverseBin.size();
    for (size_t i = 0; i < size; ++i)
    {
      out << reverseBin.top();
      reverseBin.pop();
    }

    return out;
  }

  std::ostream& operator<<(std::ostream& out, OctUnsignedLongLongIO&& dest)
  {
    out << std::oct << dest.ref_;
    return out;
  }

  std::istream& operator>>(std::istream& in, OctUnsignedLongLongIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    StreamGuard format(in);
    in >> std::oct >> dest.ref_;
    return in;
  }
}
