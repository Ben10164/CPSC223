//---------------------------------------------------------------------------
// NAME:
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"

template <typename K, typename V>
class BinSearchMap : public Map<K, V>
{
public:
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

    // Returns true if the key is in the collection, and false
    // otherwise.
    bool contains(const K &key) const;

    // Returns the keys k in the collection such that k1 <= k <= k2
    ArraySeq<K> find_keys(const K &k1, const K &k2) const;

    // Returns the keys in the collection in ascending sorted order.
    ArraySeq<K> sorted_keys() const;

private:
    // If the key is in the collection, bin_search returns true and
    // provides the key's index within the array sequence (via the index
    // output parameter). If the key is not in the collection,
    // bin_search returns false and provides the last index checked by
    // the binary search algorithm.
    bool bin_search(const K &key, int &index) const;

    // implemented as a resizable array of (key-value) pairs
    ArraySeq<std::pair<K, V> > seq;
};

// Returns the number of key-value pairs in the map
template <typename K, typename V>
int BinSearchMap<K, V>::size() const
{
    return seq.size();
}

// Tests if the map is empty
template <typename K, typename V>
bool BinSearchMap<K, V>::empty() const
{
    return seq.empty();
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template <typename K, typename V>
V &BinSearchMap<K, V>::operator[](const K &key)
{
    int idx = 0;
    if (bin_search(key, idx))
    {
        return seq[idx].second;
    }
    else
    {
        throw std::out_of_range("BinSearchMap<K, V>::operator[](key)");
    }
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template <typename K, typename V>
const V &BinSearchMap<K, V>::operator[](const K &key) const
{
    int idx = 0;
    if (bin_search(key, idx))
    {
        return seq[idx].second;
    }
    else
    {
        throw std::out_of_range("BinSearchMap<K, V>::operator[](key)");
    }
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template <typename K, typename V>
void BinSearchMap<K, V>::insert(const K &key, const V &value)
{
    /*
	int idx = 0;
	if(!bin_search(key, idx)) {
		seq.insert({key, value}, seq.size());
	}
	*/
    seq.insert({key, value}, seq.size());
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template <typename K, typename V>
void BinSearchMap<K, V>::erase(const K &key)
{
    int idx = 0;
    if (bin_search(key, idx))
    {
        seq.erase(idx);
    }
    else
    {
        throw std::out_of_range("BinSearchMap<K, V>::erase(key)");
    }
}

// Returns true if the key is in the collection, and false
// otherwise.
template <typename K, typename V>
bool BinSearchMap<K, V>::contains(const K &key) const
{
    int idx = 0;
    if (bin_search(key, idx))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns the keys k in the collection such that k1 <= k <= k2
template <typename K, typename V>
ArraySeq<K> BinSearchMap<K, V>::find_keys(const K &k1, const K &k2) const
{
    ArraySeq<K> seq_tmp;
    ArraySeq<K> keys = sorted_keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        if (k1 <= keys[i] && keys[i] <= k2)
        {
            seq_tmp.insert(keys[i], seq_tmp.size());
        }
    }
    return seq_tmp;
}

// Returns the keys in the collection in ascending sorted order.
template <typename K, typename V>
ArraySeq<K> BinSearchMap<K, V>::sorted_keys() const
{
    ArraySeq<K> seq_tmp;
    for (int i = 0; i < seq.size(); ++i)
    {
        seq_tmp.insert(seq[i].first, seq_tmp.size());
    }
    seq_tmp.merge_sort();
    return seq_tmp;
}

// If the key is in the collection, bin_search returns true and
// provides the key's index within the array sequence (via the index
// output parameter). If the key is not in the collection,
// bin_search returns false and provides the last index checked by
// the binary search algorithm.
template <typename K, typename V>
bool BinSearchMap<K, V>::bin_search(const K &key, int &index) const
{
    if (seq.empty())
    { //Check that seq is not empty
        return false;
    }
    //Sort array and set start and end values
    ArraySeq<K> seq_tmp = sorted_keys();
    int start = 0;
    int end = seq_tmp.size() - 1;
    //Search
    while (start <= end)
    {
        index = (start + end) / 2;

        if (seq_tmp[index] == key)
        {
            return true;
        }
        else if (seq_tmp[index] > key)
        {
            end = index - 1;
        }
        else
        {
            start = index + 1;
        }
    }
    //Even if key is not in collecion, update the index to the last checked
    if (seq_tmp.size() == 1)
    {
        if (seq_tmp[0] > key)
        {
            index = 0;
        }
        else
        {
            index = 1;
        }
    }
    return false;
}

#endif
