// CameraManager.h
#pragma once
#include "../objects/shape.h"
#include "ofMain.h"
#include <vector>

class CameraManager {
public:
	void setup();
	void update();

	// CHANGED: Added return type reference for getCurrentCamera
	ofEasyCam & getCurrentCamera();

	// Set which camera perspective to use (0=top, 1=front, 2=side, 3=bottom, 4=free)
	void setPerspectiveView(int viewIndex);

	// CHANGED: Now only recalculates when called (not every frame)
	// Call this when shapes are added/removed/modified
	void lookAtScene(const std::vector<Shape> & shapes, bool isQuadView = false);

	// NEW: Check if camera needs updating
	bool needsUpdate() const { return isDirty; }
	void markClean() { isDirty = false; }
	void markDirty() { isDirty = true; }

private:
	// CHANGED: Added 5th camera for free rotation
	ofEasyCam cameras[5];
	ofEasyCam * currentCam;

	// NEW: Track if scene changed
	bool isDirty = true;

	// CHANGED: Improved bounding calculation using actual mesh vertices
	void calculateSceneBounds(const std::vector<Shape> & shapes,
		ofVec3f & center, float & radius);
};
