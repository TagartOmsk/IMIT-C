#pragma once
#include <string>

template<typename K, typename V>
class HashTable
{
private:
    template<typename K, typename V>
    struct Node
    {
        K key;
        V value;
        Node* next;
        Node(Node* next = nullptr) : next(next) {}
        Node(K key, V value, Node* next) : key(key), value(value), next(next) {}
    };

    template<typename K, typename V>
    class TableEntry
    {
    public:
        class EntryIterator
        {
        public:
            EntryIterator(TableEntry<K, V> &list)
            {
                collection = &list;
            }
            EntryIterator& operator=(TableEntry<K, V> &obj)
            {
                collection = obj;
                return *this;
            }
            ~EntryIterator()
            {
                toEntryEnd();
                collection = nullptr;
            }
            void start()
            {
                collection->current = collection->root->next;
            }
            void next()
            {
                collection->current = collection->current->next;
            }
            V getValue() const
            {
                return collection->current->value;
            }
            K getKey() const
            {
                return collection->current->key;
            }
            bool finish()
            {
                return collection->current == nullptr;
            }
            void toEntryEnd()
            {
                collection->current = collection->last;
            }
        private:
            TableEntry *collection;
        };

        TableEntry()
        {
            root = new Node<K, V>();
            current = root;
            last = root;
            size = 0;
        }
        ~TableEntry()
        {
            clear();
        }
        bool push(K key, V value)
        {
            if(root == nullptr)
            {
                root = new Node<K, V>();
                current = root;
                last = root;
            }
            current = root;
            while(current != nullptr)
            {
                if(current->key == key)
                {
                    current->value = value;
                    return false;
                }
                current = current->next;
            }
            current = last;
            Node<K, V>* unit = new Node<K, V>(key, value, current->next);
            current->next = unit;
            current = current->next;
            if(current->next == nullptr)
            {
                last = current;
            }
            size++;
            return true;
        }
        V pop(const K& key)
        {
            if(isEmpty())
            {
                throw std::runtime_error("Table entry is empty.");
            }
            current = root;
            Node<K, V>* ptr = root;
            V value;
            while(current != nullptr)
            {
                if(current->key == key)
                {
                    value = current->value;
                    ptr->next = current->next;
                    delete current;
                    current = ptr;
                    if(current->next == nullptr)
                    {
                        last = current;
                    }
                    size--;
                    current = last;
                    return value;
                }
                ptr = current;
                current = current->next;
            }
            current = last;
            throw std::runtime_error("Value not found.");
        }
        V get(const K& key)
        {
            if(isEmpty())
            {
                throw runtime_error("Table entry is empty.");
            }
            V value;
            current = root;
            while(current != nullptr)
            {
                if(current->key == key)
                {
                    value = current->value;
                    current = last;
                    return value;
                }
                current = current->next;
            }
            current = last;
            throw std::runtime_error("Value not found.");
        }
        bool containsKey(const K& key)
        {
            current = root;
            while(current != nullptr)
            {
                if(current->key == key)
                {
                    current = last;
                    return true;
                }
                current = current->next;
            }
            current = last;
            return false;
        }
        bool containsValue(const V& value)
        {
            current = root;
            while(current != nullptr)
            {
                if(current->value == value)
                {
                    current = last;
                    return true;
                }
                current = current->next;
            }
            current = last;
            return false;
        }
        void clear()
        {
            if(root == nullptr && current == nullptr)
            {
                return;
            }
            current = root->next;
            while(!isEmpty())
            {
                root->next = current->next;
                delete current;
                current = root->next;
                size--;
            }
            delete root;
            root = nullptr;
            current = nullptr;
            last = nullptr;
        }
        bool isEmpty() const
        {
            return size == 0;
        }
        size_t getSize() const
        {
            return size;
        }
        EntryIterator* beginIterator()
        {
            EntryIterator* it = new EntryIterator(*this);
            it->start();
            return it;
        }
        EntryIterator* findFirstOf(const K& key)
        {
            EntryIterator* it = new EntryIterator(*this);
            it->start();
            while(!it->finish())
            {
                if(it->getKey() == key)
                {
                    return it;
                }
                it->next();
            }
            throw std::runtime_error("Value not found.");
        }
        Node<K, V>* getAddress(const K& key)
        {
            if(isEmpty())
            {
                throw std::runtime_error("Table entry is empty.");
            }
            Node<K, V>* ptr = nullptr;
            current = root;
            while(current != nullptr)
            {
                if(current->key == key)
                {
                    ptr = &(*current);
                    current = last;
                    return ptr;
                }
                current = current->next;
            }
            delete ptr;
            throw std::runtime_error("Value doesn't exsist");
        }
    private:
        Node<K, V>* root;
        Node<K, V>* last;
        Node<K, V>* current;
        size_t size;
    };

    int(*hashFunction)(K, int);
    TableEntry<K, Node<K, V>*> order;
    TableEntry<K, V>* table;
    size_t size;
    size_t fullness;
public:
    class Iterator
    {
    private:
        typedef typename TableEntry<K, Node<K, V>*>::EntryIterator* table_entry_iterator;
        table_entry_iterator orderList;
    public:
        Iterator(HashTable<K, V> &table)
        {
            orderList = table.order.beginIterator();
        }
        ~Iterator()
        {
            delete orderList;
        }
        void start()
        {
            orderList->start();
        }
        void next()
        {
            orderList->next();
        }
        V getValue()
        {
            return orderList->getValue()->value;
        }
        K getKey()
        {
            return orderList->getKey();
        }
        bool finish()
        {
            return orderList->finish();
        }
    };

    HashTable(int(*function)(K, int), int size = 16)
    {
        this->size = size;
        table = new TableEntry<K, V>[size];
        hashFunction = function;
        fullness = 0;
    }
    ~HashTable()
    {
        clear();
        size = 0;
    }
    bool put(const K& key, const V& value)
    {
        int position = hashFunction(key, size);
        if(table[position].push(key, value))
        {
            order.push(key, table[position].getAddress(key));
            fullness++;
            return true;
        }
        order.pop(key);
        order.push(key, table[position].getAddress(key));
        return false;
    }
    V remove(const K& key)
    {
        if(isEmpty())
        {
            throw std::runtime_error("Hash table is empty");
        }
        int position = hashFunction(key, size);
        order.pop(key);
        fullness--;
        return table[position].pop(key);
    }
    V get(const K& key)
    {
        return table[hashFunction(key, size)].get(key);
    }
    void clear()
    {
        for(int i = 0; i < size; i++)
        {
            table[i].clear();
        }
        order.clear();
        fullness = 0;
    }
    bool containsKey(const K& key)
    {
        return table[hashFunction(key, size)].containsKey(key);
    }
    bool containsValue(const V& value)
    {
        for(int i = 0; i < size; i++)
        {
            if(table[i].containsValue(value))
            {
                return true;
            }
        }
        return false;
    }
    size_t getSize() const
    {
        return fullness;
    }
    bool isEmpty() const
    {
        return fullness == 0;
    }
};