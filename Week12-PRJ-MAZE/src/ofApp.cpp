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
	/* Drawing DFS */
	if (routeFlag == 1) {
		/* Visited*/
		float x1;
		float y1;
		ofSetColor(200, 200, 200);

		y1 = startY + (sWall / 2);
		for (int i = 0; i < HEIGHT; i++) {
			x1 = startX + (sWall / 2);
			for (int j = 0; j < WIDTH; j++) {
				if (visitedDFS[(i * WIDTH) + j] == true) {
					ofDrawRectangle(x1, y1, sWall + lWall, sWall + lWall);
				}
				x1 += (sWall + lWall);
			}
			y1 += (sWall + lWall);
		}

		/* Route */
		node* p = routeDFS->front();
		ofSetColor(0, 255, 0);

		//while (p != NULL) {
		//	x1 = startX + (sWall/2) + (p->cellNum % WIDTH) * (sWall + lWall);
		//	y1 = startY + (sWall/2) + (p->cellNum / WIDTH) *(sWall + lWall);
		//	ofDrawRectangle(x1, y1, sWall + lWall, sWall + lWall);
		//	p = p->link;
		//}

		if (p->link == NULL) {
			x1 = startX + (2 * sWall) + (p->cellNum % WIDTH) * (sWall + lWall);
			y1 = startY + (2 * sWall) + (p->cellNum / WIDTH) * (sWall + lWall);
			ofDrawRectangle(x1, y1, sWall, sWall);
		}
		else {
			while (p->link != NULL) {
				if (p->cellNum - p->link->cellNum == WIDTH) {
					x1 = startX + (2 * sWall) + (p->link->cellNum % WIDTH) * (sWall + lWall);
					y1 = startY + (2 * sWall) + (p->link->cellNum / WIDTH) * (sWall + lWall);
					ofDrawRectangle(x1, y1, sWall, (2 * sWall) + lWall);
				}
				else if (p->cellNum - p->link->cellNum == -1 * WIDTH) {
					x1 = startX + (2 * sWall) + (p->cellNum % WIDTH) * (sWall + lWall);
					y1 = startY + (2 * sWall) + (p->cellNum / WIDTH) * (sWall + lWall);
					ofDrawRectangle(x1, y1, sWall, (2 * sWall) + lWall);
				}
				else if (p->cellNum - p->link->cellNum == 1) {
					x1 = startX + (2 * sWall) + (p->link->cellNum % WIDTH) * (sWall + lWall);
					y1 = startY + (2 * sWall) + (p->link->cellNum / WIDTH) * (sWall + lWall);
					ofDrawRectangle(x1, y1, (2 * sWall) + lWall, sWall);
				}
				else if (p->cellNum - p->link->cellNum == -1) {
					x1 = startX + (2 * sWall) + (p->cellNum % WIDTH) * (sWall + lWall);
					y1 = startY + (2 * sWall) + (p->cellNum / WIDTH) * (sWall + lWall);
					ofDrawRectangle(x1, y1, (2 * sWall) + lWall, sWall);
				}
				p = p->link;
			}
		}
	}

	/* Draw BFS */
	if (routeFlag == 2) {
		/* Visited */
		float x1;
		float y1;
		ofSetColor(200, 200, 200);

		y1 = startY + (sWall / 2);
		for (int i = 0; i < HEIGHT; i++) {
			x1 = startX + (sWall / 2);
			for (int j = 0; j < WIDTH; j++) {
				if (visitedBFS[(i * WIDTH) + j] == true) {
					ofDrawRectangle(x1, y1, sWall + lWall, sWall + lWall);
				}
				x1 += (sWall + lWall);
			}
			y1 += (sWall + lWall);
		}

		/* Route */
		ofSetColor(0, 255, 0);
		if (WIDTH * HEIGHT - 1 == 0) {
			x1 = startX + (2 * sWall) + ((WIDTH*HEIGHT-1) % WIDTH) * (sWall + lWall);
			y1 = startY + (2 * sWall) + ((WIDTH * HEIGHT - 1) / WIDTH) * (sWall + lWall);
			ofDrawRectangle(x1, y1, sWall, sWall);
		}
		for (int i = WIDTH * HEIGHT - 1; i != 0; i = parentBFS[i]) {
			if (i - parentBFS[i] == WIDTH) {
				x1 = startX + (2 * sWall) + (parentBFS[i] % WIDTH) * (sWall + lWall);
				y1 = startY + (2 * sWall) + (parentBFS[i] / WIDTH) * (sWall + lWall);
				ofDrawRectangle(x1, y1, sWall, (2 * sWall) + lWall);
			}
			else if (i - parentBFS[i] == -1 * WIDTH) {
				x1 = startX + (2 * sWall) + (i % WIDTH) * (sWall + lWall);
				y1 = startY + (2 * sWall) + (i / WIDTH) * (sWall + lWall);
				ofDrawRectangle(x1, y1, sWall, (2 * sWall) + lWall);
			}
			else if (i - parentBFS[i] == 1) {
				x1 = startX + (2 * sWall) + (parentBFS[i] % WIDTH) * (sWall + lWall);
				y1 = startY + (2 * sWall) + (parentBFS[i] / WIDTH) * (sWall + lWall);
				ofDrawRectangle(x1, y1, (2 * sWall) + lWall, sWall);
			}
			else {
				x1 = startX + (2 * sWall) + (i % WIDTH) * (sWall + lWall);
				y1 = startY + (2 * sWall) + (i / WIDTH) * (sWall + lWall);
				ofDrawRectangle(x1, y1, (2 * sWall) + lWall, sWall);
			}
		}
	}


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
		if (loadFlag == 1) {
			freeMemory();
		}
		_Exit(0);
	}

	/* Erase Route */
	if (key == 'e' && loadFlag == 1) {
		routeFlag = 0;
	}

	/* DFS */
	if (key == 'd' && loadFlag == 1) {
		routeFlag = 1;
	}

	/* BFS */
	if (key == 'b' && loadFlag == 1) {
		routeFlag = 2;
	}

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
	
	// DFS
	visitedDFS = new bool[WIDTH * HEIGHT];		// Init Visited
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		visitedDFS[i] = false;
	}
	routeDFS = new Stack;						// Init Stack S
	DFS(0);
	cout << "DFS Route Found (Press D to See the Route)" << endl;

	// BFS
	visitedBFS = new bool[WIDTH * HEIGHT];		// Init Visited
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		visitedBFS[i] = false;
	}
	parentBFS = new int[WIDTH * HEIGHT];		// Init Parent
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		parentBFS[i] = -1;
	}
	BFS();
	cout << "BFS Route Found (Press B to See the Route)" << endl << endl;

	file.close();
	return true;
}

