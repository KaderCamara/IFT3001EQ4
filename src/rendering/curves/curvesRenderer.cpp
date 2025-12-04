// CurvesRenderer.cpp
// Implémentation du renderer de courbes MVC PUR (VIEW uniquement)
#include "CurvesRenderer.h"

CurvesRenderer::CurvesRenderer() {
	// Initialisation par défaut via les valeurs membres
}

void CurvesRenderer::render(
	const std::vector<glm::vec2> & controlPoints,
	const std::vector<BezierCurve> & curves) const {
	// Dessiner dans l'ordre : points de contrôle puis courbes
	// (pour que les courbes soient au-dessus des segments de contrôle)

	// 1. Dessiner les points de contrôle et leurs segments
	renderControlPointsOnly(controlPoints);

	// 2. Dessiner les courbes de Bézier
	renderCurvesOnly(curves);
}

void CurvesRenderer::renderControlPointsOnly(const std::vector<glm::vec2> & controlPoints) const {
	// Dessiner via le renderer spécialisé
	controlPointsRenderer.render(
		controlPoints,
		controlPointsColor,
		controlPointRadius,
		lineWidth,
		showPointNumbers);
}

void CurvesRenderer::renderCurvesOnly(const std::vector<BezierCurve> & curves) const {
	// Dessiner via le renderer spécialisé
	bezierRenderer.renderMultiple(
		curves,
		curvesColor,
		lineWidth);
}
