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

    std::set< std::string > getTranslations(std::string eng);

    size_t getCountWords();
    size_t getCountTranslations(std::string eng);

    void addTranslation(std::string eng, std::string translation);
    void removeTranslation(std::string eng, std::string translation);
    void addWord(std::string eng);
    void removeWord(std::string eng);

    void addWordFromEngRusDict(EngRusDict& other);
    void removeWordFromEngRusDict(EngRusDict& other);

    friend EngRusDict getIntersectionWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2);
    friend EngRusDict getDifferenceWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2);

    void display(std::ostream& out) const;

    EngRusDict& operator=(const EngRusDict& other);

  private:
    std::map< std::string, std::set< std::string > > words_;

    std::string getLettersToLower(const std::string& word);
    bool containsOnlyRussianLetters(const std::string& word) const;
    bool containsOnlyEnglishLetters(const std::string& word) const;
  };
}

#endif
