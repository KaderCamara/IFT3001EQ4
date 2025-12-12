#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class TopologyPanel
 * @brief Controle des operations de topologie et courbes.
 */
class TopologyPanel {
public:
	TopologyPanel() = default;
	~TopologyPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

private:
	ofxPanel topologyPanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	ofxLabel lblTriangulation;
	ofxToggle toggleTriangulation;
	ofxToggle toggleVoronoi;

	ofxLabel lblCurves;
	ofxToggle toggleBezierCurve;
	ofxToggle toggleBSplineCurve;

	ofxLabel lblSurfaces;
	ofxToggle toggleBezierSurface;
	ofxToggle toggleCoonsSurface;

	ofxLabel lblDisplacement;
	ofxToggle toggleHeightMap;
	ofxToggle toggleNormalMap;

	ofxLabel lblAnimation;
	ofxToggle toggleAnimationCurve;
	ofxIntSlider animationSamples;
};
