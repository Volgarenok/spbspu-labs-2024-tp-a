#ifndef WORD_HPP
#define WORD_HPP

#include <ostream>
#include <utility>
#include <string>

namespace nikitov
{
  namespace detail
  {
    class Word
    {
    public:
      Word(const std::string& translation);
      ~Word() = default;

      std::ostream& operator<<(std::ostream& output);

      std::string& getPrimaryTranslation();
      std::string& getSecondaryTranslation();
      std::string& getAntonym();

    private:
      std::string primaryTranslation_;
      std::string secondaryTranslation_;
      std::string antonym_;
    };
  }
}
#endif