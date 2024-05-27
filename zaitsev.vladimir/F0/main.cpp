#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <string.h>
#include <experimental/filesystem>
#include <delimiter.hpp>
#include <stream_guard.hpp>
#include "i_o_processing.hpp"

using unit_t = std::map< std::string, int >;
using graph_t = std::map< std::string, unit_t >;
using base_t = std::map <std::string, graph_t >;

int main(int argc, char** argv)
{
  using namespace zaitsev;
  base_t graphs;

  if (argc > 3)
  {
    std::cerr << "Invalid number of arguments\n";
  }
  if (argc != 2 && argc != 3)
  {
    std::cout << "Created empty base\n";
  }
  try
  {
    if (argc == 2)
    {
      if (argv[1][0] == '-' && strcmp(argv[1], "-help"))
      {
        std::cerr << "Invalid option\n";
        init_base(argv[1], graphs);
      }
      if (!strcmp(argv[1], "-help"))
      {
        print_help();
      }
    }
    if (argc == 3)
    {
      if (strcmp(argv[1], "-help"))
      {
        std::cerr << "Invalid option\n";
      }
      else
      {
        print_help();
      }
      init_base(argv[2], graphs);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

 }
