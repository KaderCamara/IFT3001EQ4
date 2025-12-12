#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class VectorEditionPanel
 * @brief Outils avances pour l'edition 2D conforme aux criteres du projet.
 */
class VectorEditionPanel {
public:
	VectorEditionPanel() = default;
	~VectorEditionPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

private:
	ofxPanel vectorPanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 320.0f;
	bool visible = true;

	ofxLabel lblCursor;
	ofxToggle toggleDynamicCursor;
	ofxToggle toggleCursorFeedback;

	ofxLabel lblDrawingTools;
	ofxFloatSlider lineThickness;
	ofxFloatSlider outlineOpacity;
	ofxFloatSlider fillOpacity;

	ofxLabel lblPrimitives;
	ofxToggle toggleVectorPoint;
	ofxToggle toggleVectorLine;
	ofxToggle toggleVectorCurve;
	ofxToggle toggleVectorPolygon;

	ofxLabel lblTransforms;
	ofxToggle toggleTranslate;
	ofxToggle toggleRotate;
	ofxToggle toggleScale;
	ofxToggle toggleShear;

	ofxLabel lblForms;
	ofxToggle toggleTextShape;
	ofxToggle toggleIconShape;
	ofxToggle toggleGroupedEditing;
};
