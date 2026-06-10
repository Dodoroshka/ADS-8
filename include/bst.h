// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <stdexcept>

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
            node->count++;  // дубликат - увеличиваем счетчик
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
            return true;  // значение найдено
        }
    }
    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* removeNode(Node* node, const T& value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (value < node->data) {
            node->left = removeNode(node->left, value);
        } else if (value > node->data) {
            node->right = removeNode(node->right, value);
        } else {
            if (node->count > 1) {
                node->count--;
                return node;
            }
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->count = minNode->count;
                minNode->count = 1;
                node->right = removeNode(node->right, minNode->data);
            }
        }
        return node;
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
    Node* copyNode(Node* node) {
        if (node == nullptr) return nullptr;
        
        Node* newNode = new Node(node->data);
        newNode->count = node->count;
        newNode->left = copyNode(node->left);
        newNode->right = copyNode(node->right);
        
        return newNode;
    }
    int sizeNode(Node* node) const {
        if (node == nullptr) return 0;
        
        return node->count + sizeNode(node->left) + sizeNode(node->right);
    }
    void inorderNode(Node* node, void (*visit)(const T&, int)) const {
        if (node == nullptr) return;
        
        inorderNode(node->left, visit);
        visit(node->data, node->count);
        inorderNode(node->right, visit);
    }
 public:
    BST() : root(nullptr) {}
    BST(const BST& other) : root(nullptr) {
        root = copyNode(other.root);
    }
    ~BST() {
        clear();
    }
    BST& operator=(const BST& other) {
        if (this != &other) {
            clear();
            root = copyNode(other.root);
        }
        return *this;
    }
    void add(const T& value) {
        root = addNode(root, value);
    }
    bool search(const T& value) const {
        return searchNode(root, value);
    }
    void remove(const T& value) {
        root = removeNode(root, value);
    }
    
    // Очистка дерева
    void clear() {
        clearNode(root);
        root = nullptr;
    }
    
    // Измерение глубины (высоты) дерева (обязательный метод)
    int depth() const {
        return depthNode(root);
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return root == nullptr;
    }
    
    // Количество элементов (с учетом повторений)
    int size() const {
        return sizeNode(root);
    }
    
    // Количество уникальных узлов
    int uniqueSize() const {
        return countUniqueNodes(root);
    }
    
    // Поиск минимального значения
    T findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        Node* minNode = findMin(root);
        return minNode->data;
    }
    
    // Поиск максимального значения
    T findMax() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        Node* node = root;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->data;
    }
    
    // Проверка наличия значения
    bool contains(const T& value) const {
        return search(value);
    }
    
    // Получение количества повторений значения
    int getCount(const T& value) const {
        Node* node = root;
        while (node != nullptr) {
            if (value < node->data) {
                node = node->left;
            }
            else if (value > node->data) {
                node = node->right;
            }
            else {
                return node->count;
            }
        }
        return 0;
    }
    
    // Вывод дерева (in-order обход)
    void printInorder(void (*visit)(const T&, int)) const {
        inorderNode(root, visit);
    }
    
private:
    int countUniqueNodes(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + countUniqueNodes(node->left) + countUniqueNodes(node->right);
    }
};
#endif  // INCLUDE_BST_H_
