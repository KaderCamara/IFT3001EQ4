#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class Texture3DPanel
 * @brief Controle des textures, filtrages et HDRI.
 */
class Texture3DPanel {
public:
	Texture3DPanel() = default;
	~Texture3DPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

private:
	ofxPanel texturePanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	ofxLabel lblCoordinates;
	ofxToggle toggleUVs;
	ofxToggle toggleTriplanar;

	ofxLabel lblFiltering;
	ofxToggle toggleNearest;
	ofxToggle toggleLinear;
	ofxToggle toggleMipMap;

	ofxLabel lblToneMapping;
	ofxToggle toggleToneMapping;
	ofxToggle toggleACES;

	ofxLabel lblCubemap;
	ofxToggle toggleCubemapReflection;
	ofxToggle toggleCubemapRefraction;

	ofxLabel lblProcedural;
	ofxToggle toggleProceduralTexture;
	ofxToggle toggleTextureNoise;
};
