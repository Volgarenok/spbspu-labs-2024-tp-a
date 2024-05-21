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

      std::string& getPrimaryTranslation();
      const std::string& getPrimaryTranslation() const;
      std::string& getSecondaryTranslation();
      const std::string& getSecondaryTranslation() const;
      std::string& getAntonym();
      const std::string& getAntonym() const;

    private:
      std::string primaryTranslation_;
      std::string secondaryTranslation_;
      std::string antonym_;
    };

    std::istream& operator>>(std::istream& input, Word& word);
    std::ostream& operator<<(std::ostream& output, const Word& word);
  }
}
#endif