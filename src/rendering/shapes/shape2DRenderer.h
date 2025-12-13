// Shape2DRenderer.h
// Renderer sp�cialis� pour les formes 2D (VIEW)

#pragma once

#include "../../objects/shape.h"
#include "ofMain.h"

/**
 * @class Shape2DRenderer
 * @brief Responsable du rendu des formes 2D (VIEW pure)
 *
 * - Dessine les formes 2D pr�sentes dans la sc�ne
 * - Dessine la forme temporaire (preview) pendant le dessin
 * - G�re le style (s�lection, contour, etc.)
 */
class Shape2DRenderer {
public:
	Shape2DRenderer() = default;
	~Shape2DRenderer() = default;

	/**
     * @brief Dessine une forme 2D de la sc�ne
     * @param s Shape � dessiner
     * @param isSelected true si la forme est s�lectionn�e
     * @param isHovered true si la forme est survol�e
     * @param lineWidth �paisseur de ligne courante
     */
	void drawShape2D(const Shape & s, bool isSelected, bool isHovered, float lineWidth) const;

	/**
	 * @brief Dessine la forme de preview en utilisant des paramètres visuels fournis
	 * @param s Shape à dessiner
	 * @param strokeColor couleur du contour à utiliser pour le preview
	 * @param fillColor couleur de remplissage à utiliser pour le preview
	 * @param lineWidth épaisseur de ligne à utiliser pour le preview
	 * @param isHovered true si la preview doit être rendue comme survolée (optionnel)
	 */
	void drawPreviewShape2D(const Shape & s, const ofColor & strokeColor, const ofColor & fillColor, float lineWidth, bool isHovered = false) const;
};
