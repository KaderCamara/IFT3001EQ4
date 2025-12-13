#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class Renderer;

/**
 * @class Texture3DPanel
 * @brief Controle des textures, filtrages et HDRI.
 */
class Texture3DPanel {
public:
	Texture3DPanel() = default;
	~Texture3DPanel() = default;

	void setup();
	void update();
	void draw();

	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();

	void setRenderer(Renderer * r) {
		renderer = r;
		ofLogNotice("Texture3DPanel") << "Renderer connected";
	}


	void setVisible(bool v) { visible = v; }
	bool isVisible() const { return visible; }

private:
	ofxPanel texturePanel;

	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	// ========== COORDONNÉES ==========
	ofxLabel lblCoordinates;
	ofxToggle toggleUVs;
	ofxToggle toggleTriplanar;

	// ========== FILTRAGE ==========
	ofxLabel lblFiltering;
	ofxToggle toggleNearest;
	ofxToggle toggleLinear;
	ofxToggle toggleMipMap;

	// ========== TONE MAPPING ==========
	ofxLabel lblToneMapping;
	ofxToggle toggleToneMapping;
	ofxToggle toggleACES;

	// ========== CUBEMAP ==========
	ofxLabel lblCubemap;
	ofxToggle toggleCubemapReflection;
	ofxToggle toggleCubemapRefraction;

	// ========== PROCEDURAL ==========
	ofxLabel lblProcedural;
	ofxToggle toggleProceduralTexture;
	ofxToggle toggleTextureNoise;

	// ========== TEXTURE PROCÉDURALE ==========
	ofTexture proceduralTexture;
	bool proceduralTextureActivePrev = false;

	Renderer * renderer = nullptr;
};
