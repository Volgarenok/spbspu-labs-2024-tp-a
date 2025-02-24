#include "NotebookManager.hpp"
#include <stdexcept>
#include <algorithm>

void NotebookManager::createNotebook(const std::string& name)
{
  if (!notebooks.emplace(name, Notebook{}).second)
  {
    throw std::runtime_error("INVALID COMMAND");
  }
}

void NotebookManager::addNote(const std::string& book, const std::string& key, const std::string& note)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.add(key, note);
}

void NotebookManager::removeNote(const std::string& book, const std::string& key)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.remove(key);
}

void NotebookManager::createTag(const std::string& book, const std::string& tag)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID BOOK");
  }
  it->second.createTag(tag);
}

void NotebookManager::deleteTag(const std::string& book, const std::string& tag)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.deleteTag(tag);
}

void NotebookManager::addTagToNote(const std::string& book, const std::string& key, const std::string& tag)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.addTagToNote(key, tag);
}

void NotebookManager::removeTagFromNote(const std::string& book, const std::string& key, const std::string& tag)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.removeTagFromNote(key, tag);
}

void NotebookManager::createNotebookFromTags(const std::string& book1, const std::string& tag1, const std::string& book2,
  const std::string& tag2, const std::string& newBook)
{
  auto it1 = notebooks.find(book1);
  auto it2 = notebooks.find(book2);
  if (it1 == notebooks.end() || it2 == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  createNotebook(newBook);
  for (const auto& note : it1->second.getNotesByTag(tag1))
  {
    notebooks[newBook].add(note.key, note.description);
  }
  for (const auto& note : it2->second.getNotesByTag(tag2))
  {
    notebooks[newBook].add(note.key, note.description);
  }
}

void NotebookManager::mergeNotebooksByTags(const std::string& book1, const std::string& book2, const std::string& newBook)
{
  auto it1 = notebooks.find(book1);
  auto it2 = notebooks.find(book2);
  if (it1 == notebooks.end() || it2 == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  createNotebook(newBook);
}

void NotebookManager::sortEntriesByTag(const std::string& book, const std::string& tag)
{
  auto it = notebooks.find(book);
  if (it == notebooks.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  auto notes = it->second.getNotesByTag(tag);
  std::vector<Note> sorted_notes(notes.begin(), notes.end());
  std::sort(sorted_notes.begin(), sorted_notes.end(), [](const Note& a, const Note& b)
  {
    return a.key < b.key;
  });
  it->second.notes.clear();
  for (const auto& note : sorted_notes)
  {
    it->second.notes[note.key] = note;
  }
}
