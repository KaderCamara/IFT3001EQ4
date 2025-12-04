// imageRenderer.h
// Renderer responsable UNIQUEMENT du rendu des images (VIEW)
#pragma once

#include "ofMain.h"

/**
 * @class ImageRenderer
 * @brief Responsable du rendu visuel des images (VIEW - MVC)
 * 
 * Responsabilités :
 * - Dessiner les images à l'écran
 * - Appliquer les transformations visuelles (position, échelle)
 * - AUCUNE logique métier
 * - AUCUNE gestion de chargement
 */
class ImageRenderer {
public:
	ImageRenderer() = default;
	~ImageRenderer() = default;

	/**
	 * @brief Dessine une image à la position et taille spécifiées
	 * @param image Image OpenFrameworks à dessiner
	 * @param x Position X
	 * @param y Position Y
	 * @param width Largeur (ou -1 pour taille originale)
	 * @param height Hauteur (ou -1 pour taille originale)
	 */
	void render(const ofImage & image, float x, float y, float width = -1, float height = -1) const;

	/**
	 * @brief Dessine une image avec un facteur d'échelle
	 * @param image Image OpenFrameworks à dessiner
	 * @param x Position X
	 * @param y Position Y
	 * @param scale Facteur d'échelle (1.0 = taille originale)
	 */
	void renderScaled(const ofImage & image, float x, float y, float scale) const;

	/**
	 * @brief Dessine une image centrée dans un rectangle
	 * @param image Image OpenFrameworks à dessiner
	 * @param bounds Rectangle de destination
	 * @param maintainAspectRatio Conserver les proportions
	 */
	void renderInBounds(const ofImage & image, const ofRectangle & bounds, bool maintainAspectRatio = true) const;

private:
	/**
	 * @brief Calcule les dimensions pour conserver l'aspect ratio
	 */
	void calculateAspectFitDimensions(float srcWidth, float srcHeight,
		float dstWidth, float dstHeight,
		float & outWidth, float & outHeight) const;
};
