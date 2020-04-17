#include "ofApp.h"

/*
The system is working, however, the first round is triggered 5 seconds after its been succesfully built&run.

Acknowledgements:
I must give thanks Archie Hollyfield for his tenacity and helpfulness as he several times came to my aid when I couldn't get the system to work!
Also, a thanks to Dr. Daniel Buzzo for facilitating and putting together such interesting and rewarding workshops, allowing us to explore
different types of generative systems through our own personal creative practice - and also thanks for help with the code!
*/

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundAuto(false);
	ofBackground(0);

	//Timer for triggering new generation of image
	time = ofGetElapsedTimeMillis();

	//Generate a random number between 2 and 5 of demons and add to my vector of Demons.
	numberOfDemons = ofRandom(2, 5);
	for (int j = 0; j < numberOfDemons; j++) {
		Demon demon;
		demonGroup.push_back(demon);
	};
	//cout << demonGroup.size() << endl; 

	//add images to vector within an ofxThreadedImageLoader object 
	numberOfImgs = 4;
	images.resize(numberOfImgs);
	for (int i = 0; i < numberOfImgs; i++) {
		loader.loadFromDisk(images[i], "Image" + ofToString(i) + ".jpg");
	};

	//random selection of images and resize window from current image
	randomPicker = ofRandom(0, numberOfImgs);
	imgW = images[randomPicker].getWidth();
	imgH = images[randomPicker].getHeight();
	ofSetWindowShape(imgW, imgH);


}
//--------------------------------------------------------------
void ofApp::update() {
	//clear the blobpoint vector
	for (int i = 0; i < demonGroup.size(); i++) {
		demonGroup[i].blobpoints.clear();
	}

	//Every 5 seconds, generate a new image with daemons
	if (ofGetElapsedTimeMillis() > time + 5000) {
		//clear out the previous image and set bool to true so it generates a new
		for (int i = 0; i < demonGroup.size(); i++) {
			demonGroup[i].line.clear();
			demonGroup[i].demonPoints.clear();
			demonGroup[i].b_sp = true;
		}
		demonGroup.clear();

		//Generates image anew
		randomPicker = ofRandom(0, numberOfImgs);
		imgW = images[randomPicker].getWidth();
		imgH = images[randomPicker].getHeight();
		ofSetWindowShape(imgW, imgH);

		//generate a new set of demons
		numberOfDemons = ofRandom(2, 5);
		for (int j = 0; j < numberOfDemons; j++) {
			Demon demon;
			demonGroup.push_back(demon);
		};
		for (int i = 0; i < demonGroup.size(); i++) {
			//set demon color to a random color within the demon color palette
			demonGroup[i].currentDemonColor = ofRandom(0, demonGroup[i].demonColorPalette.size());

			//spawn demons in random position on screen between imgH and imgW 
			//I initially had intended for them to only spawn within the screen width and length with no body outside edges
			//but then I found it had a positive effect on the experience, seeing them peeping in from the edges 
			demonGroup[i].blobPositionX = ofRandom(0, imgW);
			demonGroup[i].blobPositionY = ofRandom(0, imgH);


		}
		time = ofGetElapsedTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//sets color to white so it retains its normal colours and not the colours from the Pedersen color palette and then draws the image to screen
	ofSetColor(255, 255, 255);
	images[randomPicker].draw(0, 0);
	//cout << demonGroup.size() << endl;
	//goes through the vector of Demon objects and draws them with a random color from the Pedersen color palette
	for (int i = 0; i < demonGroup.size(); i++) {
		ofSetColor(demonGroup[i].demonColorPalette[demonGroup[i].currentDemonColor]);
		demonGroup[i].drawDemons();
	}
}


void ofApp::keyPressed(int key) {
	/* // Was going to implement a save function, but then chose not to, as I just wanted to have continuous flow of transitory images 
		//As I feel there is a quality in not being able to save them, the transitory quality of "gone and never will be again"
	if (key == 's') {

		img.grabScreen(0, 0, imgW, imgH);
		img.save("myPic.jpg", OF_IMAGE_QUALITY_BEST);
		
	}
	*/
}

void Demon::drawDemons() {
	// A vector of all the points within a given distance of the centre point is stored then some points are picked at random. 
	//These points are then used to draw the shapes.

	ofPushMatrix();
	//spawn demon on random blobPositions
	ofTranslate(blobPositionX, blobPositionY);
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
	//draws a  point index at each point, if the current point is greater in x and y or less in x and y use the point in the line
	for (int i = 0; i < demonPoints.size(); i += 2) {
		line.curveTo(demonPoints[i]);
	
	}

	// I  wanted to see the difference between getCentroid2d() and the centre position and with that came the effect of the eyeballs looking in different directions,
	// unintentional but I liked it and kept it
	eyeDot.x = line.getCentroid2D().x;
	eyeDot.y = line.getCentroid2D().y;
	ofSetColor(255, 255, 255);
	ofDrawCircle(eyeDot.x, eyeDot.y, 20);
	ofFill();
	ofSetColor(0);
	ofDrawCircle(centre.x, centre.y, 10);
	ofSetColor(demonColorPalette[currentDemonColor]);
	
	//draw the linedemon.
	ofSetLineWidth(15);
	line.draw();

	ofPopMatrix();

}

Demon::Demon()
{
	//initialise centre point of the Demon, range and boolean so a demon is drawn straight away
	centre.x = 0;
	centre.y = 0;
	b_sp = true;
	//size of demon
	range = 75;
	change = 25;
	currentDemonColor = 0;

	//Adding ofColor objects (colors extracted from Pedersen's Modifikationer) to demon color palette	
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

Demon::~Demon()
{
}
