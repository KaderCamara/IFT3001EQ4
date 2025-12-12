#pragma once
#pragma once
#include "ofMain.h"

class ImageFilters {
public:
	// Apply grayscale filter
	static void applyGrayscale(ofImage & img) {
		if (!img.isAllocated()) return;

		ofPixels & pixels = img.getPixels();
		int w = img.getWidth();
		int h = img.getHeight();
		int channels = pixels.getNumChannels();

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				ofColor color = pixels.getColor(x, y);

				// Standard grayscale conversion (weighted average)
				float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;

				pixels.setColor(x, y, ofColor(gray, gray, gray, color.a));
			}
		}

		img.update();
		ofLogNotice("ImageFilters") << "Grayscale filter applied";
	}

	// Apply sepia filter
	static void applySepia(ofImage & img) {
		if (!img.isAllocated()) return;

		ofPixels & pixels = img.getPixels();
		int w = img.getWidth();
		int h = img.getHeight();

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				ofColor color = pixels.getColor(x, y);
				float r = color.r;
				float g = color.g;
				float b = color.b;

				// Sepia tone transformation
				float tr = 0.393f * r + 0.769f * g + 0.189f * b;
				float tg = 0.349f * r + 0.686f * g + 0.168f * b;
				float tb = 0.272f * r + 0.534f * g + 0.131f * b;

				pixels.setColor(x, y, ofColor(std::min(255.0f, tr), std::min(255.0f, tg), std::min(255.0f, tb), color.a));
			}
		}

		img.update();
		ofLogNotice("ImageFilters") << "Sepia filter applied";
	}

	// Apply invert filter
	static void applyInvert(ofImage & img) {
		if (!img.isAllocated()) return;

		ofPixels & pixels = img.getPixels();
		int w = img.getWidth();
		int h = img.getHeight();

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				ofColor color = pixels.getColor(x, y);

				pixels.setColor(x, y, ofColor(255 - color.r, 255 - color.g, 255 - color.b, color.a));
			}
		}

		img.update();
		ofLogNotice("ImageFilters") << "Invert filter applied";
	}
};
