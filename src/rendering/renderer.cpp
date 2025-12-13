// Renderer.cpp
// Implémentation du renderer principal MVC PUR (VIEW uniquement)
// Le Renderer REÇOIT les RenderData préparées par Application
#include "Renderer.h"
#include <algorithm>

Renderer::Renderer() {
}

void Renderer::setup() {
	ofSetFrameRate(60);
	sceneRenderer.setup();
	ofLogNotice("Renderer") << "Setup complete";
}

// ========== MÉTHODES DE RENDU (VIEW PURE) ==========

void Renderer::drawDrawCanvas(const RenderDataDraw2D & data) {
	ofDisableDepthTest();

	ensureFboMatches(drawFbo, drawDrawingArea);

	drawFbo.begin();
	ofClear(0, 0, 0, 0);
	ofPushMatrix();
	ofTranslate(-drawDrawingArea.x, -drawDrawingArea.y);

	// Dessiner le background
	drawBackground(drawDrawingArea, data.backgroundColor);

	// Configurer les paramètres visuels depuis les données
	currentLineWidth = data.lineWidth;
	currentStrokeColor = data.strokeColor;
	currentFillColor = data.fillColor;

	// Pousser les données au renderer de scène
	sceneRenderer.draw2D(data);

	ofPopMatrix();
	drawFbo.end();

	drawFbo.draw(drawDrawingArea.x, drawDrawingArea.y);
}

void Renderer::drawCurvesCanvas(const RenderDataCurves2D & data) {
	ofDisableDepthTest();

	ensureFboMatches(curvesFbo, curvesDrawingArea);

	curvesFbo.begin();
	ofClear(0, 0, 0, 0);
	ofPushMatrix();
	ofTranslate(-curvesDrawingArea.x, -curvesDrawingArea.y);

	drawBackground(curvesDrawingArea, data.backgroundColor);

	currentLineWidth = data.lineWidth;
	currentStrokeColor = data.strokeColor;

	// MODIFIER l'appel:
	curvesRenderer.render(data.controlPoints, data.curves, data.animator);

	ofPopMatrix();
	curvesFbo.end();

	curvesFbo.draw(curvesDrawingArea.x, curvesDrawingArea.y);
}

void Renderer::draw3D(const RenderData3D & data) {
	// La viewport et la zone visuelle dédiées 3D ont été supprimées.
	// Nous dessinons directement en 3D sur le contexte courant.

	// Ne plus dessiner le rectangle de fond délimitant la zone 3D
	// (remplacé par le rendu direct de la scène 3D par sceneRenderer)

	// Configurer les options 3D
	sceneRenderer.set3DDisplayOptions(data.showBoundingBox, data.showWireframe, data.showNormals);

	// Activer le test de profondeur pour le rendu 3D
	ofEnableDepthTest();

	// Pousser les données au renderer de scène (qui gère la caméra et le rendu)
	sceneRenderer.draw3D(data);

	ofDisableDepthTest();
}

void Renderer::drawQuad(const RenderDataQuad & data) {
	ofDisableDepthTest();
	// Dessiner le background
	drawBackground(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), ofColor(180, 200, 220)); // Background par défaut Quad

	// Configurer les options 3D
	sceneRenderer.set3DDisplayOptions(data.showBoundingBox, data.showWireframe, false);

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

void Renderer::set3DDisplayOptions(bool showBoundingBox, bool showWireframe, bool showNormals) {
	showBoundingBox3D = showBoundingBox;
	showWireframe3D = showWireframe;

	// Configurer le SceneRenderer
	sceneRenderer.set3DDisplayOptions(showBoundingBox, showWireframe, showNormals);
}

void Renderer::setExternalSceneCamera(ofEasyCam * cam) {
	sceneRenderer.setExternalCamera(cam);
}

// ========== RENDU DU BACKGROUND ==========

void Renderer::drawBackground(const ofRectangle & area, const ofColor & bgColor) {
	ofPushStyle();
	ofSetColor(bgColor);
	ofDrawRectangle(area.x, area.y, area.width, area.height);
	ofPopStyle();
}

void Renderer::ensureFboMatches(ofFbo & fbo, const ofRectangle & area) {
	ensureFboMatches(fbo, area, false);
}

void Renderer::ensureFboMatches(ofFbo & fbo, const ofRectangle & area, bool useDepth) {
	if (fbo.getWidth() != area.width || fbo.getHeight() != area.height) {
		ofFbo::Settings settings;
		settings.width = std::max(1.0f, area.width);
		settings.height = std::max(1.0f, area.height);
		settings.internalformat = GL_RGBA;
		settings.useDepth = useDepth;
		settings.useStencil = false;
		settings.textureTarget = GL_TEXTURE_2D;
		if (useDepth) {
			settings.depthStencilAsTexture = true;
			settings.depthStencilInternalFormat = GL_DEPTH_COMPONENT24;
		}
		fbo.allocate(settings);
	}
}
