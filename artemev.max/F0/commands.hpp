#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include "node.hpp"

namespace artemev
{
  using queue_t = std::priority_queue< Node::pointer, std::vector< Node::pointer >, LowestPriority>;
  using fileSheet = std::map< std::string, std::string >;
  using encodesSheet = std::map< std::string, std::vector< std::string > >;
  using codeText = std::map< std::string, std::string >;
  using freqSheet = std::map< std::string, std::vector< int > >;
  using queueSheet = std::map< std::string, queue_t >;

  void printHelp();
  void read(std::istream&, fileSheet&);
  void save_text(std::istream&, fileSheet&);

  void createCode(std::istream&, encodesSheet&, const fileSheet&, freqSheet&, queueSheet&);
  void encode(std::istream&, encodesSheet&, const fileSheet&, codeText&);
  void write(std::istream&, codeText&, encodesSheet&, fileSheet&, freqSheet&, queueSheet&);

  void print(std::istream&, std::ostream&, const fileSheet&, const encodesSheet&);
}

#endif
