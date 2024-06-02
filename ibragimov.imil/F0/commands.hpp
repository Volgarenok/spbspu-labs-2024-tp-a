#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <istream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "entities.hpp"

namespace ibragimov
{
  void input(const std::map< std::string, std::function< void(std::istream&) > >&, std::istream&);
  void readFromFile(const std::map< std::string, std::function< void(std::istream&) > >&, const std::string&);
  void writeIntoFile(const std::map< std::string, std::function< void(std::ostream&) > >&, const std::string&);
  void saveIntoMemory(const std::map< std::string, std::function< void() > >&, std::istream&);
  void deleteFromMemory(const std::map< std::string, std::function< void(const size_t) > >&);
  void loadFromMemory(const std::map< std::string, std::function< void(const size_t) > >&);
  void printCurrent(const std::shared_ptr< Entity >&);
  void printInfo(const std::map< std::string, std::function< void() > >&, std::istream& in);

  void huffman(const std::vector< std::shared_ptr< DecodedText > >&, const size_t, std::shared_ptr< Entity >&);
  void encode(const std::vector< std::shared_ptr< DecodedText > >&, const size_t,
      const std::vector< std::shared_ptr< Encodings > >&, const size_t, std::shared_ptr< Entity >&);
  void decode(const std::vector< std::shared_ptr< EncodedText > >&, const size_t,
      const std::vector< std::shared_ptr< Encodings > >&, const size_t, std::shared_ptr< Entity >&);

  void printAll(const std::vector< std::shared_ptr< DecodedText > >&,
      const std::vector< std::shared_ptr< EncodedText > >&,
      const std::vector< std::shared_ptr< Encodings > >&);
  void printDecoded(const std::vector< std::shared_ptr< DecodedText > >&);
  void printEncoded(const std::vector< std::shared_ptr< EncodedText > >&);
  void printEncodings(const std::vector< std::shared_ptr< Encodings > >&);

  template < class T >
  void inputEntity(std::istream&, std::shared_ptr< Entity >&);
  template < class T >
  void outputEntity(std::ostream&, const std::shared_ptr< Entity >&);
  template < class T >
  void saveEntity(std::vector< std::shared_ptr< T > >&, const std::shared_ptr< Entity >);
  template < class T >
  void deleteEntity(std::vector< std::shared_ptr< T > >&, const size_t);
  template < class T >
  void loadEntity(std::vector< std::shared_ptr< T > >&, const size_t, std::shared_ptr< Entity >&);

  template < class T >
  void inputEntity(std::istream& in, std::shared_ptr< Entity >& dest)
  {
    T temp;
    in >> temp;
    if (!in)
    {
      throw std::invalid_argument("");
    }
    dest = std::make_shared< T >(temp);
  }
  template < class T >
  void outputEntity(std::ostream& out, const std::shared_ptr< Entity >& value)
  {
    out << *std::dynamic_pointer_cast< T >(value) << '\n';
  }
  template < class T >
  void saveEntity(std::vector< std::shared_ptr< T > >& vector, const std::shared_ptr< Entity > value)
  {
    vector.push_back(std::dynamic_pointer_cast< T >(value));
  }
  template < class T >
  void deleteEntity(std::vector< std::shared_ptr< T > >& vector, const size_t pos)
  {
    vector.erase(vector.begin() + pos);
  }
  template < class T >
  void loadEntity(std::vector< std::shared_ptr< T > >& vector, const size_t pos, std::shared_ptr< Entity >& where)
  {
    where = vector.at(pos);
  }
}

#endif
