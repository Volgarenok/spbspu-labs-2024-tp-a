#include "secondary_commands.hpp"
#include <iostream>
#include <fstream>
#include "format.hpp"
#include "input_output_collection.hpp"

void erohin::printHelp(std::ostream & output)
{
  output << "Use: program [options] <freqdict> — starting with use a file <freqdict>\n";
  output << "Creation and store a frequency dictionary based on the text.";
  output << "The opportunity to change and view the contents of several frequency dictionaries.\n\n";
  output << "Аргументы командной строки:\n";
  output << "\t--help — \"помощь\" по программе\n";
  output << "\t--check — check the data correctness\n";
  output << "\t--numformat=<format> — starting with use a file <freqdict> with style <format>\n";
  output << "\t<format> = { NUMBER, PROPORTION, FRACTIONAL, PERCANTAGE }\n\n";
  output << "Commands:\n";
  output << "\t1. addtext <text> <source>\n";
  output << "\tAdd a text named <text>, read from the <source> file.\n\n";
  output << "\t2. removetext <text>\n";
  output << "\tDelete text named <text>.\n\n";
  output << "\t3. createdict <dict> <text>\n";
  output << "\tCreate a new frequency dictionary named <dict> based on a text named <text>.\n\n";
  output << "\t4. removedict <dict>\n";
  output << "\tDelete a frequency dictionary named <dict>.\n\n";
  output << "\t5. print <dict>\n";
  output << "\tPrint a frequency dictionary named <dict>.\n\n";
  output << "\t6. count <dict>\n";
  output << "\tPrint the total number of words and the number of unique words in the dictionary <dict>.\n\n";
  output << "\t7. sort <dict>\n";
  output << "\tPrint a frequency dictionary <dict> sorted by the frequency of words.\n\n";
  output << "\t8. find <dict> <word>\n";
  output << "\tFind the word <word> in the frequency dictionary <dict> and print its frequency.\n\n";
  output << "\t9. top <new_dict> <dict> <top_number>\n";
  output << "\tCreate a frequency dictionary <new_dict> from the most frequent <top_number> words of <dict>.\n\n";
  output << "\t10. bottom <new_dict> <dict> <bot_number>\n";
  output << "\tCreate a frequency dictionary <new_dict> from the least frequent <top_number> words of <dict>.\n\n";
  output << "\t11. differ <new_dict> <dict1> <dict2>\n";
  output << "\tCreate a frequency dictionary <new_dict> based on the difference between <dict1> and <dirt2>.\n\n";
  output << "\t12. unite <new_dict> <dict1> <dict2>\n";
  output << "\tCreate a frequency dictionary <new_dict> based on the union between <dict1> and <dirt2>.\n\n";
  output << "\t13. intersect <new_dict> <dict1> <dict2>\n";
  output << "\tCreate a frequency dictionary <new_dict> based on the intersection between <dict1> and <dirt2>.\n\n";
}

void erohin::checkDictionary(const char * file_name, std::ostream & output)
{
  std::fstream file(file_name, std::ios::in);
  collection dict_context;
  std::string dict_name;
  file >> StringFormat{ dict_name, ':' };
  while (!file.eof())
  {
    if (file.fail())
    {
      break;
    }
    inputDictionary(dict_context[dict_name], file);
    if (!file)
    {
      file.clear();
    }
    file >> StringFormat{ dict_name, ':' };
  }
  file.close();
  output << "File contains " << (!file.eof() && file.fail() ? "incorrect" : "correct") << " frequency dictionaries.\n";
}
