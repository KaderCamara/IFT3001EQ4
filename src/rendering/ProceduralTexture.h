// src/rendering/ProceduralTexture.h
#pragma once
#include "ofMain.h"

inline ofTexture generateSimpleProceduralTexture(int width, int height) {
	ofPixels pixels;
	pixels.allocate(width, height, OF_PIXELS_RGB);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			bool isCyan = ((x / 16) + (y / 16)) % 2 == 0;
			ofColor color = isCyan ? ofColor(0, 255, 255) : ofColor(255, 255, 0);
			pixels.setColor(x, y, color);
		}
	}

	ofTexture tex;
	tex.loadData(pixels);

	ofLogNotice("ProceduralTexture") << " Generated BRIGHT CHECKERBOARD texture: "
									 << tex.getWidth() << "x" << tex.getHeight();

	return tex;
}
