// Shape2DRenderer.cpp
#include "Shape2DRenderer.h"

void Shape2DRenderer::drawShape2D(const Shape & s, bool isSelected, float lineWidth) const {
	ofPushStyle();

	// Style selon sélection
	if (isSelected) {
		ofNoFill();
		ofSetColor(ofColor::yellow);
		ofSetLineWidth(3);
	} else {
		ofFill();
		ofSetColor(s.color);
		ofSetLineWidth(lineWidth);
	}

	// Dessiner selon le type
	if (s.type == "point") {
		ofDrawCircle(s.start, 3 * s.scale);
	} else if (s.type == "line") {
		ofDrawLine(s.start, s.end);
	} else if (s.type == "triangle") {
		ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
	} else if (s.type == "square") {
		float side = std::abs(s.end.x - s.start.x) * s.scale;
		ofDrawRectangle(s.start.x, s.start.y, side, side);
	} else if (s.type == "rectangle") {
		float w = (s.end.x - s.start.x) * s.scale;
		float h = (s.end.y - s.start.y) * s.scale;
		ofDrawRectangle(s.start.x, s.start.y, w, h);
	} else if (s.type == "circle") {
		float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y) * s.scale;
		ofDrawCircle(s.start, radius);
	} else if (s.mesh3D.getNumVertices() > 0) {
		// Cas particulier: mesh 3D affiché en wireframe en 2D
		s.mesh3D.drawWireframe();
	}

	// Contour de sélection
	if (isSelected && s.type != "line" && s.type != "point") {
		ofNoFill();
		ofSetColor(ofColor::yellow);
		ofSetLineWidth(2);

		if (s.type == "triangle") {
			ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
		} else if (s.type == "square") {
			float side = std::abs(s.end.x - s.start.x) * s.scale;
			ofDrawRectangle(s.start.x, s.start.y, side, side);
		} else if (s.type == "rectangle") {
			float w = (s.end.x - s.start.x) * s.scale;
			float h = (s.end.y - s.start.y) * s.scale;
			ofDrawRectangle(s.start.x, s.start.y, w, h);
		} else if (s.type == "circle") {
			float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y) * s.scale;
			ofDrawCircle(s.start, radius);
		}
	}

	ofPopStyle();
}

