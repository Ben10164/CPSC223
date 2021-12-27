//---------------------------------------------------------------------------
// NAME:
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"

template <typename K, typename V>
class BSTMap : public Map<K, V>
{
public:
    // default constructor
    BSTMap();

    // copy constructor
    BSTMap(const BSTMap &rhs);

    // move constructor
    BSTMap(BSTMap &&rhs);

    // copy assignment
    BSTMap &operator=(const BSTMap &rhs);

    // move assignment
    BSTMap &operator=(BSTMap &&rhs);

    // destructor
    ~BSTMap();

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

    // Returns the height of the binary search tree
    int height() const;

private:
    // node for linked-list separate chaining
    struct Node
    {
        K key;
        V value;
        Node *left;
        Node *right;
    };

    // number of key-value pairs in map
    int count = 0;

    // array of linked lists
    Node *root = nullptr;

    // clean up the tree and reset count to zero given subtree root
    void make_empty(Node *st_root);

    // copy assignment helper
    Node *copy(const Node *rhs_st_root) const;

    // erase helper
    Node *erase(const K &key, Node *st_root);

    // find_keys helper
    void find_keys(const K &k1, const K &k2, const Node *st_root,
                   ArraySeq<K> &keys) const;

    // sorted_keys helper
    void sorted_keys(const Node *st_root, ArraySeq<K> &keys) const;

    // height helper
    int height(const Node *st_root) const;
};

// TODO: Implement the above functions per the directions in HW-7

// default constructor
template <typename K, typename V>
BSTMap<K, V>::BSTMap()
{
    count = 0;
    root = nullptr;
}

// copy constructor
template <typename K, typename V>
BSTMap<K, V>::BSTMap(const BSTMap &rhs)
{
    count = rhs.count;
    root = copy(rhs.root);
}

// move constructor
template <typename K, typename V>
BSTMap<K, V>::BSTMap(BSTMap &&rhs)
{
    count = rhs.count;
    *this = std::move(rhs);
}

// copy assignment
template <typename K, typename V>
typename BSTMap<K, V>::BSTMap &
BSTMap<K, V>::operator=(const BSTMap &rhs)
{
    if (this != &rhs)
    {
        make_empty(root);
        count = rhs.count;
        root = copy(rhs.root);
    }
    return *this;
}

// move assignment
template <typename K, typename V>
typename BSTMap<K, V>::BSTMap &
BSTMap<K, V>::operator=(BSTMap &&rhs)
{
    // make sure to check and see if they are the same
    if (this != &rhs)
    {
        // delete the current linked list
        make_empty(root);

        root = rhs.root;
        rhs.root = nullptr;
        count = rhs.count;
        rhs.count = 0;
        make_empty(rhs.root);
    }
    return *this;
}

// destructor
template <typename K, typename V>
BSTMap<K, V>::~BSTMap()
{
    make_empty(root);
    count = 0;
    root = nullptr;
}

// Returns the number of key-value pairs in the map
template <typename K, typename V>
int BSTMap<K, V>::size() const
{
    return count;
}

