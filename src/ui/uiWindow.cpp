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
	// Mise à jour de la zone de dessin
	drawingArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight);

	// Fond de la barre de menu
	ofPushStyle();
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);
	ofPopStyle();

	// Dessiner les onglets
	drawTabs();

	// Calculer la largeur du menu latéral
	float sideMenuWidth = ofGetWidth() / 6;

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
