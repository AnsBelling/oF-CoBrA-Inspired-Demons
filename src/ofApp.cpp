#include "ofApp.h"

/*
Acknowledgements:

*/

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	img.load("riverscene.jpg");
	imgW = img.getWidth();
	imgH = img.getHeight();
	ofSetWindowShape(imgW, imgH);
	//ofSetColor(demonColorPalette[(int)ofRandom(0, 5)]);
	/* Rubbish	//Draw a circle
	for (int i = -30; i <= 360 + 30; i += 30) {

		float x = ofGetWidth() * 3 / 4 + cos(DEG_TO_RAD * i) * 100;
		float y = ofGetHeight() / 2 + sin(DEG_TO_RAD * i) * 100;

		body.curveTo(x, y);
	}

	*/
	
	//initialise centre point of the Demon, range and boolean so a demon is drawn straight away
	centre.x = 0;
	centre.y = 0;
	b_sp = true;
	range = 75;
	change =25;

	//Adding ofColor objects (colors extracted from CoBrA painting) to demon color palette	
	ofColor demonBlue(69, 211, 222);
	demonColorPalette.push_back(demonBlue);
	ofColor demonRed(225, 37, 21);
	demonColorPalette.push_back(demonRed);
	ofColor demonOrange(247, 125, 3);
	demonColorPalette.push_back(demonOrange);
	ofColor demonYellow(246, 202, 20);
	demonColorPalette.push_back(demonYellow);
	ofColor demonWhite(248, 251, 245);
	demonColorPalette.push_back(demonWhite);
	ofColor demonGreen(118, 229, 107);
	demonColorPalette.push_back(demonGreen);

}

//--------------------------------------------------------------
void ofApp::update() {
	/*//Make edges move randomly
	for (auto &vert : line.getVertices()) {
		vert.x += ofRandom(-1, 1);
		vert.y += ofRandom(-1, 1);
	}
	//	body = body.getSmoothed(2);
	*/
	//clear the blobpoint vector
	blobpoints.clear();
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	/*//body = body.getResampledBySpacing(0.5);

	eyeDot.x = line.getCentroid2D().x;
	eyeDot.y = line.getCentroid2D().y;
	float time = ofGetElapsedTimef()/4;
	float value = sin(time * M_TWO_PI);
	v = ofMap(value, -1, 1, 10, 20);

	ofSetColor(255);
	ofDrawCircle(eyeDot.x, eyeDot.y, v);
	body.draw();
	*/

	// A vector of all the points within a given distance of the centre point is stored then some points are picked at random. These points are then used to draw the shapes.

	ofPushMatrix();
	showImg();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	int ratio = (ofGetWidth() + ofGetHeight()) / 2;
	if (b_sp) {
		// 4 for loops to add the points to a vector in clockwise order, each covering an quarter of the space, changing the values of the x, y points with a random number to generate the random blobs
		for (int i = centre.x; i < centre.x + range; i++) {
			for (int j = centre.y - range; j < centre.y; j++) {
				dist = ofDist(centre.x, centre.y, i, j);
				if (dist == range) {
					//if the distance from the centre to i,j is the range then push the point to the blob vector
					ofVec2f point(i + ofRandom(-change, change), j + ofRandom(-change, change));
					blobpoints.push_back(point);
				}
			}
		}
		for (int i = centre.x + range; i > centre.x; i--) {
			for (int j = centre.y; j < centre.y + range; j++) {
				dist = ofDist(centre.x, centre.y, i, j);
				if (dist == range) {
					//if the distance from the centre to i,j is the range then push the point to the blob vector
					ofVec2f point(i + ofRandom(-change, change), j + ofRandom(-change, change));
					blobpoints.push_back(point);
				}
			}
		}
		for (int i = centre.x; i > centre.x - range; i--) {
			for (int j = centre.y + range; j > centre.y; j--) {
				dist = ofDist(centre.x, centre.y, i, j);
				if (dist == range) {
					//if the distance from the centre to i,j is the range then push the point to the blob vector
					ofVec2f point(i + ofRandom(-change, change), j + ofRandom(-change, change));
					blobpoints.push_back(point);
				}
			}
		}
		for (int i = centre.x - range; i < centre.x; i++) {
			for (int j = centre.y; j > centre.y - range; j--) {
				dist = ofDist(centre.x, centre.y, i, j);
				if (dist == range) {
					//if the distance from the centre to i,j is the range then push the point to the blob vector
					ofVec2f point(i + ofRandom(-change, change), j + ofRandom(-change, change));
					blobpoints.push_back(point);
				}
			}
		}

		//adds random points to the Demon vector once since it falses the bool and removes the chosen point to prevent duplicates
		for (int p = 0; p < blobpoints.size(); p++) {
			//int index = ofRandom(1,blobpoints.size());
			startPoint.x = blobpoints[p].x;
			startPoint.y = blobpoints[p].y;
			//line.curveTo(startPoint);
			//blobpoints.erase(blobpoints.begin()+p);
			demonPoints.push_back(startPoint);

			b_sp = false;
		}
	}
	//draws a circle and the point index at each point, if the current point is greater in x and y or less in x and y use the point in the line
	for (int i = 0; i < demonPoints.size(); i += 2) {
		line.curveTo(demonPoints[i]);
		//legLine.lineTo((int)ofRandom(0, demonPoints.size*());
	}

	//Eye at the centre, being silly really but I just wanted to see the diff between getCentroid2d() and the centre position but then I kind of liked how it looked
	eyeDot.x = line.getCentroid2D().x;
	eyeDot.y = line.getCentroid2D().y;
	//int xOffset = centre.x - eyeDot.x;
	ofFill();
	ofDrawCircle(centre.x, centre.y, 10);
	ofNoFill();
	ofDrawCircle(eyeDot.x, eyeDot.y, 20);

	//draw the line
	ofSetLineWidth(7); 
	line.draw();
	ofPopMatrix();
}
void ofApp::showImg() {
	ofSetColor(255, 255, 255);
	img.draw(0, 0);
	// Where to put this so it doesn't color the image? but also so it isn't causing epileptic fits by calling it from draw or update
	//ofSetColor(demonColorPalette[(int)ofRandom(0, 5)]);
}

void ofApp::keyPressed(int key) {
	if (key == 'b') {
		line.clear();
		demonPoints.clear();
		// demon is drawn with random color from demon color palette - except it isn't!!!
		ofSetColor(demonColorPalette[(int)ofRandom(0, 5)]);
		b_sp = true;
		


	}
}

