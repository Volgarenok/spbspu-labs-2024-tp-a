#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <functional>

namespace rebdev
{
  class token
  {
    union data
    {
      long long num_;
      std::function< long long(const long long & ) > * unary_;
      std::function< long long(const long long &, const long long & ) > * binary_;
      bool leftBracket_;
      data() = default;
      data(const data & d) = default;
      data(data && d) = default;
      data(long long num);
      data(bool leftBracket);
      data(std::function< long long(const long long & ) > * unary);
      data(std::function< long long(const long long &, const long long & ) > * binary);
      data & operator=(const data & d) = default;
      data & operator=(data && d) = default;
      ~data(){};
    };
    public:
      token() = default;
      token(const token & t) = default;
      token(token && t) = default;
      token(long long num);
      token(bool leftBracket);
      token(std::function< long long(const long long & ) > * unary);
      token(std::function< long long(const long long &, const long long & ) > * binary, std::string str);
      ~token() = default;
      token operator()(token f);
      token operator()(token f, token s);
      token & operator=(const token & t) = default;
      token & operator=(token && t) = default;
      long long getNum() const noexcept;
      unsigned int priority() const noexcept;
      bool leftBracket() const noexcept;
    private:
      data data_;
      unsigned int priority_;
  };
}

#endif
