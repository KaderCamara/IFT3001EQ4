#pragma once

#include "BezierCurve.h"
#include <vector>

class CurveManager {
public:
	// Ajoute une nouvelle courbe de Bézier à partir de points de contrôle
	void addBezierCurve(const std::vector<glm::vec2> & controlPoints);

	// Effacer toutes les courbes
	void clear();

	// Dessiner toutes les courbes
	void draw() const;

	const std::vector<BezierCurve> & getCurves() const { return bezierCurves; }

private:
	std::vector<BezierCurve> bezierCurves;
};
