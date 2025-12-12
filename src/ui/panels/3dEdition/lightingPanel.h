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

	bool isPBREnabled() const { return static_cast<ofParameter<bool>&>(const_cast<ofxToggle&>(togglePBR).getParameter()).get(); }
	float getMetallic() const { return static_cast<ofParameter<float>&>(const_cast<ofxFloatSlider&>(metallicity).getParameter()).get(); }
	float getRoughness() const { return static_cast<ofParameter<float>&>(const_cast<ofxFloatSlider&>(roughness).getParameter()).get(); }
	float getIOR() const { return static_cast<ofParameter<float>&>(const_cast<ofxFloatSlider&>(ior).getParameter()).get(); }
	std::vector<ofLight> getActiveLights();


private:
	ofxPanel lightingPanel;

	ofxLabel lblTitle;
	ofxToggle toggleEnvironmentMap;
	ofxToggle toggleHDRI;
	ofxToggle toggleShadows;
	ofxToggle toggleAmbientOcclusion;
	ofxToggle toggleBloom;

	// Modele d'illumination classique
	ofxLabel lblClassic;
	ofxToggle toggleLambert;
	ofxToggle toggleGouraud;
	ofxToggle togglePhong;
	ofxToggle toggleBlinnPhong;
	ofxIntSlider materialCount;
	ofxToggle togglePointType;
	ofxToggle toggleDirectionalType;
	ofxToggle toggleSpotType;
	ofxToggle toggleAreaType;

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

	// Illumination moderne / PBR
	ofxLabel lblModern;
	ofxToggle togglePBR;
	ofxFloatSlider metallicity;
	ofxFloatSlider roughness;
	ofxToggle toggleMicrofacets;
	ofxToggle toggleEnvLighting;
	ofxFloatSlider ior;

	ofxLabel lblColorControls;
	ofxFloatSlider exposureSlider;
	ofxFloatSlider temperatureSlider;
	ofxFloatSlider contrastSlider;

	float enforcedX = 0.f;
	float enforcedY = 0.f;
	float enforcedWidth = 220.f;
	bool visible = true;
};
