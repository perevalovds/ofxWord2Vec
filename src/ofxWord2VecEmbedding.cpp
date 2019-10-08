#include "ofxWord2VecEmbedding.h"

//--------------------------------------------------------------
void ofxWord2VecEmbedding::free() {
	words = size = 0;
	vocab.clear();
	M.clear();
	MN.clear();
	vec.clear();	//it's very important to clear only after clearing M and MN

	map_case_sens.clear();
	map_case_insens.clear();
	speedup_word_search = false;
}

//--------------------------------------------------------------
bool ofxWord2VecEmbedding::load_binary(string file_name, bool speedup_word_search0) {

	//Open the file
	FILE *f = fopen(ofToDataPath(file_name).c_str(), "rb");
	if (f == NULL) {
		cout << "ofxWord2VecEmbedding::load_binary error: no file " << file_name << endl;
		return false;
	}
	cout << "ofxWord2VecEmbedding - loading " << file_name << endl;

	//Read number of words and dimensions
	long long wordsLL = 0;		//number of words
	long long sizeLL = 0;			//number of dimensions

	fscanf(f, "%lld", &wordsLL);
	fscanf(f, "%lld", &sizeLL);
	words = wordsLL;
	size = sizeLL;

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

	//fill mappings
	if (speedup_word_search0) {
		update_mappings();
	}
	return true;
}

//--------------------------------------------------------------
void ofxWord2VecEmbedding::update_mappings() {
	cout << "ofxWord2VecEmbedding - updating mappings for speedup word search" << endl;
	speedup_word_search = true;
	map_case_sens.clear();
	map_case_insens.clear();
	for (int i = 0; i < words; i++) {
		map_case_sens[vocab[i]] = i;
		string lower = ofToLower(vocab[i]);
		if (map_case_insens.find(lower) == map_case_insens.end()) {
			map_case_insens[lower] = i;
		}
	}
}

//--------------------------------------------------------------
int ofxWord2VecEmbedding::find_case_sensitive(const string &word) {
	//search with mapping
	if (speedup_word_search) {
		if (map_case_sens.find(word) != map_case_sens.end()) {
			return map_case_sens[word];		//TODO twice search, remove it
		}
		return -1;
	}
	//search without mapping
	for (int i = 0; i < words; i++) {
		if (word == vocab[i]) return i;
	}
	return -1;
}

//--------------------------------------------------------------
int ofxWord2VecEmbedding::find_case_insensitive(const string &word) {
	string lower = ofToLower(word);

	//search with mapping
	if (speedup_word_search) {
		if (map_case_insens.find(lower) != map_case_insens.end()) {
			return map_case_insens[lower];  //TODO twice search, remove it
		}
		return -1;
	}

	//search without mapping
	for (int i = 0; i < words; i++) {
		if (lower == ofToLower(vocab[i])) return i;
	}
	return -1;
}

//--------------------------------------------------------------
//find best mathing words to a given vector in cosine distance
vector<ofxWord2VecEmbeddingMatch> ofxWord2VecEmbedding::match_cos(const ofxWord2VecVector &v, int count,
	const vector<int> &except_words) {
	vector<ofxWord2VecEmbeddingMatch> match(count);

	for (int i = 0; i < words; i++) {
		//check if this word is allowable (not in 'except_words' array)
		bool allow = true;
		for (int j = 0; j < except_words.size(); j++) {
			if (i == except_words[j]) {
				allow = false;
				break;
			}
		}
		if (!allow) continue;

		//compute distance and compare with matched
		float dist = vec[i].dist_cosine_optimized(v);

		for (int a = 0; a < count; a++) {
			if (dist > match[a].conf) {
				for (int d = count - 1; d > a; d--) {
					match[d] = match[d - 1];
				}
				match[a] = ofxWord2VecEmbeddingMatch(vocab[i], dist);
				break;
			}
		}
	}

	return match;
}

//--------------------------------------------------------------
