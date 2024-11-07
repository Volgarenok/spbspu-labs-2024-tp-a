#include "dictionary.hpp"
#include <iostream>
#include <stdexcept>

void petuhov::Dictionary::insert(const std::string& word, const std::string& translation, const std::string& additionalInfo) {
    dictionary_[word][translation] = additionalInfo;
    std::cout << "Word inserted.\n";
}

void petuhov::Dictionary::search(const std::string& word) const {
    auto it = dictionary_.find(word);

    if (it == dictionary_.end()) {
      throw std::runtime_error("Word not found in dictionary");
    }

    std::cout << "Translations for '" << word << "':\n";

    for (const auto& entry : it->second) {
      const std::string& trans = entry.first;
      const std::string& info = entry.second;
      std::cout << "- " << trans << " (" << info << ")\n";
    }
}

void petuhov::Dictionary::remove(const std::string& word) {
    auto it = dictionary_.find(word);
    if (it == dictionary_.end()) {
        throw std::runtime_error("Word not found in dictionary");
    }
    dictionary_.erase(it);
    std::cout << "Word deleted.\n";
}
