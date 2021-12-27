//---------------------------------------------------------------------------
// NAME: Ben Puryear
// FILE: simple_sorts.cpp
// DATE: Fall 2021
// DESC: Simple cpp file that defines all of the
//       functions layed out in simple_sorts.h.
//       These functions are:
//            Bubble Sort
//            Insertion Sort
//            Selection Sort
//---------------------------------------------------------------------------

#include <iostream>
#include "simple_sorts.h"

void swap(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

// TODO: Implement the three sorting functions below. For additional
//       information conconcerning the functions see the
//       simple_sorts.h file.

void bubble_sort(int array[], int n)
{
    for (int i = n - 1; i > 0; --i)
    {
        bool inOrder = true;        // this is by default true, and is expected to become false until it is sorted
        for (int j = 0; j < i; ++j) // goes until n-1 because i want to be able to compare array[n] and array[n+1]
        {
            if (array[j] > array[j + 1])
            {
                inOrder = false;
                swap(array[j], array[j + 1]);
            }
        }
        if (inOrder)
        {
            break;
        }
    }
}

void insertion_sort(int array[], int n)
{
    for (int i = 1; i < n; ++i) // traverse the array
    {
        for (int j = i; j > 0; --j) // go backward until the first position (or if in the right spot)
        {
            if (array[j] < array[j - 1]) // This means it is not in the right position
            {
                swap(array[j], array[j - 1]); // swap
            }
            else
            {
                break; // Breaks because it is in the right position
            }
        }
    }
}

void selection_sort(int array[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        int currentMin = array[i];
        int currentMinPos = i;
        for (int j = i; j < n; ++j) // traverse the array
        {
            if (currentMin > array[j]) // if the current min is larger than the current pos
            {
                currentMin = array[j]; // then the new current min is the current pos
                currentMinPos = j;     // also change the index stored
            }
        }
        swap(array[currentMinPos], array[i]); // swap the current min position with the current value at index i
    }
}
