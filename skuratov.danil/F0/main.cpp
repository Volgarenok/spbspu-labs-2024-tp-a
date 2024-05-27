#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <cstddef>
#include <fstream>

class Node
{
public:
  int a = {};
  char c = {};
  Node* left;
  Node* right;

  Node()
  {
    left = nullptr;
    right = nullptr;
  }

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

std::vector< bool > code;
std::map< char, std::vector< bool > > table;

void buildAssociationTable(Node* root)
{
  if (root->left != nullptr)
  {
    code.push_back(0);
    buildAssociationTable(root->left);
    code.pop_back();
  }

  if (root->right != nullptr)
  {
    code.push_back(1);
    buildAssociationTable(root->right);
    code.pop_back();
  }

  if (root->left == nullptr && root->right == nullptr)
  {
    table[root->c] = code;
  }
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Missing filename argument" << '\n';
    return 1;
  }

  std::map< char, int > m;
  std::ifstream infile(argv[1]);

  if (!infile)
  {
    std::cerr << "Error opening file" << '\n';
    return 1;
  }

  while (!infile.eof())
  {
    char c = infile.get();
    m[c]++;
  }

  std::list< Node* > t;
  std::map< char, int >::iterator it;

  for (it = m.begin(); it != m.end(); ++it)
  {
    Node* p = new Node;
    p->c = it->first;
    p->a = it->second;
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

  buildAssociationTable(root);

  infile.clear();
  infile.seekg(0);

  while (infile)
  {
    char c = {};
    infile >> c;
    if (!infile)
    {
      break;
    }
    std::vector< bool > x = table[c];
    for (int j = 0; j < x.size(); j++)
    {
      std::cout << x[j];
    }
  }
  return 0;
}
