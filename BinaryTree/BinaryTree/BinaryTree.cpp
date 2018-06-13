#include "stdafx.h"
#include "BinaryTree.h"
#include <iostream>

BinaryTree::BinaryTree(int rootValue)
{
    root = new Node(rootValue);
    level = 1;
}

BinaryTree::BinaryTree(const BinaryTree & other)
{
    root = copy(other.root);
    level = other.level;
}

BinaryTree::BinaryTree(BinaryTree && other)
{
    root = other.root;
    level = other.level;
    other.root = nullptr;
    other.level = 0;
}

BinaryTree::~BinaryTree()
{
    clear();
}

BinaryTree & BinaryTree::operator=(const BinaryTree & other)
{
    copy(other);
    return *this;
}

BinaryTree & BinaryTree::operator=(BinaryTree && other)
{
    if(this == &other)
    {
        return *this;
    }
    root = other.root;
    level = other.level;
    other.root = nullptr;
    other.level = 0;
}

void BinaryTree::add(std::vector<bool> way, int x)
{
    if(way.size() == level)
    {
        level++;
    }
    addR(root, x, way, 0);
}

void BinaryTree::add(const char * way, int x)
{
    if(strlen(way) >= level + 1)
    {
        throw std::runtime_error("Invalid way");
    }
    add2(root, way, x, 0);
    if(strlen(way) == level)
    {
        level++;
    }
}

void BinaryTree::clear()
{
    clear(root);
    level = 0;
}

void BinaryTree::copy(const BinaryTree& other)
{
    if(this == &other)
    {
        return;
    }
    clear();
    root = copy(other.root);
}

std::ostream & operator<<(std::ostream & os, BinaryTree & bin)
{
    bin.fromLeftToRightPrint(bin.root, os);
    return os;
}

int BinaryTree::evenCount()
{
    return getQuantityOfEvenElements(root);
}

bool BinaryTree::containsOnlyPositive()
{
    return areOnlyPositive(root);
}

void BinaryTree::cutLeaves()
{
    cutLeaves(root);
}

double BinaryTree::getAverage()
{
    if(level == 0)
    {
        return DBL_MIN;
    }
    int count = 0;
    return getAverage(root, count) / count;
}

std::vector<bool> BinaryTree::find(int x)
{
    std::vector<bool> way;
    find(root, x, way);
    return way;
}

void BinaryTree::levelPrint()
{
    printTree(root, INDENT*level);
}

bool BinaryTree::isBinarySearchTree()
{
    return isBinarySearchTree(root->left, root->value, root->value, 0, false) &&
        isBinarySearchTree(root->right, root->value, root->value, 1, true);
}

size_t BinaryTree::getLevel()
{
    return level;
}

bool BinaryTree::addR(Node *& root, int x, std::vector<bool>& forward, int length)
{
    if(forward.size() == 0)
    {
        if(root == nullptr)
        {
            root = new Node(x);
        }
        else
        {
            root->value = x;
        }
        return true;
    }
    if(root == nullptr)
    {
        throw std::runtime_error("Invalid way");
    }
    if(forward.front() == 0)
    {
        forward.erase(forward.begin() + length);
        if(addR(root->left, x, forward, length++))
        {
            return true;
        }
    }
    if(forward.front() == 1)
    {
        forward.erase(forward.begin() + length);
        if(addR(root->right, x, forward, length++))
        {
            return true;
        }
    }
    return false;
}

bool BinaryTree::add2(Node *& root, const char* way, int x, int position)
{
    if(position == strlen(way))
    {
        if(root == nullptr)
        {
            root = new Node(x);
        }
        else
        {
            root->value = x;
        }
        return true;
    }
    if(root == nullptr)
    {
        throw std::runtime_error("Invalid way");
    }
    if(way[position] == '0')
    {
        if(add2(root->left, way, x, ++position))
        {
            return true;
        }
    }
    if(way[position] == '1')
    {
        if(add2(root->right, way, x, ++position))
        {
            return true;
        }
    }
    return false;
}

void BinaryTree::clear(Node *& current)
{
    if(current == nullptr)
    {
        return;
    }
    clear(current->left);
    clear(current->right);
    delete current;
    current = nullptr;
}

BinaryTree::Node* BinaryTree::copy(Node * root)
{
    if(!root)
    {
        return nullptr;
    }
    return new Node(root->value, copy(root->left), copy(root->right));
}

void BinaryTree::fromLeftToRightPrint(Node * root, std::ostream & os)
{
    if(!root)
    {
        return;
    }
    fromLeftToRightPrint(root->left, os);
    os << root->value << " ";
    fromLeftToRightPrint(root->right, os);
}

int BinaryTree::getQuantityOfEvenElements(Node* root)
{
    if(!root)
    {
        return 0;
    }
    if(root->value % 2 == 0)
    {
        return 1 + getQuantityOfEvenElements(root->left) + getQuantityOfEvenElements(root->right);
    }
    else
    {
        return getQuantityOfEvenElements(root->left) + getQuantityOfEvenElements(root->right);
    }
}

bool BinaryTree::areOnlyPositive(Node* root)
{
    if(!root)
    {
        return true;
    }
    if(root->value >= 0)
    {
        return true && areOnlyPositive(root->left) && areOnlyPositive(root->right);
    }
    else
    {
        return false;
    }
}

bool BinaryTree::cutLeaves(Node*& root)
{
    if(!root) { return false; }
    if(!root->left && !root->right)
    {
        delete root;
        root = nullptr;
        return true;
    }
    if(cutLeaves(root->left))
    {
        root->left = nullptr;
    }
    if(cutLeaves(root->right))
    {
        root->right = nullptr;
    }
    return false;
}

double BinaryTree::getAverage(Node* root, int &count)
{
    if(!root)
    {
        return 0;
    }
    count++;
    return root->value + getAverage(root->left, count) + getAverage(root->right, count);
}

bool BinaryTree::find(Node* root, int x, std::vector<bool>& way)
{
    if(!root)
    {
        way.pop_back();
        return false;
    }
    if(root->value == x)
    {
        return true;
    }
    way.push_back(0);
    if(root->value == x || find(root->left, x, way))
    {
        return true;
    }
    way.push_back(1);
    if(!find(root->right, x, way))
    {
        if(way.size() == 0)
        {
            throw std::runtime_error("Value not found");
        }
        way.pop_back();
        return false;
    }
}

void BinaryTree::printTree(Node* root, int steps)
{
    if(!root)
    {
        return;
    }
    for(int i = 0; i < INDENT*level - steps; i++)
    {
        std::cout << " ";
    }
    std::cout << root->value;
    for(int i = 0; i < steps; i++)
    {
        std::cout << " ";
    }
    std::cout << "\n\n";
    printTree(root->left, steps - INDENT);
    printTree(root->right, steps - INDENT);
}

bool BinaryTree::isBinarySearchTree(Node* root, int min, int max, int from, bool minFound)
{
    if(!root)
    {
        return true;
    }
    if(root->value < min && from == 0 && !minFound)
    {
        min = root->value;
    }
    else if(root->value > max && from == 1)
    {
        max = root->value;
    }
    else if(root->value <= min || root->value >= max)
    {
        return false;
    }
    return isBinarySearchTree(root->left, min, root->value, 0, minFound) &&
        isBinarySearchTree(root->right, root->value, max, 1, minFound);
}