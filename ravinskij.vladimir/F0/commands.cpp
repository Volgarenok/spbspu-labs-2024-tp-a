#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <scopeGuard.hpp>
#include "codeWrappers.hpp"

namespace rav = ravinskij;

void rav::printHelp(std::ostream& out)
{
  out << "Usage: huffman [COMMAND] [FILES]...\n";
  out << "Working with encoding and decoding texts from files.\n";
  out << "Example: huffman encode text1 text2 encoding1\n";
  out << "\nWorking with text:\n";
  out << "\tadd-text\t <text-name> <file>\n";
  out << "\tsave-text\t <text-name> <file>\n";
  out << "\tdelete-text\t <text-name>\n";
  out << "\tprint-text\t <text-name>\n";

  out << "\nEncoding/decoding:\n";
  out << "\tcreate-encoding\t <text-name> <encoding-name>\t\n";
  out << "\tdelete-encoding\t <encoding-name>\t\n";
  out << "\tencode\t\t <text-name>  <encoded-name> <encoding-name> \t\n";
  out << "\tdecode\t\t <encoded-text> <decoded-text> <encoding-name>\t\n";
  out << "\tadd-encoding\t <encoding-name> <file>\t\n";
  out << "\tsave-encoding\t <encoding-name> <file>\t\n";

  out << "\nComparing encodings:\n";
  out << "\tcompare-encodings <text-name> <encoding-name-1> <encoding-name-2> <...> <encoding-name-N>\t";

  out << "\n\nDescription:\n";
  out << "\tadd-text\t add text to work with\n";
  out << "\tsave-text\t write text to the file (content of the file will be overwritten)\n";
  out << "\tdelete-text\t delete text to work with\n";
  out << "\tprint-text\t print the text to the console\n";
  out << "\tcreate-encoding\t create encoding table in accordance with the text\n";
  out << "\tdelete-encoding\t delete encoding table to work with\n";
  out << "\tencode\t\t encode the text in accordance with the encoding table\n";
  out << "\tdecode\t\t decode the text in accordance with the encoding table\n";
  out << "\tadd-encoding\t add the encoding table from the file in the format 'symbol - binary code'\n";
  out << "\tsave-encoding\t save the encoding table to the file in the format 'symbol - binary code'\n";
  out << "\tcompare-encodings\t Compares encodings applied to the same text.\n";
  out << "\t\t\t\tDisplays a comparison table of the format on the console:";
  out << "encoding name - size of the compressed text in bytes - \n\t\t\t\tcompression percentage accurate to two decimal places";
  out << "(for the source text, the text name is displayed instead of the encoding).\n";
}

void copyFile(std::ifstream& in, std::ostream& out)
{
  using input_it_t = std::istreambuf_iterator< char >;
  using output_it_t = std::ostream_iterator< char >;
  std::copy(input_it_t{ in }, input_it_t{}, output_it_t{ out, "" });
  out << '\n';
}

void readAlphabet(std::istream& input, std::map< char, size_t >& alphabet)
{
  char c = 0;
  while (!input.eof())
  {
    c = input.get();
    alphabet[c]++;
  }
}

auto getNodePtr(const std::pair< char, size_t >& map)
{
  return std::make_shared< rav::Node >(map.second, map.first);
}

void buildHuffmanTree(std::list< rav::nodePtr >& lst, const std::map< char, size_t >& alphabet, rav::NodeComparator comp)
{
  std::transform(alphabet.cbegin(), alphabet.cend(), std::back_inserter(lst), getNodePtr);

  while (lst.size() != 1)
  {
    lst.sort(comp);

    rav::nodePtr leftChild = lst.front();
    lst.pop_front();
    rav:: nodePtr rightChild = lst.front();
    lst.pop_front();

    rav::nodePtr parent = std::make_shared< rav::Node >(leftChild, rightChild);
    lst.push_back(parent);
  }
}

void buildTable(const rav::nodePtr& root, std::vector< bool >& code, rav::encodeMap& table)
{
  const bool ZERO_BIT = false;
  const bool ONE_BIT = true;
  if (root->left != nullptr)
  {
    code.push_back(ZERO_BIT);
    buildTable(root->left, code, table);
  }

  if (root->right != nullptr)
  {
    code.push_back(ONE_BIT);
    buildTable(root->right, code, table);
  }

  if ((root->left == nullptr) && (root->right == nullptr))
    table[root->symbol] = code;

  code.pop_back();
}

void buildTable(const rav::nodePtr& root, rav::encodeMap& table)
{
  std::vector< bool > tempCode{};
  buildTable(root, tempCode, table);
}

