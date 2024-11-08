#ifndef HELPERSTRUCTSIO_H
#define HELPERSTRUCTSIO_H

#include <iostream>
#include <string>

namespace stepanov
{
  struct DelimeterIO
  {
    explicit DelimeterIO(char exp);
    char getExp() const;

    private:
      char exp_;
  };

  struct LabelIO
  {
    explicit LabelIO(std::string exp);
    std::string getExp() const;

    private:
      std::string exp_;
  };

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
