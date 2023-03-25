#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
    std::pair<TKey,TValue> *sorted;
    int currentPos;
    int len;
public:
    bool modify(TElem new_elem);
    void sort_elements();
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;

};

