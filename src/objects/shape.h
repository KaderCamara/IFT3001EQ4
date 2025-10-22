#pragma once
#include "ofMain.h"

struct Shape {
	std::string type;
	ofPoint start, end;
	ofMesh mesh3D;
	bool is3D = false;
};
