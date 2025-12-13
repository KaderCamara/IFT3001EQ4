#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class RayTracingPanel
 * @brief Controle des options de lancer de rayon.
 */
class RayTracingPanel {
public:
	RayTracingPanel() = default;
	~RayTracingPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

	bool isGlobalIlluminationEnabled() const;

	int getBounceCount() const;

private:
	ofxPanel rayPanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	ofxLabel lblCore;
	ofxToggle toggleIntersection;
	ofxToggle toggleReflection;
	ofxToggle toggleRefraction;
	ofxToggle toggleShadows;

	ofxLabel lblGi;
	ofxToggle toggleGlobalIllumination;
	ofxIntSlider bounceCount;
};
