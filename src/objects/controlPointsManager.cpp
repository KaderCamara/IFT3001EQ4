#include "controlPointsManager.h"

void ControlPointsManager::drawPointsForCurves() const {
	// Segments between control points
	ofPushStyle();
	ofSetColor(ofColor::red);
	ofSetLineWidth(2);
	for (size_t i = 0; i + 1 < controlPoints.size(); ++i) {
		ofDrawLine(controlPoints[i], controlPoints[i + 1]);
	}
	ofPopStyle();

	// points 
	ofPushStyle();
	ofSetColor(ofColor::red);
	for (size_t i = 0; i < controlPoints.size(); ++i) {
		const auto & p = controlPoints[i];

		// red circle
		ofDrawCircle(p, 4);

		// point number
		ofDrawBitmapStringHighlight(ofToString(i + 1), p.x + 6, p.y - 6);
	}

	ofPopStyle();
}

void ControlPointsManager::addControlPoint(int x, int y) {
	// We only add the point if it's inside the drawing area
	controlPoints.push_back(glm::vec2(x, y));
}

std::vector<glm::vec2> ControlPointsManager::getControlPoints() const {
	return controlPoints;
}

void ControlPointsManager::undoLastPoint() {
	if (!controlPoints.empty()) {
		controlPoints.pop_back();
	}
}

void ControlPointsManager::clearPoints() {
	controlPoints.clear();
}
