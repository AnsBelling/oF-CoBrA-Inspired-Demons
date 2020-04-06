#pragma once

#include "ofMain.h"

#include "ofxOilPaint.h"

class Demon : public ofBaseApp {
public:
	ofVec2f demonPos;
	ofPolyline demonOutline;

	Demon();
	~Demon();
	void drawDemon();
	void updateDemon();

	//vector of demon colors
	vector<ofColor> demonColorPalette;

};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	ofImage img;
	int imgW, imgH;

	ofFbo canvas;
	ofPixels canvasPixels;
	ofxOilBrush brush;
	vector<ofColor> initialBristleColors;
	vector<ofColor> currentBristleColors;
	float alphaValue;

	glm::vec2 lastAddedPoint;
	float nextPathLength;

	Demon demon;
};

