#include "CameraManager.h"

void CameraManager::setup() {
	// CHANGED: Now setup 5 cameras (added free camera at index 4)
	for (int i = 0; i < 5; i++) {
		cameras[i].setNearClip(0.1f);
		cameras[i].setFarClip(10000.0f);
	}

	// NEW: Disable mouse control for fixed cameras (0-3)
	// Only the free camera (4) allows mouse rotation
	for (int i = 0; i < 4; i++) {
		cameras[i].disableMouseInput();
		// FIX: Use orthographic projection for fixed views (no distortion)
		cameras[i].disableOrtho(); // Disable first
		cameras[i].enableOrtho(); // Then enable for proper setup
	}
	cameras[4].enableMouseInput(); // Free camera has mouse control
	cameras[4].disableOrtho(); // Perspective for free camera

	currentCam = &cameras[4]; // CHANGED: Default to free camera instead of top
}

void CameraManager::update() {
	// You can add camera animations or smooth transitions here if needed
}

// NEW: Return reference to current camera
ofEasyCam & CameraManager::getCurrentCamera() {
	return *currentCam;
}

void CameraManager::setPerspectiveView(int viewIndex) {
	if (viewIndex >= 0 && viewIndex < 5) { // CHANGED: Now supports 0-4
		currentCam = &cameras[viewIndex];
	}
}

// CHANGED: Complete rewrite using proper 3D bounding calculation
void CameraManager::lookAtScene(const std::vector<Shape> & shapes) {
	if (shapes.empty()) return;

	// Calculate scene center and bounding radius
	ofVec3f center;
	float radius;
	calculateSceneBounds(shapes, center, radius);

	// Add padding so shapes aren't too close to edge
	float distance = radius * 10.0f;
	if (distance < 1000.0f) distance = 1000.0f;

	// Position each fixed camera at appropriate angle
	// Camera 0: Top view (looking down -Y axis)
	cameras[0].setPosition(center.x, center.y + distance, center.z);
	cameras[0].lookAt(center);

	// Camera 1: Front view (looking from -Z axis)
	cameras[1].setPosition(center.x, center.y, center.z + distance);
	cameras[1].lookAt(center);

	// Camera 2: Side view (looking from +X axis)
	cameras[2].setPosition(center.x + distance, center.y, center.z);
	cameras[2].lookAt(center);

	// Camera 3: Bottom view (looking up +Y axis)
	cameras[3].setPosition(center.x, center.y - distance, center.z);
	cameras[3].lookAt(center);

	// Camera 4: Free camera - ONLY set target and distance, don't set position!
	// This allows mouse control to work
	cameras[4].setTarget(center);
	cameras[4].setDistance(distance);
	// DON'T call setPosition or lookAt - let the user control it!

	// Mark as updated
	isDirty = false;
}

// NEW: Helper function to calculate proper 3D bounding sphere
// This uses actual mesh vertices instead of just start/end points
void CameraManager::calculateSceneBounds(const std::vector<Shape> & shapes,
	ofVec3f & center, float & radius) {
	// SAFETY CHECK: Make sure we have shapes with vertices
	if (shapes.empty()) {
		center = ofVec3f(0, 0, 0);
		radius = 100.0f;
		return;
	}

	// Find axis-aligned bounding box (AABB)
	ofVec3f minPt(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxPt(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	int totalVertices = 0;

	for (const auto & s : shapes) {
		// CHANGED: Use actual mesh vertices instead of start/end points
		// This properly accounts for 3D depth
		const auto & vertices = s.mesh3D.getVertices();

		// DEBUG: Print vertex count to help diagnose issues
		if (vertices.empty()) {
			cout << "WARNING: Shape has no vertices in mesh!" << endl;
			continue;
		}

		totalVertices += vertices.size();

		for (const auto & v : vertices) {
			minPt.x = std::min(minPt.x, v.x);
			minPt.y = std::min(minPt.y, v.y);
			minPt.z = std::min(minPt.z, v.z);

			maxPt.x = std::max(maxPt.x, v.x);
			maxPt.y = std::max(maxPt.y, v.y);
			maxPt.z = std::max(maxPt.z, v.z);
		}
	}

	// SAFETY CHECK: If no vertices found, use default
	if (totalVertices == 0) {
		cout << "ERROR: No vertices found in any shape mesh!" << endl;
		center = ofVec3f(256, 256, 0); // Middle of 512x512 window
		radius = 200.0f;
		return;
	}

	// Center is midpoint of bounding box
	center = (minPt + maxPt) * 0.5f;

	// DEBUG: Print bounds info
	cout << "Scene bounds: min(" << minPt << ") max(" << maxPt << ") center(" << center << ")" << endl;

	// CHANGED: Calculate bounding sphere radius
	// This is the maximum distance from center to any vertex
	radius = 0;
	for (const auto & s : shapes) {
		const auto & vertices = s.mesh3D.getVertices();
		for (const auto & v : vertices) {
			float dist = (v - center).length();
			if (dist > radius) {
				radius = dist;
			}
		}
	}

	cout << "Scene radius: " << radius << endl;

	// Ensure minimum radius so camera doesn't get too close
	if (radius < 50.0f) {
		radius = 50.0f;
	}
}
