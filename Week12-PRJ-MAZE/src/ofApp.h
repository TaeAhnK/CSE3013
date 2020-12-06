#pragma once

#include "ofMain.h"

class node {
public:
	int cellNum;
	bool visited;
	int parent;
	node* link;

	node() {
		cellNum = -1;
		visited = false;
		parent = -1;
		link = NULL;
	}
};

class SLList {
private:
	node* first;
	node* end;

public:
	SLList();
	node* front();
	void insert(int cNum, int par);
	void freeSLL();
	void printSLL();
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

		// Maze Functions
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
};
