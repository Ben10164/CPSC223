//---------------------------------------------------------------------------
// NAME: Ben Puryear
// DATE: Fall 2021
// DESC: Implements all the functions defined in hashmap.hh
//---------------------------------------------------------------------------

#ifndef HASHMAP_H
#define HASHMAP_H

#include <functional>
#include "map.h"
#include "arrayseq.h"

template <typename K, typename V>
class HashMap : public Map<K, V>
{
public:
    // default constructor
    HashMap();

    // copy constructor
    HashMap(const HashMap &rhs);

    // move constructor
    HashMap(HashMap &&rhs);

    // copy assignment
    HashMap &operator=(const HashMap &rhs);

    // move assignment
    HashMap &operator=(HashMap &&rhs);

    // destructor
    ~HashMap();

    // Returns the number of key-value pairs in the map
    int size() const;

    // Tests if the map is empty
    bool empty() const;

    // Allows values associated with a key to be updated. Throws
    // out_of_range if the given key is not in the collection.
    V &operator[](const K &key);

    // Returns the value for a given key. Throws out_of_range if the
    // given key is not in the collection.
    const V &operator[](const K &key) const;

    // Extends the collection by adding the given key-value
    // pair. Assumes the key being added is not present in the
    // collection. Insert does not check if the key is present.
    void insert(const K &key, const V &value);

    // Shrinks the collection by removing the key-value pair with the
    // given key. Does not modify the collection if the collection does
    // not contain the key. Throws out_of_range if the given key is not
    // in the collection.
    void erase(const K &key);

    // Returns true if the key is in the collection, and false otherwise.
    bool contains(const K &key) const;

    // Returns the keys k in the collection such that k1 <= k <= k2
    ArraySeq<K> find_keys(const K &k1, const K &k2) const;

    // Returns the keys in the collection in ascending sorted order
    ArraySeq<K> sorted_keys() const;

    // statistics functions for the hash table implementation
    int min_chain_length() const;
    int max_chain_length() const;
    double avg_chain_length() const;

private:
    // node for linked-list separate chaining
    struct Node
    {
        K key;
        V value;
        Node *next;
    };

    // number of key-value pairs in map
    int count = 0;

    // max size of the (array) table
    int capacity = 16;

    // threshold for resize and rehash
    const double load_factor_threshold = 0.75;

    // array of linked lists
    Node **table = new Node *[capacity];

    // the hash function
    int hash(const K &key) const;

    // resize and rehash the table
    void resize_and_rehash();

    // initialize the table to all nullptr
    void init_table();

    // clean up the table and reset member variables
    void make_empty();
};

// TODO: implement the public and private HashMap functions below.

// default constructor
template <typename K, typename V>
HashMap<K, V>::HashMap()
{
    count = 0;
    capacity = 16;
    table = new Node *[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }
}

// copy constructor
template <typename K, typename V>
HashMap<K, V>::HashMap(const HashMap<K, V> &rhs)
{
    count = rhs.count;
    capacity = rhs.capacity;
    init_table();
    *this = rhs;
}

// move constructor
template <typename K, typename V>
HashMap<K, V>::HashMap(HashMap<K, V> &&rhs)
{
    *this = std::move(rhs);
}

// copy assignment
template <typename K, typename V>
HashMap<K, V> &HashMap<K, V>::operator=(const HashMap<K, V> &rhs)
{
    if (this != &rhs)
    {
        Node **newTable = new Node *[rhs.capacity];
        for (int i = 0; i < rhs.capacity; ++i)
        {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < rhs.capacity; ++i) // maybe make this int i
        {
            Node *temp = rhs.table[i];
            while (temp != nullptr)
            {
                Node *newNode = new Node();
                newNode->key = temp->key;
                newNode->value = temp->value;
                newNode->next = temp->next;

                if (newTable[i] == nullptr)
                {
                    newTable[i] = newNode;
                }
                else
                {
                    newNode->next = newTable[i];
                    newTable[i] = newNode;
                }
                temp = temp->next;
            }
        }
        capacity = rhs.capacity;
        count = rhs.count;
        table = newTable;
    }
}

// move assignment
template <typename K, typename V>
HashMap<K, V> &HashMap<K, V>::operator=(HashMap<K, V> &&rhs)
{
    if (this != &rhs)
    {
        // do the assignment
        make_empty();

        count = rhs.count;

        capacity = rhs.capacity;

        for (int i = 0; i < capacity; ++i)
        {
            table[i] = std::move(rhs.table[i]);
        }
        rhs.make_empty();
        rhs.count = 0;
        rhs.capacity = 16;
    }
    return *this;
}

// destructor
template <typename K, typename V>
HashMap<K, V>::~HashMap()
{
    make_empty();
    count = 0;
    capacity = 0;
}

// Returns the number of key-value pairs in the map
template <typename K, typename V>
int HashMap<K, V>::size() const
{
    return count;
}

