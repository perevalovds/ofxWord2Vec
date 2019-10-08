#pragma once

//Structure for storing float vector in a normalized and non-normalized way

#include "ofMain.h"

struct ofxWord2VecVector {
	int size = 0;
	float *v = 0;	//pointer to raw vector
	float *vn = 0;	//pointer to normalized vector

	//allocate memory
	void allocate(int size);

	//bind to existing array - very efficient way working with huge number of vectors
	//Note: array must exist all time the vector is used
	void bind(float *pointer_v, float *pointer_vn, int size);

	//free memory
	void free();

	//compute normalized vector
	void update_normalized();	


protected:
	bool allocated_ = false;
	vector<float> vector_v;		//raw vector
	vector<float> vector_vn;	//normalized vector


};