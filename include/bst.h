// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <iostream>
#include <fstream>
template <typename T>
class BST {
 private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int count;
        Node(const T& value) : data(value), left(nullptr), right(nullptr), count(1) {}
    };
    Node* root;
    int max(int a, int b) const {
        return (a > b) ? a : b;
    }
    Node* addNode(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = addNode(node->left, value);
        } else if (value > node->data) {
            node->right = addNode(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }
    bool searchNode(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        if (value < node->data) {
            return searchNode(node->left, value);
        } else if (value > node->data) {
            return searchNode(node->right, value);
        } else {
            return true;
        }
    }
    int depthNode(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = depthNode(node->left);
        int rightDepth = depthNode(node->right);
        return 1 + max(leftDepth, rightDepth);
    }
    void clearNode(Node* node) {
        if (node == nullptr) return;
        clearNode(node->left);
        clearNode(node->right);
        delete node;
    }
    void collectNodes(Node* node, Node** nodes, int& index) {
        if (node == nullptr) return;
        collectNodes(node->left, nodes, index);
        nodes[index++] = node;
        collectNodes(node->right, nodes, index);
    }
    void sortNodesByFrequency(Node** nodes, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (nodes[j]->count < nodes[j + 1]->count) {
                    Node* temp = nodes[j];
                    nodes[j] = nodes[j + 1];
                    nodes[j + 1] = temp;
                }
            }
        }
    }
 public:
    BST() : root(nullptr) {}
    ~BST() {
        clear();
    }
    void add(const T& value) {
        root = addNode(root, value);
    }
    bool search(const T& value) const {
        return searchNode(root, value);
    }
    int depth() const {
        return depthNode(root);
    }
    void clear() {
        clearNode(root);
        root = nullptr;
    }
    bool isEmpty() const {
        return root == nullptr;
    }
    Node** getNodesArray(int& size) {
        size = getSize();
        if (size == 0) return nullptr;
        Node** nodes = new Node * [size];
        int index = 0;
        collectNodes(root, nodes, index);
        return nodes;
    }
    int getSize() const {
        return getSizeNode(root);
    }
    void printSortedByFrequency() {
        int size;
        Node** nodes = getNodesArray(size);
        if (size == 0) return;
        sortNodesByFrequency(nodes, size);
        for (int i = 0; i < size; i++) {
            std::cout << nodes[i]->data << " : " << nodes[i]->count << std::endl;
        }
        delete[] nodes;
    }
 private:
    int getSizeNode(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + getSizeNode(node->left) + getSizeNode(node->right);
    }
};
#endif  // INCLUDE_BST_H_
