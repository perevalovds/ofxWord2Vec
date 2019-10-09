#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cout << "Example using word2vec, which computes words arithmetics such as X - Y + Z = ?" << endl;
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
	cout << "Usage:" << endl;
	cout << "Word arithmetics: enter any number or words separated by ' + ' and ' - '" << endl;
	cout << "   For example, type 'king - man + woman' or 'bird'" << endl;
	cout << "EXIT - break" << endl;
	
	while (1) {
		cout << ">> ";
		//read input string from keyboard
		string s;
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

		//get linear combination of words
		vector<int> used_indices;
		ofxWord2VecVector Vec = embed.words_to_vec(s, &used_indices);

		//Print vector to console
		Vec.print_console("------------------\n", "---------------------");

		//Search closest words in the neighbourhood	
		if (!Vec.empty()) {

			int count = 5;
			vector<ofxWord2VecEmbeddingMatch> match = embed.match_cos(Vec, count, used_indices);
			cout << "Result:" << endl;
			for (int i = 0; i < match.size(); i++) {
				cout << "    " << match[i].word << ": " << match[i].conf << endl;
			}
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
