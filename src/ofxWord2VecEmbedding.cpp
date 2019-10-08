#include "ofxWord2VecEmbedding.h"

//--------------------------------------------------------------
void ofxWord2VecEmbedding::free() {
	words = size = 0;
	vocab.clear();
	M.clear();
	MN.clear();
	vec.clear();	//it's very important to clear only after clearing M and MN
}

//--------------------------------------------------------------
bool ofxWord2VecEmbedding::load_binary(string file_name) {

	//Open the file
	FILE *f = fopen(ofToDataPath(file_name).c_str(), "rb");
	if (f == NULL) {
		cout << "ofxWord2VecEmbedding::load_binary error: no file " << file_name << endl;
		return false;
	}

	//Read number of words and dimensions
	fscanf(f, "%lld", &words);
	fscanf(f, "%lld", &size);

	if (words <= 0) {
		cout << "ofxWord2VecEmbedding::load_binary error: bad words count " << words << endl;
		return false;
	}
	if (size <= 0) {
		cout << "ofxWord2VecEmbedding::load_binary error: bad dimensions count " << size << endl;
		return false;
	}

	//Allocate memory
	vocab.resize(words);

	M.resize(words*size);
	MN.resize(words*size);
	vec.resize(words);
	for (long long i = 0; i < vec.size(); i++) {
		long long pos = i * size;
		vec[i].bind(&M[pos], &MN[pos], size);
	}
	//if (M == NULL) {
	//	printf("Cannot allocate memory: %lld MB    %lld  %lld\n",
	//		(long long)words * size * sizeof(float) / 1048576, words, size);
	//	return -1;
	//}

	//Reading file

	//buffer for reading word name
	const int max_len = 50;
	char word[max_len];

	for (int i = 0; i < words; i++) {
		//Read word name
		int a = 0;
		while (1) {
			word[a] = fgetc(f);
			if (feof(f) || (word[a] == ' ')) break;
			if ((a < max_len) && (word[a] != '\n')) a++;
		}
		word[a] = 0;
		vocab[i] = word;
		
		//Read projection
		fread(&vec[i].v[0], sizeof(float), size, f);

		//Normalize
		vec[i].update_normalized();
	}
	fclose(f);

	return true;
}


//--------------------------------------------------------------
