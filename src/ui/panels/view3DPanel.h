// View3DPanel.h
// Panel responsable de la gestion de la vue 3D
#pragma once

#include "../panels/3dEdition/cameraPanel.h"
#include "../panels/3dEdition/geometry3DPanel.h"
#include "../panels/3dEdition/lightingPanel.h"
#include "../panels/3dEdition/rayTracingPanel.h"
#include "../panels/3dEdition/texture3DPanel.h"
#include "../panels/3dEdition/topologyPanel.h"
#include "../panels/3dEdition/transformation3DPanel.h"
#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class View3DPanel
 * @brief Panel UI pour les controles de la vue 3D
 *
 * Responsabilites :
 * - Basculer entre les modes de vue (2D, 3D, Quad)
 * - Controles de camera
 * - Options d'affichage (wireframe, bounding boxes)
 */
class View3DPanel {
public:
	View3DPanel();
	~View3DPanel() = default;

	void setup();
	void draw(float sideMenuWidth, float menuBarHeight);

	// Accesseurs d'etat
	bool isVisible() const { return isActive; }
	bool isShowBoundingBoxToggled() const { return cameraPanel.isBoundingBoxEnabled(); }
	bool isShowWireframeToggled() const { return cameraPanel.isWireframeEnabled(); }
	bool isQuadViewRequested() const { return quadViewRequested; }

	// Controle du panel
	void show() { isActive = true; }
	void hide() { isActive = false; }
	void toggle() { isActive = !isActive; }

	// Reset state
	void reset();

	// Clear des requetes
	void clearRequests();

private:
	// Etat du panel
	bool isActive = false;
	bool quadViewRequested = false;

	// Panel ofxGui
	ofxPanel view3DPanel;

	// Boutons et labels
	ofxButton quadViewButton;
	ofxLabel viewTitle;

	CameraPanel cameraPanel;
	Transformation3DPanel transformationPanel;
	Geometry3DPanel geometryPanel;
	Texture3DPanel texturePanel;
	TopologyPanel topologyPanel;
	RayTracingPanel rayTracingPanel;
	LightingPanel lightingPanel;

	// Callbacks
	void onQuadViewPressed();
};
