// CameraManager.h
//fichier qui gere les cameras etc
#pragma once
#include "../objects/shape.h"
#include "ofMain.h"
#include <vector>

class CameraManager {
public:
	void setup();
	void update();

	
	ofEasyCam & getCurrentCamera();

	void setPerspectiveView(int viewIndex);
	void lookAtScene(const std::vector<Shape> & shapes, bool isQuadView = false);
	void markClean() { isDirty = false; }
	void markDirty() { isDirty = true; }
	bool needsUpdate() const { return isDirty; }

	void setCameraPosition(int index, const ofVec3f & pos);
	void setCameraLookAt(int index, const ofVec3f & target);
	void setCameraOrtho(int index, bool ortho);

	int getCurrentCameraIndex() const { return currentCameraIndex; }

private:
	ofEasyCam cameras[5];
	ofEasyCam * currentCam;
	int currentCameraIndex = 4;

	// NEW: Track if scene changed
	bool isDirty = true;

	void calculateSceneBounds(const std::vector<Shape> & shapes,
		ofVec3f & center, float & radius);
};
