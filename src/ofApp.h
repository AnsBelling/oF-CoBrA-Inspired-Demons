#pragma once

#include "ofMain.h"

#include "ofxThreadedImageLoader.h"
class Demon : public ofBaseApp {
public:
	
	int blobPositionX, blobPositionY;
	vector<ofColor> demonColorPalette;
	ofPoint eyeDot;

	//set the centre point of the blob
	ofVec3f centre;
	//set distance vairable so it can be use to only collect point at a specific range
	float dist;
	//Demon Blob outline
	ofPolyline line;
	ofPolyline legLine;
	//blob points takes the points within range of the centre and demon points is made up of a number of randomly selcted points from blob points
	vector<ofVec3f> blobpoints, demonPoints;
	//startpoint just used to write to demonpoints easier
	ofVec3f startPoint;
	//boolean that allows refresh of demon
	bool b_sp;
	//the range used around the centre point
	int range, change;
	int currentDemonColor;
	void drawDemons();
	
	Demon();
	~Demon();

};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	//my group of demons
	vector <Demon> demonGroup;

	int numberOfDemons;

	ofImage img;

	//Variables for paintings
	int currentPainting;
	vector<ofImage> images;
	int numberOfImgs;
	ofxThreadedImageLoader loader;
	int randomPicker;
	int imgW, imgH;
	//the keypressed that generates new images
	void keyPressed(int key);


};
