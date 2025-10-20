#pragma once
#include "ofMain.h"

class ShapeManager {
public:
	void drawShape(const std::string & type, const ofPoint & start, const ofPoint & end);
	void draw();
	void deleteCurrentShapeToDraw();

	struct Shape {
		std::string type;
		ofPoint start, end;
	};

	Shape getCurrentShape() const { return currentShapeToDraw; }

private:
	Shape currentShapeToDraw = {
		"x", { 0, 0 }, { 0, 0 }
	};

};
	
