// CurvesRenderer.cpp
// Implémentation de l'orchestrateur de rendu des courbes
#include "CurvesRenderer.h"

CurvesRenderer::CurvesRenderer() {
	// Initialisation par défaut via les valeurs membres
}

void CurvesRenderer::render(const ControlPointsManager & controlPointsManager,
	const CurveManager & curveManager) const {
	// Dessiner dans l'ordre : points de contrôle puis courbes
	// (pour que les courbes soient au-dessus des segments de contrôle)

	// 1. Dessiner les points de contrôle et leurs segments
	renderControlPointsOnly(controlPointsManager);

	// 2. Dessiner les courbes de Bézier
	renderCurvesOnly(curveManager);
}

void CurvesRenderer::renderControlPointsOnly(const ControlPointsManager & controlPointsManager) const {
	// Récupérer les points de contrôle
	const std::vector<glm::vec2> & controlPoints = controlPointsManager.getControlPoints();

	// Dessiner via le renderer spécialisé
	controlPointsRenderer.render(
		controlPoints,
		controlPointsColor,
		controlPointRadius,
		lineWidth,
		showPointNumbers);
}

void CurvesRenderer::renderCurvesOnly(const CurveManager & curveManager) const {
	// Récupérer les courbes
	const std::vector<BezierCurve> & curves = curveManager.getCurves();

	// Dessiner via le renderer spécialisé
	bezierRenderer.renderMultiple(
		curves,
		curvesColor,
		lineWidth);
}
