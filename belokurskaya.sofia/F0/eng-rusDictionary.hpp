#ifndef ENGRUSDICTIONARY_HPP
#define ENGRUSDICTIONARY_HPP

#include <iostream>
#include <map>
#include <set>

namespace belokurskaya
{
  class EngRusDict
  {
    public:
      EngRusDict();
      EngRusDict(const EngRusDict& other);
      EngRusDict(EngRusDict&& other) noexcept;
      ~EngRusDict();
      void clear();

      std::set< std::string > getTranslations(const std::string& eng) const;

      size_t getCountWords() const;
      size_t getCountTranslations(const std::string& eng) const;

      void addTranslation(const std::string& eng, const std::string& translation);
      void removeTranslation(const std::string& eng, const std::string& translation);
      void addWord(const std::string& eng);
      void removeWord(const std::string& eng);

      bool containsWord(const std::string& word) const;
      bool containsTranslation(const std::string& eng, const std::string& translation) const;

      std::set< std::string > getWords() const;

      void addWordFromEngRusDict(const EngRusDict& other);
      void removeWordFromEngRusDict(const EngRusDict& other);

      friend EngRusDict getIntersectionWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2);
      friend EngRusDict getDifferenceWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2);

      void display(std::ostream& out) const;

      EngRusDict& operator=(const EngRusDict& other);

    private:
      std::map< std::string, std::set< std::string > > words_;

      std::string getLettersToLower(std::string word);
      bool containsOnlyEnglishLetters(const std::string& word) const;
  };
  EngRusDict getIntersectionWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2);
  EngRusDict getDifferenceWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2);
}

#endif
