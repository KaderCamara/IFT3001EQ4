// ControlPointsRenderer.h
// Renderer spécialisé pour les points de contrôle des courbes
#pragma once

#include "glm/glm.hpp"
#include "ofMain.h"
#include <vector>

/**
 * @class ControlPointsRenderer
 * @brief Renderer spécialisé pour afficher les points de contrôle (VIEW)
 * 
 * Responsabilités :
 * - Dessiner les points de contrôle
 * - Dessiner les segments entre les points
 * - Afficher les numéros des points
 * - Appliquer le style visuel
 */
class ControlPointsRenderer {
public:
	ControlPointsRenderer() = default;
	~ControlPointsRenderer() = default;

	/**
	 * @brief Dessine les points de contrôle et les segments qui les relient
	 * @param controlPoints Vector des points de contrôle
	 * @param pointColor Couleur des points et segments (défaut: rouge)
	 * @param pointRadius Rayon des cercles de points (défaut: 4)
	 * @param lineWidth Épaisseur des segments (défaut: 2)
	 * @param showNumbers Afficher les numéros de points (défaut: true)
	 */
	void render(const std::vector<glm::vec2> & controlPoints,
		const ofColor & pointColor = ofColor::red,
		float pointRadius = 4.0f,
		float lineWidth = 2.0f,
		bool showNumbers = true) const;

private:
	/**
	 * @brief Dessine les segments entre points consécutifs
	 */
	void drawSegments(const std::vector<glm::vec2> & points,
		const ofColor & color,
		float lineWidth) const;

	/**
	 * @brief Dessine les points de contrôle avec leurs numéros
	 */
	void drawPoints(const std::vector<glm::vec2> & points,
		const ofColor & color,
		float radius,
		bool showNumbers) const;
};
