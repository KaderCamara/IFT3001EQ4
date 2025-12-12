// imageRenderer.cpp
// Implémentation du renderer d'images (VIEW)
#include "imageRenderer.h"

void ImageRenderer::render(const ofImage & image, float x, float y, float width, float height) const {
	// Ne rien dessiner si l'image n'est pas allouée
	if (!image.isAllocated()) {
		return;
	}

	// Utiliser les dimensions originales si non spécifiées
	float drawWidth = (width < 0) ? image.getWidth() : width;
	float drawHeight = (height < 0) ? image.getHeight() : height;

	// Dessiner l'image
	image.draw(x, y, drawWidth, drawHeight);
}

void ImageRenderer::renderScaled(const ofImage & image, float x, float y, float scale) const {
	if (!image.isAllocated()) {
		return;
	}

	float scaledWidth = image.getWidth() * scale;
	float scaledHeight = image.getHeight() * scale;

	image.draw(x, y, scaledWidth, scaledHeight);
}

void ImageRenderer::renderInBounds(const ofImage & image, const ofRectangle & bounds, bool maintainAspectRatio) const {
	if (!image.isAllocated()) {
		return;
	}

	float drawWidth, drawHeight;

	if (maintainAspectRatio) {
		// Calculer les dimensions en conservant l'aspect ratio
		calculateAspectFitDimensions(
			image.getWidth(), image.getHeight(),
			bounds.width, bounds.height,
			drawWidth, drawHeight);

		// Centrer dans le rectangle
		float x = bounds.x + (bounds.width - drawWidth) * 0.5f;
		float y = bounds.y + (bounds.height - drawHeight) * 0.5f;

		image.draw(x, y, drawWidth, drawHeight);
	} else {
		// Étirer pour remplir le rectangle
		image.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	}
}

void ImageRenderer::calculateAspectFitDimensions(float srcWidth, float srcHeight,
	float dstWidth, float dstHeight,
	float & outWidth, float & outHeight) const {
	// Calculer les ratios
	float srcAspect = srcWidth / srcHeight;
	float dstAspect = dstWidth / dstHeight;

	if (srcAspect > dstAspect) {
		// Image plus large : limiter par la largeur
		outWidth = dstWidth;
		outHeight = dstWidth / srcAspect;
	} else {
		// Image plus haute : limiter par la hauteur
		outHeight = dstHeight;
		outWidth = dstHeight * srcAspect;
	}
}
