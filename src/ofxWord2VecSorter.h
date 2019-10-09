#pragma once

//Helper structure for compute top values in sorted arrays

#include "ofMain.h"

//Resulting item
struct ofxWord2VecSorterItem {
	int index = -1;
	float value = 0;
	ofxWord2VecSorterItem() {}
	ofxWord2VecSorterItem(int index, float value) {
		this->index = index;
		this->value = value;
	}
	bool empty() { return index == -1; }
	void clear() {
		index = -1;
		value = 0;
	}
};

//Sorted structure
struct ofxWord2VecSorter {
	void setup(int size, bool descending);
	void setup_ascending(int size);
	void setup_descending(int size);

	void push_value(int index, float value);

	vector<ofxWord2VecSorterItem> sorted();

protected:
	int descend = 0;
	int size = 0;
	vector<ofxWord2VecSorterItem> items;
	void setup_();

};