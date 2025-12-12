// BezierCurveRenderer.h
// Renderer spécialisé pour les courbes de Bézier
#pragma once

#include "../../objects/BezierCurve.h"
#include "ofMain.h"
#include <vector>

/**
 * @class BezierCurveRenderer
 * @brief Renderer spécialisé pour afficher les courbes de Bézier (VIEW)
 * 
 * Responsabilités :
 * - Dessiner une courbe de Bézier à partir de ses points échantillonnés
 * - Appliquer le style visuel (couleur, épaisseur)
 * - Aucune logique métier, uniquement du rendu
 */
class BezierCurveRenderer {
public:
	BezierCurveRenderer() = default;
	~BezierCurveRenderer() = default;

	/**
	 * @brief Dessine une courbe de Bézier
	 * @param curve La courbe à dessiner (contient les données)
	 * @param color Couleur de la courbe (défaut: bleu)
	 * @param lineWidth Épaisseur de la ligne (défaut: 2)
	 */
	void render(const BezierCurve & curve,
		const ofColor & color = ofColor::blue,
		float lineWidth = 2.0f) const;

	/**
	 * @brief Dessine plusieurs courbes de Bézier
	 * @param curves Vector de courbes à dessiner
	 * @param color Couleur des courbes (défaut: bleu)
	 * @param lineWidth Épaisseur de la ligne (défaut: 2)
	 */
	void renderMultiple(const std::vector<BezierCurve> & curves,
		const ofColor & color = ofColor::blue,
		float lineWidth = 2.0f) const;

private:
	/**
	 * @brief Dessine une polyline à partir de points échantillonnés
	 * @param points Points de la courbe échantillonnée
	 * @param color Couleur de la ligne
	 * @param lineWidth Épaisseur de la ligne
	 */
	void drawPolyline(const std::vector<glm::vec2> & points,
		const ofColor & color,
		float lineWidth) const;
};
