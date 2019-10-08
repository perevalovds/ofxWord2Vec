#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cout << "Example using word2vec, which computes words ariphmetics such as X - Y + Z = ?" << endl;
	string file_name = "vec_text8.bin";
		
	cout << "Loading embeddings file: " << file_name << endl;
	embed.load_binary(file_name);

	cout << "words: " << embed.words << endl;
	cout << "dimensions: " << embed.size << endl;
	cout << "vocabulary (first 100 words): " << endl;
	for (int i = 0; i <  min(embed.words, 100); i++) {
		cout << " " << embed.vocab[i];
	}
	cout << endl;

	//Dialog
	cout << endl;
	cout << "Enter any number or words separated by ' + ' and ' - ', they will be treated as X-Y+Z... Type EXIT to break" << endl;
	cout << "For example, type 'man + animal'" << endl;
	cout << "(Also, man + animal * god returns cosine distance between 'man + animal' and 'god'); the last arg must be one word" << endl;
	
	while (1) {
		cout << ">> ";
		string s;
		//read input data
		while (1) {
			char c = fgetc(stdin);
			if (c == '\n') {
				break;
			}
			string temp = " ";
			temp[0] = c;
			s += temp;
		}

		//cout << "-- " << s << " --" << endl;
		if (s == "EXIT") {
			break;
		}

		vector<string> tokens = ofSplitString(s, " ");
		if (tokens.empty()) {
			cout << "Please type something" << endl;
			continue;
		}

		ofxWord2VecVector Vec(embed.size);

		//search words in vocabulary and summing to 'vec'
		int ok = 1;
		int oper = 1;		//1 - "+", 0 - "-"
		int dot = 0;	    //1 means dot product
		float dot_result = 0;

		vector<int> used_indices;	//placeholder for found words - later we will except them from the search

		for (int i = 0; i < tokens.size(); i++) {
			string &token = tokens[i];
			if (token == "+") {
				oper = 1;
				continue;
			}
			if (token == "-") {
				oper = -1;
				continue;
			}
			if (token == "*") {
				dot = 1;
				continue;
			}
			int index = embed.find_case_sensitive(token);
			if (index == -1) {
				cout << "Unknown word '" << token << "'" << endl;
				ok = 0;
				break;
			}

			if (!dot) {
				//add to vector
				Vec.add(embed.vec[index], oper, false);
				//store found index
				used_indices.push_back(index);
				//set operation to "+"
				oper = 1;
			}
			else {
				//perform dist_cos multiplication
				Vec.update_normalized();
				dot_result = Vec.dist_cosine_optimized(embed.vec[index]);
			}
		}
		if (!ok) continue;

		//Compute normalized version
		Vec.update_normalized();

		//Print resulted (unnormalized) vector
		Vec.print_console("------------------\n", "---------------------");

		//Request for dot, it's already stored in dot_result
		if (dot) {
			cout << "dist_cos: " << dot_result << endl;
			continue;
		}


		//Search resulted words in neighbourhood

		int count = 5;
		
		vector<ofxWord2VecEmbeddingMatch> match = embed.match_cos(Vec, count, used_indices);
		cout << "Result:" << endl;
		for (int i = 0; i < match.size(); i++) {
			cout << "    " << match[i].word << ": " << match[i].conf << endl;
		}
	}
	cout << "Exiting now..." << endl;
	OF_EXIT_APP(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
