#include "SMMIterator.h"
#include "SortedMultiMap.h"

// Best case: theta(n)
// Average case: theta(n^2)
// Worst case: theta(n^2)
// Complexity: O(n^2)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
    // we copy the elements which are not empty/deleted
    this->len = this->map.size();
    this->sorted = new std::pair<TKey, TValue>[this->len];
    int j = 0;
    for (int index = 0; index < this->map.m; index++)
        if (this->map.elems[index].first != NULL_TVALUE && this->map.elems[index].first != DELETED)
        {
            this->sorted[j] = this->map.elems[index];
            j++;
        }
    // Bubble sort
    int end = this->len - 1;
    bool swap = true;
    std::pair<TKey,TValue> elem;
    while (swap)
    {
        // we suppose that it is already sorted, no swaps will be executed
        swap = false;
        for (int index = 0; index < end; index++)
            // if the relation is not respected -> swap elements, mark swap
            if (!this->map.rel(sorted[index].first, sorted[index+1].first))
            {
                elem = sorted[index];
                sorted[index] = sorted[index+1];
                sorted[index+1] = elem;
                swap = true;
            }
        end--;
    }
    this->currentPos = 0;
}

// Complexity: theta(1)
void SMMIterator::first(){
	//TODO - Implementation
    this->currentPos = 0;
}

// Complexity: theta(1)
void SMMIterator::next(){
	//TODO - Implementation
    if (SMMIterator::valid())
        this->currentPos++;
    else
    {
        exception E;
        throw E;
    }
}

// Complexity: theta(1)
bool SMMIterator::valid() const{
	//TODO - Implementation
	return this->currentPos < this->len;
}

// Complexity: theta(1)
TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
    // check if the iterator is corrent and return element
    if (SMMIterator::valid())
        return this->sorted[this->currentPos];
    else
    {
        exception E;
        throw E;
    }
}


// Best case: theta(n)
// Average case: theta(n^2)
// Worst case: theta(n^2)
// Complexity: O(n^2)
void SMMIterator::sort_elements()
{
    // Bubble sort
    int end = this->len - 1;
    bool swap = true;
    std::pair<TKey,TValue> elem;
    while (swap)
    {
        // we suppose that it is already sorted, no swaps will be executed
        swap = false;
        for (int index = 0; index < end; index++)
            // if the relation is not respected -> swap elements, mark swap
            if (!this->map.rel(sorted[index].first, sorted[index+1].first))
            {
                elem = sorted[index];
                sorted[index] = sorted[index+1];
                sorted[index+1] = elem;
                swap = true;
            }
        end--;
    }
}

