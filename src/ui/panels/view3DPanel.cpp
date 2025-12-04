// View3DPanel.cpp
// Implémentation du panel de vue 3D
#include "View3DPanel.h"

View3DPanel::View3DPanel() {
}

void View3DPanel::setup() {
	// Setup du menu 3D View
	view3DPanel.setup("3D View Menu");
	view3DPanel.add(showBoundingBoxButton.setup("Show Bounding Boxes"));
	view3DPanel.add(wireframeButton.setup("Wireframe Mode"));
	view3DPanel.add(cameraTitle.setup("Camera Controls", ""));
	view3DPanel.add(cameraInstructions1.setup("1:Top 2:Front 3:Side", ""));
	view3DPanel.add(cameraInstructions2.setup("4:Bottom 5:Free (drag)", ""));
	view3DPanel.add(quadViewButton.setup("4 Cameras View"));

	// Listeners
	showBoundingBoxButton.addListener(this, &View3DPanel::onShowBoundingBoxPressed);
	wireframeButton.addListener(this, &View3DPanel::onWireframePressed);
	quadViewButton.addListener(this, &View3DPanel::onQuadViewPressed);
}

void View3DPanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	// Positionner et dessiner le panel
	view3DPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	view3DPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	view3DPanel.draw();
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

void View3DPanel::onShowBoundingBoxPressed() {
	showBoundingBox = !showBoundingBox;
	ofLogNotice("View3DPanel") << "Bounding boxes: " << (showBoundingBox ? "ON" : "OFF");
}

void View3DPanel::onWireframePressed() {
	showWireframe = !showWireframe;
	ofLogNotice("View3DPanel") << "Wireframe: " << (showWireframe ? "ON" : "OFF");
}

void View3DPanel::onQuadViewPressed() {
	quadViewRequested = !quadViewRequested;
	ofLogNotice("View3DPanel") << "Quad view: " << (quadViewRequested ? "ON" : "OFF");
}
