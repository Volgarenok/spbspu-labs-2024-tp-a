#include <iostream>

void show_help()
{
  std::cout << "Commands: " << endl;
  std::cout << "load [filename]" << endl;
  std::cout << "add <dict> <key> - <lines>" << endl;
  std::cout << "top <dict>" << endl;
  std::cout << "remove <dict> <key>" << endl;
  std::cout << "merge <combDict> <dict1> <dict2>" << endl;
  std::cout << "countwords <dict>" << endl;
  std::cout << "clear <dict>" << endl;
  std::cout << "search <dict> <key>" << endl;
  std::cout << "matchWords <dict>" << endl;
  std::cout << "createDict <dict> <filename>" << endl;
  std::cout << "getAllEntries <dict>" << endl;
  std::cout << "intersection <dict> <dict2>" << endl;
  std::cout << "show" << endl;
  std::cout << "exit" << endl;
}

int main()
{
  return 0;
}
