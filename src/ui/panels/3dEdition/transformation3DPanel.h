#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class Transformation3DPanel
 * @brief Gestion des transformations et de la hierarchie de scene pour la vue 3D.
 */
class Transformation3DPanel {
public:
	Transformation3DPanel() = default;
	~Transformation3DPanel() = default;

	void setup();
	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();
	void draw();

	// Accesseurs utilitaires
	bool isSceneGraphEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleSceneGraph)); }
	bool isMultipleSelectionEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleMultipleSelection)); }
	bool isSnapEnabled() const { return static_cast<bool>(const_cast<ofxToggle&>(toggleSnapping)); }

private:
	ofxPanel transformPanel;
	float enforcedX = 0.0f;
	float enforcedY = 0.0f;
	float enforcedWidth = 300.0f;
	bool visible = true;

	ofxLabel lblSceneGraph;
	ofxToggle toggleSceneGraph;
	ofxToggle toggleMultipleSelection;
	ofxToggle toggleParenting;

	ofxLabel lblTransforms;
	ofxToggle toggleTranslate;
	ofxToggle toggleRotate;
	ofxToggle toggleScale;
	ofxToggle toggleGizmo;

	ofxLabel lblHistory;
	ofxButton btnUndo;
	ofxButton btnRedo;

	ofxLabel lblSnapping;
	ofxToggle toggleSnapping;
	ofxFloatSlider snapTranslation;
	ofxFloatSlider snapRotation;
	ofxFloatSlider snapScale;
};
