#include "commands.hpp"
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <bitset>
#include <functional>
#include <climits>
#include <limits>

void artemev::printHelp()
{
  std::setlocale(LC_ALL, "RU");
  std::cout << "1. read <textName> <file> - ";
  std::cout << "считывает текст из файла <file> и";
  std::cout << " записывает под именем <textName>\n";
  std::cout << "2. code <textName> <codeName> - ";
  std::cout << "создает кодировку из незашифрованного текста";
  std::cout << " <textName> и сохраняет под именем <codeName>,";
  std::cout << "выводя в стандартный поток вывода информацию о кодировке в виде: \n";
  std::cout << "[{символ}] = {количество встречаемого в тексте символа}:";
  std::cout << "{бинарный код символа}\n";
  std::cout << "3. encode <textName>  <codeName> <codedText> - ";
  std::cout << "кодирует текст <textname>, используя кодировку <codename> и";
  std::cout << " записывает результат в новый текст <codedtext>\n";
  std::cout << "4. write <codeName> <codedText> <newFileName> - ";
  std::cout << "создает закодированный файл <newFileName> на основании кодировки";
  std::cout << "<codeName> и закодированного текста <codedText>\n";
  std::cout << "5. uncode <textName> <fileName> - расшифровывает текст <textName>";
  std::cout << "и записывает в файл <fileName>\n";
  std::cout << "6. save text <textName> <newFile> - сохраняет текст <textName>";
  std::cout << " в новый файл\n";
  std::cout << "7. printtext <textName> - выводит текст на экран\n";
  std::cout << "8. printtable <codeName> - выводит частотную таблицу кодировки\n";
  std::cout << "9. delete <fileName> - удаляет <fileName>\n";
  std::cout << "10. size <textName> - выводит количество байтов в тексте\n";
  std::cout << "11. comp <coded_text> <original_text> - выводит процент сжатия файла\n";
  std::cout << "12. create <fileName> - сохраняет пользовательский ввод в <fileName>\n";
}

void artemev::create(std::istream& input)
{
  std::string fileName;
  input >> fileName;
  std::cout << "Enter text:\n";
  std::ofstream file(fileName);
  std::string text;
  input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  while (input)
  {
    input >> text;
    if (input)
    {
      file << text << std::endl;
    }
    else if (input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();
}

void artemev::printText(std::istream& input, std::ostream& out, const fileSheet& files)
{
  std::string textName;
  input >> textName;
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("ERROR! The text was not found");
  }

  std::ifstream fileT(files.find(textName)->second);
  char s[256];
  while (!fileT.eof())
  {
    fileT.getline(s, 256);
    out << s;
  }
  out << "\n\n";
}

void artemev::printTable(std::istream& input, std::ostream& out, const freqSheet& frequency)
{
  std::string codeName;
  input >> codeName;
  if (frequency.find(codeName) == frequency.cend())
  {
    throw std::logic_error("ERROR! The code was not found");
  }

  std::vector< int > freq = frequency.find(codeName)->second;
  for (size_t i = 0; i < freq.size(); ++i)
  {
    if (freq[i] != 0)
    {
      out << "[" << i << "] = " << freq[i] << "\t" << "\n";
    }
  }
  out << "\n";
}

void artemev::read(std::istream& in, fileSheet& file)
{
  std::string textName;
  std::string fileName;
  in >> textName >> fileName;

  if (file.find(textName) != file.cend())
  {
    throw std::logic_error("ERROR! Text exists");
  }

  if (!std::ifstream(fileName).is_open())
  {
    throw std::logic_error("ERROR! The file was not found");
  }

  for (const auto& pair : file)
  {
    if (pair.second == fileName)
    {
      throw std::logic_error("ERROR! The file is busy");
    }
  }
  file.insert({ textName, fileName });
}

void copyFile(std::ifstream& in, std::ostream& out)
{
  while (!in.eof())
  {
    std::string line;
    std::getline(in, line, '\n');
    out << line << '\n';
  }
}

void artemev::save(std::istream& in, fileSheet& file)
{
  std::string textName, fileName;
  in >> textName >> fileName;
  if (file.find(textName) == file.cend())
  {
    throw std::logic_error("ERROR! Text is not found");
  }

  std::ifstream input(file.find(textName)->second);
  std::ofstream output(fileName);
  if (!input.is_open() || !output.is_open())
  {
    throw std::logic_error("ERROR! Couldn't open file");
  }
  copyFile(input, output);
}

void artemev::deleteFiles(std::istream& in)
{
  std::string fileName;
  in >> fileName;
  if (remove(fileName.c_str()) == 0)
  {
    std::cout << "File " << fileName << " successfully deleted\n";
  }
  else
  {
    throw std::logic_error("ERROR! File " + fileName + " is not found");
  }
}

void getFreq(const std::string& filename, std::vector< int >& freq)
{
  std::ifstream file(filename, std::ifstream::binary);
  while (true)
  {
    char ch;
    file.read(&ch, 1);
    if (file.eof())
    {
      break;
    }
    freq[static_cast<unsigned char>(ch)]++;
  }
  file.close();
}

void processValue(artemev::queue_t& queue, uchar& byte, const int value)
{
  if (value != 0)
  {
    Node::pointer node = std::make_shared< Node >(byte, value);
    queue.push(node);
  }
  ++byte;
}

void fillQueue(std::vector< int >& frequency, artemev::queue_t& queue)
{
  uchar byte = 0;
  auto func = std::bind(processValue, std::ref(queue), std::ref(byte), std::placeholders::_1);
  std::for_each(frequency.begin(), frequency.end(), func);
}

void build_tree(artemev::queue_t& queue)
{
  while (queue.size() > 1)
  {
    Node::pointer x = queue.top();
    queue.pop();
    Node::pointer  y = queue.top();
    queue.pop();
    std::string name = x->get_name() + y->get_name();
    Node::pointer z = std::make_shared< Node >(name, x->getFrequency() + y->getFrequency());
    z->left = x;
    z->right = y;
    x->parent = z;
    y->parent = z;
    queue.push(z);
  }
}

void make_code(Node::pointer& node, std::string str, std::vector< std::string >& codes)
{
  if (node->left)
  {
    make_code(node->left, str + "0", codes);
  }

  if (node->right)
  {
    make_code(node->right, str + "1", codes);
  }

  if (!node->left && !node->right)
  {
    node->code(str);
    codes[node->get_byte()] = str;
    std::cout << *node << ": " << node->code() << "\n";
  }
}

void artemev::code(std::istream& input, codesSheet& codes, const fileSheet& files, freqSheet& frequency, queueSheet& queueMap)
{
  std::string textName;
  std::string codeName;
  input >> textName >> codeName;
  if (codes.find(codeName) != codes.cend())
  {
    throw std::logic_error("ERROR! Such coding already exists");
  }

  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("ERROR! Text is not found");
  }

  std::string ifs = files.at(textName);
  std::vector< int > freq(256, 0);
  getFreq(ifs, freq);

  artemev::queue_t queue;
  fillQueue(freq, queue);
  build_tree(queue);

  std::vector< std::string > code(256, "");
  Node::pointer root = queue.top();
  make_code (root, "", code);
  codes.insert({ codeName, code });
  frequency.insert({ codeName, freq });
  queueMap.insert({ codeName, queue });
  std::cout << std::endl;
}

