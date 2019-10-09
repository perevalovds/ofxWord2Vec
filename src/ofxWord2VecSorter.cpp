#include "ofxWord2VecSorter.h"


//--------------------------------------------------------------
ofxWord2VecSorter::ofxWord2VecSorter(int size, bool descending) {
	setup(size, descending);
}

//--------------------------------------------------------------
void ofxWord2VecSorter::setup(int size, bool descending) {
	if (!descending) setup_ascending(size);
	else setup_descending(size);
}

//--------------------------------------------------------------
void ofxWord2VecSorter::setup_ascending(int size) {
	descend = 0;
	this->size = size;
	setup_();
}

//--------------------------------------------------------------
void ofxWord2VecSorter::setup_descending(int size) {
	descend = 1;
	this->size = size;
	setup_();
}

//--------------------------------------------------------------
void ofxWord2VecSorter::setup_() {
	items.resize(size);
	for (auto &item: items) {
		item.clear();
	}
}

//--------------------------------------------------------------
void ofxWord2VecSorter::push_value(int index, float value, const string &word) {
	for (int a = 0; a < size; a++) {
		if (items[a].empty() || (!descend && (value > items[a].value)) || (descend && (value < items[a].value))) {
			for (int d = size - 1; d > a; d--) {
				items[d] = items[d - 1];
			}
			items[a] = ofxWord2VecSorterItem(index, value, word);
			break;
		}
	}

}

//--------------------------------------------------------------
vector<ofxWord2VecSorterItem> ofxWord2VecSorter::sorted() {
	vector<ofxWord2VecSorterItem> itm;
	for (auto &item : items) {
		if (!item.empty()) {
			itm.push_back(item);
		}
	}
	return itm;
}

//--------------------------------------------------------------
