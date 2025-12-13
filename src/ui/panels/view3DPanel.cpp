// View3DPanel.cpp
// Implementation du panel de vue 3D
#include "View3DPanel.h"

View3DPanel::View3DPanel() { }

void View3DPanel::setup() {
	// Setup du bandeau principal 3D
	view3DPanel.setup("3D EDITION");
	view3DPanel.enableHeader();
	view3DPanel.minimize();
	viewTitle.setup("Camera & View", "");
	view3DPanel.add(&viewTitle);

	quadViewButton.setup("4 Cameras View");
	view3DPanel.add(&quadViewButton);

	// Navigation entre sections
	navigationPanel.setup("3D Sections");
	navigationPanel.enableHeader();
	navigationPanel.minimize();
	navigationPanel.add(sceneAssetsButton.setup("Scene & Assets"));
	navigationPanel.add(cameraButton.setup("Camera"));
	navigationPanel.add(transformButton.setup("Transform"));
	navigationPanel.add(geometryButton.setup("Geometry & Bounds"));
	navigationPanel.add(topologyButton.setup("Topology & Curves"));
	navigationPanel.add(textureButton.setup("Materials & Textures"));
	navigationPanel.add(rayTracingButton.setup("Ray Tracing"));
	navigationPanel.add(lightingButton.setup("Lighting & Environment"));

	sceneAssetsPanel.setup();
	cameraPanel.setup();
	transformationPanel.setup();
	geometryPanel.setup();
	topologyPanel.setup();
	texturePanel.setup();
	rayTracingPanel.setup();
	lightingPanel.setup();

	// Listener
	quadViewButton.addListener(this, &View3DPanel::onQuadViewPressed);
	sceneAssetsButton.addListener(this, &View3DPanel::onSceneAssetsButton);
	cameraButton.addListener(this, &View3DPanel::onCameraButton);
	transformButton.addListener(this, &View3DPanel::onTransformButton);
	geometryButton.addListener(this, &View3DPanel::onGeometryButton);
	topologyButton.addListener(this, &View3DPanel::onTopologyButton);
	textureButton.addListener(this, &View3DPanel::onTextureButton);
	rayTracingButton.addListener(this, &View3DPanel::onRayTracingButton);
	lightingButton.addListener(this, &View3DPanel::onLightingButton);
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

	// Panneau de navigation (accordeon)
	navigationPanel.setPosition(panelX, currentY);
	navigationPanel.setSize(sideMenuWidth, navigationPanel.getHeight());
	navigationPanel.draw();
	currentY += navigationPanel.getHeight() + 10.0f;

	float rightX = panelX;
	float rightY = currentY;

	switch (activeSection) {
	case Section::SceneAssets:
		sceneAssetsPanel.draw(rightX, rightY, sideMenuWidth);
		break;
	case Section::Camera:
		cameraPanel.setPosition(rightX, rightY);
		cameraPanel.setWidth(sideMenuWidth);
		cameraPanel.draw();
		break;
	case Section::Transformation:
		transformationPanel.setPosition(rightX, rightY);
		transformationPanel.setWidth(sideMenuWidth);
		transformationPanel.draw();
		break;
	case Section::Geometry:
		geometryPanel.setPosition(rightX, rightY);
		geometryPanel.setWidth(sideMenuWidth);
		geometryPanel.draw();
		break;
	case Section::Topology:
		topologyPanel.setPosition(rightX, rightY);
		topologyPanel.setWidth(sideMenuWidth);
		topologyPanel.draw();
		break;
	case Section::Texture:
		texturePanel.setPosition(rightX, rightY);
		texturePanel.setWidth(sideMenuWidth);
		texturePanel.draw();
		break;
	case Section::RayTracing:
		rayTracingPanel.setPosition(rightX, rightY);
		rayTracingPanel.setWidth(sideMenuWidth);
		rayTracingPanel.draw();
		break;
	case Section::Lighting:
		lightingPanel.setPosition(rightX, rightY);
		lightingPanel.setWidth(sideMenuWidth);
		lightingPanel.draw();
		break;
	}
}

void View3DPanel::clearRequests() {
	//quadViewRequested = false;
	sceneAssetsPanel.clearRequests();
}

void View3DPanel::reset() {
	// Reinitialiser l'etat du panel
	quadViewRequested = false;
	activeSection = Section::SceneAssets;
	sceneAssetsPanel.clearRequests();
	ofLogNotice("View3DPanel") << "Panel reset";
}

// ========== CALLBACKS ==========

void View3DPanel::onQuadViewPressed() {
	quadViewRequested = !quadViewRequested;
	ofLogNotice("View3DPanel") << "Quad view: " << (quadViewRequested ? "ON" : "OFF");
}

void View3DPanel::onSectionButtonPressed(Section section) {
	activeSection = section;
}

void View3DPanel::onSceneAssetsButton() { onSectionButtonPressed(Section::SceneAssets); }
void View3DPanel::onCameraButton() { onSectionButtonPressed(Section::Camera); }
void View3DPanel::onTransformButton() { onSectionButtonPressed(Section::Transformation); }
void View3DPanel::onGeometryButton() { onSectionButtonPressed(Section::Geometry); }
void View3DPanel::onTopologyButton() { onSectionButtonPressed(Section::Topology); }
void View3DPanel::onTextureButton() { onSectionButtonPressed(Section::Texture); }
void View3DPanel::onRayTracingButton() { onSectionButtonPressed(Section::RayTracing); }
void View3DPanel::onLightingButton() { onSectionButtonPressed(Section::Lighting); }
