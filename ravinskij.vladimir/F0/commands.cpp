#include "commands.hpp"
#include <iostream>

namespace rav = ravinskij;

void rav::printHelp()
{
  std::cout << "Usage: huffman [COMMAND] [FILES]...\n";
  std::cout << "Working with encoding and decoding texts from files.\n";
  std::cout << "Example: huffman encode text1 text2 encoding1\n";
  std::cout << "\nWorking with text:\n";
  std::cout << "\tadd-text\t <text-name> <file>\n";
  std::cout << "\tsave-text\t <text-name> <file>\n";
  std::cout << "\tdelete-text\t <text-name>\n";
  std::cout << "\tprint-text\t <text-name>\n";

  std::cout << "\nEncoding/decoding:\n";
  std::cout << "\tcreate-encoding\t <text-name> <encoding-name>\t\n";
  std::cout << "\tdelete-encoding\t <encoding-name>\t\n";
  std::cout << "\tencode\t\t <text-name>  <encoded-name> <encoding-name> \t\n";
  std::cout << "\tdecode\t\t <encoded-text> <decoded-text> <encoding-name>\t\n";
  std::cout << "\tadd-encoding\t <encoding-name> <file>\t\n";
  std::cout << "\tsave-encoding\t <encoding-name> <file>\t\n";

  std::cout << "\nComparing encodings:\n";
  std::cout << "\tcompare-encodings <text-name> <encoding-name-1> <encoding-name-2> <...> <encoding-name-N>\t";

  std::cout << "\n\nDescription:\n";
  std::cout << "\tadd-text\t add text to work with\n";
  std::cout << "\tsave-text\t write text to the file (content of the file will be overwritten)\n";
  std::cout << "\tdelete-text\t delete text to work with\n";
  std::cout << "\tprint-text\t print the text to the console\n";
  std::cout << "\tcreate-encoding\t create encoding table in accordance with the text\n";
  std::cout << "\tdelete-encoding\t delete encoding table to work with\n";
  std::cout << "\tencode\t\t encode the text in accordance with the encoding table\n";
  std::cout << "\tdecode\t\t decode the text in accordance with the encoding table\n";
  std::cout << "\tadd-encoding\t add the encoding table from the file in the format 'symbol - binary code'\n";
  std::cout << "\tsave-encoding\t save the encoding table to the file in the format 'symbol - binary code'\n";
  std::cout << "\tcompare-encodings\t Compares encodings applied to the same text.\n";
  std::cout << "\t\t\t\tDisplays a comparison table of the format on the console:";
  std::cout << "encoding name - size of the compressed text in bytes - \n\t\t\t\tcompression percentage accurate to two decimal places";
  std::cout << "(for the source text, the text name is displayed instead of the encoding).\n";
}

void rav::addText(std::istream& in, fileTable& files)
{
  std::string textName, fileName;
  in >> textName >> fileName;

  if (files.find(textName) != files.cend())
  {
    throw std::logic_error("Such text already exists");
  }

  std::ifstream input(fileName);
  if (!input.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }
  files.insert({textName, fileName});
}

void copyFile(std::ifstream& in, std::ostream& out)
{
  while(!in.eof())
  {
    std::string line;
    std::getline(in, line, '\n');
    out << line << '\n';
  }
}


void rav::saveText(std::istream& in, fileTable& files)
{
std::string textName, fileName;
  in >> textName >> fileName;
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("Requested text is not found");
  }
  std::ifstream input(files.find(textName)->second);
  std::ofstream output(fileName);
  if (!input.is_open() || !output.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }
  copyFile(input, output);
}

void rav::deleteText(std::istream& in, fileTable& files)
{
  std::string textName;
  in >> textName;
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("Requested text is not found");
  }
  files.erase(textName);
}

void rav::printText(std::istream& in, std::ostream& out, const fileTable& files)
{
  std::string textName;
  in >> textName;
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("Requested text is not found");
  }
  std::ifstream input(files.find(textName)->second);
  if (!input.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }
  copyFile(input, out);
}

void rav::createEncoding(std::istream& in, encodesTable& encodings, traverserTable& traverses, const fileTable& files)
{
}

void rav::deleteEncoding(std::istream& in, encodesTable& encodings, traverserTable& traverses)
{
}

void rav::encode(std::istream& in, const encodesTable& encodings, fileTable& files)
{
}

void rav::decode(std::istream& in, const traverserTable& traverses, fileTable& files)
{
}

void rav::addEncoding(std::istream& in, encodesTable& encodings)
{
}

void rav::saveEncoding(std::istream& in, encodesTable& encodings)
{
}

void rav::compareEncodings(std::istream& in, const encodesTable& encodings)
{
}

constexpr int bitsInByte()
{
  return 8;
}

void readAlphabet(std::istream &input, std::map<char, int> &alphabet)
{
  char c = 0;
  while (!input.eof())
  {
    c = input.get();
    alphabet[c]++;
  }

  input.clear();
  input.seekg(0);
}

void buildHuffmanTree(std::list<rav::Node *> &lst, const std::map<char, int> &alphabet, rav::NodeComparator comp)
{
  for (auto itr = alphabet.cbegin(); itr != alphabet.cend(); ++itr)
  {
    rav::Node *p = new rav::Node;
    p->symbol = itr->first;
    p->frequency = itr->second;
    lst.push_back(p);
  }


  while (lst.size() != 1)
  {
    lst.sort(comp);

    rav::Node *leftChild = lst.front();
    lst.pop_front();
    rav::Node *rightChild = lst.front();
    lst.pop_front();

    rav::Node *parent = new rav::Node(leftChild, rightChild);
    lst.push_back(parent);
  }
}

void buildTable(rav::Node *root, std::vector<bool> &code, rav::encodeMap &table)
{
  if (root->left != nullptr)
  {
    code.push_back(0);
    buildTable(root->left, code, table);
  }

  if (root->right != nullptr)
  {
    code.push_back(1);
    buildTable(root->right, code, table);
  }

  if (root->left == nullptr && root->right == nullptr)
    table[root->symbol] = code;

  code.pop_back();
}
