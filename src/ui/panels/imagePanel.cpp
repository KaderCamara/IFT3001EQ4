// ImagePanel.cpp
// Implémentation du panel d'images et modèles 3D
#include "ImagePanel.h"

ImagePanel::ImagePanel() {
}

void ImagePanel::setup() {
	// Setup du menu image
	imageMenuPanel.setup("Image Menu");
	imageMenuPanel.add(importImageButton.setup("Import Image"));
	imageMenuPanel.add(clearImageButton.setup("Clear Image"));
	imageMenuPanel.add(import3DModelButton.setup("Import 3D Model"));
	imageMenuPanel.add(clear3DModelButton.setup("Clear 3D Models"));

	// Listeners
	importImageButton.addListener(this, &ImagePanel::onImportImagePressed);
	clearImageButton.addListener(this, &ImagePanel::onClearImagePressed);
	import3DModelButton.addListener(this, &ImagePanel::onImport3DModelPressed);
	clear3DModelButton.addListener(this, &ImagePanel::onClear3DModelPressed);
}

void ImagePanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	// Positionner et dessiner le panel
	imageMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	imageMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	imageMenuPanel.draw();
}

void ImagePanel::clearRequests() {
	importImageRequested = false;
	clearImageRequested = false;
	import3DModelRequested = false;
	clear3DModelRequested = false;
}

void ImagePanel::reset() {
	// Réinitialiser l'état du panel lors du changement d'onglet
	importImageRequested = false;
	clearImageRequested = false;
	import3DModelRequested = false;
	clear3DModelRequested = false;
	ofLogNotice("ImagePanel") << "Panel reset - ready for new interaction";
}

// ========== CALLBACKS ==========

void ImagePanel::onImportImagePressed() {
	importImageRequested = true;
	ofLogNotice("ImagePanel") << "Import image requested";
}

void ImagePanel::onClearImagePressed() {
	clearImageRequested = true;
	ofLogNotice("ImagePanel") << "Clear image requested";
}

void ImagePanel::onImport3DModelPressed() {
	import3DModelRequested = true;
	ofLogNotice("ImagePanel") << "Import 3D model requested";
}

void ImagePanel::onClear3DModelPressed() {
	clear3DModelRequested = true;
	ofLogNotice("ImagePanel") << "Clear 3D models requested";
}
