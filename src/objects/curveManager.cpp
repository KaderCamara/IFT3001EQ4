#include "CurveManager.h"

/**
 * @file curveManager.cpp
 * @brief Implementation of CurveManager: manage and render multiple Bezier curves.
 */

void CurveManager::addBezierCurve(const std::vector<glm::vec2> & controlPoints) {
	// Construct a BezierCurve from the provided control points and store it.
	BezierCurve curve(controlPoints);
	bezierCurves.push_back(curve);
}

void CurveManager::clear() {
	// Remove all stored curves.
	bezierCurves.clear();
}

void CurveManager::draw() const {
	// Draw each managed Bezier curve.
	for (const auto & curve : bezierCurves) {
		curve.draw();
	}
}
