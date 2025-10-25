//classe qui s'occupe des formes
#pragma once
#include "ShapeManager3D.h"
#include "ofMain.h"
#include "shape.h"

class ShapeManager {
public:
	void drawShape(const std::string & type, const ofPoint & start, const ofPoint & end);
	void draw();
	void deleteCurrentShapeToDraw();

	Shape getCurrentShape() const {
		Shape s = currentShapeToDraw;
		s.color = fillColor;
		return s;
	}

	void convertTo3d(Shape & shape);
	void setDrawingParameters(float lineW, ofColor stroke, ofColor fill);
	void drawShapePrimitive(const Shape & s);

private:
	Shape currentShapeToDraw = {
		"x", { 0, 0 }, { 0, 0 }
	};
	ShapeManager3D shapeManager3D;

	float lineWidth = 2.0f;
	ofColor strokeColor = ofColor::black;
	ofColor fillColor = ofColor::white;
};