void encodeImplement(const rav::encodeMap& table, std::istream& input, std::ostream& output)
{
  size_t position = 0;
  char buf = 0;
  const size_t BITS_IN_BYTE = 8;
  while (!input.eof())
  {
    char c = input.get();
    std::vector< bool > temp = table.at(c);
    for (size_t n = 0; n < temp.size(); n++)
    {
      buf = buf | temp[n] << (BITS_IN_BYTE - 1 - position);
      position++;
      if (position == BITS_IN_BYTE)
      {
        position = 0;
        output << buf;
        buf = 0;
      }
    }
  }
}

void decodeImplement(const std::list< rav::nodePtr >& travers, std::istream& input, std::ostream& output)
{
  rav::nodePtr root = travers.front();
  rav::nodePtr traverser = root;
  size_t position = 0;
  char byte = 0;
  byte = input.get();
  const size_t BITS_IN_BYTE = 8;
  while (!input.eof())
  {
    bool checkedBitState = byte & (1 << (BITS_IN_BYTE - 1 - position));
    if (checkedBitState)
    {
      traverser = traverser->right;
    }
    else
    {
      traverser = traverser->left;
    }
    if (traverser->left == nullptr && traverser->right == nullptr)
    {
      if (traverser->symbol != EOF)
      {
        output << traverser->symbol;
        traverser = root;
      }
    }
    position++;
    if (position == BITS_IN_BYTE)
    {
      position = 0;
      byte = input.get();
    }
  }
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
  files.insert({ textName, fileName });
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
  std::string textName, encodingName;
  in >> textName >> encodingName;
  if (encodings.find(encodingName) != encodings.cend())
  {
    throw std::logic_error("Such encoding already exists");
  }

  std::ifstream input(files.at(textName));
  if (!input.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }

  std::map< char, size_t > alphabet;
  readAlphabet(input, alphabet);
  std::list< rav::nodePtr > tree;
  buildHuffmanTree(tree, alphabet, rav::NodeComparator{});
  traverses.insert({ encodingName, tree });
  buildTable(tree.front(), encodings[encodingName]);
}

void rav::deleteEncoding(std::istream& in, encodesTable& encodings, traverserTable& traverses)
{
  std::string encodingName;
  in >> encodingName;
  if (encodings.find(encodingName) == encodings.cend())
  {
    throw std::logic_error("No such encoding is provided");
  }
  encodings.erase(encodingName);
  traverses.erase(encodingName);
}

void rav::encode(std::istream& in, const encodesTable& encodings, fileTable& files)
{
  std::string textName, encodedName, encodingName;
  in >> textName >> encodedName >> encodingName;

  if (encodings.find(encodingName) == encodings.cend())
  {
    throw std::logic_error("No such encoding is provided");
  }
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("No such text is provided");
  }
  if (textName == encodedName)
  {
    throw std::logic_error("Names collision occured");
  }

  std::ifstream input(files[textName]);
  files.insert({ encodedName, encodedName });
  std::ofstream output(files[encodedName], std::ios::out | std::ios::binary);
  if (!input.is_open() || !output.is_open())
  {
    throw std::logic_error("Couldn't open files");
  }
  encodeImplement(encodings.find(encodingName)->second, input, output);
}

void rav::decode(std::istream& in, const traverserTable& traverses, fileTable& files)
{
  std::string textName, decodedName, encodingName;
  in >> textName >> decodedName >> encodingName;
  if (textName == decodedName)
  {
    throw std::logic_error("Names collision has occured");
  }
  if (traverses.find(encodingName) == traverses.cend())
  {
    throw std::logic_error("No such encoding is provided");
  }
  std::ifstream input(files.at(textName), std::ios::in | std::ios::binary);
  std::ofstream output(decodedName);
  if (!input.is_open() || !output.is_open())
  {
    throw std::logic_error("Couldn't open any file");
  }
  std::list< rav::nodePtr > traverser = traverses.find(encodingName)->second;
  decodeImplement(traverser, input, output);
  files.insert({ decodedName, decodedName });
}

void rav::addEncoding(std::istream& in, encodesTable& encodings, traverserTable& traverses)
{
  std::string encodingName, fileName;
  in >> encodingName >> fileName;
  if (encodings.find(encodingName) != encodings.cend())
  {
    throw std::logic_error("Such encoding already exists");
  }
  std::ifstream input(fileName);
  if (!input.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }
  rav::encodeMap map;
  std::map< char, size_t > alphabet;
  while (!input.eof())
  {
    char ch = 0;
    std::vector< bool > code;
    size_t freq = 0;
    input >> rav::ReadWrapper{ ch, code, freq };
    map.insert({ ch, code });
    alphabet.insert({ ch, freq });
  }
  encodings.insert({ encodingName, map });
  std::list< rav::nodePtr > newTraverser;
  buildHuffmanTree(newTraverser, alphabet, rav::NodeComparator{});
  traverses.insert({ encodingName, newTraverser });
}

