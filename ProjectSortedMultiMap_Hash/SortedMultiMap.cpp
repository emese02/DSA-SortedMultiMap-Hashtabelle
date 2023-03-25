#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// Complexity: theta(1)
TFunction SortedMultiMap::hash(TKey k, int i) const {
    // we choose c1 and c2 in such a way in order to get permutation
    float c1 = 0.5, c2 = 0.5;
    int result = (int) (k % this->m + c1 * i + c2 * i * i) % this->m;
    // hashfunction returns always a positive value
    if (result < 0)
        result *= -1;
    return result;
}

// Complexity: theta(m)  - initialize each pair
SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
    this->rel = r;
    // we choose m as power of 2 (size)
    this->m = 16;
    this->elems = new std::pair<TKey, TValue> [this->m];
    // at the beginning the map is empty
    for (int index = 0; index < this->m; index++)
        this->elems[index] = NULL_TELEM;
}

// Best Case: theta(1) - the first found position pos is free
// Average case: theta(1)
// Worst Case: theta(m) amortisiert - resize, rehash / we have to continue hashing, last found position is free
// Complexity: O(m)
void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
    // we start "hashing" with index 0
    int i = 0;
    int pos = hash(c, i);
    // we continue hasing until we find an empty position / deleted
    while (i < this->m && this->elems[pos].first != NULL_TVALUE && this->elems[pos].first != DELETED)
    {
        i++;
        pos = hash(c, i);
    }
    // arrived at the end of the map -> map is full
    if (i == this->m)
    {
        // resize, rehash
        int new_size = this->m * 2;
        auto *newElements = new std::pair<TKey, TValue> [new_size];
        for (int index = 0; index < new_size; index++)
            newElements[index] = NULL_TELEM;

        this->m *= 2;
        TElem old_elem;
        for (int index = 0; index < this->m/2; index++)
        {
            // save old pair, find new position in the new dynamic array
            old_elem = this->elems[index];
            i = 0;
            pos = hash(old_elem.first, i);
            while (i < new_size && newElements[pos].first != NULL_TVALUE)
            {
                i++;
                pos = hash(old_elem.first, i);
            }
            newElements[pos] = old_elem;
        }
        // copy the new array
        this->elems = newElements;
        // find the correct position for the new pair
        i=0;
        pos = hash(c, i);
        while (i < this->m && this->elems[pos].first != NULL_TVALUE)
        {
            i++;
            pos = hash(c,i);
        }
    }

    // insert new pair at the correct position
    this->elems[pos] = TElem (c,v);
}

// Best Case: theta(1) - TKey c is not in the map (NULL_TVALUE is on the first found pos)
// Average case: theta(1)
// Worst Case: theta(m) - at all positions there is the same TKey c - we must go through the whole map
// Complexity: O(m)
vector<TValue> SortedMultiMap::search(TKey c) const {
    //TODO - Implementation
    vector<TValue> searched_values;
    int i = 0;
    int pos = hash(c, i);
    // hashing while we don't find NULL_TVALUE
    // we continue searching if at a position we find DELETED
    while (i < this->m && this->elems[pos].first != NULL_TVALUE) {
        // we check if the key matches (if we have collisions -> at positions pairs with other key can appear)
        if (this->elems[pos].first == c)
            searched_values.push_back(this->elems[pos].second);
        i++;
        pos = hash(c, i);
    }
    return searched_values;
}

// Best Case: theta(1) - pair (c,v) found on the first hash-position  / TKey c is not in the map (NULL_TVALUE is on the first found pos)
// Average case: theta(1)
// Worst Case: theta(m) - at all positions there is the same TKey c, TValue is on the last found position- we must go through the whole map
// Complexity: O(m)
bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
    int i = 0;
    int pos = hash(c, i);
    while (i < this->m && (this->elems[pos].first != c || this->elems[pos].second != v) && this->elems[pos].first != NULL_TVALUE)
    {
        i++;
        pos = hash(c,i);
    }
    // if pair found -> we mark as deleted
    if (this->elems[pos].first == c && this->elems[pos].second == v)
    {
        this->elems[pos] = DELETED_TELEM;
        return true;
    }
    else
        return false;
}

// Complexity: theta(m) - we go through all elements
int SortedMultiMap::size() const {
    //TODO - Implementation
    int count = 0;
    // if pair is not marked as deleted, and is not empty -> increment count
    for (int index = 0; index < this->m ;index++)
        if (this->elems[index].first != DELETED && this->elems[index].first != NULL_TVALUE)
            count++;
    return count;
}

// Complexity: theta(m) - because of size
bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return SortedMultiMap::size() == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

// Complexity: theta(m) - deleting all slots
SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
    delete []this->elems;
}
