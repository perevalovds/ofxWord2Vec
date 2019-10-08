#pragma once

//Embedding of words

#include "ofMain.h"
#include "ofxWord2VecVector.h"

struct ofxWord2VecEmbedding {
	bool load_binary(string file_name);
	void free();

	long long words = 0;		//number of words
	long long size = 0;			//number of dimensions
	vector<float> M;			//matrix
	vector<float> MN;			//normalized matrix
	vector<ofxWord2VecVector>  vec;			//words embedding
	vector<string> vocab;		//vocabulary



};