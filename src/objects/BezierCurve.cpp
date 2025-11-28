#include "BezierCurve.h"

BezierCurve::BezierCurve(const std::vector<glm::vec2> & controlPts) {
	setControlPoints(controlPts);
}

void BezierCurve::setControlPoints(const std::vector<glm::vec2> & controlPts) {
	controlPoints = controlPts;
	recompute();
}

void BezierCurve::recompute(int segments) {
	curvePoints.clear();

	if (controlPoints.size() < 2) {
		return;
	}

	// De Casteljau
	auto deCasteljau = [this](float t) {
		std::vector<glm::vec2> tmp = controlPoints;
		size_t n = tmp.size();

		for (size_t k = 1; k < n; ++k) {
			for (size_t i = 0; i < n - k; ++i) {
				tmp[i] = (1.0f - t) * tmp[i] + t * tmp[i + 1];
			}
		}
		return tmp[0];
	};

	for (int i = 0; i <= segments; ++i) {
		float t = static_cast<float>(i) / segments;
		curvePoints.push_back(deCasteljau(t));
	}
}

void BezierCurve::draw() const {
	if (curvePoints.size() < 2) {
		return;
	}

	ofPushStyle();
	ofSetColor(ofColor::blue); // couleur de la courbe
	ofSetLineWidth(2);
	for (size_t i = 0; i + 1 < curvePoints.size(); ++i) {
		ofDrawLine(curvePoints[i], curvePoints[i + 1]);
	}
	ofPopStyle();
}
