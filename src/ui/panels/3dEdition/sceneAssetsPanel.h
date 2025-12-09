#pragma once

#include "ofMain.h"
#include "ofxGui.h"

// Panel dédié aux assets et aux options de viewport 3D
class SceneAssetsPanel {
public:
	SceneAssetsPanel() = default;
	~SceneAssetsPanel() = default;

	void setup();
	void draw(float x, float y, float width);
	void clearRequests();

	bool isVisible() const { return visible; }
	void show() { visible = true; }
	void hide() { visible = false; }

	// Accesseurs d'actions
	bool isImportRequested() const { return import3DRequested; }
	bool isClearRequested() const { return clear3DRequested; }

	// Options d'affichage
	bool isGridEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleGrid)); }
	bool isAxesEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleAxes)); }
	bool isWireframeEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleWireframe)); }
	bool isBoundingBoxEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleBoundingBoxes)); }
	bool isNormalsEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleNormals)); }

	// Lighting
	bool isLightingEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleLighting)); }
	float getLightIntensity() const { return static_cast<float>(const_cast<ofxFloatSlider&>(lightIntensity)); }
	ofColor getLightColor() const { return static_cast<ofColor>(const_cast<ofxColorSlider&>(lightColor)); }

private:
	bool visible = true;

	bool import3DRequested = false;
	bool clear3DRequested = false;

	ofxPanel panel;
	ofxButton import3DButton;
	ofxButton clear3DButton;

	ofxLabel viewportTitle;
	ofxToggle toggleGrid;
	ofxToggle toggleAxes;
	ofxToggle toggleWireframe;
	ofxToggle toggleBoundingBoxes;
	ofxToggle toggleNormals;

	ofxLabel lightingTitle;
	ofxToggle toggleLighting;
	ofxFloatSlider lightIntensity;
	ofxColorSlider lightColor;

	void onImport3D();
	void onClear3D();
	void onLightingToggle(bool & value);
};
