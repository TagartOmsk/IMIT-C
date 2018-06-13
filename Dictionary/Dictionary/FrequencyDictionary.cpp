#include "stdafx.h"
#include "FrequencyDictionary.h"


FrequencyDictionary::FrequencyDictionary() : root(nullptr) {}


FrequencyDictionary::~FrequencyDictionary()
{
    clear();
}


FrequencyDictionary& FrequencyDictionary::operator=(const FrequencyDictionary& orig)
{
    copy(orig);
    return *this;
}

FrequencyDictionary& FrequencyDictionary::operator=(FrequencyDictionary&& orig)
{
    if(this == &orig)
    {
        return *this;
    }
    root = orig.root;
    orig.root = nullptr;
}

int FrequencyDictionary::search(std::string& word)
{
    return search(word, root);
}

void FrequencyDictionary::add(std::string& word)
{
    add(word, root);
}

int FrequencyDictionary::wordsCount()
{
    return wordsCount(root);
}

void FrequencyDictionary::remove(std::string & word)
{
    remove(word, root, nullptr);
}

std::ostream& operator <<(std::ostream &os, FrequencyDictionary &dic)
{
    dic.fromLeftToRightPrint(dic.root, os);
    return os;
}

void FrequencyDictionary::copy(const FrequencyDictionary& other)
{
    if(this == &other)
    {
        return;
    }
    clear();
    root = copy(other.root);
}

void FrequencyDictionary::clear()
{
    clear(root);
}

bool operator==(const FrequencyDictionary& first, const FrequencyDictionary& second)
{
    return &first == &second || equals(first.root, second.root);
}


FrequencyDictionary::Node* FrequencyDictionary::copy(Node * root)
{
    if(!root)
    {
        return nullptr;
    }
    return new Node (root->word, root->count, copy(root->left), copy(root->right));
}

void FrequencyDictionary::clear(Node *& current)
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

int FrequencyDictionary::search(std::string& word, Node* node)
{
    if(!node)
    {
        return 0;
    }
    if(node->word == word)
    {
        return node->count;
    }
    return search(word, node->left) + search(word, node->right);
}

void FrequencyDictionary::add(std::string& word, Node*& node)
{
    if(!node)
    {
        node = new Node(word, 1, nullptr, nullptr);
        return;
    }
    if(node->word == word)
    {
        node->count++;
        return;
    }
    if(word < node->word)add(word, node->left);
    else
    {
        add(word, node->right);
    }
}

int FrequencyDictionary::wordsCount(Node* node)
{
    if(!node)return 0;
    return node->count + wordsCount(node->left) + wordsCount(node->right);
}

bool FrequencyDictionary::remove(std::string word, Node* node, Node *prev)
{
    if(word > node->word)return remove(word, node->right, node);
    if(word < node->word)return remove(word, node->left, node);
    if(node->word == word)
    {
        if(node->count > 1)
        {
            node->count--;
            return true;
        }
        else
        {
            if(node->left && node->right)
            {
                Node *succParent = rightNodeOfLeftSubtreeParent(node);
                node->word = succParent->right->word;
                node->count = succParent->right->count;
                succParent->right = succParent->right->left;
            }
            else if(node->left)
            {
                if(prev->left == node)
                    prev->left = node->left;
                else
                    prev->right = node->left;
            }
            else if(node->right)
            {
                if(prev->left == node)
                    prev->left = node->right;
                else
                    prev->right = node->right;
            }
            else
            {
                if(prev->left == node)
                    prev->left = nullptr;
                else
                    prev->right = nullptr;
            }
            return true;
        }
    }
}

FrequencyDictionary::Node* FrequencyDictionary::rightNodeOfLeftSubtreeParent(Node* node)
{
    Node *prev = nullptr;
    while(node->right != nullptr)
    {
        prev = node;
        node = node->right;
    }
    return prev;
}

void FrequencyDictionary::fromLeftToRightPrint(Node * root, std::ostream & os)
{
    if(!root)
    {
        return;
    }
    fromLeftToRightPrint(root->left, os);
    os <<"Word: " << root->word << "[" << root->count << "]\n";
    fromLeftToRightPrint(root->right, os);
}

bool equals(const FrequencyDictionary::Node* first, const FrequencyDictionary::Node* second)
{
    if(!first || !second)return first == second;
    return first->count == second->count && first->word == second->word &&
        equals(first->left, second->left) && equals(first->right, second->right);
}