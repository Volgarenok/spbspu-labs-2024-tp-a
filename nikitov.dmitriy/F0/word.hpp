#ifndef WORD_HPP
#define WORD_HPP

#include <utility>
#include <string>

namespace nikitov
{
  namespace detail
  {
    class Word
    {
      std::string primaryTranslation_;
      std::string secondaryTranslation_;
      std::string antonym_;
    public:
      Word(const std::string& translation);

      std::string& getPrimaryTranslation();
      std::string& getSecondaryTranslation();
      const std::string& getAntonym() const;

      void addTranslation(const std::string& translation);
      void addAntonym(const std::string& antonym);
      void deleteTranslation(const std::string& translation);
    };
  }
}
#endif