
//---------------------------------------------------------------------------
// NAME: Ben Puryear
// FILE: linkedlist.h
// DATE: Fall 2021
// DESC: This file defines all of the functions defined for HW-2, as well as the sorting functions for HW-4
//----------------------------------------------------------------------

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"
#include <iostream>

template <typename T>
class LinkedSeq : public Sequence<T>
{
public:
    // Default constructor
    LinkedSeq();

    // Copy constructor
    LinkedSeq(const LinkedSeq &rhs);

    // Move constructor
    LinkedSeq(LinkedSeq &&rhs);

    // Copy assignment operator
    LinkedSeq &operator=(const LinkedSeq &rhs);

    // Move assignment operator
    LinkedSeq &operator=(LinkedSeq &&rhs);

    // Destructor
    ~LinkedSeq();

    // Returns the number of elements in the sequence
    int size() const override;

    // Tests if the sequence is empty
    bool empty() const override;

    // Returns a reference to the element at the index in the
    // sequence. Used for lvalues (assignments into the
    // sequence). Throws out_of_range if index is invalid (less than 0
    // or greater than or equal to size()).
    T &operator[](int index) override;

    // Returns a constant address to the element at the index in the
    // sequence. Used for rvalues (evaluating to the value at the
    // index). Throws out_of_range if index is invalid (less than 0 or
    // greater than or equal to size()).
    const T &operator[](int index) const override;

    // Extends (grows) the sequence by inserting the element at the
    // given index (shifting existing elements to the "right" in the
    // sequence).  Throws out_of_range if the index is invalid (less
    // than 0 or greater than size()).
    void insert(const T &elem, int index) override;

    // Shrinks the sequence by removing the element at the index in the
    // sequence (shifing elements to the "left" in the sequence). Throws
    // out_of_range if index is invalid.
    void erase(int index) override;

    // Returns true if the element is in the sequence, and false
    // otherwise.
    bool contains(const T &elem) const override;

    // Sorts the elements in the sequence using less than equal (<=)
    // operator. (Not implemented in HW-2)
    void sort() override;

    // MORE
    // implements merge sort over current sequence
    void merge_sort();
    // implements quick sort over current sequence
    void quick_sort();

private:
    // linked list node
    struct Node
    {
        T value;
        Node *next = nullptr;
    };

    // head pointer
    Node *head = nullptr;

    // tail pointer
    Node *tail = nullptr;

    // size of list
    int node_count = 0;

    // helper to delete all the nodes in the list (called by destructor
    // and copy assignment operator)
    void make_empty();

    // MORE
    // helper functions for merge and quick sort
    static Node *merge_sort(Node *left, int len);
    static Node *quick_sort(Node *start, int len);
};

// TODO: implement the following stream insertion operator. Note that
//       the function should be implemented using only public
//       functions of LinkedSeq

template <typename T>
std::ostream &operator<<(std::ostream &stream, const LinkedSeq<T> &seq)
{
    for (int i = 0; i < seq.size(); i++)
    {
        if (i != seq.size() - 1)
        {
            stream << seq[i] << ", ";
        }
        else
        {
            stream << seq[i];
        }
    }
    return stream;
}

template <typename T>
LinkedSeq<T>::LinkedSeq()
{
    head = nullptr;
    tail = nullptr;
    node_count = 0;
}

// TODO: Finish the remaining LinkedSeq functions below. To get your
//       code to initially compile, "stub out" each function (i.e.,
//       define each function but with an empty function body less a
//       return if required by the function). Then incrementally
//       implement each function as per the homework specfications.

// helper to delete all the nodes in the list (called by destructor
// and copy assignment operator)
template <typename T>
void LinkedSeq<T>::make_empty()
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    node_count = 0;
}

// Copy constructor
template <typename T>
LinkedSeq<T>::LinkedSeq(const LinkedSeq &rhs)
{
    head = nullptr;
    tail = nullptr;
    node_count = 0;
    if (!rhs.empty())
    {
        for (int i = 0; i < rhs.size(); ++i)
        {
            insert(rhs[i], i);
        }
    }
}

