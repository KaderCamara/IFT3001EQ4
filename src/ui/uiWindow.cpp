// uiWindow.cpp
// Implémentation de l'orchestrateur UI
#include "uiWindow.h"

void UIWindow::setup() {
	// Setup de tous les panels
	drawingPanel.setup();
	imagePanel.setup();
	view3DPanel.setup();
	infoPanel.setup();

	// Setup de la zone de statut
	statusBox.set(10, menuBarHeight + 10, 250, 40);

	ofLogNotice("UIWindow") << "UI Window setup complete";
}

void UIWindow::update() {
	// Update des panels
	drawingPanel.update();
	// update info panel with current state
	infoPanel.update(
		(imageTab.active ? "Image" : (drawTab.active ? "2D" : "3D")),
		view3DActive && !view3DPanel.isQuadViewRequested(),
		view3DPanel.isQuadViewRequested(),
		drawingArea,
		statusMessage
	);
}

void UIWindow::draw() {
	// Calculer la largeur du menu latéral
	float sideMenuWidth = ofGetWidth() / 6;
	float leftPanelWidth = sideMenuWidth; // width reserved for the left camera panel when in 3D view or left tools in 2D
	float rightPanelWidth = 0.0f; // width reserved for right sidebar in 2D

	// Determine whether left and right columns are active
	bool leftActive = (drawTab.active && drawingPanel.isVisible()) || (view3DActive && view3DPanel.isVisible());
	bool rightActive = (drawTab.active && drawingPanel.isVisible());
	// Also show the right sidebar background in 3D so it matches 2D darkness
	if (view3DActive) rightActive = true;
	if (rightActive) rightPanelWidth = sideMenuWidth;

	// bottom inset reserved for info panel
	float bottomInset = infoPanel.getHeight();

	// Mise à jour de la zone de dessin
	if (view3DActive) {
		// Reserve left and right side panels from the drawing area so the 3D view is centered
		float left = leftPanelWidth;
		float right = sideMenuWidth;
		float w = ofGetWidth() - left - right;
		if (w < 0) w = ofGetWidth();
		drawingArea.set(left, menuBarHeight, w, ofGetHeight() - menuBarHeight - bottomInset);
	} else if (leftActive || rightActive) {
		// Reserve space for left and/or right sidebars in 2D mode
		float left = leftActive ? leftPanelWidth : 0.0f;
		float right = rightActive ? rightPanelWidth : 0.0f;
		float w = ofGetWidth() - left - right;
		if (w < 0) w = ofGetWidth();
		drawingArea.set(left, menuBarHeight, w, ofGetHeight() - menuBarHeight - bottomInset);
	} else {
		drawingArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight - bottomInset);
	}

	// Fond de la barre de menu
	ofPushStyle();
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);
	ofPopStyle();

	// Dessiner les onglets
	drawTabs();

	// Draw left vertical delimiter when left column is active (2D editing or 3D with camera panel)
	if (leftActive) {
		ofPushStyle();
		// semi-transparent fill for the left column
		ofSetColor(30, 30, 35, 180);
		ofFill();
		ofDrawRectangle(0, menuBarHeight, leftPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		// outline
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(2);
		ofDrawRectangle(0, menuBarHeight, leftPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		ofPopStyle();
	}

	// Draw right vertical delimiter when right sidebar is active (2D editing or 3D view)
	if (rightActive) {
		float rx = ofGetWidth() - rightPanelWidth;
		ofPushStyle();
		// semi-transparent fill for the right column
		ofSetColor(30, 30, 35, 180);
		ofFill();
		ofDrawRectangle(rx, menuBarHeight, rightPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		// outline
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(2);
		ofDrawRectangle(rx, menuBarHeight, rightPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		ofPopStyle();
	}

	// Delimiter for 3D view: draw a visible border where the 3D view will be rendered
	// Only show when the 3D panel is active and visible
	if (view3DActive && view3DPanel.isVisible()) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(3);
		ofDrawRectangle(drawingArea.x + 2, drawingArea.y + 2, drawingArea.width - 4, drawingArea.height - 4);
		// label
		ofSetColor(200);
		ofDrawBitmapString("3D VIEW", drawingArea.x + 10, drawingArea.y + 20);
		ofPopStyle();
	}

	// Dessiner les panels actifs
	drawingPanel.draw(sideMenuWidth, menuBarHeight);
	imagePanel.draw(sideMenuWidth, menuBarHeight);
	view3DPanel.draw(sideMenuWidth, menuBarHeight);

	// draw info panel at bottom
	infoPanel.draw(menuBarHeight);

	// Dessiner la boîte de statut
	drawStatusBox();
}

void UIWindow::drawTabs() {
	for (auto & tab : { imageTab, drawTab, view3DTab }) {
		ofPushStyle();
		ofSetColor(tab.active ? 100 : 150);
		ofDrawRectangle(tab.bounds);
		ofSetColor(255);
		ofDrawBitmapString(tab.label, tab.bounds.x + 10, tab.bounds.y + 30);
		ofPopStyle();
	}
}

void UIWindow::drawStatusBox() {
	if (!statusMessage.empty()) {
		ofPushStyle();
		ofSetColor(0, 0, 0, 180);
		ofDrawRectangle(statusBox);
		ofSetColor(255);
		ofDrawBitmapString(statusMessage, statusBox.x + 10, statusBox.y + 25);
		ofPopStyle();
	}
}

void UIWindow::mousePressed(int x, int y, int button) {
	handleTabClick(x, y);
}

void UIWindow::mouseReleased(int x, int y, int button) {
	// Logique de mouse released si nécessaire
}

void UIWindow::handleFileDragAndDrop(ofDragInfo dragInfo) {
	if (dragInfo.files.empty()) return;
	statusMessage = "File loaded via drag & drop";
}

void UIWindow::handleTabClick(int x, int y) {
	if (imageTab.bounds.inside(x, y)) {
		activateImageTab();
	} else if (drawTab.bounds.inside(x, y)) {
		activateDrawTab();
	} else if (view3DTab.bounds.inside(x, y)) {
		activateView3DTab();
	}
}

void UIWindow::activateImageTab() {
	// Désactiver tous les autres
	imageTab.active = true;
	drawTab.active = false;
	view3DTab.active = false;

	imagePanel.show();
	drawingPanel.hide();
	view3DPanel.hide();

	view3DActive = false;

	ofLogNotice("UIWindow") << "Image tab activated";
}

void UIWindow::activateDrawTab() {
	// Désactiver tous les autres
	imageTab.active = false;
	drawTab.active = true;
	view3DTab.active = false;

	imagePanel.hide();
	drawingPanel.show();
	view3DPanel.hide();

	view3DActive = false;

	ofLogNotice("UIWindow") << "2D Edition tab activated";
}

void UIWindow::activateView3DTab() {
	// Désactiver tous les autres
	imageTab.active = false;
	drawTab.active = false;
	view3DTab.active = true;

	imagePanel.hide();
	drawingPanel.hide();
	view3DPanel.show();

	view3DActive = true;

	ofLogNotice("UIWindow") << "3D Edition tab activated";
}

void UIWindow::clearRequests() {
	drawingPanel.clearRequests();
	imagePanel.clearRequests();
	view3DPanel.clearRequests();
}

// Forwarders for image panel specific clear requests
void UIWindow::clearImport3DModelRequest() {
	imagePanel.clearRequests();
}

void UIWindow::clearClear3DModelRequest() {
	imagePanel.clearRequests();
}
