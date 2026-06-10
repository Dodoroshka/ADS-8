// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "bst.h"
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
    std::string currentWord = "";
    char ch;
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
            currentWord += toLowerChar(ch);
        } else {
            if (!currentWord.empty()) {
                tree.add(currentWord);
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        tree.add(currentWord);
    }
    file.close();
    std::cout << "File processed successfully!" << std::endl;
    std::cout << "Unique words: " << tree.getSize() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
}
void printFreq(BST<std::string>& tree) {
    std::cout << "\nWord Frequency Analysis" << std::endl;
    std::cout << "Words sorted by frequency :" << std::endl;
    tree.printSortedByFrequency();
    tree.saveToFile("result/freq.txt");   
    std::cout << "\nResults saved to result/freq.txt" << std::endl;
}
