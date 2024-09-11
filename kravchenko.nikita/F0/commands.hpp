#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <algorithm>
#include <exception>
#include <functional>
#include <istream>
#include <iterator>
#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace kravchenko
{
  using FrequencyDict = std::map< std::string, size_t >;
  using DictionaryMap = std::map< std::string, FrequencyDict >;

  namespace cmd
  {
    using FreqCmd = std::function< void(std::istream&, std::ostream&, const DictionaryMap&) >;
    using FreqArgs = std::map< std::string, FreqCmd >;
    void freqWord(std::istream& in, std::ostream& out, const DictionaryMap& data);
    template < class Compare >
    void freqPred(std::istream& in, std::ostream& out, const DictionaryMap& data, Compare comp);

    using DictOperation = std::function< void(FrequencyDict&, const FrequencyDict&, const FrequencyDict&) >;
    void dictIntersect(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs);
    void dictUnion(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs);
    void dictDifference(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs);
    void dictComplement(FrequencyDict& out, const FrequencyDict& lhs, const FrequencyDict& rhs);
  }

  void cmdScanText(std::istream& in, std::ostream&, DictionaryMap& data);
  void cmdNew(std::istream& in, std::ostream&, DictionaryMap& data);
  void cmdRemove(std::istream& in, std::ostream&, DictionaryMap& data);
  void cmdList(std::ostream& out, const DictionaryMap& data);
  void cmdSave(std::istream& in, std::ostream& out, const DictionaryMap& data);
  void cmdFreq(std::istream& in, std::ostream& out, const DictionaryMap& data, const cmd::FreqArgs& args);
  void cmdSetOperation(std::istream& in, std::ostream& out, DictionaryMap& data, cmd::DictOperation dictOp, const char* opName);
}

template < class Compare >
void kravchenko::cmd::freqPred(std::istream& in, std::ostream& out, const DictionaryMap& data, Compare comp)
{
  std::string dictName;
  in >> dictName;

  if (data.find(dictName) == data.cend())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  size_t n = 10;
  if (!(in.peek() == '\n') && (!(in >> n) || (n == 0)))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  const FrequencyDict& dict = data.at(dictName);
  using WordPair = std::pair< std::string, size_t >;
  std::vector< WordPair > wordPairs;
  wordPairs.reserve(dict.size());

  std::copy(dict.cbegin(), dict.cend(), std::back_inserter(wordPairs));
  {
    using namespace std::placeholders;
    std::function< bool(const WordPair&, const WordPair&) > pairComp = std::bind(
      comp,
      std::bind(&WordPair::second, _1),
      std::bind(&WordPair::second, _2)
    );
    std::sort(wordPairs.begin(), wordPairs.end(), pairComp);
  }

  std::vector< std::string > sortedWords;
  sortedWords.reserve(wordPairs.size());
  std::function< std::string(const WordPair&) > getFirst = &WordPair::first;
  std::transform(wordPairs.begin(), wordPairs.end(), std::back_inserter(sortedWords), getFirst);

  using OutputItT = std::ostream_iterator< std::string >;
  std::copy_n(sortedWords.cbegin(), std::min(n, sortedWords.size()), OutputItT{ out, "\n" });
}

#endif
