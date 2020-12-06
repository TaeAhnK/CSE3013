#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(15);				// 15 frames per second
	ofBackground(255, 255, 255);	// white background

	// Init Variables
	mazeFlag = 0;	// 0: Don't  1: Draw Maze
	routeFlag = 0;	// 0: Don't  1. Draw DFS  2. Draw BFS
	loadFlag = 0;	// 0: No File Loaded  1. File Loaded

	WIDTH = 0;
	HEIGHT = 0;
	sWall = 10;
	lWall = 20;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	/* Draw Maze */
	if (mazeFlag == 1) {
		int lNum = 0;
		float x1 = 0;
		float y1 = startY;
		ofSetColor(0, 0, 255);
		for (ofBuffer::Line it = maz.getLines().begin(), end = maz.getLines().end(); it != end; ++it, lNum++) {
			string line = *it;
			x1 = startX;

			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					if (i % 2 == 0) {
						x1 += sWall;
					}
					else {
						x1 += lWall;
					}
				}
				else if (line[i] == '+') {
					ofDrawRectangle(x1, y1, sWall, sWall);
					x1 += sWall;
				}
				else if (line[i] == '-') {
					ofDrawRectangle(x1, y1, lWall, sWall);
					x1 += lWall;
				}
				else if (line[i] == '|') {
					ofDrawRectangle(x1, y1, sWall, lWall);
					x1 += sWall;
				}
			}
			if (lNum % 2 == 0) {
				y1 += sWall;
			}
			else {
				y1 += lWall;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/* Quit */
	if (key == 'q') {
		freeMemory();
		_Exit(0);
	}

	////* DFS */
	//if (key == 'd') {

	//}

	///* BFS */
	//if (key == 'b') {	// BFS 

	//}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	/* Load File */
	if (key == 'l') {

		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only .maz file for Maze");

		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");
			char* fileName;
			fileName = new char[openFileResult.getName().length()];
			strcpy(fileName, openFileResult.getName().c_str());
			cout << "Selected File : " << fileName << endl;
			if (readFile(fileName) == true)
				loadFlag = 1;
		}
	}
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

//--------------------------------------------------------------
bool ofApp::readFile(const char* fileName) {
	ofFile file(fileName);

	if (!file.exists()) {
		cout << "Target file does not exists." << endl;
		return false;
	}
	else {
		cout << "Target File Found" << endl;
	}
	
	// Free Existing Adj and Buffer
	if (loadFlag == 1) {
		freeMemory();
	}
	loadFlag = 1;

	// Read Width and Height Data
	WIDTH = 0;
	HEIGHT = 0;

	// Read File
	ofBuffer buffer(file);
	maz = buffer;
	string line;

	// Calculate Height and Width
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		line = *it;
		HEIGHT++;
	}
	WIDTH = ((*buffer.getLines().begin()).length() - 1) / 2;
	HEIGHT = (HEIGHT - 1) / 2;
	mazeFlag = 1;

	cout << "Reading Maze..." << endl << "Size : " << WIDTH << " * " << HEIGHT  << endl;
	
	WallSizeCal();
	AdjListGen();
	
	file.close();
	return true;
}

void ofApp::freeMemory() {
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		Adj[i].freeSLL();
	}
	delete[] Adj;
	mazeFlag = 0;
	routeFlag = 0;
	WIDTH = 0;
	HEIGHT = 0;
	maz.clear();
}

void ofApp::AdjListGen() {
	Adj = new SLList [WIDTH * HEIGHT];

	int idx = 0;
	int cNum = 0;

	ofBuffer::Line it = ++(maz.getLines().begin());
	for (int i = 0; i < HEIGHT; i++) {
		cNum++;
		string line = *it;

		// read lines with right wall
		for (int j = 2; j < line.length(); j += 2) {
			if (line[j] == ' ') {
				Adj[idx].insert(cNum, idx);
				Adj[cNum].insert(idx, cNum);
			}
			idx++;
			cNum++;
		}
		it++;
		line = *it;
		idx -= WIDTH;
		cNum--;

		// read lines with bottom wall
		for (int j = 1; j < line.length(); j += 2) {
			if (line[j] == ' ') {
				Adj[idx].insert(cNum, idx);
				Adj[cNum].insert(idx, cNum);
			}
			idx++;
			cNum++;
		}
		it++;
		line = *it;
		cNum = cNum - WIDTH ;
	}

	//// For Debugging 
	//for (int i = 0; i < WIDTH * HEIGHT; i++) {
	//	cout << i << " ";
	//	Adj[i].printSLL();
	//}
}

void ofApp::WallSizeCal() {
	float maxH, maxW;

	// maximum wall size on 1028*768
	maxW = (float) 1020 / (4 * WIDTH + 1);
	maxH = (float) 760 / (4 * HEIGHT + 1);

	if (maxH <= maxW) {
		sWall = maxH;
		lWall = 3 * maxH;
	}
	else {
		sWall = maxW;
		lWall = 3 * maxW;
	}

	// Middle point to draw maze
	startX = (1028 - ((4 * WIDTH + 1) * sWall))/2;
	startY = (768 - ((4 * HEIGHT + 1) * sWall))/2;
	
	printf("Drawing Maze with width %.2f...\n", lWall);
}

SLList::SLList() {
	first = NULL;
	end = NULL;
}

node* SLList::front() {
	return first;
}

void SLList::insert(int cNum, int par) {
	node* p = new node;
	p->cellNum = cNum;
	p->parent = par;
	p->link = NULL;

	if (first == NULL) {
		first = p;
		end = p;
	}
	else {
		end->link = p;
		end = end->link;
	}
}

void SLList::freeSLL() {
	node* p = first;
	while (p != nullptr) {
		first = p->link;
		delete p;
		p = first;
	}
	delete first;
}

void SLList::printSLL() {
	node* p = first;
	while (p != NULL) {
		cout << "(" << p->cellNum << ")" << "->";
		p = p->link;
	}
	cout << "(END)" << endl;
}