// BezierCurveRenderer.cpp
// Implémentation du renderer pour courbes de Bézier
#include "BezierCurveRenderer.h"

void BezierCurveRenderer::render(const BezierCurve & curve,
	const ofColor & color,
	float lineWidth) const {
	// Récupérer les points échantillonnés de la courbe
	const std::vector<glm::vec2> & curvePoints = curve.getCurvePoints();

	// Besoin d'au moins 2 points pour dessiner
	if (curvePoints.size() < 2) {
		return;
	}

	// Dessiner la polyline
	drawPolyline(curvePoints, color, lineWidth);
}

void BezierCurveRenderer::renderMultiple(const std::vector<BezierCurve> & curves,
	const ofColor & color,
	float lineWidth) const {
	// Dessiner chaque courbe
	for (const auto & curve : curves) {
		render(curve, color, lineWidth);
	}
}

void BezierCurveRenderer::drawPolyline(const std::vector<glm::vec2> & points,
	const ofColor & color,
	float lineWidth) const {
	ofPushStyle();
	ofSetColor(color);
	ofSetLineWidth(lineWidth);

	// Dessiner les segments entre les points consécutifs
	for (size_t i = 0; i + 1 < points.size(); ++i) {
		ofDrawLine(points[i], points[i + 1]);
	}

	ofPopStyle();
}
