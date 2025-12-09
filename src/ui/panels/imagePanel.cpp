// ImagePanel.cpp
// Implémentation du panel d'images et modèles 3D
#include "ImagePanel.h"

ImagePanel::ImagePanel() { }

void ImagePanel::setup() {
	// Setup du menu image
	imageMenuPanel.setup("Image Menu");
	imageMenuPanel.enableHeader();
	imageMenuPanel.minimize();
	imageMenuPanel.add(importImageButton.setup("Import Image"));
	imageMenuPanel.add(clearImageButton.setup("Clear Image"));
	imageMenuPanel.add(import3DModelButton.setup("Import 3D Model"));
	imageMenuPanel.add(clear3DModelButton.setup("Clear 3D Models"));
	imageMenuPanel.add(exportImageButton.setup("Export Image"));
	imageMenuPanel.add(exportSequenceButton.setup("Export Sequence"));

	// Panel des opérations de génération/analyses d'image
	imageGenerationPanel.setup("Image Processing");
	imageGenerationPanel.enableHeader();
	imageGenerationPanel.minimize();
	imageGenerationPanel.add(generateFromSamplesButton.setup("Generate from samples"));
	imageGenerationPanel.add(paletteButton.setup("Build color palette"));
	imageGenerationPanel.add(histogramButton.setup("Compute histogram"));

	// Listeners
	importImageButton.addListener(this, &ImagePanel::onImportImagePressed);
	clearImageButton.addListener(this, &ImagePanel::onClearImagePressed);
	import3DModelButton.addListener(this, &ImagePanel::onImport3DModelPressed);
	clear3DModelButton.addListener(this, &ImagePanel::onClear3DModelPressed);
	exportImageButton.addListener(this, &ImagePanel::onExportImagePressed);
	exportSequenceButton.addListener(this, &ImagePanel::onExportSequencePressed);
	generateFromSamplesButton.addListener(this, &ImagePanel::onGenerateFromSamplesPressed);
	paletteButton.addListener(this, &ImagePanel::onPalettePressed);
	histogramButton.addListener(this, &ImagePanel::onHistogramPressed);
}

void ImagePanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	// Positionner et dessiner le panel principal
	float x = ofGetWidth() - sideMenuWidth;
	float y = menuBarHeight;
	imageMenuPanel.setPosition(x, y);
	imageMenuPanel.setSize(sideMenuWidth, imageMenuPanel.getHeight());
	imageMenuPanel.draw();

	// Panel additionnel pour les opérations d'image
	y += imageMenuPanel.getHeight() + 10.0f;
	imageGenerationPanel.setPosition(x, y);
	imageGenerationPanel.setSize(sideMenuWidth, imageGenerationPanel.getHeight());
	imageGenerationPanel.draw();
}

void ImagePanel::clearRequests() {
	importImageRequested = false;
	clearImageRequested = false;
	import3DModelRequested = false;
	clear3DModelRequested = false;
	exportImageRequested = false;
	exportSequenceRequested = false;
	generateFromSamplesRequested = false;
	paletteRequested = false;
	histogramRequested = false;
}

void ImagePanel::reset() {
	// Rinitialiser l'état du panel lors du changement d'onglet
	clearRequests();
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

void ImagePanel::onExportImagePressed() {
	exportImageRequested = true;
	ofLogNotice("ImagePanel") << "Export image requested";
}

void ImagePanel::onExportSequencePressed() {
	exportSequenceRequested = true;
	ofLogNotice("ImagePanel") << "Export sequence requested";
}

void ImagePanel::onGenerateFromSamplesPressed() {
	generateFromSamplesRequested = true;
	ofLogNotice("ImagePanel") << "Generate from samples requested";
}

void ImagePanel::onPalettePressed() {
	paletteRequested = true;
	ofLogNotice("ImagePanel") << "Palette generation requested";
}

void ImagePanel::onHistogramPressed() {
	histogramRequested = true;
	ofLogNotice("ImagePanel") << "Histogram requested";
}
