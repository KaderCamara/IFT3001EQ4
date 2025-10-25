#include "shapeManager.h"
float lineWidth = 2.0f;
ofColor strokeColor = ofColor::black;
ofColor fillColor = ofColor::white;

void ShapeManager::setDrawingParameters(float lineW, ofColor stroke, ofColor fill) {
	lineWidth = lineW;
	strokeColor = stroke;
	fillColor = fill;
}

void ShapeManager::draw() {
	const auto & s = currentShapeToDraw;
	if (s.type == "x") return;

	if (s.type == "point") {
		ofFill();
		ofSetColor(fillColor);
		ofSetLineWidth(lineWidth);
		ofDrawCircle(s.start, 2);
		ofNoFill();
		ofSetColor(strokeColor);
		ofSetLineWidth(lineWidth);
		ofFill();
	} else if (s.type == "line") {
		ofFill();
		ofSetColor(fillColor);
		ofSetLineWidth(lineWidth);
		ofDrawLine(s.start, s.end);
		ofNoFill();
		ofSetColor(strokeColor);
		ofSetLineWidth(lineWidth);
		ofFill();
	} else if (s.type == "triangle") {
		ofFill();
		ofSetColor(fillColor);
		ofSetLineWidth(lineWidth);
		ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
		ofNoFill();
		ofSetColor(strokeColor);
		ofSetLineWidth(lineWidth);
		ofFill();
	} else if (s.type == "square") {
		ofFill();
		ofSetColor(fillColor);
		ofSetLineWidth(lineWidth);
		float side = std::abs(s.end.x - s.start.x);
		ofDrawRectangle(s.start.x, s.start.y, side, side);
		ofNoFill();
		ofSetColor(strokeColor);
		ofSetLineWidth(lineWidth);
		ofFill();
	} else if (s.type == "rectangle") {
		ofFill();
		ofSetColor(fillColor);
		ofSetLineWidth(lineWidth);
		ofDrawRectangle(s.start.x, s.start.y,
			s.end.x - s.start.x, s.end.y - s.start.y);
		ofNoFill();
		ofSetColor(strokeColor);
		ofSetLineWidth(lineWidth);
		ofFill();
	} else if (s.type == "circle") {
		ofFill();
		ofSetColor(fillColor);
		ofSetLineWidth(lineWidth);
		float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y);
		ofDrawCircle(s.start, radius);
		ofNoFill();
		ofSetColor(strokeColor);
		ofSetLineWidth(lineWidth);
		ofFill();
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

void ShapeManager::convertTo3d(Shape& shape) {
	shape.is3D = true;
	shape.mesh3D = shapeManager3D.to3DDraw(shape);
}

void ShapeManager::drawShapePrimitive(const Shape & s) {
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
		ofDrawRectangle(
			s.start.x, s.start.y,
			s.end.x - s.start.x,
			s.end.y - s.start.y);
	} else if (s.type == "circle") {
		float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y);
		ofDrawCircle(s.start, radius);
	}
}


