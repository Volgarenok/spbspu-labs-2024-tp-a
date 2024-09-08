#include "non_interactive_cmd.hpp"
#include <algorithm>
#include <ostream>
#include <fstream>
#include <functional>

void isaychev::print_help(std::ostream & out)
{
  out << "Command Line Options:\n  --saved start with loading previously saved data from the <saved> file\n";
  out << "  --help output help\n\nCommands:\n";
  out << "1.  make <file name> <new list name>\n    Create a frequency list based on a text file.\n";
  out << "2.  delete <list name>\n    Delete a frequency list.\n";
  out << "3.  merge <new list> <list name 1> <list name 2>\n";
  out << "    Create a new frequency list by merging contents of the following lists\n";
  out << "4.  print <list name>\n    Output the contents of the list.\n";
  out << "5.  printlast <list name> <number of words>\n    Output n positions of the frequency list, ";
  out << "starting from the end.\n";
  out << "6.  printfirst <list name> <number of words>\n";
  out << "    Output the first n words of the frequency list to the console, starting from begining.\n";
  out << "7.  intersect <new list> <list name 1> <list name 2>\n";
  out << "    Create a new frequency list containing words that are in both lists at the same time.\n";
  out << "8.  getcount <word> <list name>\n";
  out << "    Output how many times a word occurs in the text, based on the frequency list.\n";
  out << "9.  total <list name>\n";
  out << "    Output the number of words in the text based on the list.\n";
  out << "10. unique <list name>\n";
  out << "    Print the number of unique words that are in the list.\n";
  out << "11. clear\n    Clear data of current session.\n12. ls\n    Print names of all lists.\n";
  out << "13. execlude [more/less] <new list> <list name> <total>\n"
  out << "    Create a frequency list based on words of <list name> which amount ";
  out << "is greater or lesser than total\n";
}

isaychev::value_t read_value(std::istream & in)
{
  size_t n = 0;
  std::string str;
  in >> n >> str;
  return {{str}, n};
}

std::pair< std::string, isaychev::FreqList > read_list(std::istream & in)
{
  std::string name;
  size_t elem_count = 0;
  in >> name >> elem_count;
  std::map< isaychev::Word, size_t > temp;
  auto generator = std::bind(read_value, std::ref(in));
  std::generate_n(std::inserter(temp, temp.end()), elem_count, generator);
  return {name, isaychev::FreqList(std::move(temp))};
}

void isaychev::load_saved(std::map< std::string, FreqList > & col)
{
  std::fstream in("saved");
  if (!in.is_open())
  {
    throw std::runtime_error("bad file");
  }
  size_t count = 0;
  in >> count;
  auto generator = std::bind(read_list, std::ref(in));
  std::generate_n(std::inserter(col, col.end()), count, generator);
}

void output_name_and_content(std::ostream & out, const std::pair< std::string, isaychev::FreqList> & rhs)
{
  out << rhs.first << ' ' << rhs.second.size() << '\n';
  out << rhs.second;
}

void isaychev::save(const collection_t & col)
{
  using namespace std::placeholders;
  std::ofstream file("saved");
  file << col.size() << "\n";
  auto functor = std::bind(output_name_and_content, std::ref(file), _1);
  std::for_each(col.begin(), col.end(), functor);
}
