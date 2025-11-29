#include "controlPointsManager.h"

/**
 * @file controlPointsManager.cpp
 * @brief Implementation of ControlPointsManager: drawing and management of control points.
 */

void ControlPointsManager::drawPointsForCurves() const {
	// Draw segments between consecutive control points
	ofPushStyle();
	ofSetColor(ofColor::red);
	ofSetLineWidth(2);
	for (size_t i = 0; i + 1 < controlPoints.size(); ++i) {
		// Draw a line between point i and i+1
		ofDrawLine(controlPoints[i], controlPoints[i + 1]);
	}
	ofPopStyle();

	// Draw each control point and its index
	ofPushStyle();
	ofSetColor(ofColor::red);
	for (size_t i = 0; i < controlPoints.size(); ++i) {
		const auto & p = controlPoints[i];

		// Draw a small circle to represent the control point
		ofDrawCircle(p, 4);

		// Draw the point number next to the point for easier identification
		ofDrawBitmapStringHighlight(ofToString(i + 1), p.x + 6, p.y - 6);
	}

	ofPopStyle();
}

void ControlPointsManager::addControlPoint(int x, int y) {
	// Add a new control point at the specified integer coordinates.
	// No validation is performed here; the caller is expected to ensure
	// the point is within the desired drawing bounds if necessary.
	controlPoints.push_back(glm::vec2(x, y));
}

std::vector<glm::vec2> ControlPointsManager::getControlPoints() const {
	// Return a copy of the internal control points vector.
	// Returning a copy preserves encapsulation of the internal storage.
	return controlPoints;
}

void ControlPointsManager::undoLastPoint() {
	// Remove the most recently added control point, if any exist.
	if (!controlPoints.empty()) {
		controlPoints.pop_back();
	}
}

void ControlPointsManager::clearPoints() {
	// Remove all stored control points
	controlPoints.clear();
}
