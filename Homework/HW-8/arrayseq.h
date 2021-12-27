
//---------------------------------------------------------------------------
// NAME: Ben Puryear
// FILE: arrayseq.h
// DATE: Fall 2021
// DESC: This file defines all of the functions defined for HW-3, as well as the sorting functions for HW-4
//----------------------------------------------------------------------

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>
#include <ostream>
#include <iostream>
#include <random>
#include "sequence.h"

template <typename T>
class ArraySeq : public Sequence<T>
{
public:
    // Default constructor
    ArraySeq();

    // Copy constructor
    ArraySeq(const ArraySeq &rhs);

    // Move constructor
    ArraySeq(ArraySeq &&rhs);

    // Copy assignment operator
    ArraySeq &operator=(const ArraySeq &rhs);

    // Move assignment operator
    ArraySeq &operator=(ArraySeq &&rhs);

    // Destructor
    ~ArraySeq();

    // Returns the number of elements in the sequence
    virtual int size() const;

    // Tests if the sequence is empty
    virtual bool empty() const;

    // Returns a reference to the element at the index in the
    // sequence. Throws out_of_range if index is invalid.
    virtual T &operator[](int index);

    // Returns a constant address to the element at the index in the
    // sequence. Throws out_of_range if index is invalid.
    virtual const T &operator[](int index) const;

    // Extends the sequence by inserting the element at the given
    // index. Throws out_of_range if the index is invalid.
    virtual void insert(const T &elem, int index);

    // Shrinks the sequence by removing the element at the index in the
    // sequence. Throws out_of_range if index is invalid.
    virtual void erase(int index);

    // Returns true if the element is in the sequence, and false
    // otherwise.
    virtual bool contains(const T &elem) const;

    // Sorts the elements in the sequence using less than equal (<=)
    // operator. (Not implemented in HW-3)
    virtual void sort();

    // MORE
    // implements merge sort over current sequence
    virtual void merge_sort();
    // implements quick sort over current sequence
    virtual void quick_sort();

private:
    // resizable array
    T *array = nullptr;

    // size of list
    int count = 0;

    // max capacity of the array
    int capacity = 0;

    // helper to double the capacity of the array
    void resize();

    // helper to delete the array list (called by destructor and copy
    // constructor)
    void make_empty();

    // MORE
    // helper functions for merge and quick sort
    void merge_sort(int start, int end);

    void quick_sort(int start, int end);
};

template <typename T>
ArraySeq<T>::ArraySeq()
{
    array = nullptr;
    count = 0;
    capacity = 0;
}

// Copy constructor
template <typename T>
ArraySeq<T>::ArraySeq(const ArraySeq &rhs)
{
    for (int i = 0; i < rhs.size(); ++i)
    {
        insert(rhs[i], i);
    }
}

// Move constructor
template <typename T>
ArraySeq<T>::ArraySeq(ArraySeq<T> &&rhs)
{
    *this = std::move(rhs);
}

// Copy assignment operator
template <typename T>
ArraySeq<T> &ArraySeq<T>::operator=(const ArraySeq &rhs)
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
ArraySeq<T> &ArraySeq<T>::operator=(ArraySeq<T> &&rhs)
{
    if (this != &rhs)
    {
        // do the assignment
        make_empty();

        count = rhs.count;

        capacity = rhs.capacity;

        array = rhs.array;

        rhs.make_empty();
        rhs.array = nullptr;
    }

    return *this;
}

// Destructor
template <typename T>
ArraySeq<T>::~ArraySeq()
{
    make_empty();
    delete[] array;
}

// Returns the number of elements in the sequence
template <typename T>
int ArraySeq<T>::size() const
{
    return count;
}

// Tests if the sequence is empty
template <typename T>
bool ArraySeq<T>::empty() const
{
    return (count == 0);
}

// Returns a reference to the element at the index in the
// sequence. Throws out_of_range if index is invalid.

template <typename T>
T &ArraySeq<T>::operator[](int index)
{
    // check the index
    if (index >= size() || index < 0)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }

    return array[index];
}

