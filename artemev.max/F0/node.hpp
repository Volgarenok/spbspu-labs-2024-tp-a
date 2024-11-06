#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <memory>

using uchar = unsigned char;

class Node
{
  public:
    using pointer = std::shared_ptr< Node >;

    pointer left{ nullptr };
    pointer right{ nullptr };
    pointer parent{ nullptr };

    Node() = default;
    Node(uchar uch, int f);
    Node(const std::string& name, int f);
    ~Node() = default;

    int getFrequency() const;
    void setFrequency(int f);
    std::string code() const;
    void code(const std::string& c);
    std::string get_name() const;
    uchar get_byte() const;
    friend std::ostream& operator<<(std::ostream& out, const Node& node);
  private:
    std::string name_{ "" };
    uchar ch_ = 0;
    int frequency_ = 0;
    std::string code_string{ "" };
};

struct LowestPriority
{
public:
  bool operator()(const Node::pointer& left, const Node::pointer& right) const
  {
    return left->getFrequency() > right->getFrequency();
  }
};

#endif
