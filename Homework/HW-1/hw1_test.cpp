//---------------------------------------------------------------------------
// NAME: Ben Puryear
// FILE: hw1_test.cpp
// DATE: Fall 2021
// DESC: GTests designed to test the
//       versatility of the functions
//       outlined in simple_sorts.h and
//       implimented in simple_sorts.cpp
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "simple_sorts.h"

//---------------------------------------------------------------------------
// Bubble Sort Tests
//---------------------------------------------------------------------------

// Test 1
TEST(BasicBubbleSortTest, EmptyArray)
{
   int array[]{};
   bubble_sort(array, 0);
}

// Test 2
TEST(BasicBubbleSortTest, ReverseOrder)
{
   int array[]{4, 3, 2, 1};
   bubble_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
}

// Test 3
TEST(BasicBubbleSortTest, InOrder)
{
   int array[]{1, 2, 3, 4};
   bubble_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
}

// TODO: Implement the following test. The test should define a list
//       that is "partially unordered", i.e., unlike in the reverse
//       order check, some items are in the correct relative
//       order. Remove this TODO comment once finished.

// Test 4
TEST(BasicBubbleSortTest, PartiallyUnorderedList)
{
   int array[]{1, 3, 2, 4};
   bubble_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
   // Force test to fail -- remove once test is completed.
   // ASSERT_EQ(false, true);
}

// TODO: Fill in the following test, which you should develop on your
//       own. Change the name to better reflect your test case. Remove
//       this TODO once finished.

// Test 5
TEST(BasicBubbleSortTest, MyNewTestCase)
{
   int array[]{3, 2, 4, 1};
   bubble_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
   // Force test to fail -- remove once test is completed.
   // ASSERT_EQ(false, true);
}

//---------------------------------------------------------------------------
// Insertion Sort Tests
//---------------------------------------------------------------------------

// Test 6
TEST(BasicInsertionSortTest, EmptyArray)
{
   int array[]{};
   insertion_sort(array, 0);
}

// Test 7
TEST(BasicInsertionSortTest, ReverseOrder)
{
   int array[]{4, 3, 2, 1};
   insertion_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
}

// Test 8
TEST(BasicInsertionSortTest, InOrder)
{
   int array[]{1, 2, 3, 4};
   insertion_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
}

// TODO: Implement the following test. The test should define a list
//       that is "partially unordered", i.e., unlike in the reverse
//       order check, some items are in the correct relative
//       order. Remove this TODO comment once finished.

// Test 9
TEST(BasicInsertionSortTest, PartiallyUnorderedList)
{
   int array[]{1, 3, 2, 4};
   insertion_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
   // Force test to fail -- remove once test is completed.
   // ASSERT_EQ(false, true);
}

// TODO: Fill in the following test, which you should develop on your
//       own. Change the name to better reflect your test case. Remove
//       this TODO once finished.

// Test 10
TEST(BasicInsertionSortTest, MyNewTestCase)
{
   int array[]{3, 2, 4, 1};
   insertion_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
   // Force test to fail -- remove once test is completed.
   // ASSERT_EQ(false, true);
}

//---------------------------------------------------------------------------
// Selection Sort Tests
//---------------------------------------------------------------------------

// Test 11
TEST(BasicSelectionSortTest, EmptyArray)
{
   int array[]{};
   selection_sort(array, 0);
}

// Test 12
TEST(BasicSelectionSortTest, ReverseOrder)
{
   int array[]{4, 3, 2, 1};
   selection_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
}

// Test 13
TEST(BasicSelectionSortTest, InOrder)
{
   int array[]{1, 2, 3, 4};
   selection_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
}

// TODO: Implement the following test. The test should define a list
// that is "partially unordered", i.e., unlike in the reverse order
// check, some items are in the correct relative order. Remove this
// TODO comment once finished.

// Test 14
TEST(BasicSelectionSortTest, PartiallyUnorderedList)
{
   int array[]{1, 3, 2, 4};
   selection_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
   // Force test to fail -- remove once test is completed.
   // ASSERT_EQ(false, true);
}

// TODO: Fill in the following test, which you should develop on your
//       own. Change the name to better reflect your test case. Remove
//       this TODO once finished.

// Test 15
TEST(BasicSelectionSortTest, MyNewTestCase)
{
   int array[]{3, 2, 4, 1};
   selection_sort(array, 4);
   for (int i = 0; i < 3; ++i)
      ASSERT_LE(array[i], array[i + 1]);
   // Force test to fail -- remove once test is completed.
   // ASSERT_EQ(false, true);
}

//---------------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char *argv[])
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
