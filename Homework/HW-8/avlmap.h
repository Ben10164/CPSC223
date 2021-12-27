//---------------------------------------------------------------------------
// NAME: Ben Puryear
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef AVLMAP_H
#define AVLMAP_H

#include "map.h"
#include "arrayseq.h"

template <typename K, typename V>
class AVLMap : public Map<K, V>
{
public:
    // default constructor
    AVLMap();

    // copy constructor
    AVLMap(const AVLMap &rhs);

    // move constructor
    AVLMap(AVLMap &&rhs);

    // copy assignment
    AVLMap &operator=(const AVLMap &rhs);

    // move assignment
    AVLMap &operator=(AVLMap &&rhs);

    // destructor
    ~AVLMap();

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

    // helper to print the tree for debugging
    void print() const;

private:
    // node for avl tree
    struct Node
    {
        K key;
        V value;
        Node *left;
        Node *right;
        int height;
    };

    // number of nodes
    int count = 0;

    // root node
    Node *root = nullptr;

    // clean up the tree and reset count to zero given subtree root
    void make_empty(Node *st_root);

    // copy assignment helper
    Node *copy(const Node *rhs_st_root) const;

    // erase helper
    Node *erase(const K &key, Node *st_root);

    // insert helper
    Node *insert(const K &key, const V &value, Node *st_root);

    // find_keys helper
    void find_keys(const K &k1, const K &k2, const Node *st_root,
                   ArraySeq<K> &keys) const;

    // sorted_keys helper
    void sorted_keys(const Node *st_root, ArraySeq<K> &keys) const;

    // rotations
    Node *right_rotate(Node *k2);
    Node *left_rotate(Node *k2);

    // rebalance
    Node *rebalance(Node *st_root);

    // print helper
    void print(std::string indent, const Node *st_root) const;
};

template <typename K, typename V>
void AVLMap<K, V>::print() const
{
    print(std::string(""), root);
}

template <typename K, typename V>
void AVLMap<K, V>::print(std::string indent, const Node *st_root) const
{
    if (!st_root)
        return;
    std::cout << st_root->key << " (" << st_root->height << ")" << std::endl;
    if (st_root->left)
    {
        std::cout << indent << " lft: ";
        print(indent + " ", st_root->left);
    }
    if (st_root->right)
    {
        std::cout << indent << " rgt: ";
        print(indent + " ", st_root->right);
    }
}

//----------------------------------------------------------------------
// TODO: Implement the above functions below
//----------------------------------------------------------------------
// default constructor
template <typename K, typename V>
AVLMap<K, V>::AVLMap()
{
    count = 0;
    root = nullptr;
}

// copy constructor
template <typename K, typename V>
AVLMap<K, V>::AVLMap(const AVLMap &rhs)
{
    count = rhs.count;
    root = copy(rhs.root);
}

// move constructor
template <typename K, typename V>
AVLMap<K, V>::AVLMap(AVLMap &&rhs)
{
    count = rhs.count;
    *this = std::move(rhs);
}

// copy assignment
template <typename K, typename V>
AVLMap<K, V> &AVLMap<K, V>::operator=(const AVLMap &rhs)
{
    if (this != &rhs)
    {
        make_empty(root);
        root = copy(rhs.root);
        count = rhs.count;
    }
    return *this;
}

// move assignment
template <typename K, typename V>
AVLMap<K, V> &AVLMap<K, V>::operator=(AVLMap &&rhs)
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
AVLMap<K, V>::~AVLMap()
{
    make_empty(root);
    count = 0;
}

// Returns the number of key-value pairs in the map
template <typename K, typename V>
int AVLMap<K, V>::size() const
{
    return count;
}

