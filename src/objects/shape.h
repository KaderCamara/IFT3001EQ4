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
	float scale = 1.0f;
};
