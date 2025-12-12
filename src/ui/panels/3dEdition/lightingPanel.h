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

	bool isEnvironmentMapEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleEnvironmentMap).getParameter()).get();}
	bool isHDRIEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleHDRI).getParameter()).get();}
	bool isShadowsEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleShadows).getParameter()).get();}
	bool isAmbientOcclusionEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleAmbientOcclusion).getParameter()).get();}
	bool isBloomEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleBloom).getParameter()).get();}

	// Classic Illumination
	bool isLambertEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleLambert).getParameter()).get();}
	bool isGouraudEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleGouraud).getParameter()).get();}
	bool isPhongEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(togglePhong).getParameter()).get();}
	bool isBlinnPhongEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleBlinnPhong).getParameter()).get();}
	int getMaterialCount() const {return static_cast<ofParameter<int> &>(const_cast<ofxIntSlider &>(materialCount).getParameter()).get();}

	//non realistic illumination
	bool isFlatEnabled() const { return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleFlat).getParameter()).get(); }
	bool isCelEnabled() const { return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleCel).getParameter()).get(); }
	bool isGoochEnabled() const { return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleGooch).getParameter()).get(); }
	

	// Light Types
	bool isPointTypeEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(togglePointType).getParameter()).get();}
	bool isDirectionalTypeEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleDirectionalType).getParameter()).get();}
	bool isSpotTypeEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleSpotType).getParameter()).get();}
	bool isAreaTypeEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleAreaType).getParameter()).get();}

	// Sun Light
	bool isSunLightEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleSunLight).getParameter()).get();}
	float getSunIntensity() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(sunIntensity).getParameter()).get();}
	float getSunAzimuth() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(sunAzimuth).getParameter()).get();}
	float getSunElevation() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(sunElevation).getParameter()).get();}

	// Point Light
	bool isPointLightEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(togglePointLight).getParameter()).get();}
	float getPointIntensity() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(pointIntensity).getParameter()).get();}

	// Spot Light
	bool isSpotLightEnabled() const { return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleSpotLight).getParameter()).get(); }
	float getSpotIntensity() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(spotIntensity).getParameter()).get();}
	float getSpotAngle() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(spotAngle).getParameter()).get();}

	// PBR (Modern Illumination)
	// Note: isPBREnabled, getMetallic, getRoughness, getIOR already exist in your code!
	bool isMicrofacetsEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleMicrofacets).getParameter()).get();}
	bool isEnvLightingEnabled() const {return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleEnvLighting).getParameter()).get();}

	// Color & Tone
	float getExposure() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(exposureSlider).getParameter()).get();}
	float getTemperature() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(temperatureSlider).getParameter()).get();}
	float getContrast() const {return static_cast<ofParameter<float> &>(const_cast<ofxFloatSlider &>(contrastSlider).getParameter()).get();}

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

	//animated shading
	ofxLabel lblNonRealistic;
	ofxToggle toggleFlat;
	ofxToggle toggleCel;
	ofxToggle toggleGooch;

	float enforcedX = 0.f;
	float enforcedY = 0.f;
	float enforcedWidth = 220.f;
	bool visible = true;
};
