#include <fstream>
#include "huffmanCoding.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
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

  std::list< HuffmanTreeNode* > t;
  std::map< char, int >::iterator it;

  for (it = m.begin(); it != m.end(); ++it)
  {
    HuffmanTreeNode* p = new HuffmanTreeNode;
    p->c = it->first;
    p->a = it->second;
    t.push_back(p);
  }

  while (t.size() != 1)
  {
    t.sort(MyCompare());

    HuffmanTreeNode* SonL = t.front();
    t.pop_front();
    HuffmanTreeNode* SonR = t.front();
    t.pop_front();

    HuffmanTreeNode* parent = new HuffmanTreeNode(SonL, SonR);
    t.push_back(parent);
  }
  HuffmanTreeNode* root = t.front();

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
