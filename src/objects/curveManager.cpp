#include "CurveManager.h"

void CurveManager::addBezierCurve(const std::vector<glm::vec2> & controlPoints) {
	BezierCurve curve(controlPoints);
	bezierCurves.push_back(curve);
}

void CurveManager::clear() {
	bezierCurves.clear();
}

void CurveManager::draw() const {
	for (const auto & curve : bezierCurves) {
		curve.draw();
	}
}
