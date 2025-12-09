// InfoPanel.cpp
// Implémentation du bandeau d'information en bas de l'écran
#include "InfoPanel.h"

void InfoPanel::setup() {
	// Valeurs par défaut
	activeTab = "Image";
	viewMode = "2D";
	drawingAreaInfo.set(0, 0, ofGetWidth(), ofGetHeight());
	statusText.clear();
	fps = ofGetFrameRate();
}

void InfoPanel::update(const std::string & activeTabLabel, bool is3DView, bool isQuadView, const ofRectangle & drawingArea, const std::string & statusMessage) {
	activeTab = activeTabLabel;
	viewMode = isQuadView ? "Quad" : (is3DView ? "3D" : "2D");
	drawingAreaInfo = drawingArea;
	statusText = statusMessage;
	fps = ofGetFrameRate();
}

void InfoPanel::draw(float menuBarHeight) {
	(void)menuBarHeight; // Parametre conserve pour coherence potentielle

	float yPosition = ofGetHeight() - panelHeight;

	// Dessiner le fond et le contenu
	drawBackground(yPosition);
	drawContent(yPosition);

	// Ligne de séparation avec la zone de dessin
	ofPushStyle();
	ofSetColor(255, 255, 255, 80);
	ofDrawLine(0, yPosition, ofGetWidth(), yPosition);
	ofPopStyle();
}

void InfoPanel::drawBackground(float yPosition) {
	ofPushStyle();
	// Use opaque colors (no transparency)
	ofColor startColor(30, 30, 35, 255);
	ofColor endColor(20, 20, 25, 255);

	// Dégrader simple de haut en bas
	ofMesh gradientMesh;
	gradientMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
	gradientMesh.addColor(startColor);
	gradientMesh.addVertex(glm::vec3(0, yPosition, 0));
	gradientMesh.addColor(startColor);
	gradientMesh.addVertex(glm::vec3(ofGetWidth(), yPosition, 0));
	gradientMesh.addColor(endColor);
	gradientMesh.addVertex(glm::vec3(ofGetWidth(), yPosition + panelHeight, 0));
	gradientMesh.addColor(endColor);
	gradientMesh.addVertex(glm::vec3(0, yPosition + panelHeight, 0));
	gradientMesh.draw();

	ofPopStyle();
}

void InfoPanel::drawContent(float yPosition) {
	ofPushStyle();
	// Set text color to green
	ofSetColor(0, 200, 0);

	float padding = 16.0f;
	float lineHeight = 18.0f;
	float textY = yPosition + padding;

	std::string viewLabel = "View: " + viewMode;
	std::string tabLabel = "Tab: " + activeTab;
	std::string drawingLabel = "Drawing area: " + ofToString((int)drawingAreaInfo.width) + "x" + ofToString((int)drawingAreaInfo.height);
	std::string statusLabel = statusText.empty() ? "Status: ready" : "Status: " + statusText;
	std::string fpsLabel = "FPS: " + ofToString(fps, 1);

	ofDrawBitmapString(tabLabel, padding, textY);
	ofDrawBitmapString(viewLabel, padding, textY + lineHeight);
	ofDrawBitmapString(drawingLabel, padding, textY + lineHeight * 2);
	ofDrawBitmapString(statusLabel, padding + 260, textY);
	ofDrawBitmapString(fpsLabel, padding + 260, textY + lineHeight);

	ofPopStyle();
}
