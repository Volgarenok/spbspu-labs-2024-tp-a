#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "NotebookManager.hpp"
#include <iostream>
#include <sstream>

void printHelp();
void executeAddNote(NotebookManager& manager, std::istream& is);
void executeRemoveNote(NotebookManager& manager, std::istream& is);
void executeCreateNotebook(NotebookManager& manager, std::istream& is);
void executeCreateTag(NotebookManager& manager, std::istream& is);
void executeDeleteTag(NotebookManager& manager, std::istream& is);
void executeAddTagToNote(NotebookManager& manager, std::istream& is);
void executeRemoveTagFromNote(NotebookManager& manager, std::istream& is);
void executeCreateNotebookFromTags(NotebookManager& manager, std::istream& is);
void executeMergeNotebooksByTags(NotebookManager& manager, std::istream& is);
void executeSortEntriesByTag(NotebookManager& manager, std::istream& is);

#endif
