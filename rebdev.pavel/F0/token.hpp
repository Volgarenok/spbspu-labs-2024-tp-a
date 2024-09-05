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
      double num_;
      std::function< double(const double & ) > * unary_;
      std::function< double(const double &, const double & ) > * binary_;
      bool leftBracket_;
      data() = default;
      data(const data & d) = default;
      data(data && d) = default;
      data(double num);
      data(bool leftBracket);
      data(std::function< double(const double & ) > * unary);
      data(std::function< double(const double &, const double & ) > * binary);
      data & operator=(const data & d) = default;
      data & operator=(data && d) = default;
      ~data(){};
    };
    public:
      token() = default;
      token(const token & t) = default;
      token(token && t) = default;
      token(double num);
      token(bool leftBracket);
      token(std::function< double(const double & ) > * unary);
      token(std::function< double(const double &, const double & ) > * binary, std::string str);
      ~token() = default;
      token operator()(token f);
      token operator()(token f, token s);
      token & operator=(const token & t) = default;
      token & operator=(token && t) = default;
      double getNum() const noexcept;
      unsigned int priority() const noexcept;
      bool leftBracket() const noexcept;
    private:
      data data_;
      unsigned int priority_;
  };
}

#endif
