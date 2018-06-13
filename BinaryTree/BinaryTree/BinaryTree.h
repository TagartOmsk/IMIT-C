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

    void add(std::vector<bool> way, int x);
    void add(const char* way, int x);

    void clear();
    void copy(const BinaryTree &other);
    friend std::ostream& operator <<(std::ostream &os, BinaryTree &tree);

    int evenCount();
    bool containsOnlyPositive();
    void cutLeaves();
    double getAverage();
    std::vector<bool> find(int x);

    void levelPrint();

    bool isBinarySearchTree();
    bool isBST()
    {
        return isBST(root, INT_MIN, INT_MAX);
    }

    size_t getLevel();
private:
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node(int nValue, Node* nLeft = nullptr, Node* nRight = nullptr) : value(nValue), left(nLeft), right(nRight) {}
    };
    Node *root;
    size_t level;

    bool addR(Node*& root, int x, std::vector<bool>& forward, int length);
    bool add2(Node*& root, const char* way, int x, int position);
    void clear(Node*& current);
    Node* copy(Node* root);
    void stole(BinaryTree& other);
    void fromLeftToRightPrint(Node* root, std::ostream &os);

    int getQuantityOfEvenElements(Node* root);
    bool areOnlyPositive(Node* root);
    bool cutLeaves(Node*& root);
    double getAverage(Node* root, int &count);
    bool find(Node* root, int x, std::vector<bool> &way);

    void printTree(Node* root, int steps);

    bool isBinarySearchTree(Node* root, int min, int max, int from, bool minFound);

    bool isBST(Node * root, int min, int max)
    {
        if(!root)
        {
            return true;
        }
        if(root->value <= min || root->value >= max)
        {
            return false;
        }
        return isBST(root->left, min, root->value) && isBST(root->right, root->value, max);
    }
};

