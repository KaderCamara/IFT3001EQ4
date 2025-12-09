#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <string>
#include <vector>

// Panneau listant et organisant les objets de la scene 3D
class SceneHierarchyPanel {
public:
	SceneHierarchyPanel();
	~SceneHierarchyPanel();

	void setup();
	void update();
	void draw();

	void setPosition(float x, float y);
	void setWidth(float w);
	float getHeight();

	void show();
	void hide();
	bool isVisible() const;

private:
	ofxPanel hierarchyPanel;

	ofxLabel lblTitle;
	ofxButton btnAddEmpty;
	ofxButton btnAddPrimitive;
	ofxButton btnAddLight;
	ofxButton btnDuplicate;
	ofxButton btnDelete;

	ofxLabel lblFilters;
	ofxToggle toggleShowMeshes;
	ofxToggle toggleShowLights;
	ofxToggle toggleShowCameras;
	ofxToggle toggleLockSelection;
	ofxToggle toggleSoloSelection;

	ofxLabel lblObjects;
	ofParameter<bool> cameraEntry { "Camera 01", false };
	ofParameter<bool> meshEntry { "Mesh 01", false };
	ofParameter<bool> lightEntry { "Directional Light", false };
	ofParameter<bool> helperEntry { "Empty Helper", false };

	ofxLabel lblParenting;
	ofxToggle toggleSnapToGrid;
	ofxToggle toggleInheritTransform;
	ofxToggle toggleShowGizmos;

	float enforcedX = 0.f;
	float enforcedY = 0.f;
	float enforcedWidth = 220.f;
	bool visible = true;
};
