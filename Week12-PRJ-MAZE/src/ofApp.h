#pragma once

#include "ofMain.h"

class node {
public:
	int cellNum;
	int parent;
	node* link;

	node() {
		cellNum = -1;
		parent = -1;
		link = NULL;
	}
};

class SLList {
protected:
	node* first;
	node* end;

public:
	SLList();
	node* front();
	void insert(int cNum, int par);
	void freeSLL();
	void printSLL();
};

class Stack:public SLList {
public:

	node* pop();
	void push(int i);
	bool isEmpty();
	node* top();
};

class Queue:public SLList {
public:
	node* pop();
	void push(int i);
	bool isEmpty();
};


class ofApp : public ofBaseApp{

	public:
		// OpenFrameWorks Basic Functions
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);

		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		bool readFile(const char* filename);
		void freeMemory();

		// Maze Variables and Functions
		int loadFlag;
		int mazeFlag;	// Draw Flag for Maze
		int routeFlag;	// Draw Flag for DFS and BFS

		int WIDTH;		// Width of Maze
		int HEIGHT;		// Height of Maze
		
		float sWall;	// width of line
		float lWall;	// width of blanks

		float startX;	// x of maze
		float startY;	// y of maze
		ofBuffer maz;	// buffer of .maz

		SLList* Adj;	// Adjaceny List of Maze Graph

		void AdjListGen();
		void WallSizeCal();

		// Search Variables and Functions
		bool* visitedDFS;	// visited
		Stack* routeDFS;	// Stack S for route

		bool* visitedBFS;	// visited
		int* parentBFS;		// parent
		
		void DFS(int i);
		void BFS();
};
