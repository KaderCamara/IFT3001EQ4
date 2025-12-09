// Renderer.cpp
// Implémentation du renderer principal MVC PUR (VIEW uniquement)
// Le Renderer REÇOIT les RenderData préparées par Application
#include "Renderer.h"

Renderer::Renderer() {
}

void Renderer::setup() {
	ofSetFrameRate(60);
	ofLogNotice("Renderer") << "Setup complete";
}

// ========== MÉTHODES DE RENDU (VIEW PURE) ==========

void Renderer::draw2D(const RenderData2D & data) {
	ofDisableDepthTest();
	// Dessiner le background
	drawBackground(data.backgroundColor);

	// Configurer les paramètres visuels depuis les données
	currentLineWidth = data.lineWidth;
	currentStrokeColor = data.strokeColor;
	currentFillColor = data.fillColor;

	// Pousser les données au renderer de scène
	sceneRenderer.draw2D(data);
}

void Renderer::draw3D(const RenderData3D & data) {
	ofDisableDepthTest();
	// Dessiner le background
	drawBackground(ofColor(180, 200, 220)); // Background par défaut 3D

	// Configurer les options 3D
	sceneRenderer.set3DDisplayOptions(data.showBoundingBox, data.showWireframe);

	// Pousser les données au renderer de scène
	sceneRenderer.draw3D(data);
}

void Renderer::drawQuad(const RenderDataQuad & data) {
	ofDisableDepthTest();
	// Dessiner le background
	drawBackground(ofColor(180, 200, 220)); // Background par défaut Quad

	// Configurer les options 3D
	sceneRenderer.set3DDisplayOptions(data.showBoundingBox, data.showWireframe);

	// Pousser les données au renderer de scène
	sceneRenderer.drawQuadView(data);
}

// ========== CONFIGURATION ==========

void Renderer::setVisualParameters(
	float lineW,
	const ofColor & stroke,
	const ofColor & fill,
	const ofColor & bg) {
	currentLineWidth = lineW;
	currentStrokeColor = stroke;
	currentFillColor = fill;
	currentBgColor = bg;
}

void Renderer::set3DDisplayOptions(bool showBoundingBox, bool showWireframe) {
	showBoundingBox3D = showBoundingBox;
	showWireframe3D = showWireframe;

	// Configurer le SceneRenderer
	sceneRenderer.set3DDisplayOptions(showBoundingBox, showWireframe);
}

// ========== RENDU DU BACKGROUND ==========

void Renderer::drawBackground(const ofColor & bgColor) {
	ofPushStyle();
	ofSetColor(bgColor);
	ofDrawRectangle(drawingArea.x, drawingArea.y, drawingArea.width, drawingArea.height);
	ofPopStyle();
}
