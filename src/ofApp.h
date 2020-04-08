#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

    ofImage img;
	//vector of demon colors
	vector<ofColor> demonColorPalette;
	ofPoint eyeDot;

	int imgW, imgH;
	void keyPressed(int key);

	ofPolyline legLine;

	//set the centre point of the blob
	ofVec3f centre;
	//set distance vairable so it can be use to only collect point at a specific range
	float dist;
	//poly line duh
	ofPolyline line;
	//blob points takes the points within range of the centre and demon points is made up of a number of randomly selcted points from blob points
	vector<ofVec3f> blobpoints, demonPoints;
	//startpoint just used to write to demonpoints easier
	ofVec3f startPoint;
	//boolean that allows refresh of demon
	bool b_sp;
	//the range used around the centre point
	int range, change;
    int currentDemonCol;

};
