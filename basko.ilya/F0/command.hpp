#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

namespace basko
{
  bool checkInt(const std::string& s);
  void readFile(std::map< std::string, std::set< int > >& map_words, std::string filename);
  void topCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void Addcommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void createDictCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void removeCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void searchCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void showCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void mergeCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void countWordsCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void clearCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void matchWordsCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void intersectionCommand(const std::vector< std::string >& words, std::map< std::string, std::map< std::string, std::set< int > > >& maps);
  void helpCommand(std::ostream& out);
}
