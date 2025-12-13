#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class Primitives3DPanel
 * @brief Panneau pour dessiner des primitives 3D natives OpenFrameworks/OpenGL avec textures et matériaux.
 */
class Primitives3DPanel {
public:
	Primitives3DPanel() = default;
	~Primitives3DPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

	// Accesseurs pour récupérer les paramètres sélectionnés
	std::string getSelectedPrimitive() const { return selectedPrimitive; }
	bool isDrawPrimitiveRequested() const { return drawPrimitiveRequested; }
	void clearDrawPrimitiveRequest() { drawPrimitiveRequested = false; }

	// Paramètres de la primitive
	float getPrimitiveSize() const { return primitiveSize; }
	int getPrimitiveResolution() const { return primitiveResolution; }

	// Paramètres de texture
	bool useTexture() const { return enableTexture; }
	std::string getTextureType() const { return textureType; }

	// Paramètres de matériau
	ofColor getDiffuseColor() const { return diffuseColor; }
	ofColor getSpecularColor() const { return specularColor; }
	float getShininess() const { return shininess; }
	float getMetallic() const { return metallic; }
	float getRoughness() const { return roughness; }

private:
	ofxPanel primitivesPanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	// Section Primitives
	ofxLabel lblPrimitives;
	ofxButton btnSphere;
	ofxButton btnBox;
	ofxButton btnCylinder;
	ofxButton btnCone;
	ofxButton btnPlane;
	ofxButton btnIcosahedron;

	// Paramètres de primitive
	ofxLabel lblPrimitiveParams;
	ofParameter<float> primitiveSize;
	ofParameter<int> primitiveResolution;

	// Section Textures
	ofxLabel lblTextures;
	ofParameter<bool> enableTexture;
	ofxButton btnCheckerTexture;
	ofxButton btnGradientTexture;
	ofxButton btnNoiseTexture;
	ofxButton btnLoadTexture;

	// Section Matériaux
	ofxLabel lblMaterials;
	ofParameter<ofColor> diffuseColor;
	ofParameter<ofColor> specularColor;
	ofParameter<float> shininess;
	ofParameter<float> metallic;
	ofParameter<float> roughness;

	// État interne
	std::string selectedPrimitive = "none";
	std::string textureType = "none";
	bool drawPrimitiveRequested = false;

	// Callbacks
	void onSpherePressed();
	void onBoxPressed();
	void onCylinderPressed();
	void onConePressed();
	void onPlanePressed();
	void onIcosahedronPressed();
	void onCheckerTexturePressed();
	void onGradientTexturePressed();
	void onNoiseTexturePressed();
	void onLoadTexturePressed();
};
