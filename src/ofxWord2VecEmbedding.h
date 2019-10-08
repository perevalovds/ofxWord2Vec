#pragma once

//Embedding of words

#include "ofMain.h"
#include "ofxWord2VecVector.h"

//result for matching
struct ofxWord2VecEmbeddingMatch {
	string word;		//word name
	int index = -1;		//word index
	float conf = -2;	//confidence [-1..1]
	ofxWord2VecEmbeddingMatch() {}
	ofxWord2VecEmbeddingMatch(string word, float conf, int index) {
		this->word = word;
		this->conf = conf;
		this->index = index;
	}

};

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
	//search words in vocabulary, -1 means no word found
	//case insensitive - Note: it applies only to search,
	//but actually there are can be several words with the same name
	int find_case_sensitive(const string &word);
	int find_case_insensitive(const string &word);

	//find best matching words to a given vector in cosine distance
	vector<ofxWord2VecEmbeddingMatch> match_cos(const ofxWord2VecVector &v, int count,
		const vector<int> &except_words = vector<int>());

	//find worst matching words to a given vector in cosine distance
	vector<ofxWord2VecEmbeddingMatch> match_worst_cos(const ofxWord2VecVector &v, int count,
		const vector<int> &except_words = vector<int>());

protected:
	bool speedup_word_search = false;
	map<string, int> map_case_sens;	//mapping word->index for fast word search
	map<string, int> map_case_insens;
	void update_mappings();


};