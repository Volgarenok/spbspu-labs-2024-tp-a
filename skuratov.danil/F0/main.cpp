#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <cstddef>

class Node
{
public:
  int a = {};
  char c = {};
  Node* left = {};
  Node* right = {};

  Node()
  {}

  Node(Node* L, Node* R)
  {
    left = L;
    right = R;
    a = L->a + R->a;
  }
};

struct MyCompare
{
  bool operator()(Node* l, Node* r) const
  {
    return l->a < r->a;
  }
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

  std::list< Node* > t;

  std::map< char, int >::iterator ii;

  for (ii = m.begin(); ii != m.end(); ++ii)
  {
    Node* p = new Node;
    p->c = ii->first;
    p->a = ii->second;
    t.push_back(p);
  }

  while (t.size() != 1)
  {
    t.sort(MyCompare());

    Node* SonL = t.front();
    t.pop_front();
    Node* SonR = t.front();
    t.pop_front();

    Node* parent = new Node(SonL, SonR);
    t.push_back(parent);
  }
  Node* root = t.front();

  return 0;
}
