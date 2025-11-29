# pragma once

#include "ofMain.h"
#include <vector>
#include "glm/glm.hpp"


class ControlPointsManager {
public:
	ControlPointsManager() = default;
	void drawPointsForCurves() const;
	void addControlPoint(int x, int y);
	std::vector<glm::vec2> getControlPoints() const;
	void undoLastPoint();
	void clearPoints();

private:
	std::vector<glm::vec2> controlPoints;
	bool hasPointPreview = false;
	glm::vec2 pointPreview;
	glm::vec2 startPoint;

};
