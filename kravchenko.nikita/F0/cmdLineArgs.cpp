#include "cmdLineArgs.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <delimiterI.hpp>
#include "wordFreqPair.hpp"

void kravchenko::printHelp(std::ostream& out)
{
  out << "The \"Frequency Dictionary\" command system:\n";
  out << "1. scantext <dict> <text file>\n";
  out << "Analyze the text from the <text file> for frequency and add this data to the <dict> dictionary\n";
  out << "2. new <dict>\n";
  out << "Create an empty new <dict> dictionary\n";
  out << "3. list\n";
  out << "Print the names of all available dictionaries separated by a space\n";
  out << "4. remove <dict>\n";
  out << "Delete a dictionary named <dict>\n";
  out << "5. freq word <dict> <word>\n";
  out << "Output the frequency of the <word> word in the <dict> dictionary\n";
  out << "6. freq least <dict> [n]\n";
  out << "Output [n] of the most rarely occurring words in the <dict> dictionary in ascending order of frequency\n";
  out << "If [n] is not specified, output 10 words\n";
  out << "7. freq most <dict> [n]\n";
  out << "Output [n] of the most frequently occurring words in the <dict> dictionary in ascending order of frequency\n";
  out << "If [n] is not specified, output 10 words\n";
  out << "8. save [<dict1> ... <dictn>]\n";
  out << "Save the dictionaries [<dict1> ... <dictn>] into appropriate files in <dict>.txt format\n";
  out << "If dictionaries [<dict1> ... <dictn>] are not specified, save all available dictionaries in this way\n";
  out << "9. intersect <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Create a new <new dict> dictionary as the intersection of the <dict1> and <dict2> ... <dictn> dictionaries\n";
  out << "10. union <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Create a new <new dict> dictionary as a union of the <dict1> and <dict2> ... <dictn> dictionaries\n";
  out << "11. difference <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Create a new dictionary <new dict> as a difference of dictionaries <dict1> and <dict2> ... <dictn>\n";
  out << "12. complement <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Create a new <new dict> dictionary as a relative complement of the <dict1> dictionary with respect to <dict2> ... <dictn>\n";
}

void kravchenko::loadDict(const char* name, DictionaryMap& data)
{
  FrequencyDict loaded;
  std::ifstream file(std::string(name) + ".txt");
  std::function< const std::pair< std::string, size_t >&(const WordFreqPair&) > getPair = &WordFreqPair::pairT;
  using inputIt = std::istream_iterator< WordFreqPair >;
  std::transform(inputIt{ file }, inputIt{}, std::inserter(loaded, loaded.begin()), getPair);
  file.close();
  data[name] = loaded;
}

bool kravchenko::checkFile(const char* name)
{
  std::ifstream file(std::string(name) + ".txt");
  WordFreqPair toCheck;
  while (file >> toCheck);
  bool isValid = file.eof();
  file.close();
  return isValid;
}
