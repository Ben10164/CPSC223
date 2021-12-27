
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "sequence.h"
#include "arrayseq.h"

using namespace std;

int main()
{
    // move empty seq
    ArraySeq<int> seq1;
    ArraySeq<int> seq2(move(seq1));
    // move one-element seq
    ArraySeq<char> seq3;
    seq3.insert('a', 0);
    cout << seq3 << endl;

    ArraySeq<char> seq4(move(seq3));
    cout << seq4 << endl;

    // add item to new seq (to ensure correct move)
    seq4.insert('b', 1);
    cout << seq4 << endl;
    cout << seq3 << endl;
}
