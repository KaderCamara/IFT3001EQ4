#include "CameraManager.h"

void CameraManager::setup() {
	for (int i = 0; i < 5; i++) {
		cameras[i].setNearClip(0.1f);
		cameras[i].setFarClip(10000.0f);
	}

	//camera free pour faire ce qu'on veut
	for (int i = 0; i < 4; i++) {
		cameras[i].disableMouseInput();
		cameras[i].disableOrtho(); 
		cameras[i].enableOrtho();
	}
	cameras[4].enableMouseInput();
	cameras[4].disableOrtho();

	currentCam = &cameras[4];
}

void CameraManager::update() {
	
}

ofEasyCam & CameraManager::getCurrentCamera() {
	return *currentCam;
}

void CameraManager::setPerspectiveView(int viewIndex) {
	if (viewIndex >= 0 && viewIndex < 5) { // CHANGED: Now supports 0-4
	currentCam = &cameras[viewIndex];
	}
}

void CameraManager::lookAtScene(const std::vector<Shape> & shapes, bool isQuadView) {
	if (shapes.empty()) return;

	ofVec3f center;
	float radius;
	calculateSceneBounds(shapes, center, radius);

	float distance;
	if (isQuadView) {
		distance = radius * 3.0f;
		if (distance < 500.0f) distance = 500.0f;
	} else {
		distance = radius * 15.0f;
		if (distance < 1500.0f) distance = 1500.0f;
	}

	// Different ortho scales for different cameras
	float orthoScale = radius * 2.5f;
	if (orthoScale < 300.0f) orthoScale = 300.0f;

	// ✅ Larger scale for problematic cameras (1 and 3)
	float orthoScaleLarge = radius * 3.5f;
	if (orthoScaleLarge < 500.0f) orthoScaleLarge = 500.0f;

	ofLogNotice("CameraManager") << "Center: " << center << " Radius: " << radius
								 << " Distance: " << distance;

	// Camera 0: Top view - WORKING
	cameras[0].setPosition(center.x, center.y + distance, center.z);
	cameras[0].lookAt(center, ofVec3f(0, 0, -1));
	cameras[0].setScale(orthoScale);

	// Camera 1: Front view - PROBLEMATIC - try larger scale and different distance
	float frontDistance = distance * 1.2f; // ✅ Slightly farther
	cameras[1].setPosition(center.x, center.y, center.z + frontDistance);
	cameras[1].lookAt(center, ofVec3f(0, 1, 0));
	cameras[1].setScale(orthoScaleLarge); // ✅ Larger scale
	ofLogNotice("CameraManager") << "Camera 1 (Front): distance=" << frontDistance
								 << " scale=" << orthoScaleLarge;

	// Camera 2: Side view - WORKING
	cameras[2].setPosition(center.x + distance, center.y, center.z);
	cameras[2].lookAt(center, ofVec3f(0, 1, 0));
	cameras[2].setScale(orthoScale);

	// Camera 3: Bottom view - PROBLEMATIC - try larger scale
	cameras[3].setPosition(center.x, center.y - distance, center.z);
	cameras[3].lookAt(center, ofVec3f(0, 0, 1));
	cameras[3].setScale(orthoScaleLarge); // ✅ Larger scale
	ofLogNotice("CameraManager") << "Camera 3 (Bottom): scale=" << orthoScaleLarge;

	// Camera 4: Free camera
	cameras[4].setTarget(center);
	cameras[4].setDistance(distance);

	isDirty = false;
}


/* void CameraManager::calculateSceneBounds(const std::vector<Shape> & shapes,
	ofVec3f & center, float & radius) {
	if (shapes.empty()) {
		center = ofVec3f(0, 0, 0);
		radius = 100.0f;
		return;
	}

	ofVec3f minPt(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxPt(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	int totalVertices = 0;

	for (const auto & s : shapes) {
		const auto & vertices = s.mesh3D.getVertices();

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

	if (totalVertices == 0) {
		cout << "ERROR: No vertices found in any shape mesh!" << endl;
		center = ofVec3f(256, 256, 0);
		radius = 200.0f;
		return;
	}

	center = (minPt + maxPt) * 0.5f;

	cout << "Scene bounds: min(" << minPt << ") max(" << maxPt << ") center(" << center << ")" << endl;

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

	if (radius < 50.0f) {
		radius = 50.0f;
	}
}*/

void CameraManager::calculateSceneBounds(const std::vector<Shape> & shapes,
	ofVec3f & center, float & radius) {
	if (shapes.empty()) {
		center = ofVec3f(0, 0, 0);
		radius = 100.0f;
		return;
	}

	ofVec3f minPt(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxPt(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	int totalVertices = 0;

	for (const auto & s : shapes) {
		const auto & vertices = s.mesh3D.getVertices();
		if (vertices.empty()) {
			cout << "WARNING: Shape has no vertices in mesh!" << endl;
			continue;
		}

		// ✅ BUILD TRANSFORMATION MATRIX FOR THIS SHAPE
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(s.translation.x, s.translation.y, 0.0f));
		transform = glm::rotate(transform, glm::radians(s.rotation), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, glm::vec3(s.scale, s.scale, s.scale));

		totalVertices += vertices.size();

		for (const auto & v : vertices) {
			// ✅ TRANSFORM VERTEX TO WORLD SPACE
			glm::vec4 worldV = transform * glm::vec4(v, 1.0f);
			glm::vec3 transformedV = glm::vec3(worldV);

			minPt.x = std::min(minPt.x, transformedV.x);
			minPt.y = std::min(minPt.y, transformedV.y);
			minPt.z = std::min(minPt.z, transformedV.z);

			maxPt.x = std::max(maxPt.x, transformedV.x);
			maxPt.y = std::max(maxPt.y, transformedV.y);
			maxPt.z = std::max(maxPt.z, transformedV.z);
		}
	}

	if (totalVertices == 0) {
		cout << "ERROR: No vertices found in any shape mesh!" << endl;
		center = ofVec3f(256, 256, 0);
		radius = 200.0f;
		return;
	}

	center = (minPt + maxPt) * 0.5f;
	cout << "Scene bounds: min(" << minPt << ") max(" << maxPt << ") center(" << center << ")" << endl;

	radius = 0;
	for (const auto & s : shapes) {
		// ✅ BUILD TRANSFORMATION MATRIX AGAIN FOR RADIUS CALCULATION
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(s.translation.x, s.translation.y, 0.0f));
		transform = glm::rotate(transform, glm::radians(s.rotation), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, glm::vec3(s.scale, s.scale, s.scale));

		const auto & vertices = s.mesh3D.getVertices();
		for (const auto & v : vertices) {
			// ✅ TRANSFORM TO WORLD SPACE
			glm::vec4 worldV = transform * glm::vec4(v, 1.0f);
			glm::vec3 transformedV = glm::vec3(worldV);

			float dist = glm::distance(transformedV, glm::vec3(center.x, center.y, center.z));
			if (dist > radius) {
				radius = dist;
			}
		}
	}

	cout << "Scene radius: " << radius << endl;

	if (radius < 50.0f) {
		radius = 50.0f;
	}
}


void CameraManager::setCameraPosition(int index, const ofVec3f & pos) {
	if (index >= 0 && index < 5) cameras[index].setPosition(pos);
}

void CameraManager::setCameraLookAt(int index, const ofVec3f & target) {
	if (index >= 0 && index < 5) cameras[index].lookAt(target);
}

void CameraManager::setCameraOrtho(int index, bool ortho) {
	if (index < 0 || index >= 5) return;
	if (ortho)
		cameras[index].enableOrtho();
	else
		cameras[index].disableOrtho();
}
