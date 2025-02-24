#include "functions.hpp"
#include <stdexcept>

void printHelp()
{
  std::cout << "--help: Show available commands and their usage.\n";
  std::cout << "add <book> <key> <note>: Add a note with the given key and description to the book.\n";
  std::cout << "remove <book> <key>: Remove the note with the given key from the book.\n";
  std::cout << "create <book>: Create a new notebook with the given name.\n";
  std::cout << "tag-create <book> <tag>: Create a new tag in the book.\n";
  std::cout << "tag-delete <book> <tag>: Delete the tag from the book.\n";
  std::cout << "tag-add <book> <key> <tag>: Add a tag to the note with the given key in the book.\n";
  std::cout << "tag-remove <book> <key> <tag>: Remove a tag from the note with the given key in the book.\n";
  std::cout << "tag-create-book <book1> <tag1> <book2> <tag2> <new_book>: Create a new notebook based on notes tagged in the given books.\n";
  std::cout << "tag-merge-books <book1> <book2> <new_book>: Merge notes from the given books into a new book based on common tags.\n";
  std::cout << "tag-sort-entries <source_book> <tag>: Sort entries in the book by the given tag.\n";
}

void executeAddNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key, note;
  is >> book >> key;
  std::getline(is, note);
  manager.addNote(book, key, note);
}

void executeRemoveNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key;
  is >> book >> key;
  manager.removeNote(book, key);
}

void executeCreateNotebook(NotebookManager& manager, std::istream& is)
{
  std::string name;
  is >> name;
  manager.createNotebook(name);
}

void executeCreateTag(NotebookManager& manager, std::istream& is)
{
  std::string book, tag;
  is >> book >> tag;
  manager.createTag(book, tag);
}

void executeDeleteTag(NotebookManager& manager, std::istream& is)
{
  std::string book, tag;
  is >> book >> tag;
  manager.deleteTag(book, tag);
}

void executeAddTagToNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key, tag;
  is >> book >> key >> tag;
  manager.addTagToNote(book, key, tag);
}

void executeRemoveTagFromNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key, tag;
  is >> book >> key >> tag;
  manager.removeTagFromNote(book, key, tag);
}

void executeCreateNotebookFromTags(NotebookManager& manager, std::istream& is)
{
  std::string book1, tag1, book2, tag2, newBook;
  is >> book1 >> tag1 >> book2 >> tag2 >> newBook;
  manager.createNotebookFromTags(book1, tag1, book2, tag2, newBook);
}

void executeMergeNotebooksByTags(NotebookManager& manager, std::istream& is)
{
  std::string book1, book2, newBook;
  is >> book1 >> book2 >> newBook;
  manager.mergeNotebooksByTags(book1, book2, newBook);
}

void executeSortEntriesByTag(NotebookManager& manager, std::istream& is)
{
  std::string book, tag;
  is >> book >> tag;
  manager.sortEntriesByTag(book, tag);
}
