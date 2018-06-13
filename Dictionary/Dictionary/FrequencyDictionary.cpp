#include "stdafx.h"
#include "FrequencyDictionary.h"


FrequencyDictionary::FrequencyDictionary() : root(nullptr) {}


FrequencyDictionary::~FrequencyDictionary()
{
    clear();
}

//PUBLIC

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
    stole(orig);
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
    remove(word, root);
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

//PRIVATE

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

void FrequencyDictionary::stole(FrequencyDictionary & orig)
{
    root = orig.root;
    orig.root = nullptr;
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

bool FrequencyDictionary::remove(std::string word, Node* node)
{
    if(word > node->word)return remove(word, node->right);
    if(word < node->word)return remove(word, node->left);
    if(node->word == word)
    {
        if(node->count > 1)
        {
            node->count--;
            return true;
        }
        else
        {
            Node *temp = rightNodeOfLeftSubtree(node);
            Node *cur = node->left;
            if(temp->left != nullptr)
            {
                while(cur->right != temp)
                {
                    cur = cur->right;
                }
                cur->right = temp->left;
            }
            node->word = temp->word;
            node->count = temp->count;
            temp->left = nullptr;
            return true;
        }
    }
}

FrequencyDictionary::Node* FrequencyDictionary::rightNodeOfLeftSubtree(Node* node)
{
    Node* cur = node->left;
    while(cur->right != nullptr)
    {
        cur = cur->right;
    }
    return cur;
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

bool FrequencyDictionary::equals(const Node* first, const Node* second)
{
    if(!first || !second)return first == second;
    return first->count == second->count && first->word == second->word && 
        equals(first->left, second->left) &&
}