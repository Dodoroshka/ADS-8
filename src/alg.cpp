// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

bool isLatinLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << std::endl;
        return;
    }
    std::vector<std::string> words;
    std::string currentWord = "";
    char ch;
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
            currentWord += toLowerChar(ch);
        } else {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }
    file.close();
    std::sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());
    for (const auto& word : words) {
        tree.add(word);
    }
    std::cout << "File processed successfully!" << std::endl;
    std::cout << "Unique words: " << tree.getSize() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
}
void printFreq(BST<std::string>& tree) {
    std::cout << "\n Word Frequency Analysis" << std::endl;
    
    tree.printSortedByFrequency();
}
