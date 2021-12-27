//---------------------------------------------------------------------------
// NAME:
// FILE: hw4_test.cpp
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "arrayseq.h"

using namespace std;

//----------------------------------------------------------------------
// ArraySeq Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqQuickSort)
{
    ArraySeq<int> seq;
    ASSERT_EQ(true, seq.empty());
    seq.quick_sort();
    ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemQuickSort)
{
    ArraySeq<int> seq;
    seq.insert(10, 0);
    ASSERT_EQ(1, seq.size());
    ASSERT_EQ(10, seq[0]);
    seq.quick_sort();
    ASSERT_EQ(1, seq.size());
    ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderQuickSort)
{
    ArraySeq<int> seq;
    seq.insert(10, 0);
    seq.insert(20, 1);
    ASSERT_EQ(2, seq.size());
    ASSERT_EQ(10, seq[0]);
    ASSERT_EQ(20, seq[1]);
    seq.quick_sort();
    ASSERT_EQ(10, seq[0]);
    ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, TwoElemReverseQuickSort)
{
    ArraySeq<int> seq;
    seq.insert(20, 0);
    seq.insert(10, 1);
    ASSERT_EQ(2, seq.size());
    ASSERT_EQ(20, seq[0]);
    ASSERT_EQ(10, seq[1]);
    seq.quick_sort();
    ASSERT_EQ(10, seq[0]);
    ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, ThreeElemQuickSortCases)
{
    ArraySeq<int> seq1; // <10,20,30>
    ArraySeq<int> seq2; // <20,30,10>
    ArraySeq<int> seq3; // <30,10,20>
    seq1.insert(10, 0);
    seq1.insert(20, 1);
    seq1.insert(30, 2);
    seq2.insert(20, 0);
    seq2.insert(30, 1);
    seq2.insert(10, 2);
    seq3.insert(30, 0);
    seq3.insert(10, 1);
    seq3.insert(20, 2);
    seq1.quick_sort();
    seq2.quick_sort();
    seq3.quick_sort();
    for (int i = 1; i <= 3; ++i)
    {
        ASSERT_EQ(i * 10, seq1[i - 1]);
        ASSERT_EQ(i * 10, seq2[i - 1]);
        ASSERT_EQ(i * 10, seq3[i - 1]);
    }
}

//----------------------------------------------------------------------
// ArraySeq Quick Sort Rand Pivot Tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqQuickSortRand)
{
    ArraySeq<int> seq;
    ASSERT_EQ(true, seq.empty());
    seq.quick_sort_rand_pivot();
    ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemQuickSortRand)
{
    ArraySeq<int> seq;
    seq.insert(10, 0);
    ASSERT_EQ(1, seq.size());
    ASSERT_EQ(10, seq[0]);
    seq.quick_sort_rand_pivot();
    ASSERT_EQ(1, seq.size());
    ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderQuickSortRand)
{
    ArraySeq<int> seq;
    seq.insert(10, 0);
    seq.insert(20, 1);
    ASSERT_EQ(2, seq.size());
    ASSERT_EQ(10, seq[0]);
    ASSERT_EQ(20, seq[1]);
    seq.quick_sort_rand_pivot();
    ASSERT_EQ(10, seq[0]);
    ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, TwoElemReverseQuickSortRand)
{
    ArraySeq<int> seq;
    seq.insert(20, 0);
    seq.insert(10, 1);
    ASSERT_EQ(2, seq.size());
    ASSERT_EQ(20, seq[0]);
    ASSERT_EQ(10, seq[1]);
    seq.quick_sort_rand_pivot();
    ASSERT_EQ(10, seq[0]);
    ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, ThreeElemQuickSortRandCases)
{
    ArraySeq<int> seq; // <10,20,30>

    seq.insert(20, 0);
    seq.insert(30, 1);
    seq.insert(10, 2);

    seq.quick_sort_rand_pivot();

    for (int i = 1; i <= 3; ++i)
    {
        EXPECT_EQ(i * 10, seq[i - 1]);
    }
}

TEST(BasicArraySeqTests, FiveElemReverseQuickSortRand)
{
    ArraySeq<int> seq;
    seq.insert(20, 0);
    seq.insert(10, 1);
    seq.insert(40, 0);
    seq.insert(30, 1);
    seq.insert(90, 0);

    seq.quick_sort_rand_pivot();

    for (int i = 0; i < 4; ++i)
    {
        ASSERT_LE(seq[i], seq[i + 1]);
    }
}

TEST(BasicArraySeqTests, FiveElemReverseCocktail)
{
    ArraySeq<int> seq; //40 20 10
    seq.insert(20, 0);
    seq.insert(10, 1);
    seq.insert(40, 0);
    seq.insert(30, 1);
    seq.insert(90, 0);

    seq.cocktail_shaker_sort();

    for (int i = 0; i < seq.size() - 1; ++i)
    {
        ASSERT_LE(seq[i], seq[i + 1]);
    }
}

//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
