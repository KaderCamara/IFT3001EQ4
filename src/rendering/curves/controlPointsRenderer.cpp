// ControlPointsRenderer.cpp
// Implémentation du renderer pour points de contrôle
#include "ControlPointsRenderer.h"

void ControlPointsRenderer::render(const std::vector<glm::vec2> & controlPoints,
	const ofColor & pointColor,
	float pointRadius,
	float lineWidth,
	bool showNumbers) const {
	// Ne rien dessiner si pas de points
	if (controlPoints.empty()) {
		return;
	}

	// Dessiner les segments entre points
	drawSegments(controlPoints, pointColor, lineWidth);

	// Dessiner les points et leurs numéros
	drawPoints(controlPoints, pointColor, pointRadius, showNumbers);
}

void ControlPointsRenderer::drawSegments(const std::vector<glm::vec2> & points,
	const ofColor & color,
	float lineWidth) const {
	ofPushStyle();
	ofSetColor(color);
	ofSetLineWidth(lineWidth);

	// Dessiner une ligne entre chaque paire de points consécutifs
	for (size_t i = 0; i + 1 < points.size(); ++i) {
		ofDrawLine(points[i], points[i + 1]);
	}

	ofPopStyle();
}

void ControlPointsRenderer::drawPoints(const std::vector<glm::vec2> & points,
	const ofColor & color,
	float radius,
	bool showNumbers) const {
	ofPushStyle();
	ofSetColor(color);

	for (size_t i = 0; i < points.size(); ++i) {
		const auto & p = points[i];

		// Dessiner un cercle pour représenter le point
		ofDrawCircle(p, radius);

		// Dessiner le numéro du point si demandé
		if (showNumbers) {
			ofDrawBitmapStringHighlight(
				ofToString(i + 1), // Numérotation à partir de 1
				p.x + 6, // Offset à droite
				p.y - 6 // Offset en haut
			);
		}
	}

	ofPopStyle();
}
