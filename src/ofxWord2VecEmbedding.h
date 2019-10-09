#pragma once

//Embedding of words

#include "ofMain.h"
#include "ofxWord2VecVector.h"
#include "ofxWord2VecSorter.h"

//embedding class
struct ofxWord2VecEmbedding {

	//Setup ------------------------------------------------
	//load embedding from binary file
	//'speedup_word_search' - if true, then will be created maps for faster searching words
	//for this preparation consumes a time
	bool load_binary(string file_name, bool speedup_word_search = false);
	void free();

	int words = 0;		//number of words
	int size = 0;			//number of dimensions
	vector<float> M;			//matrix
	vector<float> MN;			//normalized matrix
	vector<ofxWord2VecVector>  vec;			//words embedding
	vector<string> vocab;		//vocabulary

	//Operations ------------------------------------------------
	//returns vector corresponding the arithmetics of words,
	//using " + " and " - ", such as 'bird', 'king - man + woman'
	//on error - returns empty vector (size==0)
	//used_indices - pass it if you need to know which words where used
	ofxWord2VecVector words_to_vec(const string &sentence, vector<int> *used_indices = 0);

	
	//search words in vocabulary, -1 means no word found
	//case insensitive - Note: it applies only to search,
	//but actually there are can be several words with the same name
	int find_case_sensitive(const string &word);
	int find_case_insensitive(const string &word);


	//find best or worst mathcing words to a given vector in cosine distance
	//for worst case set descending = true
	vector<ofxWord2VecSorterItem> match_cos(const ofxWord2VecVector &v, int count,
		const vector<int> &except_words = vector<int>(), bool descending = false);



protected:
	bool speedup_word_search = false;
	map<string, int> map_case_sens;	//mapping word->index for fast word search
	map<string, int> map_case_insens;
	void update_mappings();


};