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

  Encodings createEncodings(const DecodedText&);
  EncodedText encode(const DecodedText&, const Encodings&);
  DecodedText decode(const EncodedText&, const Encodings&);

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
}

#endif
