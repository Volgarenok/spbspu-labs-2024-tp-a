#ifndef NOTEBOOK_MANAGER_HPP
#define NOTEBOOK_MANAGER_HPP

#include "Notebook.hpp"
#include <map>
#include <string>

class NotebookManager
{
public:
  std::map<std::string, Notebook> notebooks;

  void createNotebook(const std::string& name);
  void addNote(const std::string& book, const std::string& key, const std::string& note);
  void removeNote(const std::string& book, const std::string& key);
  void createTag(const std::string& book, const std::string& tag);
  void deleteTag(const std::string& book, const std::string& tag);
  void addTagToNote(const std::string& book, const std::string& key, const std::string& tag);
  void removeTagFromNote(const std::string& book, const std::string& key, const std::string& tag);
  void createNotebookFromTags(const std::string& book1, const std::string& tag1, const std::string& book2,
    const std::string& tag2, const std::string& newBook);
  void mergeNotebooksByTags(const std::string& book1, const std::string& book2, const std::string& newBook);
  void sortEntriesByTag(const std::string& book, const std::string& tag);
};

#endif
