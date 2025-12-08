// View3DPanel.cpp
// Implémentation du panel de vue 3D
#include "View3DPanel.h"

View3DPanel::View3DPanel() {
}

void View3DPanel::setup() {
	// Setup du menu 3D View
	view3DPanel.setup("3D EDITION");
	viewTitle.setup("Camera & View", "");
	view3DPanel.add(&viewTitle);

	quadViewButton.setup("4 Cameras View");
	view3DPanel.add(&quadViewButton);

	cameraPanel.setup();

	// Listener
	quadViewButton.addListener(this, &View3DPanel::onQuadViewPressed);
}

void View3DPanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	float panelX = ofGetWidth() - sideMenuWidth;
	float panelY = menuBarHeight;

	// Positionner et dessiner le bandeau supérieur
	view3DPanel.setPosition(panelX, panelY);
	view3DPanel.setSize(sideMenuWidth, 70);
	view3DPanel.draw();

	// Positionner et dessiner le camera panel juste sous le titre
	cameraPanel.setPosition(panelX, panelY + view3DPanel.getHeight());
	cameraPanel.setWidth(sideMenuWidth);
	cameraPanel.draw();
}

void View3DPanel::clearRequests() {
	quadViewRequested = false;
}

void View3DPanel::reset() {
	// Réinitialiser l'état du panel
	quadViewRequested = false;
	ofLogNotice("View3DPanel") << "Panel reset";
}

// ========== CALLBACKS ==========

void View3DPanel::onQuadViewPressed() {
	quadViewRequested = !quadViewRequested;
	ofLogNotice("View3DPanel") << "Quad view: " << (quadViewRequested ? "ON" : "OFF");
}
