#ifndef VALUE_HPP
#define VALUE_HPP
#include <string>

namespace kozlova
{
  struct DblLitIO
  {
    double & dbllit_key ;
  };

  struct RatLspFIO
  {
    long long & ratlspf_key;
  };

  struct RatLspSIO
  {
    unsigned long long & ratlsps_key;
  };

  struct StringIO
  {
    std::string & string_key;
  };

  std::istream & operator>>(std::istream & in, DblLitIO && dest);
  std::istream & operator>>(std::istream & in, RatLspFIO && dest);
  std::istream & operator>>(std::istream & in, RatLspSIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
}
#endif
