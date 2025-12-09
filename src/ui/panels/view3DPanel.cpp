// View3DPanel.cpp
// Implementation du panel de vue 3D
#include "View3DPanel.h"

View3DPanel::View3DPanel() { }

void View3DPanel::setup() {
	// Setup du menu 3D View
	view3DPanel.setup("3D EDITION");
	view3DPanel.enableHeader();
	view3DPanel.minimize();
	viewTitle.setup("Camera & View", "");
	view3DPanel.add(&viewTitle);

	quadViewButton.setup("4 Cameras View");
	view3DPanel.add(&quadViewButton);

	cameraPanel.setup();
	transformationPanel.setup();
	geometryPanel.setup();
	topologyPanel.setup();
	texturePanel.setup();
	rayTracingPanel.setup();
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

	// Positionner et dessiner le panneau de camera (fixe à gauche, collé au bord sous la barre des tabs)
	const float leftWidth = sideMenuWidth; // match the left bar width
	float cameraX = 0.0f; // flush to left edge
	float cameraY = menuBarHeight; // directly under menu bar
	cameraPanel.setPosition(cameraX, cameraY);
	cameraPanel.setWidth(leftWidth);
	cameraPanel.draw();

	// Start stacking the other panels on the right column
	float rightX = panelX;
	float rightY = currentY;

	// Panneau transformations et hierarchie (à droite)
	transformationPanel.setPosition(rightX, rightY);
	transformationPanel.setWidth(sideMenuWidth);
	transformationPanel.draw();
	rightY += transformationPanel.getHeight() + 10.0f;

	// Panneau geometrie
	geometryPanel.setPosition(rightX, rightY);
	geometryPanel.setWidth(sideMenuWidth);
	geometryPanel.draw();
	rightY += geometryPanel.getHeight() + 10.0f;

	// Panneau topologie et courbes
	topologyPanel.setPosition(rightX, rightY);
	topologyPanel.setWidth(sideMenuWidth);
	topologyPanel.draw();
	rightY += topologyPanel.getHeight() + 10.0f;

	// Panneau textures
	texturePanel.setPosition(rightX, rightY);
	texturePanel.setWidth(sideMenuWidth);
	texturePanel.draw();
	rightY += texturePanel.getHeight() + 10.0f;

	// Panneau ray tracing
	rayTracingPanel.setPosition(rightX, rightY);
	rayTracingPanel.setWidth(sideMenuWidth);
	rayTracingPanel.draw();
	rightY += rayTracingPanel.getHeight() + 10.0f;

	// Panneau d'eclairage et environnement
	lightingPanel.setPosition(rightX, rightY);
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
