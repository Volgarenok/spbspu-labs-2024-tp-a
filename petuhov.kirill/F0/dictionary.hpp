#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <string>
#include <stdexcept>

namespace petuhov {
  using namespace std;

  class Dictionary {
    public:
      void insert(const string& word, const string& translation, const string& additionalInfo);
      void search(const string& word) const;
      void remove(const string& word);

    private:
      map< string, map< string, string > > dictionary_;
};
}

#endif
