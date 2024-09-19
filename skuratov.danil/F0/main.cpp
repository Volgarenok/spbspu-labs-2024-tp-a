#include <limits>
#include <exception>
#include <functional>
#include "ownCmds.hpp"
#include "huffmanCoding.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;

  std::cout << "Hello! Type '--help' to see the available commands." << '\n';

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
    cmds["comp"] = std::bind(compress, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["save"] = std::bind(save, _1, _2, std::ref(context));
    cmds["encload"] = std::bind(loadEncoded, _1, _2, std::ref(context));
    cmds["decomp"] = std::bind(decompress, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["eff"] = std::bind(eff, _1, _2, std::ref(context), std::ref(codeContext));
    cmds["sort"] = std::bind(sortData, _1, _2, std::ref(context));
    cmds["rm"] = std::bind(removeDuplicates, _1, _2, std::ref(context));
    cmds["count"] = std::bind(countWords, _1, _2, std::ref(context));
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      auto it = cmds.find(cmd);
      if (it != cmds.end())
      {
        it->second(std::cin, std::cout);
      }
      else
      {
        std::cerr << "<INVALID COMMAND>" << '\n';
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
