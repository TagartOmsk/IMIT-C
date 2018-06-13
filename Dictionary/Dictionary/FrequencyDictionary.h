#pragma once
#include <string>
#include <ostream>
class FrequencyDictionary
{
    struct Node
    {
        std::string word;
        int count;
        Node *left, *right;
        Node(std::string nWord, int nCount, Node* nLeft = nullptr, Node* nRight = nullptr) : 
            word(nWord), count(nCount), left(nLeft), right(nRight) {}
    };
    Node *root;
public:
    FrequencyDictionary();
    ~FrequencyDictionary();
    FrequencyDictionary& operator= (const FrequencyDictionary&);
    FrequencyDictionary& operator= (FrequencyDictionary&&);

    int search(std::string&);
    void add(std::string&);
    int wordsCount();
    void remove(std::string&);
    
    friend std::ostream& operator <<(std::ostream &, FrequencyDictionary &);
    friend bool operator==(const FrequencyDictionary&, const FrequencyDictionary&);

    void copy(const FrequencyDictionary&);
    void clear();

private:

    Node* copy(Node*);
    void clear(Node*&);

    int search(std::string&, Node*);
    void add(std::string&, Node*&);
    int wordsCount(Node*);
    bool remove(std::string, Node*, Node*);

    Node* rightNodeOfLeftSubtreeParent(Node*);
    void fromLeftToRightPrint(Node*, std::ostream&);

    friend bool equals(const Node*, const Node*);
};

