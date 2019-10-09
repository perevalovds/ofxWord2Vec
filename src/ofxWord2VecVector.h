#pragma once

//Structure for storing float vector in a normalized and non-normalized way

#include "ofMain.h"

struct ofxWord2VecVector {
	int size = 0;
	float *v = 0;	//pointer to raw vector
	float *vn = 0;	//pointer to normalized vector

	//Setup ------------------------------------------
	ofxWord2VecVector();
	ofxWord2VecVector(int size);		//create vector allocated with its own memory

	//allocate memory
	void allocate(int size);

	//bind to existing array - very efficient way working with huge number of vectors
	//Note: array must exist all time the vector is used
	void bind(float *pointer_v, float *pointer_vn, int size);

	//free memory
	void free();

	//call to compute normalized vector
	//some operations do it by default ('auto_update_normalized' parameter)
	void update_normalized();	

	//Operations ------------------------------------------
	//if you need to perform many operations with vector,
	//discard 'auto_update_normalized' and call update_normalized() after operations

	//set fixed value
	void set(float value, bool auto_update_normalized = true);

	//multiply on scalar
	void multiply(float value, bool auto_update_normalized = true);
	
	//adding with weight
	void add(const ofxWord2VecVector &vec, float weight = 1, bool auto_update_normalized = true);

	//dot multiplication of original vectors
	double dot(const ofxWord2VecVector &vec);

	//cosine distance, applied to normalized vectors, so they must be updated before using this
	double dist_cosine_optimized(const ofxWord2VecVector &vec);

	//L2 distance
	double dist_L2(const ofxWord2VecVector &vec);

	//Utilities ------------------------------------------
	void print_console(string title, string postscript="", int precision = 2);

protected:
	bool allocated_ = false;
	vector<float> vector_v;		//raw vector
	vector<float> vector_vn;	//normalized vector


};