std::string messageBinCode(const std::string& filename, const std::vector< std::string >& codes)
{
  std::string msg = "";
  std::ifstream ifs(filename, std::ifstream::binary);

  while (true)
  {
    char ch;
    ifs.read(&ch, 1);
    if (ifs.eof())
    {
      break;
    }
    msg += codes[static_cast< uchar >(ch)];
  }
  return msg;
}

void artemev::encode(std::istream& input, codesSheet& codes, const fileSheet& files, codeText& codeText)
{
  std::string textName;
  std::string codeName;
  std::string newText;

  input >> textName >> codeName >> newText;
  if (codes.find(codeName) == codes.cend())
  {
    throw std::logic_error("ERROR! Coding is not found");
  }
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("ERROR! Text is not found");
  }
  if (codeText.find(newText) != codeText.cend())
  {
    throw std::logic_error("ERROR! Such encoding already exists");
  }

  std::vector< std::string > code(codes.find(codeName)->second);
  std::string ifs = files.at(textName);
  std::string message = messageBinCode(ifs, code);
  codeText.insert({ newText, message });
}

void writeIndex(std::ofstream& ofs, unsigned char& index, int& value)
{
  if (value != 0) {
    ofs.write(reinterpret_cast< char* >(&index), sizeof(index));
    ofs.write(reinterpret_cast< char* >(&value), sizeof(value));
  }
  ++index;
}

void writeFile(const std::string& filename, std::vector< int >& frequency, const std::string& message)
{
  std::string newFilename = filename + ".art";
  std::ofstream ofs(newFilename, std::ofstream::binary);
  uchar count = std::count_if(frequency.begin(), frequency.end(), [](const int& value)
  { return (value != 0); });
  ofs.write(reinterpret_cast< char* >(&count), sizeof count);
  uchar index = 0;
  auto func = std::bind(writeIndex, std::ref(ofs), std::ref(index), std::placeholders::_1);
  std::for_each(frequency.begin(), frequency.end(), func);

  int byte_count = message.size() / 8;
  uchar modulo = message.size() % 8;
  ofs.write(reinterpret_cast< char* >(&byte_count), sizeof byte_count);
  ofs.write(reinterpret_cast< char* >(&modulo), sizeof modulo);

  int i = 0;
  for (; i < byte_count; ++i)
  {
    std::bitset< 8 > b(message.substr(i * 8, 8));
    uchar value = static_cast< uchar >(b.to_ulong());
    ofs.write(reinterpret_cast< char* >(&value), sizeof value);
  }

  if (modulo > 0)
  {
    std::bitset< 8 > b(message.substr(i * 8, modulo));
    uchar value = static_cast< uchar >(b.to_ulong());
    ofs.write(reinterpret_cast< char* >(&value), sizeof value);
  }
}

