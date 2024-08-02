#include <iostream>
#include <functional>
#include <exception>
#include <limits>
#include "ownCmds.hpp"
#include "huffmanCoding.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  setlocale(LC_ALL, "Russian");

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
  }

  Context context;
  CodeContext codeContext;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["--help"] = std::bind(help, _2);

    cmds["load"] = std::bind(load, _1, _2, std::ref(context));
    cmds["huff"] = std::bind(huff, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["compress"] = std::bind(compress, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["save"] = std::bind(save, _1, _2, std::ref(context));
    cmds["load_encoded"] = std::bind(loadEncoded, _1, _2, std::ref(codeContext));
    cmds["decompress"] = std::bind(decompress, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["eff"] = std::bind(eff, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["sort_data"] = std::bind(sortData, _1, _2, std::ref(context));
    cmds["remove_duplicates"] = std::bind(removeDuplicates, _1, _2, std::ref(context));
    cmds["count_words"] = std::bind(countWords, _1, _2, std::ref(context));
  }

  std::string cmd;
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return 0;
}