//--------------------------------------------------------------
void ofApp::freeMemory() {
	// Free Adj List
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		Adj[i].freeSLL();
	}
	delete[] Adj;

	// Free DFS Variables
	delete[] visitedDFS;
	routeDFS->freeSLL();

	// Free BFS Variables
	delete[] visitedBFS;
	delete[] parentBFS;

	// Init Variables
	mazeFlag = 0;
	routeFlag = 0;
	WIDTH = 0;
	HEIGHT = 0;
	maz.clear();
}

//--------------------------------------------------------------
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
				Adj[cNum].insert(idx, cNum);	// logically does not access out-of-index point
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

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void ofApp::DFS(int i) {
	/* DFS with Iterative */
	bool flag;
	routeDFS->push(i);		// S.push(v)
	visitedDFS[i] = true;	// mark v as visited
	while (routeDFS->isEmpty() == false) {
		if (routeDFS->top()->cellNum == WIDTH * HEIGHT - 1) {	// found the target
			return;
		}
		flag = false;
		for (node* w = Adj[routeDFS->top()->cellNum].front(); w != NULL; w = w->link) {
			if (visitedDFS[w->cellNum] == false) {	// S.top has an unvisited adjacent node u
				routeDFS->push(w->cellNum);		// S.push(u)
				visitedDFS[w->cellNum] = true;	// mark u as visited
				flag = true;
				break;
			}
		}
		if (flag == false) {	// S.top does not an unvisited adjacent node
			routeDFS->pop();
		}
	}

	/* DFS with Recursive*/
	//visitedDFS[i] = true;
	//routeDFS->push(i);
	//if (i == WIDTH * HEIGHT - 1) {
	//	foundFlag = true;
	//	return;
	//}
	//for (node* w = Adj[i].front(); w != NULL; w = w->link) {
	//	if (visitedDFS[w->cellNum] == false) {
	//		DFS(w->cellNum);
	//		if (foundFlag == true) {
	//			return;
	//		}
	//	}
	//}
	//routeDFS->pop();
}

//--------------------------------------------------------------
void ofApp::BFS() {
	Queue q;
	int v;
	q.push(0);				// enqueue(v)
	visitedBFS[0] = true;	// mark v as visited

	while (q.isEmpty() == false) { // Q not empty
		v = q.pop()->cellNum;	// dequeue()
		for (node* w = Adj[v].front(); w != NULL; w = w->link) {
			if (visitedBFS[w->cellNum] == false) {	// for all unvisited adjacent nodes
				q.push(w->cellNum);				// enqueue
				visitedBFS[w->cellNum] = true;	// mark as visited
				parentBFS[w->cellNum] = v;		// set parent 
			}
			if (w->cellNum == WIDTH * HEIGHT - 1) {	// found
				q.freeSLL(); // free Q
				return;
			}
		}
	}
	q.freeSLL();
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
node* Stack::pop() {
	node* p = this->first;
	if (this->first->link == NULL) {
		this->first = NULL;
	}
	else {
		this->first = this->first->link;
	}
	return p;
}

void Stack::push(int i) {
	node* p = new node;
	p->cellNum = i;
	p->parent = 0;
	p->link = this->first;
	this->first = p;
}

bool Stack::isEmpty() {
	if (this->first) {
		return false;
	}
	else {
		return true;
	}
}

node* Stack::top() {
	return first;
}

//--------------------------------------------------------------
node* Queue::pop() {
	node* p = this->first;
	if (this->first->link == NULL) {
		this->first = NULL;
	}
	else {
		this->first = this->first->link;
	}
	return p;
}

void Queue::push(int i) {
	this->insert(i, 0);
}

bool Queue::isEmpty() {
	if (this->first != NULL) {
		return false;
	}
	else {
		return true;
	}
}