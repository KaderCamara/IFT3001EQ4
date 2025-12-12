#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class Geometry3DPanel
 * @brief Panneau pour la gestion des primitives et maillages 3D.
 */
class Geometry3DPanel {
public:
	Geometry3DPanel() = default;
	~Geometry3DPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

private:
	ofxPanel geometryPanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	ofxLabel lblBounds;
	ofxToggle toggleBoundingBox;

	ofxLabel lblPrimitives;
	ofxToggle togglePrimitiveSetA;
	ofxToggle togglePrimitiveSetB;

	ofxLabel lblModels;
	ofxToggle toggleModelTypeA;
	ofxToggle toggleModelTypeB;
	ofxToggle toggleModelTypeC;
	ofxIntSlider variantCount;

	ofxLabel lblLod;
	ofxIntSlider lodLevel;
	ofxToggle toggleSimplifiedViewport;
};
