// View3DPanel.cpp
// Implementation du panel de vue 3D
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
	sceneHierarchyPanel.setup();
	lightingPanel.setup();

	// Listener
	quadViewButton.addListener(this, &View3DPanel::onQuadViewPressed);
}

void View3DPanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	float panelX = ofGetWidth() - sideMenuWidth;
	float currentY = menuBarHeight;

	// Positionner et dessiner le bandeau superieur
	view3DPanel.setPosition(panelX, currentY);
	view3DPanel.setSize(sideMenuWidth, 70);
	view3DPanel.draw();
	currentY += view3DPanel.getHeight() + 10.0f;

	// Positionner et dessiner le panneau de camera
	cameraPanel.setPosition(panelX, currentY);
	cameraPanel.setWidth(sideMenuWidth);
	cameraPanel.draw();
	currentY += cameraPanel.getHeight() + 10.0f;

	// Panneau de hierarchie de scene
	sceneHierarchyPanel.setPosition(panelX, currentY);
	sceneHierarchyPanel.setWidth(sideMenuWidth);
	sceneHierarchyPanel.draw();
	currentY += sceneHierarchyPanel.getHeight() + 10.0f;

	// Panneau d'eclairage et environnement
	lightingPanel.setPosition(panelX, currentY);
	lightingPanel.setWidth(sideMenuWidth);
	lightingPanel.draw();
}

void View3DPanel::clearRequests() {
	quadViewRequested = false;
}

void View3DPanel::reset() {
	// Reinitialiser l'etat du panel
	quadViewRequested = false;
	ofLogNotice("View3DPanel") << "Panel reset";
}

// ========== CALLBACKS ==========

void View3DPanel::onQuadViewPressed() {
	quadViewRequested = !quadViewRequested;
	ofLogNotice("View3DPanel") << "Quad view: " << (quadViewRequested ? "ON" : "OFF");
}
