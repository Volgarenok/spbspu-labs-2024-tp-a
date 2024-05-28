#include <fstream>
#include <functional>
#include <exception>
#include <limits>
#include "ownCmds.hpp"
#include "huffmanCoding.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  setlocale(LC_ALL, "Russian");

  std::map< std::string, std::string > texts;

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    std::string key, text = {};
    while (infile >> key)
    {
      infile.ignore();
      getline(infile, text);
      texts[key] = text;
    }
  }

  std::map< std::string, std::function< void(std::istream& in, std::ostream& out)>> cmds;
  {
    using namespace std::placeholders;
    cmds["--help"] = std::bind(help, _2);

    cmds["load"] = std::bind(load, _1, _2);
    cmds["huff"] = std::bind(huff, _1, _2);
    cmds["compress"] = std::bind(compress, _1, _2);
    cmds["save"] = std::bind(save, _1, _2);
    cmds["load_encoded"] = std::bind(loadEncoded,_1, _2);
    cmds["decompress"] = std::bind(decompress, _1, _2);
    cmds["eff"] = std::bind(eff, _1, _2);
    cmds["sort_data"] = std::bind(sortData, _1, _2);
    cmds["remove_duplicates"] = std::bind(removeDuplicates, _1, _2);
    cmds["count_words"] = std::bind(countWords, _1, _2);
  }

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
