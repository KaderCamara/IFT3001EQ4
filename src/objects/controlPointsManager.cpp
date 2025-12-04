#include "controlPointsManager.h"

/**
 * @file controlPointsManager.cpp
 * @brief Implementation of ControlPointsManager: management of control points.
 * 
 * REFACTORISATION MVC :
 * - SUPPRIMÉ : drawPointsForCurves() (maintenant dans ControlPointsRenderer)
 * - CONSERVÉ : Toute la logique de gestion des données (MODEL)
 */

// ========== SUPPRIMÉ : drawPointsForCurves() const ==========
// AVANT :
// void ControlPointsManager::drawPointsForCurves() const {
//     ofPushStyle();
//     ofSetColor(ofColor::red);
//     ofSetLineWidth(2);
//     for (size_t i = 0; i + 1 < controlPoints.size(); ++i) {
//         ofDrawLine(controlPoints[i], controlPoints[i + 1]);
//     }
//     ofPopStyle();
//
//     ofPushStyle();
//     ofSetColor(ofColor::red);
//     for (size_t i = 0; i < controlPoints.size(); ++i) {
//         const auto & p = controlPoints[i];
//         ofDrawCircle(p, 4);
//         ofDrawBitmapStringHighlight(ofToString(i + 1), p.x + 6, p.y - 6);
//     }
//     ofPopStyle();
// }
//
// APRÈS : Le rendu est délégué à ControlPointsRenderer::render()
// ==============================================================

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
