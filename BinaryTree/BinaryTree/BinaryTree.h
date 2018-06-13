#pragma once
#include <vector>
#define INDENT 4

class BinaryTree
{
public:
    BinaryTree(int rootValue);
    BinaryTree(const BinaryTree& other);
    BinaryTree(BinaryTree&& other);
    ~BinaryTree();

    BinaryTree& operator=(const BinaryTree & other);
    BinaryTree& operator=(BinaryTree && other);
    friend std::ostream& operator <<(std::ostream &os, BinaryTree &tree);

    void add(std::vector<bool> way, int x);
    void add(const char* way, int x);
    void cutLeaves();
    void clear();
    void copy(const BinaryTree &other);
    void levelPrint();

    int evenCount();
    double getAverage();
    std::vector<bool> find(int x);


    bool containsOnlyPositive();
    bool isBinarySearchTree();

    size_t getLevel();
private:
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node(int value, Node* left = nullptr, Node* right = nullptr) : value(value), left(left), right(right) {}
    };
    Node *root;
    size_t level;

    bool addR(Node*& root, int x, std::vector<bool>& forward, int length);
    bool add2(Node*& root, const char* way, int x, int position);
    void clear(Node*& current);
    Node* copy(Node* root);
    void fromLeftToRightPrint(Node* root, std::ostream &os);

    int getQuantityOfEvenElements(Node* root);
    bool areOnlyPositive(Node* root);
    bool cutLeaves(Node*& root);
    double getAverage(Node* root, int &count);
    bool find(Node* root, int x, std::vector<bool> &way);

    void printTree(Node* root, int steps);

    bool isBinarySearchTree(Node* root, int min, int max, int from, bool minFound);
};

