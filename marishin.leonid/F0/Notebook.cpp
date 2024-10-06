#include "Notebook.hpp"
#include <stdexcept>

void Notebook::add(const std::string& key, const std::string& note)
{
  if (notes.find(key) != notes.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  notes.emplace(key, Note{ key, note });
}

void Notebook::remove(const std::string& key)
{
  if (notes.erase(key) == 0)
  {
    throw std::runtime_error("INVALID COMMAND");
  }
}

void Notebook::createTag(const std::string& tag)
{
  if (!tags.insert(tag).second)
  {
    throw std::runtime_error("INVALID COMMAND");
  }
}

void Notebook::deleteTag(const std::string& tag)
{
  if (tags.erase(tag) == 0)
  {
    throw std::runtime_error("INVALID COMMAND");
  }
}

void Notebook::addTagToNote(const std::string& key, const std::string& tag)
{
  auto it = notes.find(key);
  if (it == notes.end() || tags.find(tag) == tags.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.addTag(tag);
}

void Notebook::removeTagFromNote(const std::string& key, const std::string& tag)
{
  auto it = notes.find(key);
  if (it == notes.end() || tags.find(tag) == tags.end())
  {
    throw std::runtime_error("INVALID COMMAND");
  }
  it->second.removeTag(tag);
}

std::vector<Note> Notebook::getNotesByTag(const std::string&) const
{
  return {};
}
