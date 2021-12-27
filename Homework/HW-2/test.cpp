#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "sequence.h"
#include "linkedseq.h"

using namespace std;
int main()
{
    LinkedSeq<char> list1;
    LinkedSeq<char> list2;
    // both empty
    list2 = list1;

    // add to list1 (shouldn't change list2)
    list1.insert('a', 0);
    list1.insert('b', 1);

    // assign list 1 to itself (shouldn't change anything)
    list1 = list1;

    // add items to list 2 and assign list2 to list
    list2.insert('c', 0);
    list2.insert('d', 1);
    list2.insert('e', 2);
    list1 = list2;

    // add to list1 (shouldn't change list2)
    list1.insert('f', 3);
    cout << list1 << endl;
    cout << list2 << endl;
}
