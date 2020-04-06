#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//loading image for background
	img.load("riverscene.jpg");
	imgW = img.getWidth();
	imgH = img.getHeight();
	ofSetWindowShape(imgW, imgH);

	//Q for DAN: Is it necessary to instantiate a demon object like this? 
	demon = Demon();

	//Adding ofColor elements (colors extracted from CoBrA painting) to demon color palette	
	ofColor demonBlue(69, 211, 222);
	demon.demonColorPalette.push_back(demonBlue);
	ofColor demonRed(225, 37, 21);
	demon.demonColorPalette.push_back(demonRed);
	ofColor demonOrange(247, 125, 3);
	demon.demonColorPalette.push_back(demonOrange);
	ofColor demonYellow(246, 202, 20);
	demon.demonColorPalette.push_back(demonYellow);
	ofColor demonWhite(248, 251, 245);
	demon.demonColorPalette.push_back(demonWhite);
	ofColor demonGreen(118, 229, 107);
	demon.demonColorPalette.push_back(demonGreen);



	// Initialize the oil painting canvas where it will paint to img size 
	canvas.allocate(imgW, imgH, GL_RGB, 3);
	canvas.begin();
	//ofClear();
	canvas.end();

	// Initialize the application variables
	alphaValue = 1;
	nextPathLength = 0;

	//Setting position of demon to random place on image and random brush size between 5 and 25
	demon.demonPos = ofVec2f(ofRandom(0, imgW), ofRandom(0, imgH));
	brush = ofxOilBrush(demon.demonPos, ofRandom(5, 25));
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	// Paint the canvas on the application window
	canvas.draw(0, 0);
	demon.drawDemon();
}

Demon::Demon()
{
}

Demon::~Demon()
{
}

void Demon::drawDemon()
{

}

void Demon::updateDemon()
{
}
