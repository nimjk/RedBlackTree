#pragma once
using namespace std;

enum Color { RED, BLACK };

template <typename KeyType>
struct Node {
    KeyType key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(const KeyType& k, Color c = RED) : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename KeyType>
class RedBlackTree {
private:
    Node<KeyType>* root;

    Node<KeyType>* searchNode(Node<KeyType>* node, const KeyType& key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return searchNode(node->left, key);
        } else {
            return searchNode(node->right, key);
        }
    }

    Node<KeyType>* minimumNode(Node<KeyType>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void rotateLeft(Node<KeyType>* x) {
        Node<KeyType>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node<KeyType>* y) {
        Node<KeyType>* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    void transplant(Node<KeyType>* u, Node<KeyType>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
    
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }


    void insertFixup(Node<KeyType>* z) {
        while (z != root && z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node<KeyType>* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node<KeyType>* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void eraseFixup(Node<KeyType>* x) {
    while (x != root && x != nullptr && x->color == BLACK) {
        if (x == x->parent->left) {
            Node<KeyType>* w = x->parent->right;
            if (w != nullptr) {
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }

                if ((w->left == nullptr || w->left->color == BLACK) && 
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr) {
                            w->left->color = BLACK;
                        }
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr) {
                        w->right->color = BLACK;
                    }
                    rotateLeft(x->parent);
                    x = root;  // Terminate loop
                }
            }
        } else {
            Node<KeyType>* w = x->parent->left;
            if (w != nullptr) {
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }

                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr) {
                            w->right->color = BLACK;
                        }
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr) {
                        w->left->color = BLACK;
                    }
                    rotateRight(x->parent);
                    x = root;  // Terminate loop
                }
            }
        }
    }

    if (x != nullptr) {
        x->color = BLACK;
    }

    
}


public:
    RedBlackTree() : root(nullptr) {}

    Node<KeyType>* getRoot() const {
        return root;
    }

    void insert(const KeyType& key) {
        Node<KeyType>* newNode = new Node<KeyType>(key);
        Node<KeyType>* y = nullptr;
        Node<KeyType>* x = root;

        while (x != nullptr) {
            y = x;
            if (key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        newNode->parent = y;
        if (y == nullptr) {
            root = newNode;
        } else if (key < y->key) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        insertFixup(newNode);
    }

    void erase(const KeyType& key) {
        Node<KeyType>* z = searchNode(root, key);
        if (z == nullptr) {
            return;  // Node with the given key doesn't exist in the tree
        }

        Node<KeyType>* y = z;
        Node<KeyType>* x = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimumNode(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr) {
                    x->parent = y;
                }
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK) {
            eraseFixup(x);
        }
    }

    void search(const KeyType& key) {
        Node<KeyType>* result = searchNode(root, key);
        if (result != nullptr) {
            cout << "Node with key " << key << " found in the tree." << endl;
        } else {
            cout << "Node with key " << key << " not found in the tree." << endl;
        }
    }

    void inOrderTraversal(Node<KeyType>* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

    void printTree(Node<KeyType>* node, int level = 0, char direction = 'R') {
    if (node != nullptr) {
        printTree(node->right, level + 1, 'R');

        for (int i = 0; i < level; ++i) {
            cout << "    ";
        }

        cout << "|--";
        if (node->color == RED) {
            cout << "\033[31m";  // Red color code for console
        }
        cout << node->key;
        if (node->color == RED) {
            cout << "\033[0m";  // Reset color
        }
        cout << std::endl;

        printTree(node->left, level + 1, 'L');
    }
}

    

};