// Tests if the map is empty
template <typename K, typename V>
bool AVLMap<K, V>::empty() const
{
    return count == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template <typename K, typename V>
V &AVLMap<K, V>::operator[](const K &key)
{
    Node *st_root = root;
    while (st_root)
    {
        if (key == st_root->key)
        {
            return st_root->value;
        }
        else if (key < st_root->key)
        {
            st_root = st_root->left;
        }
        else
        {
            st_root = st_root->right;
        }
    }
    throw std::out_of_range("key not found");
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template <typename K, typename V>
const V &AVLMap<K, V>::operator[](const K &key) const
{
    Node *st_root = root;
    while (st_root)
    {
        if (key == st_root->key)
        {
            return st_root->value;
        }
        else if (key < st_root->key)
        {
            st_root = st_root->left;
        }
        else
        {
            st_root = st_root->right;
        }
    }
    throw std::out_of_range("key not found");
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template <typename K, typename V>
void AVLMap<K, V>::insert(const K &key, const V &value)
{
    root = insert(key, value, root);
    count++;
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template <typename K, typename V>
void AVLMap<K, V>::erase(const K &key)
{
    if (contains(key))
    {
        root = erase(key, root);
        count--;
    }
    else
    {
        throw std::out_of_range("Key is not in the tree");
    }
}

// Returns true if the key is in the collection, and false otherwise.
template <typename K, typename V>
bool AVLMap<K, V>::contains(const K &key) const
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

// Returns the keys k in the collection such that k1 <= k <= k2
template <typename K, typename V>
ArraySeq<K> AVLMap<K, V>::find_keys(const K &k1, const K &k2) const
{
    ArraySeq<K> foundKeys;
    find_keys(k1, k2, root, foundKeys);
    return foundKeys;
}

// Returns the keys in the collection in ascending sorted order
template <typename K, typename V>
ArraySeq<K> AVLMap<K, V>::sorted_keys() const
{
    ArraySeq<K> foundKeys;
    sorted_keys(root, foundKeys);
    return foundKeys;
}

// Returns the height of the binary search tree
template <typename K, typename V>
int AVLMap<K, V>::height() const
{
    if (root)
    {
        return root->height;
    }
    else
    {
        return 0;
    }
}

// Private

// clean up the tree and reset count to zero given subtree root
template <typename K, typename V>
void AVLMap<K, V>::make_empty(Node *st_root)
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
typename AVLMap<K, V>::Node *AVLMap<K, V>::copy(const Node *rhs_st_root) const
{
    if (rhs_st_root == nullptr)
    {
        return nullptr;
    }
    Node *new_node = new Node;
    new_node->key = rhs_st_root->key;
    new_node->value = rhs_st_root->value;
    new_node->height = rhs_st_root->height;
    new_node->left = copy(rhs_st_root->left);
    new_node->right = copy(rhs_st_root->right);
    return new_node;
}

// erase helper
template <typename K, typename V>
typename AVLMap<K, V>::Node *AVLMap<K, V>::erase(const K &key, Node *st_root)
{
    if (key < st_root->key)
    {
        st_root->left = erase(key, st_root->left);
    }
    else if (key > st_root->key)
    {
        st_root->right = erase(key, st_root->right);
    }
    else if (key == st_root->key)
    {
        if (!st_root->left)
        {
            //left subtree empty
            Node *tmp = st_root;
            st_root = st_root->right;
            delete tmp;
        }
        else if (!st_root->right)
        {
            //right subtree empty
            Node *tmp = st_root;
            st_root = st_root->left;
            delete tmp;
        }
        else
        {
            //find in-order successor
            Node *succ = st_root->right;
            Node *prev = st_root;
            while (succ->left)
            {
                prev = succ;
                succ = succ->left;
            }
            //copy into st_root
            st_root->key = succ->key;
            st_root->value = succ->value;

            st_root->right = erase(succ->key, st_root->right);
            if (prev != st_root)
            {
                prev->left = succ->right;
            }
            else
            {
                prev->right = succ->right;
            }
        }
    }

    if (st_root)
    {
        if (st_root->left and st_root->right)
        {
            st_root->height = 1 + (std::max(st_root->left->height, st_root->right->height));
        }
        else if (st_root->left and !st_root->right)
        {
            st_root->height = 1 + st_root->left->height;
        }
        else if (!st_root->left and st_root->right)
        {
            st_root->height = 1 + st_root->right->height;
        }
        else
        {
            st_root->height = 1;
        }
    }
    return rebalance(st_root);
}

// insert helper
template <typename K, typename V>
typename AVLMap<K, V>::Node *AVLMap<K, V>::insert(const K &key, const V &value, Node *st_root)
{
    if (st_root == nullptr)
    {
        Node *ptr = new Node;
        ptr->key = key;
        ptr->value = value;
        ptr->left = nullptr;
        ptr->right = nullptr;
        ptr->height = 1;
        return ptr;
    }
    else
    {
        if (key < st_root->key)
        {
            st_root->left = insert(key, value, st_root->left);
        }
        else
        {
            st_root->right = insert(key, value, st_root->right);
        }
        //backtrack: update height
        if (st_root->left and st_root->right)
        {
            st_root->height = 1 + (std::max(st_root->left->height, st_root->right->height));
        }
        else if (st_root->left and !st_root->right)
        {
            st_root->height = 1 + st_root->left->height;
        }
        else
        {
            st_root->height = 1 + st_root->right->height;
        }
    }
    return rebalance(st_root);
}

// find_keys helper
template <typename K, typename V>
void AVLMap<K, V>::find_keys(const K &k1, const K &k2, const Node *st_root, ArraySeq<K> &keys) const
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
void AVLMap<K, V>::sorted_keys(const Node *st_root, ArraySeq<K> &keys) const
{
    if (st_root != nullptr)
    {
        sorted_keys(st_root->left, keys);
        keys.insert(st_root->key, keys.size());
        sorted_keys(st_root->right, keys);
    }
}

// rotations
template <typename K, typename V>
typename AVLMap<K, V>::Node *AVLMap<K, V>::right_rotate(Node *k2)
{
    Node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    int r_height = 0;
    int l_height = 0;
    if (k2->left)
    {
        l_height = k2->left->height;
    }
    if (k2->right)
    {
        r_height = k2->right->height;
    }
    if (l_height > r_height)
    {
        k2->height = l_height + 1;
    }
    else
    {
        k2->height = r_height + 1;
    }

    r_height = 0;
    l_height = 0;
    if (k1->left)
    {
        l_height = k1->left->height;
    }
    if (k1->right)
    {
        r_height = k1->right->height;
    }
    if (l_height > r_height)
    {
        k1->height = l_height + 1;
    }
    else
    {
        k1->height = r_height + 1;
    }

    return k1;
}

template <typename K, typename V>
typename AVLMap<K, V>::Node *AVLMap<K, V>::left_rotate(Node *k2)
{
    Node *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    int r_height = 0;
    int l_height = 0;
    if (k2->left)
    {
        l_height = k2->left->height;
    }
    if (k2->right)
    {
        r_height = k2->right->height;
    }
    if (l_height > r_height)
    {
        k2->height = l_height + 1;
    }
    else
    {
        k2->height = r_height + 1;
    }

    r_height = 0;
    l_height = 0;
    if (k1->left)
    {
        l_height = k1->left->height;
    }
    if (k1->right)
    {
        r_height = k1->right->height;
    }
    if (l_height > r_height)
    {
        k1->height = l_height + 1;
    }
    else
    {
        k1->height = r_height + 1;
    }

    return k1;
}

// rebalance
template <typename K, typename V>
typename AVLMap<K, V>::Node *AVLMap<K, V>::rebalance(Node *st_root)
{
    if (!st_root)
    {
        return st_root;
    }

    Node *left_ptr = st_root->left;
    Node *right_ptr = st_root->right;

    int bal_factor = 0;
    int r_height = 0;
    int l_height = 0;
    if (left_ptr)
    {
        l_height = left_ptr->height;
    }
    if (right_ptr)
    {
        r_height = right_ptr->height;
    }
    bal_factor = l_height - r_height;

    if (left_ptr and !right_ptr and left_ptr->height > 1)
    {
        //Check for double rotation
        if (left_ptr->right)
        {
            left_ptr = left_rotate(left_ptr);
            st_root->left = left_ptr;
        }
        st_root = right_rotate(st_root);
    }
    //right-right case
    else if (!left_ptr and right_ptr and right_ptr->height > 1)
    {
        //Check for double rotation
        if (right_ptr->left)
        {
            right_ptr = right_rotate(right_ptr);
            st_root->right = right_ptr;
        }
        st_root = left_rotate(st_root);
    }
    else if (left_ptr and right_ptr and bal_factor > 1)
    {
        //Check for double rotation
        if (left_ptr->right->height > left_ptr->left->height)
        {
            left_ptr = left_rotate(left_ptr);
            st_root->left = left_ptr;
        }
        st_root = right_rotate(st_root);
    }
    else if (left_ptr and right_ptr and bal_factor < -1)
    {
        //Check for double rotation
        if (right_ptr->left->height > right_ptr->right->height)
        {
            right_ptr = right_rotate(right_ptr);
            st_root->right = right_ptr;
        }
        st_root = left_rotate(st_root);
    }

    return st_root;
}

#endif
