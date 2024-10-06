#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
#include <set>

class Note
{
public:
  std::string key;
  std::string description;
  std::set<std::string> tags;

  Note() = default;
  Note(const std::string& k, const std::string& d);
  Note(const Note& other);
  Note& operator=(const Note& other);

  void addTag(const std::string& tag);
  void removeTag(const std::string& tag);
};

#endif
