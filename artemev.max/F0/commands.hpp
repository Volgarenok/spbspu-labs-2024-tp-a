#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <queue>
#include <map>
#include <list>
#include "node.hpp"

namespace artemev
{
  using queue_t = std::priority_queue< Node::pointer, std::vector< Node::pointer >, LowestPriority>;
  using fileSheet = std::map< std::string, std::string >;
  using codesSheet = std::map< std::string, std::vector< std::string > >;
  using codeText = std::map< std::string, std::string >;
  using freqSheet = std::map< std::string, std::vector< int > >;
  using queueSheet = std::map< std::string, queue_t >;

  void printHelp();
  void create(std::istream&);
  void read(std::istream&, fileSheet&);
  void save(std::istream&, fileSheet&);
  void code(std::istream&, codesSheet&, const fileSheet&, freqSheet&, queueSheet&);
  void encode(std::istream&, codesSheet&, const fileSheet&, codeText&);
  void write(std::istream&, codeText&, codesSheet&, freqSheet&, queueSheet&);
  void uncode(std::istream&);
  void printText(std::istream&, std::ostream&, const fileSheet&);
  void printTable(std::istream&, std::ostream&, const freqSheet&);
  void deleteFiles(std::istream&);
  void size(std::istream&, std::ostream&);
  void comparator(std::istream&, std::ostream&);
}

#endif
