//pour la structure des formes, vu notre architecture, ca evite les boucle entre les include
#pragma once
#include "ofMain.h"

struct Shape {
	std::string type;
	ofPoint start, end;
	ofMesh mesh3D;
	bool is3D = false;
	//JORDAN: transformation attributes
	ofVec2f translation = { 0, 0 };
	float rotation = 0.0f;
	ofColor color = ofColor::white;
	float scale = 1.0f;

};
