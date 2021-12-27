//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw4_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-4. To run from the
//       command line use:
//          ./hw4_perf
//       which will print out timing data resulting from running merge
//       sort and quick sort over different sized sorted, reverse
//       sorted, and shuffled resizable array and linked list
//       sequences. To save this data to a file, run the command:
//          ./hw4_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include "util.h"
#include "sequence.h"
#include "arrayseq.h"

using namespace std;
using namespace std::chrono;

typedef function<void(ArraySeq<int> &)> array_sort_fn;

// helper functions: build sequence and sort
void array_quick_sort_rand_pivot(ArraySeq<int> &s)
{
    s.quick_sort_rand_pivot();
}

void array_cocktail_shaker_sort(ArraySeq<int> &s)
{
    s.cocktail_shaker_sort();
}

void array_bubble_sort(ArraySeq<int> &s)
{
    s.bubble_sort();
}

void array_quick_sort(ArraySeq<int> &s)
{
    s.quick_sort();
}

// helper functions: timed array
double array_timed_sorted(int size, array_sort_fn f);
double array_timed_reversed(int size, array_sort_fn f);
double array_timed_shuffled(int size, array_sort_fn f);

void check_sorted(const Sequence<int> &s);

// test parameters
const int start = 0;
const int step = 1000;
const int stop = 20000;
const int runs = 1;
const int shuffles = 5;

int main(int argc, char *argv[])
{
    // configure output
    cout << fixed << showpoint;
    cout << setprecision(2);

    // output data header
    cout << "# All times in milliseconds (msec)" << endl;
    cout << "# Column 4 = avg time array quick sort with rand pivot, shuffled" << endl;
    cout << "# Column 5 = avg time array quick sort with rand pivot, sorted" << endl;
    cout << "# Column 6 = avg time array quick sort with rand pivot, reversed" << endl;
    cout << "# Column 1 = avg time array quick sort, shuffled" << endl;
    cout << "# Column 2 = avg time array quick sort, sorted" << endl;
    cout << "# Column 3 = avg time array quick sort, reversed" << endl;

    // run tests and print test results
    for (int size = start; size <= stop; size += step)
    {
        // double c1 = array_timed_shuffled(size, array_cocktail_shaker_sort);
        // double c2 = array_timed_sorted(size, array_cocktail_shaker_sort);
        // double c3 = array_timed_reversed(size, array_cocktail_shaker_sort);
        // double c4 = array_timed_shuffled(size, array_bubble_sort);
        // double c5 = array_timed_sorted(size, array_bubble_sort);
        // double c6 = array_timed_reversed(size, array_bubble_sort);
        // double c1 = array_timed_shuffled(size, array_quick_sort_rand_pivot);
        // double c2 = array_timed_sorted(size, array_quick_sort_rand_pivot);
        // double c3 = array_timed_reversed(size, array_quick_sort_rand_pivot);

        //cout << size << " " << c1 << " " << c2 << " " << c3 << endl;

        cout << size << " " << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << " " << c6 << endl;
    }
}

double array_timed_sorted(int size, array_sort_fn f)
{
    int total = 0;
    ArraySeq<int> s;
    load_in_order(s, size);
    for (int r = 0; r < runs; ++r)
    {
        auto t0 = high_resolution_clock::now();
        f(s);
        auto t1 = high_resolution_clock::now();
        total += duration_cast<milliseconds>(t1 - t0).count();
        check_sorted(s);
        reset_ordered(s);
    }
    return (total * 1.0) / runs;
}

double array_timed_reversed(int size, array_sort_fn f)
{
    int total = 0;
    ArraySeq<int> s;
    load_reverse_order(s, size);
    for (int r = 0; r < runs; ++r)
    {
        auto t0 = high_resolution_clock::now();
        f(s);
        auto t1 = high_resolution_clock::now();
        total += duration_cast<milliseconds>(t1 - t0).count();
        check_sorted(s);
        reset_reversed(s);
    }
    return (total * 1.0) / runs;
}

double array_timed_shuffled(int size, array_sort_fn f)
{
    int total = 0;
    ArraySeq<int> s;
    load_shuffled(s, size, shuffles);
    for (int r = 0; r < runs; ++r)
    {
        auto t0 = high_resolution_clock::now();
        f(s);
        auto t1 = high_resolution_clock::now();
        total += duration_cast<milliseconds>(t1 - t0).count();
        check_sorted(s);
        reset_shuffled(s, shuffles);
    }
    return (total * 1.0) / runs;
}

void check_sorted(const Sequence<int> &s)
{
    for (int i = 0; i < s.size() - 1; ++i)
    {
        if (s[i] > s[i + 1])
        {
            std::cerr << "Error: Sequence not sorted: s[" << i << "] = "
                      << s[i] << " > "
                      << "s[" << (i + 1) << "] = "
                      << s[i + 1] << endl;
            std::terminate();
        }
    }
}
