#include "shapeManager.h"

void ShapeManager::draw() {
	const auto & s = currentShapeToDraw;
	if (s.type == "point") {
		ofDrawCircle(s.start, 2);
	} else if (s.type == "line") {
		ofDrawLine(s.start, s.end);
	} else if (s.type == "triangle") {
		ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
	} else if (s.type == "square") {
		float side = std::abs(s.end.x - s.start.x);
		ofDrawRectangle(s.start.x, s.start.y, side, side);
	} else if (s.type == "rectangle") {
		ofDrawRectangle(s.start.x, s.start.y,
			s.end.x - s.start.x, s.end.y - s.start.y);
	} else if (s.type == "circle") {
		float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y);
		ofDrawCircle(s.start, radius);
	}
}

void ShapeManager::drawShape(const std::string & type, const ofPoint & start, const ofPoint & end) {
	currentShapeToDraw.type = type;
	currentShapeToDraw.start = start;
	currentShapeToDraw.end = end;
}

void ShapeManager::deleteCurrentShapeToDraw() {
	currentShapeToDraw = {
		"x", { 0, 0 }, { 0, 0 }
	};
}

void ShapeManager::convertTo3d(Shape& shape, float depth) {
	shape.is3D = true;
	shape.mesh3D = shapeManager3D.to3DDraw(shape, depth);
}