size_t getFrequency(rav::nodePtr root, const std::pair< char, std::vector< bool > >& map)
{
  const std::vector< bool >& code = map.second;
  for (bool bit: code)
  {
    if (root == nullptr)
    {
      return 0;
    }
    root = (bit == 0 ? root->left : root->right);
  }
  return root->frequency;
}

void rav::saveEncoding(std::istream& in, const encodesTable& encodings, const traverserTable& traverses)
{
  std::string encodingName, fileName;
  in >> encodingName >> fileName;
  auto currEncoding = encodings.find(encodingName);
  if (currEncoding == encodings.cend())
  {
    throw std::logic_error("No such encoding is provided");
  }
  std::ofstream output(fileName);
  auto beginIt = currEncoding->second.cbegin();
  auto endIt = currEncoding->second.cend();
  std::list< size_t > frequencies;
  auto root = traverses.find(encodingName)->second.front();
  auto unaryOperator = std::bind(getFrequency, root, std::placeholders::_1);
  std::transform(beginIt, endIt, std::back_inserter(frequencies), unaryOperator);

  output << WriteWrapper{ beginIt->first, beginIt->second, frequencies.front() };
  frequencies.pop_front();
  ++beginIt;
  for (auto it = beginIt; it != endIt; ++it)
  {
    output << '\n' << WriteWrapper{ it->first, it->second, frequencies.front() };
    frequencies.pop_front();
  }
}

std::ifstream::pos_type getFileSize(const std::string& filename)
{
  std::ifstream in(filename, std::ios::ate | std::ios::binary);
  return in.tellg();
}

double getCompessionPercentage(size_t oldSize, size_t newSize)
{
  return static_cast< double >((oldSize - newSize)) / oldSize;
}

void inputArgs(std::list< std::string >& args, std::istream& in)
{
  std::string arg;
  rav::ScopeGuard guard(in);
  in >> std::noskipws;
  char delim = 0;
  in >> delim;
  while (in && delim != '\n')
  {
    in >> arg >> delim;
    if (in)
    {
      args.push_back(arg);
    }
  }
}

void rav::compareEncodings(std::istream& in, std::ostream& output, const fileTable& files, const encodesTable& encodings)
{
  std::list< std::string > args;
  inputArgs(args, in);
  if (args.empty())
  {
    throw std::logic_error("No arguments are provided");
  }
  std::string fileName = args.front();
  args.pop_front();
  if (files.find(fileName) == files.cend())
  {
    throw std::logic_error("No such file is provided");
  }
  std::ifstream file(files.find(fileName)->second);
  ScopeGuard outGuard(output);
  output << std::fixed << std::setprecision(2);
  size_t fileSize = getFileSize(files.find(fileName)->second);
  output << fileName << ' ' << fileSize << ' ' << getCompessionPercentage(fileSize, fileSize) << '\n';
  file.close();
  for (const auto& arg: args)
  {
    if (encodings.find(arg) == encodings.cend())
    {
      throw std::logic_error("No such encoding is provided");
    }
    file.open(files.find(fileName)->second);
    std::ofstream out(arg, std::ios::binary);
    encodeImplement(encodings.find(arg)->second, file, out);
    out.close();
    file.close();
    size_t compressedSize = getFileSize(arg);
    output << arg << ' ' << compressedSize << ' ' << getCompessionPercentage(fileSize, compressedSize) << '\n';
  }
}

std::string getFirst(const std::pair< std::string, std::string >& textPair)
{
  return textPair.first;
}

std::string getSecond(const std::pair< std::string, std::string >& textPair)
{
  return textPair.second;
}

std::string getAll(const std::pair< std::string, std::string >& textPair)
{
  return textPair.first + " " + textPair.second;
}

void rav::printFiles(std::istream&, std::ostream& out, const fileTable& files)
{
  if (files.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  using output_it_t = std::ostream_iterator< std::string >;
  std::transform(files.cbegin(), files.cend(), output_it_t{ out, " " }, getSecond);
  out << '\n';
}

void rav::printTexts(std::istream&, std::ostream& out, const fileTable& files)
{
  if (files.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  using output_it_t = std::ostream_iterator< std::string >;
  std::transform(files.cbegin(), files.cend(), output_it_t{ out, " " }, getFirst);
  out << '\n';
}

void rav::printAll(std::istream&, std::ostream& out, const fileTable& files)
{
  if (files.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  using output_it_t = std::ostream_iterator< std::string >;
  std::transform(files.cbegin(), files.cend(), output_it_t{ out, " " }, getAll);
  out << '\n';
}
