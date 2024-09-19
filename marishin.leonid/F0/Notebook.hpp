#ifndef NOTEBOOK_HPP
#define NOTEBOOK_HPP

#include "Note.hpp"
#include <map>
#include <vector>
#include <string>
#include <set>

class Notebook
{
public:
  std::map<std::string, Note> notes;
  std::set<std::string> tags;

  void add(const std::string& key, const std::string& note);
  void remove(const std::string& key);
  void createTag(const std::string& tag);
  void deleteTag(const std::string& tag);
  void addTagToNote(const std::string& key, const std::string& tag);
  void removeTagFromNote(const std::string& key, const std::string& tag);
  std::vector<Note> getNotesByTag(const std::string& tag) const;
};

#endif
