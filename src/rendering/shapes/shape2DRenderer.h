// Shape2DRenderer.h
// Renderer spécialisé pour les formes 2D (VIEW)

#pragma once

#include "../../objects/shape.h"
#include "ofMain.h"

/**
 * @class Shape2DRenderer
 * @brief Responsable du rendu des formes 2D (VIEW pure)
 *
 * - Dessine les formes 2D présentes dans la scène
 * - Dessine la forme temporaire (preview) pendant le dessin
 * - Gère le style (sélection, contour, etc.)
 */
class Shape2DRenderer {
public:
	Shape2DRenderer() = default;
	~Shape2DRenderer() = default;

	/**
     * @brief Dessine une forme 2D de la scène
     * @param s Shape à dessiner
     * @param isSelected true si la forme est sélectionnée
     * @param lineWidth épaisseur de ligne courante
     */
	void drawShape2D(const Shape & s, bool isSelected, float lineWidth) const;
};