// Tests if the map is empty
template <typename K, typename V>
bool BSTMap<K, V>::empty() const
{
    return (count == 0);
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template <typename K, typename V>
V &BSTMap<K, V>::operator[](const K &key)
{
    if (contains(key))
    {
        Node *curr = root;
        while (curr != nullptr)
        {
            if (curr->key == key) // eventually want to get to this
            {
                return curr->value;
            }
            else if (curr->key < key)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
    }
    else
    {
        throw std::out_of_range("Key not found");
    }
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template <typename K, typename V>
const V &BSTMap<K, V>::operator[](const K &key) const
{
    if (contains(key))
    {
        Node *curr = root;
        while (curr != nullptr)
        {
            if (curr->key == key) // eventually want to get to this
            {
                return curr->value;
            }
            else if (curr->key < key)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
    }
    else
    {

        throw std::out_of_range("Key not found");
    }
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template <typename K, typename V>
void BSTMap<K, V>::insert(const K &key, const V &value)
{
    // Create and initialize the new node
    Node *new_node = new Node;

    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->key = key;
    new_node->value = value;

    Node *curr = root;
    Node *prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (curr->key < key)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }

    if (prev == nullptr)
    {
        root = new_node;
    }
    else if (prev->key < key)
    {
        prev->right = new_node;
    }
    else
    {
        prev->left = new_node;
    }
    count++;
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template <typename K, typename V>
void BSTMap<K, V>::erase(const K &key)
{
    if (contains(key))
    {
        root = erase(key, root);
    }
    else
    {
        throw std::out_of_range("Key not found");
    }
}

// Returns true if the key is in the collection, and false otherwise.
template <typename K, typename V>
bool BSTMap<K, V>::contains(const K &key) const
{
    Node *curr = root;
    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            return true;
        }
        else if (curr->key < key)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    return false;
}

// Returns the height of the binary search tree
template <typename K, typename V>
int BSTMap<K, V>::height() const
{
    return height(root);
}

template <typename K, typename V>
void BSTMap<K, V>::make_empty(Node *st_root)
{
    if (st_root != nullptr)
    {
        make_empty(st_root->left);
        make_empty(st_root->right);
        st_root = nullptr;
    }
}

// copy assignment helper
template <typename K, typename V>
typename BSTMap<K, V>::Node *
BSTMap<K, V>::copy(const Node *rhs_st_root) const
{
    if (rhs_st_root == nullptr)
    {
        return nullptr;
    }
    Node *new_node = new Node;
    new_node->key = rhs_st_root->key;
    new_node->value = rhs_st_root->value;
    new_node->left = copy(rhs_st_root->left);
    new_node->right = copy(rhs_st_root->right);
    return new_node;
}

// erase helper
template <typename K, typename V>
typename BSTMap<K, V>::Node *
BSTMap<K, V>::erase(const K &key, Node *st_root)
{
    if (st_root == nullptr)
    {
        return st_root;
    }
    if (st_root->key == key)
    {
        Node *temp = st_root;
        if (st_root->right == nullptr)
        {
            st_root = st_root->left;
        }
        else if (st_root->left == nullptr)
        {
            st_root = st_root->right;
        }
        else
        {
            Node *curr = st_root->right;
            Node *prev = st_root;
            while (curr->left != nullptr)
            {
                prev = curr;
                curr = curr->left;
            }
            temp->key = curr->key;
            temp->value = curr->value;
            if (prev == st_root)
            {
                prev->right = curr->right;
            }
            else
            {
                prev->left = curr->right;
            }
        }
        count--;
    }
    else if (st_root->key < key)
    {
        st_root->right = erase(key, st_root->right);
    }
    else
    {
        st_root->left = erase(key, st_root->left);
    }
    return st_root;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template <typename K, typename V>
ArraySeq<K> BSTMap<K, V>::find_keys(const K &k1, const K &k2) const
{
    ArraySeq<K> foundKeys;
    find_keys(k1, k2, root, foundKeys);
    return foundKeys;
}

// Returns the keys in the collection in ascending sorted order
template <typename K, typename V>
ArraySeq<K> BSTMap<K, V>::sorted_keys() const
{
    ArraySeq<K> keys_in_order;
    sorted_keys(root, keys_in_order);
    return keys_in_order;
}


// find_keys helper
template <typename K, typename V>
void BSTMap<K, V>::find_keys(const K &k1, const K &k2, const Node *st_root, ArraySeq<K> &keys) const
{
    if (st_root == nullptr)
    {
        return;
    }
    if (st_root->key >= k1)
    {
        find_keys(k1, k2, st_root->left, keys);
    }
    if (st_root->key >= k1 && st_root->key <= k2)
    {
        keys.insert(st_root->key, keys.size());
    }
    if (st_root->key <= k2)
    {
        find_keys(k1, k2, st_root->right, keys);
    }
}

// sorted_keys helper
template <typename K, typename V>
void BSTMap<K, V>::sorted_keys(const Node *st_root, ArraySeq<K> &keys) const
{
    if (st_root != nullptr)
    {
        const Node *cur = st_root;
        Node *tmp = cur->left;
        while (tmp != nullptr)
        {
            cur = tmp;
            tmp = cur->left;
        }
        K min_key = cur->key;

        cur = st_root;
        tmp = cur->right;
        while (tmp != nullptr)
        {
            cur = tmp;
            tmp = cur->right;
        }
        K max_key = cur->key;

        keys = find_keys(min_key, max_key);
    }
}

// height helper
template <typename K, typename V>
int BSTMap<K, V>::height(const Node *st_root) const
{
    if (st_root == nullptr)
    {
        return 0;
    }
    else
    {
        return (1 + std::max(height(st_root->left), height(st_root->right)));
    }
}

#endif
