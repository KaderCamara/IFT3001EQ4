// View3DPanel.h
// Panel responsable de la gestion de la vue 3D
#pragma once

#include "../panels/3dEdition/cameraPanel.h"
#include "../panels/3dEdition/geometry3DPanel.h"
#include "../panels/3dEdition/lightingPanel.h"
#include "../panels/3dEdition/rayTracingPanel.h"
#include "../panels/3dEdition/sceneAssetsPanel.h"
#include "../panels/3dEdition/texture3DPanel.h"
#include "../panels/3dEdition/topologyPanel.h"
#include "../panels/3dEdition/transformation3DPanel.h"
#include "ofMain.h"
#include "ofxGui.h"
#include <rendering/camera/cameraManager.h>

/**
 * @class View3DPanel
 * @brief Panel UI pour les controles de la vue 3D
 *
 * Responsabilites :
 * - Basculer entre les modes de vue (2D, 3D, Quad)
 * - Controles de camera
 * - Options d'affichage (wireframe, bounding boxes)
 */
class View3DPanel {
public:
	View3DPanel();
	~View3DPanel() = default;

	void setup();
	void draw(float sideMenuWidth, float menuBarHeight);

	// Accesseurs d'etat
	bool isVisible() const { return isActive; }
	bool isShowBoundingBoxToggled() const { return sceneAssetsPanel.isBoundingBoxEnabled(); }
	bool isShowWireframeToggled() const { return sceneAssetsPanel.isWireframeEnabled(); }
	bool isQuadViewRequested() const { return quadViewRequested; }
	bool isGridEnabled() const { return sceneAssetsPanel.isGridEnabled(); }
	bool isAxesEnabled() const { return sceneAssetsPanel.isAxesEnabled(); }
	bool isNormalsEnabled() const { return sceneAssetsPanel.isNormalsEnabled(); }
	bool isLightingEnabled() const { return sceneAssetsPanel.isLightingEnabled(); }
	float getLightIntensity() const { return sceneAssetsPanel.getLightIntensity(); }
	ofColor getLightColor() const { return sceneAssetsPanel.getLightColor(); }

	bool isImport3DModelRequested() const { return sceneAssetsPanel.isImportRequested(); }
	bool isClear3DModelRequested() const { return sceneAssetsPanel.isClearRequested(); }

	// Controle du panel
	void show() { isActive = true; }
	void hide() { isActive = false; }
	void toggle() { isActive = !isActive; }

	// Reset state
	void reset();

	// Clear des requetes
	void clearRequests();

	void setCameraManager(CameraManager * manager) { cameraManager = manager; }
	void setSceneShapes(std::vector<Shape> * shapes) { sceneShapes = shapes; }

	std::vector<Shape> * getSceneShapes() { return sceneShapes; }
	CameraManager * getCameraManager() { return cameraManager; }
	RayTracingPanel & getRayTracingPanel() { return rayTracingPanel; }
	LightingPanel & getLightingPanel() { return lightingPanel; }

private:
	enum class Section {
		SceneAssets,
		Camera,
		Transformation,
		Geometry,
		Topology,
		Texture,
		RayTracing,
		Lighting
	};

	// Etat du panel
	bool isActive = false;
	bool quadViewRequested = false;
	Section activeSection = Section::SceneAssets;

	// Panel ofxGui
	ofxPanel view3DPanel;
	ofxPanel navigationPanel;
	ofxButton sceneAssetsButton;
	ofxButton cameraButton;
	ofxButton transformButton;
	ofxButton geometryButton;
	ofxButton topologyButton;
	ofxButton textureButton;
	ofxButton rayTracingButton;
	ofxButton lightingButton;

	// Boutons et labels
	ofxButton quadViewButton;
	ofxLabel viewTitle;

	CameraPanel cameraPanel;
	SceneAssetsPanel sceneAssetsPanel;
	Transformation3DPanel transformationPanel;
	Geometry3DPanel geometryPanel;
	Texture3DPanel texturePanel;
	TopologyPanel topologyPanel;
	RayTracingPanel rayTracingPanel;
	LightingPanel lightingPanel;
	CameraManager * cameraManager = nullptr;
	std::vector<Shape> * sceneShapes = nullptr;


	// Callbacks
	void onQuadViewPressed();
	void onSectionButtonPressed(Section section);
	void onSceneAssetsButton();
	void onCameraButton();
	void onTransformButton();
	void onGeometryButton();
	void onTopologyButton();
	void onTextureButton();
	void onRayTracingButton();
	void onLightingButton();


};
