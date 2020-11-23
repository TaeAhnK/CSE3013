#pragma once

#include "ofMain.h"
#include <stdlib.h>

/* Classes for Linked List */
class Node {
public:
	float x;
	float y;
	Node* link;

	Node() {
		x = NULL;
		y = NULL;
		link = NULL;
	}
};

class SLList {
private:
	Node* first;
	Node* end;
public:
	SLList();
	Node* front();
	void insert(float x, float y);
	void freeSLL();
	void printSLL();
};

typedef struct inputline {
	int x1;
	int y1;
	int x2;
	int y2;
} inputline;


typedef struct inputdot {
	int x1;
	int y1;
	SLList* water;
} inputdot;


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	/* WaterFall-related member variables Regions */

	// flag variables
	int draw_flag;
	int load_flag;
	int waterlineflag;
	// Line segment and dot related variables
	int num_of_line, num_of_dot;
	float dot_diameter;
	int selc_index;

	/* Input Data */
	inputline* inputlines;
	inputdot* inputdots;
	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.
};
