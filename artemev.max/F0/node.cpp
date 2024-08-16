#include "node.hpp"

Node::Node(uchar uch, int f) :
  ch_(uch),
  frequency_(f)
{};

Node::Node(const std::string& name, int f) :
  name_(name),
  frequency_(f)
{};

int Node::getFrequency() const
{
  return frequency_;
}

void Node::setFrequency(int f)
{
  frequency_ = f;
}

std::string Node::code() const
{
  return code_string;
}

void Node::code(const std::string& c)
{
  code_string = c;
}

std::string Node::get_name() const
{
  if (ch_ == 0)
  {
    return name_;
  }
  else
  {
    if (ch_ == 9)
    {
      return "\\t";
    }
    if (ch_ == 10)
    {
      return "\\n";
    }
    else if (ch_ == 13)
    {
      return "\\r";
    }
    return std::string(1, static_cast<char>(ch_));
  }
}

uchar Node::get_byte() const
{
  return ch_;
}

std::ostream& operator<<(std::ostream& out, const Node& node)
{
  return out << "[" << node.get_name() << "] = " << node.frequency_;
}
