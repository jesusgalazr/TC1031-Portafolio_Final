#ifndef NODE_H
#define NODE_H

#include "Registros.h"

class Node {
private:
    Registros registro;
    Node* left;
    Node* right;

public:
    // Constructor
    Node(const Registros& registro, Node* left = nullptr, Node* right = nullptr)
        : registro(registro), left(left), right(right) {}

    // Getters
    Registros getRegistro() const {
        return registro;
    }

    Node* getLeft() const {
        return left;
    }

    Node* getRight() const {
        return right;
    }

    // Setters
    void setRegistro(const Registros& registro) {
        this->registro = registro;
    }

    void setLeft(Node* left) {
        this->left = left;
    }

    void setRight(Node* right) {
        this->right = right;
    }
};

#endif // NODE_H
