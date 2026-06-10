// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << std::endl;
        return;
    }
    std::string currentWord = "";
    char ch;
    while (file.get(ch)) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            // Приводим к нижнему регистру
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + ('a' - 'A');
            }
            currentWord += ch;
        } else {
            if (!currentWord.empty()) {
                bool valid = true;
                for (size_t i = 0; i < currentWord.length(); i++) {
                    if (currentWord[i] < 'a' || currentWord[i] > 'z') {
                        valid = false;
                        break;
                    }
                }
                if (valid && currentWord.length() > 0) {
                    tree.add(currentWord);
                }
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        bool valid = true;
        for (size_t i = 0; i < currentWord.length(); i++) {
            if (currentWord[i] < 'a' || currentWord[i] > 'z') {
                valid = false;
                break;
            }
        }
        if (valid && currentWord.length() > 0) {
            tree.add(currentWord);
        }
    }
    file.close();
    std::cout << "File processed successfully!" << std::endl;
    std::cout << "Unique words: " << tree.getSize() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
}
void printFreq(BST<std::string>& tree) {
    std::cout << "\n Word Frequency Analysis" << std::endl;
    std::cout << "Words sorted by frequency :" << std::endl;
    tree.printSortedByFrequency();
}
