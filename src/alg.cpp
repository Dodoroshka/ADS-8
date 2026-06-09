// Copyright 2021 NNTU-CS
#include <cctype>
#include <fstream>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    return;
  }

  std::string word;
  int ch;

  while ((ch = file.get()) != EOF) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += static_cast<char>(
          std::tolower(static_cast<unsigned char>(ch)));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}
