#include "Note.hpp"

Note::Note(const std::string& k, const std::string& d):
  key(k),
  description(d)
{}

Note::Note(const Note& other):
  key(other.key),
  description(other.description),
  tags(other.tags)
{}

Note& Note::operator=(const Note& other)
{
  if (this != &other)
  {
    key = other.key;
    description = other.description;
    tags = other.tags;
  }
  return *this;
}

void Note::addTag(const std::string& tag)
{
  tags.insert(tag);
}

void Note::removeTag(const std::string& tag)
{
  tags.erase(tag);
}
