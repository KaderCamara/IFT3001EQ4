// View3DPanel.h
// Panel responsable de la gestion de la vue 3D
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class View3DPanel
 * @brief Panel UI pour les contrôles de la vue 3D
 * 
 * Responsabilités :
 * - Basculer entre les modes de vue (2D, 3D, Quad)
 * - Contrôles de caméra
 * - Options d'affichage (wireframe, bounding boxes)
 */
class View3DPanel {
public:
	View3DPanel();
	~View3DPanel() = default;

	void setup();
	void draw(float sideMenuWidth, float menuBarHeight);

	// Accesseurs d'état
	bool isVisible() const { return isActive; }
	bool isShowBoundingBoxToggled() const { return showBoundingBox; }
	bool isShowWireframeToggled() const { return showWireframe; }
	bool isQuadViewRequested() const { return quadViewRequested; }

	// Contrôle du panel
	void show() { isActive = true; }
	void hide() { isActive = false; }
	void toggle() { isActive = !isActive; }

	// Reset state
	void reset();

	// Clear des requêtes
	void clearRequests();

private:
	// État du panel
	bool isActive = false;
	bool showBoundingBox = false;
	bool showWireframe = false;
	bool quadViewRequested = false;

	// Panel ofxGui
	ofxPanel view3DPanel;

	// Boutons et labels
	ofxButton showBoundingBoxButton;
	ofxButton wireframeButton;
	ofxButton quadViewButton;
	ofxLabel cameraTitle;
	ofxLabel cameraInstructions1;
	ofxLabel cameraInstructions2;

	// Callbacks
	void onShowBoundingBoxPressed();
	void onWireframePressed();
	void onQuadViewPressed();
};