// Returns a constant address to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template <typename T>
const T &ArraySeq<T>::operator[](int index) const
{
    // check the index
    if (index >= size() || index < 0)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }

    return array[index];
}

// Extends the sequence by inserting the element at the given
// index. Throws out_of_range if the index is invalid.

template <typename T>
void ArraySeq<T>::insert(const T &elem, int index)
{
    // check the index
    if (index > size() || index < 0)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
    if (size() + 1 > capacity)
    {
        resize();
    }
    T temp1 = array[index];
    for (int i = index; i < count; ++i)
    {
        T temp2 = array[i + 1];
        array[i + 1] = temp1;
        temp1 = temp2;
    }
    array[index] = elem;
    count++;
}

// Shrinks the sequence by removing the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template <typename T>
void ArraySeq<T>::erase(int index)
{
    // check the index
    if (index >= size() || index < 0)
    {
        throw std::out_of_range("Out of range in the [] nonconst");
    }
    for (int i = index; i < count - 1; ++i)
    {
        array[i] = array[i + 1];
    }
    --count;
}

// Returns true if the element is in the sequence, and false
// otherwise.
template <typename T>
bool ArraySeq<T>::contains(const T &elem) const
{
    for (int i = 0; i < size(); ++i)
    {
        if (array[i] == elem)
        {
            return true;
        }
    }
    return false;
}

// helper to double the capacity of the array
template <typename T>
void ArraySeq<T>::resize()
{
    if (capacity == 0)
    {
        capacity = 1;
    }
    else
    {
        capacity *= 2;
    }
    T *new_array = new T[capacity];
    for (int i = 0; i < capacity / 2; ++i)
    {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
}

// helper to delete the array list (called by destructor and copy
// constructor)
template <typename T>
void ArraySeq<T>::make_empty()
{
    count = 0;
    capacity = 0;
}

// TODO: Implement the above functions below using the approaches
//       discussed in class and specified in the homework assignment.

template <typename T>
void ArraySeq<T>::sort()
{
    quick_sort();
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const ArraySeq<T> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (i != array.size() - 1)
        {
            stream << array[i] << ", ";
        }
        else
        {
            stream << array[i];
        }
    }
    return stream;
}

// implements merge sort over current sequence
template <typename T>
void ArraySeq<T>::merge_sort()
{
    merge_sort(0, count - 1);
}

// implements quick sort over current sequence
template <typename T>
void ArraySeq<T>::quick_sort()
{
    quick_sort(0, count - 1);
}

// helper functions for merge and quick sort
template <typename T>
void ArraySeq<T>::merge_sort(int start, int end)
{
    int mid = (start + end) / 2;
    if (start < end)
    {
        merge_sort(start, mid);
        merge_sort(mid + 1, end);
    }
    else
    {
        return;
    }

    T temp[(end - start) + 1];
    int first1 = start;
    int first2 = mid + 1;
    int i = 0;
    while (first1 <= mid && first2 <= end)
    {
        if (array[first1] < array[first2])
        {
            temp[i++] = array[first1++];
        }
        else
        {
            temp[i++] = array[first2++];
        }
    }
    while (first1 <= mid)
    {
        temp[i++] = array[first1++];
    }
    while (first2 <= end)
    {
        temp[i++] = array[first2++];
    }
    for (i = 0; i <= (end - start); ++i)
    {
        array[start + i] = temp[i];
    }
}

template <typename T>
void ArraySeq<T>::quick_sort(int start, int end)
{
    if (start < end)
    {
        T pivot_val = array[start];
        int end_p1 = start;
        for (int i = start + 1; i <= end; ++i)
        {
            if (array[i] < pivot_val)
            {
                end_p1++;
                T temp = array[i];
                array[i] = array[end_p1];
                array[end_p1] = temp;
            }
        }
        T temp = array[start];
        array[start] = array[end_p1];
        array[end_p1] = temp;
        quick_sort(start, end_p1 - 1);
        quick_sort(end_p1 + 1, end);
    }
}
#endif
