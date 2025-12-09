// ImagePanel.h
// Panel responsable de la gestion des images et modèles 3D
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class ImagePanel
 * @brief Panel UI pour l'import/export d'images et modèles 3D
 *
 * Responsabilités :
 * - Import/clear d'images
 * - Import/clear de modèles 3D
 * - Gestion du drag & drop de fichiers
 */
class ImagePanel {
public:
	ImagePanel();
	~ImagePanel() = default;

	void setup();
	void draw(float sideMenuWidth, float menuBarHeight);

	// Accesseurs d'état
	bool isVisible() const { return isActive; }
	bool isImportImageRequested() const { return importImageRequested; }
	bool isClearImageRequested() const { return clearImageRequested; }
	bool isImport3DModelRequested() const { return import3DModelRequested; }
	bool isClear3DModelRequested() const { return clear3DModelRequested; }
	bool isExportImageRequested() const { return exportImageRequested; }
	bool isExportSequenceRequested() const { return exportSequenceRequested; }
	bool isGenerateFromSamplesRequested() const { return generateFromSamplesRequested; }
	bool isPaletteRequested() const { return paletteRequested; }
	bool isHistogramRequested() const { return histogramRequested; }

	// Contrôle du panel
	void show() { isActive = true; }
	void hide() { isActive = false; }
	void toggle() { isActive = !isActive; }

	// Clear des requêtes
	void clearRequests();

	// Reset state
	void reset();

private:
	// état du panel
	bool isActive = false;
	bool importImageRequested = false;
	bool clearImageRequested = false;
	bool import3DModelRequested = false;
	bool clear3DModelRequested = false;
	bool exportImageRequested = false;
	bool exportSequenceRequested = false;
	bool generateFromSamplesRequested = false;
	bool paletteRequested = false;
	bool histogramRequested = false;

	// Panel ofxGui
	ofxPanel imageMenuPanel;
	ofxPanel imageGenerationPanel;

	// Boutons
	ofxButton importImageButton;
	ofxButton clearImageButton;
	ofxButton import3DModelButton;
	ofxButton clear3DModelButton;
	ofxButton exportImageButton;
	ofxButton exportSequenceButton;
	ofxButton generateFromSamplesButton;
	ofxButton paletteButton;
	ofxButton histogramButton;

	// Callbacks
	void onImportImagePressed();
	void onClearImagePressed();
	void onImport3DModelPressed();
	void onClear3DModelPressed();
	void onExportImagePressed();
	void onExportSequencePressed();
	void onGenerateFromSamplesPressed();
	void onPalettePressed();
	void onHistogramPressed();
};
