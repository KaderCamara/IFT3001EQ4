#include "BezierCurve.h"

/**
 * @file BezierCurve.cpp
 * @brief Implementation of BezierCurve: sampling and drawing a Bezier curve.
 */

BezierCurve::BezierCurve(const std::vector<glm::vec2> & controlPts) {
	// Initialize control points and compute the curve samples
	setControlPoints(controlPts);
}

void BezierCurve::setControlPoints(const std::vector<glm::vec2> & controlPts) {
	// Replace control points and recompute sampled curve points
	controlPoints = controlPts;
	recompute();
}

void BezierCurve::recompute(int segments) {
	// Clear previous samples
	curvePoints.clear();

	// Need at least two points to form a curve
	if (controlPoints.size() < 2) {
		return;
	}

	// De Casteljau algorithm for evaluating a Bezier curve at parameter t
	auto deCasteljau = [this](float t) {
		// Work on a temporary copy of control points
		std::vector<glm::vec2> tmp = controlPoints;
		size_t n = tmp.size();

		// Iteratively interpolate between points
		for (size_t k = 1; k < n; ++k) {
			for (size_t i = 0; i < n - k; ++i) {
				// Linear interpolation between tmp[i] and tmp[i+1]
				tmp[i] = (1.0f - t) * tmp[i] + t * tmp[i + 1];
			}
		}
		// Resulting point at parameter t
		return tmp[0];
	};

	// Sample the curve at regular intervals in [0,1]
	for (int i = 0; i <= segments; ++i) {
		float t = static_cast<float>(i) / segments;
		curvePoints.push_back(deCasteljau(t));
	}
}

void BezierCurve::draw() const {
	// Need at least two sampled points to draw a segment
	if (curvePoints.size() < 2) {
		return;
	}

	// Draw the sampled polyline representing the curve
	ofPushStyle();
	ofSetColor(ofColor::blue); // curve color
	ofSetLineWidth(2);
	for (size_t i = 0; i + 1 < curvePoints.size(); ++i) {
		ofDrawLine(curvePoints[i], curvePoints[i + 1]);
	}
	ofPopStyle();
}