void artemev::write(std::istream& input, codeText& codeText, codesSheet& codes, freqSheet& freqMap, queueSheet& queueMap)
{
  std::string newFileName;
  std::string codedText;
  std::string codeName;
  input >> codeName >> codedText >> newFileName;
  if (codes.find(codeName) == codes.cend())
  {
    throw std::logic_error("ERROR! Code is not found");
  }
  if (codeText.find(codedText) == codeText.cend())
  {
    throw std::logic_error("ERROR! Text is not found");
  }

  std::string message(codeText.find(codedText)->second);
  std::vector< int > frequency(freqMap.find(codeName)->second);
  artemev::queue_t queue(queueMap.find(codeName)->second);
  writeFile(newFileName, frequency, message);
}

void readDecodingFile(std::string& filename, std::vector< int >& frequency, std::string& message)
{
  std::string new_filename = filename + ".art";
  std::ifstream ifs(new_filename, std::istream::binary);
  if (!ifs.is_open())
  {
    throw std::logic_error("ERROR! File " + filename + " is not found");
  }
  uchar count = 0;
  ifs.read(reinterpret_cast< char* >(&count), sizeof count);

  int i = 0;
  while (i < count)
  {
    uchar ch;
    ifs.read(reinterpret_cast< char* >(&ch), sizeof ch);

    int f = 0;
    ifs.read(reinterpret_cast< char* >(&f), sizeof f);
    frequency[ch] = f;
    ++i;
  }

  int byte_count = 0;
  uchar modulo = 0;
  ifs.read(reinterpret_cast< char* >(&byte_count), sizeof byte_count);
  ifs.read(reinterpret_cast< char* >(&modulo), sizeof modulo);

  i = 0;
  for (; i < byte_count; ++i)
  {
    uchar byte;
    ifs.read(reinterpret_cast< char* >(&byte), sizeof byte);

    std::bitset< 8 > b(byte);
    message += b.to_string();
  }

  if (modulo > 0)
  {
    uchar byte;
    ifs.read(reinterpret_cast< char* >(&byte), sizeof byte);

    std::bitset< 8 > b(byte);
    message += b.to_string().substr(8 - modulo, 8);
  }
}

void makeChar(const Node::pointer& root, const std::string& message, std::string& text)
{
  Node::pointer node = root;

  for (size_t i = 0; i < message.size(); ++i)
  {
    char ch = message[i];
    if (ch == '0')
    {
      if (node->left)
      {
        node = node->left;
        if (!node->left && !node->right)
        {
          text += node->get_byte();
          node = root;
        }
      }
    }
    else if (ch == '1')
    {
      if (node->right)
      {
        node = node->right;
        if (!node->left && !node->right)
        {
          text += node->get_byte();
          node = root;
        }
      }
    }
  }
}

void writeDecodingFile(const std::string& filename, const std::string& text)
{
  std::string new_filename = filename + ".txt";
  std::ofstream ofs(new_filename, std::ofstream::binary);
  ofs << text;
}

void artemev::uncode(std::istream& input)
{
  std::string codedFileName;
  std::string newFileName;
  input >> codedFileName >> newFileName;
  std::vector< int > freq2(256, 0);
  std::string msg2 = "";
  readDecodingFile(codedFileName, freq2, msg2);
  queue_t queue2;
  fillQueue(freq2, queue2);
  build_tree(queue2);
  Node::pointer root2 = queue2.top();
  std::string text = "";
  makeChar(root2, msg2, text);
  writeDecodingFile(newFileName, text);
}

size_t getSize(const std::string& fileName)
{
  std::fstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("ERROR! File not found: " + fileName);
  }
  size_t size = 0;
  file.seekg(0, std::ios::end);
  size = file.tellg();
  file.close();
  return size;
}

void artemev::size(std::istream& in, std::ostream& out)
{
  std::string fileName;
  in >> fileName;
  size_t size = getSize(fileName);
  out << "Your file weight " << size << " bytes\n\n";
}

void artemev::comparator(std::istream& in, std::ostream& out)
{
  std::string fileName1;
  std::string fileName2;
  in >> fileName1 >> fileName2;
  double size1 = getSize(fileName1);
  double size2 = getSize(fileName2);
  double comp = size1 / size2;
  if (size1 < size2)
  {
    out << "File size " << fileName1 << " is smaller than " << fileName2 <<
    " by " << std::setprecision(2) << comp * 100 << " % \n\n";
  }
  else
  {
    out << "File size " << fileName1 << " is bigger than " << fileName2 <<
    " by " << comp * 100 << " % \n\n";
  }
}
