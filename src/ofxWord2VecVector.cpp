#include "ofxWord2VecVector.h"


//--------------------------------------------------------------
void ofxWord2VecVector::allocate(int size) {
	this->size = size;
	vector_v.resize(size);
	vector_vn.resize(size);
	v = &vector_v[0];
	vn = &vector_vn[0];
	allocated_ = true;
}

//--------------------------------------------------------------
//bind to existing array - very efficient way working with huge number of vectors
void ofxWord2VecVector::bind(float *pointer_v, float *pointer_vn, int size) {
	v = pointer_v;
	vn = pointer_vn;
}

//--------------------------------------------------------------
void ofxWord2VecVector::free() {
	size = 0;
	vector_v.clear();
	vector_vn.clear();
	allocated_ = false;
}

//--------------------------------------------------------------
void ofxWord2VecVector::update_normalized() {
	if (size > 0) {
		double len = 0;
		for (int i = 0; i < size; i++) {
			len += v[i] * v[i];
		}
		len = sqrt(len);
		float koef = (len > 0) ? 1.0 / len : 0;
		for (int i = 0; i < size; i++) {
			vn[i] = v[i] * koef;
		}
	}
}

//--------------------------------------------------------------