// Tests if the map is empty
template <typename K, typename V>
bool HashMap<K, V>::empty() const
{
    return (count == 0);
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template <typename K, typename V>
V &HashMap<K, V>::operator[](const K &key)
{
    if (contains(key) != true)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }

    int tempValue = hash(key);
    int index = tempValue % capacity;

    Node *temp = table[index];

    while (temp != nullptr && temp->key != key) // The nullptr should never cause this loop to exit
    {
        temp = temp->next;
    }
    return temp->value;
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template <typename K, typename V>
const V &HashMap<K, V>::operator[](const K &key) const
{
    if (contains(key) != true)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }

    int tempValue = hash(key);
    int index = tempValue % capacity;

    Node *temp = table[index];

    while (temp != nullptr && temp->key != key) // The nullptr should never cause this loop to exit
    {
        temp = temp->next;
    }
    return temp->value;
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template <typename K, typename V>
void HashMap<K, V>::insert(const K &key, const V &value)
{

    if (count / capacity > load_factor_threshold)
    {
        //std::cout << max_chain_length() << std::endl;
        resize_and_rehash();
    }
    count++;

    int tempValue = hash(key);
    int index = tempValue % capacity;
    //std::cout << "index is " << index << ", count is " << count << " and capacity is " << capacity << " and max chain length is " << max_chain_length() << std::endl;
    Node *newKey = new Node();
    newKey->key = key;
    newKey->value = value;

    if (table[index] == nullptr)
    {
        table[index] = newKey;
        newKey->next = nullptr;
    }
    else
    {
        Node *temp = table[index];
        newKey->next = temp;
        table[index] = newKey;
    }
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template <typename K, typename V>
void HashMap<K, V>::erase(const K &key)
{
    if (contains(key) != true)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
    int tempValue = hash(key);
    int index = tempValue % capacity;

    if (table[index] != nullptr)
    {
        if (table[index]->key == key)
        {
            Node *temp = table[index];
            table[index] = temp->next;
            delete temp;
            count--;
        }
        else
        {
            Node *temp = table[index];
            Node *prev = nullptr;
            while (temp != nullptr)
            {
                if (temp->key == key)
                {
                    prev->next = temp->next;
                    delete temp;
                    count--;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }
    }
}

// Returns true if the key is in the collection, and false otherwise.
template <typename K, typename V>
bool HashMap<K, V>::contains(const K &key) const
{
    int tempValue = hash(key);
    int index = tempValue % capacity;
    Node *temp = table[index];
    while (temp != nullptr)
    {
        if (temp->key == key)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template <typename K, typename V>
ArraySeq<K> HashMap<K, V>::find_keys(const K &k1, const K &k2) const
{
    ArraySeq<K> keys;
    for (int i = 0; i < capacity; ++i)
    {
        Node *temp = table[i];
        while (temp != nullptr)
        {
            if (temp->key <= k2 && temp->key >= k1)
            {
                K key = temp->key;
                keys.insert(key, 0);
            }
            temp = temp->next;
        }
    }
    return keys;
}

// Returns the keys in the collection in ascending sorted order
template <typename K, typename V>
ArraySeq<K> HashMap<K, V>::sorted_keys() const
{
    ArraySeq<K> allKeys;

    for (int i = 0; i < capacity; ++i)
    {
        Node *temp = table[i];
        while (temp != nullptr)
        {
            allKeys.insert(temp->key, allKeys.size());
            temp = temp->next;
        }
    }
    allKeys.sort();
    return allKeys;
}

// statistics functions for the hash table implementation
template <typename K, typename V>
int HashMap<K, V>::min_chain_length() const
{
    int min = 0;
    int increment = 0;
    Node *temp = nullptr;
    for (int i = 0; i < capacity; ++i)
    {
        if (table[i] != nullptr)
        {
            temp = table[i];
            while (temp != nullptr)
            {
                increment++;
                temp = temp->next;
            }
        }
        if (min > increment)
        {
            min = increment;
        }
    }
    return min;
}

template <typename K, typename V>
int HashMap<K, V>::max_chain_length() const
{
    int max = 0;
    Node *temp = nullptr;
    for (int i = 0; i < capacity; ++i)
    {
        int increment = 0;
        if (table[i] != nullptr)
        {
            temp = table[i];
            while (temp != nullptr)
            {
                increment++;
                temp = temp->next;
            }
        }
        if (max < increment)
        {
            max = increment;
        }
    }
    return max;
}

template <typename K, typename V>
double HashMap<K, V>::avg_chain_length() const
{

    return (double)count / capacity;
}

// Private
// the hash function
template <typename K, typename V>
int HashMap<K, V>::hash(const K &key) const
{
    std::hash<K> hashFunction;
    return hashFunction(key);
}

// resize and rehash the table
template <typename K, typename V>
void HashMap<K, V>::resize_and_rehash()
{
    Node **newTable = new Node *[capacity * 2];
    for (int i = 0; i < capacity * 2; ++i)
    {
        newTable[i] = nullptr;
    }
    for (int i = 0; i < capacity; ++i)
    {
        if (table[i] != nullptr)
        {
            Node *curr = table[i];
            while (curr != nullptr)
            {
                Node *newNode = curr;
                newNode->key = curr->key;
                newNode->value = curr->value;
                newNode->next = nullptr;

                K newKey = curr->key;
                int index = (hash(newKey)) % (capacity * 2);

                if (newTable[index] == nullptr)
                {
                    newTable[index] = newNode;
                }
                else
                {
                    newNode->next = newTable[index];
                    newTable[index]->next = newNode;
                }
                curr = curr->next;
            }
        }
    }
    capacity = capacity * 2;
    table = newTable;
}

// initialize the table to all nullptr
template <typename K, typename V>
void HashMap<K, V>::init_table()
{
    // use in copy assignment and copy constructor
    table = new Node *[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }
}

// clean up the table and reset member variables
template <typename K, typename V>
void HashMap<K, V>::make_empty()
{
    if (*table != nullptr)
    {
        for (int i = 0; i < capacity; ++i)
        {
            if (table[i] != nullptr)
            {
                Node *curr = table[i];
                Node *next = nullptr;
                while (curr != nullptr)
                {
                    next = curr->next;
                    delete curr;
                    curr = next;
                }
            }
        }
    }
    count = 0;
}

#endif