// Move constructor
template <typename T>
LinkedSeq<T>::LinkedSeq(LinkedSeq &&rhs)
{
    *this = std::move(rhs);
}

// Copy assignment operator
template <typename T>
LinkedSeq<T> &LinkedSeq<T>::operator=(const LinkedSeq<T> &rhs)
{
    if (this != &rhs)
    {
        make_empty();
        if (!rhs.empty())
        {
            for (int i = 0; i < rhs.size(); ++i)
            {
                insert(rhs[i], i);
            }
        }
    }
    return *this;
}

// Move assignment operator
template <typename T>
LinkedSeq<T> &LinkedSeq<T>::operator=(LinkedSeq<T> &&rhs)
{
    // make sure to check and see if they are the same
    if (this != &rhs)
    {
        // delete the current linked list
        make_empty();
        // transfer
        head = rhs.head;
        tail = rhs.tail;
        node_count = rhs.node_count;
        // zero out rhs
        rhs.tail = rhs.head = nullptr;
        rhs.node_count = 0;
    }
    return *this;
}

// Destructor
template <typename T>
LinkedSeq<T>::~LinkedSeq()
{
    make_empty();
    tail = head = nullptr;
    node_count = 0;
}

// Returns the number of elements in the sequence
template <typename T>
int LinkedSeq<T>::size() const
{
    return node_count;
}

// Tests if the sequence is empty
template <typename T>
bool LinkedSeq<T>::empty() const
{
    return node_count == 0;
}

// Returns a reference to the element at the index in the
// sequence. Used for lvalues (assignments into the
// sequence). Throws out_of_range if index is invalid (less than 0
// or greater than or equal to size()).
template <typename T>
T &LinkedSeq<T>::operator[](int index)
{
    // check the index
    if (index >= size() || index < 0)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
    if (index == size() - 1)
    {
        return tail->value;
    }

    Node *temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }
    return temp->value;
}

// Returns a constant address to the element at the index in the
// sequence. Used for rvalues (evaluating to the value at the
// index). Throws out_of_range if index is invalid (less than 0 or
// greater than or equal to size()).
template <typename T>
const T &LinkedSeq<T>::operator[](int index) const
{
    // check the index
    if (index >= size() || index < 0)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
    if (index == size() - 1)
    {
        return tail->value;
    }

    Node *temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }
    return temp->value;
}

// Extends (grows) the sequence by inserting the element at the
// given index (shifting existing elements to the "right" in the
// sequence).  Throws out_of_range if the index is invalid (less
// than 0 or greater than size()).
template <typename T>
void LinkedSeq<T>::insert(const T &elem, int index)
{
    // check the index
    if (index > node_count || index < 0)
    {
        throw std::out_of_range("Out of range in insert");
    }
    Node *newNode = new Node;
    newNode->value = elem;
    // empty
    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else if (index == size())
    {
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        Node *temp = head;

        // its not empty
        for (int i = 1; i < index; ++i)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    if (index == size())
    {
        tail = newNode;
    }
    // increase node_count
    node_count++;
}

// Shrinks the sequence by removing the element at the index in the
// sequence (shifing elements to the "left" in the sequence). Throws
// out_of_range if index is invalid.
template <typename T>
void LinkedSeq<T>::erase(int index)
{
    // check the index
    if (index >= size() || index < 0)
    {
        throw std::out_of_range("Out of range in erase");
    }
    Node *nodeToDelete;
    if (node_count == 1)
    {
        nodeToDelete = head;
        head = tail = nullptr;
    }
    else
    {
        Node *temp = head;
        //get to the pos
        for (int i = 1; i < index; ++i)
        {
            temp = temp->next;
        }

        nodeToDelete = temp->next;
        if (index == 0) // its the frist
        {
            nodeToDelete = head;
            head = head->next;
        }
        else if (index == node_count - 1) // its the last index
        {
            tail = temp;
            temp->next = nullptr;
        }
        else
        {
            temp->next = nodeToDelete->next;
        }
    }
    delete nodeToDelete;

    node_count--;
}

// Returns true if the element is in the sequence, and false
// otherwise.
template <typename T>
bool LinkedSeq<T>::contains(const T &elem) const
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->value == elem)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <typename T>
void LinkedSeq<T>::sort()
{
    merge_sort();
}

