// Renderer.cpp
// Implémentation du renderer pur (VIEW uniquement)
//
// REFACTORISATION MVC (Phase 1 - Problème 3) :
// - AVANT : Appels directs à controlPointsManager.drawPointsForCurves() et curveManager.draw()
// - APRÈS : Délégation à curvesRenderer.render()
#include "Renderer.h"
#include <cfloat>

Renderer::Renderer() {
}

void Renderer::setup() {
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);
	ofLogNotice("Renderer") << "Setup complete";
}

void Renderer::setSceneController(SceneController * controller) {
	sceneController = controller;
	ofLogNotice("Renderer") << "SceneController injected";
	sceneRenderer.setSceneController(sceneController);
	sceneRenderer.setCurvesRenderer(&curvesRenderer);
}

// ========== MÉTHODES DE RENDU PRINCIPALES ==========

void Renderer::draw() {
	if (!sceneController) {
		ofLogError("Renderer") << "No SceneController set!";
		return;
	}

	// Dessiner le background dans la zone de dessin
	drawBackground();

	// Router vers la bonne méthode de rendu selon le mode
	if (sceneController->isQuadView()) {
		sceneRenderer.drawQuadView();
	} else if (sceneController->is3DView()) {
		sceneRenderer.draw3D();
	} else if (sceneController->is2DView()) {
		sceneRenderer.draw2D();
	}
}

// ========== MÉTHODES PRIVÉES DE RENDU ==========

void Renderer::drawBackground() {
	ofPushStyle();
	ofSetColor(currentBgColor);
	ofDrawRectangle(drawingArea.x, drawingArea.y, drawingArea.width, drawingArea.height);
	ofPopStyle();
}

// ========== CONFIGURATION DU RENDU ==========

void Renderer::applyDrawingParameters(float lineW, const ofColor & stroke, const ofColor & fill,
	const ofColor & bg, bool useHSB, float hue, float saturation, float brightness) {
	currentLineWidth = lineW;
	useHSBmode = useHSB;

	if (useHSBmode) {
		currentStrokeColor = ofColor::fromHsb(hue, saturation, brightness);
		currentFillColor = ofColor::fromHsb(hue, saturation, brightness);
		currentBgColor = ofColor::fromHsb(hue, saturation, brightness);
	} else {
		currentStrokeColor = stroke;
		currentFillColor = fill;
		currentBgColor = bg;
	}
}

void Renderer::updateShapeManagerParams(float lineW, ofColor stroke, ofColor fill) {
	if (sceneController) {
		sceneController->getShapeManager().setDrawingParameters(lineW, stroke, fill);
	}
}

void Renderer::setCurvesController(CurvesController * controller) {
	sceneRenderer.setCurvesController(controller);
	ofLogNotice("Renderer") << "CurvesController injected";
}

// Configuration des options d'affichage 3D
void Renderer::set3DDisplayOptions(bool showBoundingBox, bool showWireframe) {
	// On délègue au SceneRenderer, qui lui-même configure Shape3DRenderer
	sceneRenderer.set3DDisplayOptions(showBoundingBox, showWireframe);
}

