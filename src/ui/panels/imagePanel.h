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

	// Contrôle du panel
	void show() { isActive = true; }
	void hide() { isActive = false; }
	void toggle() { isActive = !isActive; }

	// Clear des requêtes
	void clearRequests();

	// Reset state
	void reset();

private:
	// État du panel
	bool isActive = false;
	bool importImageRequested = false;
	bool clearImageRequested = false;
	bool import3DModelRequested = false;
	bool clear3DModelRequested = false;

	// Panel ofxGui
	ofxPanel imageMenuPanel;

	// Boutons
	ofxButton importImageButton;
	ofxButton clearImageButton;
	ofxButton import3DModelButton;
	ofxButton clear3DModelButton;

	// Callbacks
	void onImportImagePressed();
	void onClearImagePressed();
	void onImport3DModelPressed();
	void onClear3DModelPressed();
};