// implements merge sort over current sequence
template <typename T>
void LinkedSeq<T>::merge_sort()
{
    if (node_count <= 1)
    {
        return;
    }
    head = merge_sort(head, node_count);

    Node *temp = head;
    int i = 0;
    while (i < node_count - 1)
    {
        temp = temp->next;
        i++;
    }
    tail = temp;
}

// implements quick sort over current sequence
template <typename T>
void LinkedSeq<T>::quick_sort()
{
    if (node_count <= 1)
    {
        return;
    }

    head = quick_sort(head, node_count);

    tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
}

template <typename T>
typename LinkedSeq<T>::Node *LinkedSeq<T>::merge_sort(Node *left, int len)
{
    if (len <= 1)
    {
        return left;
    }
    int mid = (len + 1) / 2;

    Node *last_left = left;
    for (int i = 1; i < mid; ++i) // we know that the left side will have a len of at least 1
    {
        last_left = last_left->next;
    }

    Node *right = last_left->next;
    last_left->next = nullptr;

    left = merge_sort(left, mid);
    right = merge_sort(right, len - mid);

    Node *new_left = nullptr;

    if (left == nullptr)
    {
        return right;
    }
    if (right == nullptr)
    {
        return left;
    }

    Node *cur_left = left;
    Node *cur_right = right;

    if (cur_left->value <= cur_right->value)
    {
        new_left = left;
        cur_left = cur_left->next;
    }
    else
    {
        new_left = right;
        cur_right = cur_right->next;
    }

    Node *cur_new_left = new_left;

    while (cur_left != NULL && cur_right != NULL)
    {
        if (cur_left->value <= cur_right->value)
        {
            cur_new_left->next = cur_left;
            cur_left = cur_left->next;
            cur_new_left = cur_new_left->next;
        }
        else
        {
            cur_new_left->next = cur_right;
            cur_right = cur_right->next;
            cur_new_left = cur_new_left->next;
        }
    }

    if (cur_left == NULL)
    {
        cur_new_left->next = cur_right;
    }
    else
    {
        cur_new_left->next = cur_left;
    }
    return new_left;
}

template <typename T>
typename LinkedSeq<T>::Node *LinkedSeq<T>::quick_sort(Node *start, int len)
{
    if (len <= 1)
    {
        return start;
    }

    Node *pivot_node = start;

    int pivot = pivot_node->value;

    int smaller_len = 0, larger_len = 0;
    Node *smaller_tail = nullptr;
    Node *smaller = smaller_tail;

    Node *larger_tail = nullptr;
    Node *larger = larger_tail;

    Node *cur = start->next;

    while (cur != nullptr)
    {
        if (cur->value > pivot)
        {
            if (larger_len == 0)
            {
                larger = cur;
            }
            else
            {
                larger_tail->next = cur;
            }
            larger_tail = cur;
            larger_len++;
            cur = cur->next;
            larger_tail->next = nullptr;
        }
        else
        {
            if (smaller_len == 0)
            {
                smaller = cur;
            }
            else
            {
                smaller_tail->next = cur;
            }
            smaller_tail = cur;
            smaller_len++;
            cur = cur->next;
            smaller_tail->next = nullptr;
        }
    }

    smaller = quick_sort(smaller, smaller_len);

    if (smaller == nullptr)
    {
        smaller = pivot_node;
    }
    else
    {
        smaller_tail = smaller;
        while (smaller_tail->next != nullptr)
        {
            smaller_tail = smaller_tail->next;
        }
        smaller_tail->next = pivot_node;
    }

    larger = quick_sort(larger, larger_len);

    if (larger_tail != nullptr)
    {
        larger_tail = larger;
        while (larger_tail->next != nullptr)
        {
            larger_tail = larger_tail->next;
        }
        larger_tail->next = nullptr;
    }
    pivot_node->next = larger;
    return smaller;
}

#endif
