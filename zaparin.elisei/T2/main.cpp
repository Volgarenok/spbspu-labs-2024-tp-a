#include"delimeter.hpp"
#include<iostream>

#include<fstream>
#include<string>

int main()
{
  int num = 0b010101;
  std::string text = "";

  std::ifstream in;
  in.open("text.txt");
  if (in)
  {
    std::cout << "Good";
  }
  else
  {
    std::cerr << "Error!";
  }

  in.close();
}