#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    // 构造函数
    Node(int data) {
        this->data = data;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;

    // 左旋转
    void leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }

        rightChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }

        rightChild->left = node;
        node->parent = rightChild;
    }

    // 右旋转
    void rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }

        leftChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }

        leftChild->right = node;
        node->parent = leftChild;
    }

    // 修正插入后的红黑树性质
    void fixInsert(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    // 插入节点
    void insertNode(Node* node) {
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (node->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr) {
            root = node;
        } else if (node->data < parent->data) {
            parent->left = node;
        } else {
            parent->right = node;
        }

        fixInsert(node);
    }

    // 中序遍历
    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

public:
    // 构造函数
    RedBlackTree() {
        root = nullptr;
    }

    // 插入元素
    void insert(int data) {
        Node* node = new Node(data);
        insertNode(node);
    }

    // 中序遍历
    void inorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    RedBlackTree tree;

    // 插入测试样例
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    // 中序遍历测试样例
    tree.inorder(); // 输出：2 3 6 7 8 10 11 13 18 22 26

    return 0;
}