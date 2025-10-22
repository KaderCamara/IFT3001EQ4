#pragma once
#include "ofMain.h"
#include "shape.h"
#include "ShapeManager3D.h"

class ShapeManager {
public:
	void drawShape(const std::string & type, const ofPoint & start, const ofPoint & end);
	void draw();
	void deleteCurrentShapeToDraw();

	Shape getCurrentShape() const { return currentShapeToDraw; }
	void convertTo3d(Shape & shape, float depth);

private:
	Shape currentShapeToDraw = {
		"x", { 0, 0 }, { 0, 0 }
	};
	ShapeManager3D shapeManager3D;

};
	
