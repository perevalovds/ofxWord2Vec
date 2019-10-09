#include "ofxWord2VecVector.h"

//--------------------------------------------------------------
ofxWord2VecVector::ofxWord2VecVector() {

}

//--------------------------------------------------------------
ofxWord2VecVector::ofxWord2VecVector(int size) {		//create vector allocated with its own memory
	allocate(size);
}

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
	this->size = size;
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
//set fixed value
void ofxWord2VecVector::set(float value, bool auto_update_normalized) {
	for (int i = 0; i < size; i++) {
		v[i] = value;
	}
	if (auto_update_normalized) update_normalized();
}

//--------------------------------------------------------------
//multiply on scalar
void ofxWord2VecVector::multiply(float value, bool auto_update_normalized) {
	for (int i = 0; i < size; i++) {
		v[i] *= value;
	}
	if (auto_update_normalized) update_normalized();
}

//--------------------------------------------------------------
//adding with weight
void ofxWord2VecVector::add(const ofxWord2VecVector &vec, float weight, bool auto_update_normalized) {
	for (int i = 0; i < size; i++) {
		v[i] += vec.v[i] * weight;
	}
	if (auto_update_normalized) update_normalized();
}

//--------------------------------------------------------------
//dot multiplication of original vectors
double ofxWord2VecVector::dot(const ofxWord2VecVector &vec) {
	double res = 0;
	for (int i = 0; i < size; i++) {
		res += v[i] * vec.v[i];
	}
	return res;
}

//--------------------------------------------------------------
//cosine distance, applied to normalized vectors, so they must be updated before using this
double ofxWord2VecVector::dist_cosine_optimized(const ofxWord2VecVector &vec) {
	double res = 0;
	for (int i = 0; i < size; i++) {
		res += vn[i] * vec.vn[i];
	}
	return res;
}

//--------------------------------------------------------------
//L2 distance
double ofxWord2VecVector::dist_L2(const ofxWord2VecVector &vec) {
	double res = 0;
	float u;
	for (int i = 0; i < size; i++) {
		u = v[i] - vec.v[i];
		res += u * u;
	}
	return sqrt(res);
}

//--------------------------------------------------------------
void ofxWord2VecVector::print_console(string title, string postscript, int precision) {
	cout << title;
	for (int i = 0; i < size; i++) {
		if (i > 0) cout << " ";
		cout << ofToString(v[i], precision);
	}
	cout << endl;
	cout << postscript << endl;
}

//--------------------------------------------------------------
