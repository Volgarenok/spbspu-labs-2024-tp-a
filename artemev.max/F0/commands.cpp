#include "commands.hpp"
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <climits>

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

void fill_queue(std::vector< int >& frequency, artemev::queue_t& queue)
{
  uchar byte = 0;
  for (size_t i = 0; i < frequency.size(); ++i)
  {
    int value = frequency[i];
    if (value != 0)
    {
        Node::pointer node = std::make_shared<Node>(byte, value);
        queue.push(node);
    }
    ++byte;
  }
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
  }
}

std::string message2code(const std::string& filename, const std::vector< std::string >& codes)
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

    msg += codes[static_cast<uchar>(ch)];
  }
  return msg;
}

void write_file(const std::string& filename, std::vector< int >& frequency, const std::string& message)
{
  std::string new_filename = filename + ".art";
  std::ofstream ofs(new_filename, std::ofstream::binary);
  uchar count = std::count_if(frequency.begin(), frequency.end(), [](const int& value) { return (value != 0); });
  ofs.write(reinterpret_cast<char*>(&count), sizeof count);
  for (size_t i = 0; i < frequency.size(); ++i)
  {
    int value = frequency[i];
    if (value != 0)
    {
        uchar index = static_cast<uchar>(i);
        ofs.write(reinterpret_cast<char*>(&index), sizeof(index));
        ofs.write(reinterpret_cast<char*>(&value), sizeof(value));
    }
  }

  int byte_count = message.size() / CHAR_BIT;
  uchar modulo = message.size() % CHAR_BIT;
  ofs.write(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
  ofs.write(reinterpret_cast<char*>(&modulo), sizeof modulo);

  int i = 0;
  for (; i < byte_count; ++i)
  {
    std::bitset< CHAR_BIT > b(message.substr(i * CHAR_BIT, CHAR_BIT));
    uchar value = static_cast<uchar>(b.to_ulong());
    ofs.write(reinterpret_cast<char*>(&value), sizeof value);
  }

  if (modulo > 0)
  {
    std::bitset< CHAR_BIT > b(message.substr(i * CHAR_BIT, modulo));
    uchar value = static_cast<uchar>(b.to_ulong());
    ofs.write(reinterpret_cast<char*>(&value), sizeof value);
  }
}

void read_decoding_file(std::string& filename, std::vector< int >& frequency, std::string& message)
{
  std::string new_filename = filename + ".art";
  std::ifstream ifs(new_filename, std::istream::binary);

  uchar count = 0;
  ifs.read(reinterpret_cast<char*>(&count), sizeof count);

  int i = 0;
  while (i < count)
  {
    uchar ch;
    ifs.read(reinterpret_cast<char*>(&ch), sizeof ch);

    int f = 0;
    ifs.read(reinterpret_cast<char*>(&f), sizeof f);
    frequency[ch] = f;
    ++i;
  }

  int byte_count = 0;
  uchar modulo = 0;
  ifs.read(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
  ifs.read(reinterpret_cast<char*>(&modulo), sizeof modulo);

  i = 0;
  for (; i < byte_count; ++i)
  {
    uchar byte;
    ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);

    std::bitset<CHAR_BIT> b(byte);
    message += b.to_string();
  }

  if (modulo > 0)
  {
    uchar byte;
    ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);

    std::bitset<CHAR_BIT> b(byte);
    message += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
  }
}

void make_char(const Node::pointer& root, const std::string& message, std::string& text)
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

void write_decoding_file(const std::string& filename, const std::string& text)
{
  std::string new_filename = filename + ".1";
  std::ofstream ofs(new_filename, std::ofstream::binary);

  ofs << text;
}

void artemev::printHelp()
{
  throw;
}

void artemev::read(std::istream& in, fileSheet& file) //ok
{
  std::string textName;
  std::string fileName;
  in >> textName >> fileName;

  if (file.find(textName) != file.cend())
  {
    throw std::logic_error("TEXT EXISTS");
  }

  file.insert({ textName, fileName });
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

void artemev::save_text(std::istream& in, fileSheet& file)
{
  std::string textName, fileName;
  in >> textName >> fileName;
  if (file.find(textName) == file.cend())
  {
    throw std::logic_error("Requested text is not found");
  }
  std::ifstream input(file.find(textName)->second);
  std::ofstream output(fileName);
  if (!input.is_open() || !output.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }
  copyFile(input, output);
}

void artemev::createCode(std::istream& input, encodesSheet& codes, const fileSheet& files, freqSheet& frequency, queueSheet& queueMap)
{
  std::string textName;
  std::string encodingName;

  input >> textName >> encodingName;
  if (codes.find(encodingName) != codes.cend())
  {
    throw std::logic_error("Such encoding already exists");
  }

  std::string ifs = files.at(textName);
  std::vector< int > freq{256, 0};
  getFreq(std::cref(ifs), std::ref(freq));

  artemev::queue_t queue;
  fill_queue(freq, queue);
  build_tree(queue);

  std::vector< std::string > code(256, "");
  Node::pointer root = queue.top();
  std::bind(make_code, std::ref(root), "", std::ref(code));
  codes.insert({ encodingName, code });
  frequency.insert({ encodingName, freq });
  queueMap.insert({ encodingName, queue});
}

void artemev::encode(std::istream& input, encodesSheet& codes, const fileSheet& files, codeText& codeText)
{
  std::string textName;
  std::string codeName;
  std::string newText;

  input >> textName >> codeName >> newText;
  if (codes.find(newText) == codes.cend())
  {
    throw std::logic_error("No such encoding is provided");
  }
  if (files.find(textName) == files.cend())
  {
    throw std::logic_error("No such text is provided");
  }

  std::vector< std::string > code(codes.find(codeName)->second);
  std::string ifs = files.at(textName);
  std::string message = message2code(ifs, code);
  codeText.insert({ newText, message });
}

void artemev::write(std::istream& input, codeText& codeText, encodesSheet& codes, fileSheet& files, freqSheet& freqMap, queueSheet& queueMap)
{
  std::string newFileName;
  std::string codedText;
  std::string encodingName;
  input >> encodingName >> codedText >> newFileName;
  std::string message(codeText.find(codedText)->second);
  std::vector< int > frequency(freqMap.find(encodingName)->second);
  artemev::queue_t queue(queueMap.find(encodingName)->second);
  write_file(newFileName, frequency, message);
}

void artemev::print(std::istream& input, std::ostream& out, const fileSheet& files, const encodesSheet& codes)
{
  std::string command{""};
  input >> command;

  if (command == "-t")
  {
    std::string textName;
    input >> textName;

    std::ifstream fileT(files.find(textName)->second);
    char s[256];
    while (!fileT.eof())
    {
      fileT.getline(s, 256);
      std::cout << s;
    }
  }

  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

  std::cout << "\n";
}
