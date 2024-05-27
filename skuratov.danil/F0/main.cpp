#include <iostream>
#include <map>
#include <vector>
#include <list>

template < typename T >
class Node
{
public:
  int a;
  Node< T >* left;
  Node< T >* right;
};

int main(int argc, char* argv[])
{
  std::string s = "it is my striiiiing!!!!";
  std::map< char, int > m;

  for (int i = 0; i < s.length(); i++)
  {
    char c = s[i];
    m[c]++;
  }

  std::map< char, int >::iterator i;

  for (i = m.begin(); i != m.end(); ++i)
  {
    std::cout << i->first << ":" << i->second << '\n';
  }
  return 0;
}
