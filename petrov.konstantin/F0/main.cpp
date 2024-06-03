#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include "HuffmanCoding.hpp"
#include "userInterface.hpp"

int main()
{
  using UI = petrov::UserInterface;
  UI ui;
  ui.readCommand(std::cin, std::cout);
  return 0;
}
