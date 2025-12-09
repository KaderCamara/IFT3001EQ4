#pragma once

#include "ofMain.h"
#include "ofxGui.h"

	// Panneau pour configurer l'environnement lumineux 3D
	class LightingPanel {
public:
	LightingPanel();
	~LightingPanel();

	void setup();
	void update();
	void draw();

	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();

	void show();
	void hide();
	bool isVisible() const;

private:
	ofxPanel lightingPanel;

	ofxLabel lblTitle;
	ofxToggle toggleEnvironmentMap;
	ofxToggle toggleHDRI;
	ofxToggle toggleShadows;
	ofxToggle toggleAmbientOcclusion;
	ofxToggle toggleBloom;

	ofxLabel lblSunLight;
	ofxToggle toggleSunLight;
	ofxFloatSlider sunIntensity;
	ofxFloatSlider sunAzimuth;
	ofxFloatSlider sunElevation;

	ofxLabel lblFillLights;
	ofxToggle togglePointLight;
	ofxFloatSlider pointIntensity;
	ofxToggle toggleSpotLight;
	ofxFloatSlider spotIntensity;
	ofxFloatSlider spotAngle;

	ofxLabel lblColorControls;
	ofxFloatSlider exposureSlider;
	ofxFloatSlider temperatureSlider;
	ofxFloatSlider contrastSlider;

	float enforcedX = 0.f;
	float enforcedY = 0.f;
	float enforcedWidth = 220.f;
	bool visible = true;
};
