#include "ofApp.h"

/*
Acknowledgements:
Archie is blob master.
*/

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundAuto(false);
	ofBackground(0);

	//Generate a random number between 2 and 5 of demons and add to my vector of Demons.
	numberOfDemons = ofRandom(2, 10);
	demonGroup.resize(numberOfDemons);
	for (int j = 0; j < numberOfDemons; j++) {
		Demon demon;
		demonGroup.push_back(demon);
	};
	
	//add images to vector within an ofxThreadedImageLoader object 
	numberOfImgs = 4;
	images.resize(numberOfImgs);
	for (int i = 0; i < numberOfImgs; i++) {
		loader.loadFromDisk(images[i], "Image" + ofToString(i) + ".jpg");
	};

	//random selection of images
	randomPicker = ofRandom(0, numberOfImgs);
	imgW = images[randomPicker].getWidth();
	imgH = images[randomPicker].getHeight();
	ofSetWindowShape(imgW, imgH);


}
//--------------------------------------------------------------
void ofApp::update() {
	/*//Make edges move randomly
	for (auto &vert : line.getVertices()) {
		vert.x += ofRandom(-1, 1);
		vert.y += ofRandom(-1, 1);
	}
	//	line = line.getSmoothed(2);
	*/

	//clear the blobpoint vector
	for (int i = 0; i < demonGroup.size(); i++) {
		demonGroup[i].blobpoints.clear();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {	
	ofSetColor(255, 255, 255);
	images[randomPicker].draw(0, 0);

	for (int i = 0; i < demonGroup.size(); i++) {
		ofSetColor(demonGroup[i].demonColorPalette[demonGroup[i].currentDemonColor]);
		demonGroup[i].drawDemons();
	}
}


void ofApp::keyPressed(int key) {
	if (key == 'b') {
		for (int i = 0; i < demonGroup.size(); i++) {
			demonGroup.clear();
			demonGroup[i].line.clear();
			demonGroup[i].demonPoints.clear();
			demonGroup[i].b_sp = true;

			//Provides a random image at keypressed
			randomPicker = ofRandom(0, numberOfImgs);
			imgW = images[randomPicker].getWidth();
			imgH = images[randomPicker].getHeight();
			ofSetWindowShape(imgW, imgH);

			//generate a new set of demons
			numberOfDemons = ofRandom(2, 10);
			demonGroup.resize(numberOfDemons);
			for (int j = 0; j < numberOfDemons; j++) {
				Demon demon;
				demonGroup.push_back(demon);
			};

			//set demon color to a random color within the demon color palette
			demonGroup[i].currentDemonColor = ofRandom(0, demonGroup[i].demonColorPalette.size());

			//spawn demons in random position on screen - ignore the - line.getArea() , i was trying to get it to stay within picture, 
			//but then felt it was interesting when it sometimes spawned some of the demon body out of view, will delete later 
			demonGroup[i].blobPositionX = ofRandom(0, (imgW - demonGroup[i].line.getArea()));
			demonGroup[i].blobPositionY = ofRandom(0, (imgH - demonGroup[i].line.getArea()));


			//img.grabScreen(0, 0, imgW, imgH);
			//img.save("myPic.jpg", OF_IMAGE_QUALITY_BEST);
		}
	}
}

void Demon::drawDemons(){
	// A vector of all the points within a given distance of the centre point is stored then some points are picked at random. 
	//These points are then used to draw the shapes.
	ofPushMatrix();
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
	//draws a circle and the point index at each point, if the current point is greater in x and y or less in x and y use the point in the line
	for (int i = 0; i < demonPoints.size(); i += 2) {
		line.curveTo(demonPoints[i]);

		//brush.updatePosition(demonPoints[i], 5);
		//legLine.lineTo((int)ofRandom(0, demonPoints.size*());
	}

	//EYES at the centre, silly really but I just wanted to see the diff between getCentroid2d() and the centre position but then I kind of liked how it looked
	eyeDot.x = line.getCentroid2D().x;
	eyeDot.y = line.getCentroid2D().y;
	//int xOffset = centre.x - eyeDot.x;
	//ofNoFill();
	ofSetColor(255, 255, 255);
	ofDrawCircle(eyeDot.x, eyeDot.y, 20);
	ofFill();
	ofSetColor(0);
	ofDrawCircle(centre.x, centre.y, 10);
	//

	ofSetColor(demonColorPalette[currentDemonColor]);
	//draw the linedemon.
	ofSetLineWidth(7);
	line.draw();

	ofPopMatrix();

}

Demon::Demon()
{
	//initialise centre point of the Demon, range and boolean so a demon is drawn straight away
	centre.x = 0;
	centre.y = 0;
	b_sp = true;
	range = 75;
	change = 25;


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

Demon::~Demon()
{
}
