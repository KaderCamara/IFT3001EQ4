// ProceduralTexture.h
#pragma once
#include "ofMain.h"

/**
 * @brief Génère une texture procédurale simple de type bruit de Perlin
 * 
 * @param width  Largeur de la texture
 * @param height Hauteur de la texture
 * @return ofTexture Texture générée
 */
inline ofTexture generateSimpleProceduralTexture(int width = 128, int height = 128) {
	ofPixels pixels;
	pixels.allocate(width, height, OF_PIXELS_RGB);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Bruit 2D Perlin
			float n = ofNoise(x * 0.1f, y * 0.1f);

			// Couleur gris
			ofColor c(n * 255, n * 255, n * 255);
			pixels.setColor(x, y, c);
		}
	}

	ofTexture tex;
	tex.loadData(pixels);
	return tex;
}
