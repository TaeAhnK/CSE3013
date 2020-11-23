#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255, 255, 255);
    ofSetLineWidth(4);

    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(127, 23, 31);  // Set the drawing color to brown

    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);


    ofSetLineWidth(5);
    if (draw_flag) {

        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */
        for (int i = 0; i < num_of_line; i++) {
            ofDrawLine(inputlines[i].x1, inputlines[i].y1, inputlines[i].x2, inputlines[i].y2);
        }
        for (int i = 0; i < num_of_dot; i++) {
            ofSetColor(0, 0, 0);
            ofDrawCircle(inputdots[i].x1, inputdots[i].y1, 10);
        }

        ofSetColor(255, 0, 0);
        ofDrawCircle(inputdots[selc_index].x1, inputdots[selc_index].y1, 10);

         // 2nd week portion.
        ofSetLineWidth(4);
        ofSetColor(0, 0, 255);
        if (waterlineflag) {
            Node* p = inputdots[selc_index].water->front();
            while (p->link != NULL) {
                ofDrawLine(p->x, p->y, p->link->x, p->link->y);
                p = p->link;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
    }
    if (key == 'q') {
        // Reset flags
        draw_flag = 0;
        waterlineflag = 0;

        // Free Linked List of waterfall points
        for (int i = 0; i < num_of_dot; i++) {
            inputdots[i].water->freeSLL();
        }
        // Free the dynamically allocated memory exits.
        delete[] inputlines;
        delete[] inputdots;

        cout << "Dynamically allocated memory has been freed." << endl;

        _Exit(0);
    }
    if (key == 'd') {
        if (!load_flag) return;
        draw_flag = 1;
    }
    if (key == 's') {
        // 2nd week portion.
        if (draw_flag)
            waterlineflag = 1;

    }
    if (key == 'e') {
        // 2nd week portion.
        waterlineflag = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (key == 'l') {
        // Open the Open File Dialog
        ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

        // Check whether the user opened a file
        if (openFileResult.bSuccess) {
            ofLogVerbose("User selected a file");

            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }

    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
    if (key == OF_KEY_RIGHT) {
        if (waterlineflag == 0) {
            selc_index = (selc_index + 1) % num_of_dot;
            cout << "Selcted Dot Coordinate is (" << inputdots[selc_index].x1 << ", " << inputdots[selc_index].y1 << ")" << endl;
        }
    }
    if (key == OF_KEY_LEFT) {
        if (waterlineflag == 0) {
            selc_index = (selc_index - 1 + num_of_dot) % num_of_dot;
            cout << "Selcted Dot Coordinate is (" << inputdots[selc_index].x1 << ", " << inputdots[selc_index].y1 << ")" << endl;
        }

        
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
    //Path to the comma delimited file
    //string fileName = "input.txt";

    string fileName = openFileResult.getName();
    ofFile file(fileName);

    if (!file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;

    ofBuffer buffer(file);

    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
    int linesRead = 0;
    int index = 0;
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */


    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
 
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
 

        if (words.size() == 1) {
            if (input_type == 0) { // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
                inputlines = new inputline [num_of_line];
                linesRead = 0;
                if (num_of_line == 0) {
                    input_type = 1;
                }
            }
            else { // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
                inputdots = new inputdot [num_of_dot];
                index = 0;
            }
        }
        else if (words.size() >= 2) {
            int x1, y1, x2, y2;
            if (input_type == 0) { // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());
                inputlines[index].x1 = x1;
                inputlines[index].y1 = y1;
                inputlines[index].x2 = x2;
                inputlines[index].y2 = y2;
                index++;
                linesRead++;
                if (num_of_line == linesRead) {
                    input_type = 1;
                }
                if ((0 > x1) || ( x1 > 1024) || (0 > x2) || (x2 > 1024) || (40 > y1) || (y1 > 768) || (40 > y2) || (y2 > 768)) {
                    cout << "Error: Input out of bound!" << endl;
                    delete[] inputlines;
                    delete[] inputdots;
                    _Exit(1);
                }
            }
            else { // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                inputdots[index].x1 = x1;
                inputdots[index].y1 = y1;
                index++;
                if ((0 > x1) || (x1 > 1024) || (40 > y1) || (y1 > 768)) {
                    cout << "Error: Input out of bound!" << endl;
                    delete[] inputlines;
                    delete[] inputdots;
                    _Exit(1);
                }
            }



        } // End of else if.
    } // End of for-loop (Read file line by line).
    selc_index = 0;

    initializeWaterLines();
}

/* Calculate the water points */
void ofApp::initializeWaterLines() {
    float curX, curY; // x, y of current point
    float maxY;
    int closestLineNum = 0;       // y of closest point
    float ix, iy;   // x, y of intersect point
    bool waterflag;
    for (int i = 0; i < num_of_dot; i++) {
        // init linked list water
        SLList* temp = new SLList;
        temp->insert(inputdots[i].x1, inputdots[i].y1);
        inputdots[i].water = temp;
        curX = inputdots[i].x1;
        curY = inputdots[i].y1;
        maxY = 728;
        waterflag = 0;
        ix = 0;
        iy = 0;

        while (curY < 728) {
            // When water falls
            if (waterflag == 0) {
                maxY = 728;
                for (int j = 0; j < num_of_line; j++) {
                    if (inputlines[j].x1 <= curX && curX <= inputlines[j].x2) {
                        ix = curX;
                        iy = (float)((float)(inputlines[j].y1 - inputlines[j].y2) / (inputlines[j].x1 - inputlines[j].x2)) * (ix - inputlines[j].x1) + inputlines[j].y1;
                        if (iy > curY && iy < maxY) {
                            maxY = iy;
                            closestLineNum = j;
                        }
                    }
                }
                curY = maxY;
                inputdots[i].water->insert(curX, curY);
                waterflag = 1;
            }
            // When water slides
            else {
                if (inputlines[closestLineNum].y1 <= inputlines[closestLineNum].y2) {
                    curX = inputlines[closestLineNum].x2;
                    curY = inputlines[closestLineNum].y2;

                }
                else {
                    curX = inputlines[closestLineNum].x1;
                    curY = inputlines[closestLineNum].y1;
                }
                inputdots[i].water->insert(curX, curY);
                waterflag = 0;
            }
        }
    }

}

Node* SLList::front() {
    return first;
}

SLList::SLList() {
    first = NULL;
    end = NULL;
}

void SLList::insert(float x, float y) {
    Node* p = new Node;
    p->x = x;
    p->y = y;
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
    Node* p = first;
    while (p != nullptr) {
        first = p->link;
        delete p;
        p = first;
    }
    delete first;
}

void SLList::printSLL() {
    Node* p = first;
    while (p != NULL) {
        cout << "(" << p->x << "," << p->y << ")" << "->";
        p = p->link;
    }
    cout << "(END)" << endl;
}