#pragma once

#include "ofMain.h"
#include <vector>

class BezierCurve {
public:
	BezierCurve() = default;
	explicit BezierCurve(const std::vector<glm::vec2> & controlPts);

	void setControlPoints(const std::vector<glm::vec2> & controlPts);
	const std::vector<glm::vec2> & getControlPoints() const { return controlPoints; }

	// recalculer les points de la courbe (samples)
	void recompute(int segments = 100);

	// dessiner la courbe
	void draw() const;

private:
	std::vector<glm::vec2> controlPoints;
	std::vector<glm::vec2> curvePoints;
};
