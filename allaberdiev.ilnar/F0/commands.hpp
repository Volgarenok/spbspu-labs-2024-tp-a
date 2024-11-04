#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

namespace allaberdiev
{
 void createDict(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void deleteDict(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void addWord(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void removeWord(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void translateWord(std::ostream&, std::istream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void mergeDict(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void combineDict(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
 void diffDict(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
}

#endif
