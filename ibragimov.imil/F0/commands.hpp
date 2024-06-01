#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <memory>
#include <vector>
#include "entities.hpp"

namespace ibragimov
{
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

  void huffman(const std::vector< std::shared_ptr< DecodedText > >&, const size_t, std::shared_ptr< Entity >&);
  void encode(const std::vector< std::shared_ptr< DecodedText > >&, const size_t,
      const std::vector< std::shared_ptr< Encodings > >&, const size_t, std::shared_ptr< Entity >&);
  void decode(const std::vector< std::shared_ptr< EncodedText > >&, const size_t,
      const std::vector< std::shared_ptr< Encodings > >&, const size_t, std::shared_ptr< Entity >&);


  Encodings findEfficient(const std::vector< Encodings >&, const DecodedText&);
  Encodings findUnefficient(const std::vector< Encodings >&, const DecodedText&);
  std::vector< Encodings > compareEncodings(const std::vector< Encodings >&, const DecodedText&);

  template < class T >
  void inputEntity(std::istream& in, std::shared_ptr< Entity >& dest)
  {
    T temp;
    in >> temp;
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
