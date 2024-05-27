#ifndef ENGRUSDICTIONARY_HPP
#define ENGRUSDICTIONARY_HPP

#include <iostream>
#include <map>
#include <vector>
#include <set>

namespace belokurskaya
{
  class EngRusDict
  {
  public:
    EngRusDict();
    EngRusDict(const std::string& name);
    EngRusDict(const EngRusDict& other);
    ~EngRusDict();
    void clear();

    std::string getName() const;
    std::vector< std::string > getTranslations(std::string eng);

    size_t getCountWords();
    size_t getCountTranslations(std::string eng);

    void addTranslation(std::string eng, std::string translation);
    void removeTranslation(std::string eng, std::string translation);
    void addWord(std::string eng);
    void removeWord(std::string eng);

    void addWordFromEngRusDict(EngRusDict& other);
    void removeWordFromEngRusDict(EngRusDict& other);

    friend EngRusDict getIntersectionWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2);
    friend EngRusDict getDifferenceWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2);

    void display(std::ostream& out) const;

    EngRusDict& operator=(const EngRusDict& other);

  private:
    std::string name_;
    std::map< std::string, std::set< std::string > > words_;

    std::string getLettersToLower(const std::string& word);
    bool containsOnlyRussianLetters(const std::string& word) const;
    bool containsOnlyEnglishLetters(const std::string& word) const;
  };
}

#endif
