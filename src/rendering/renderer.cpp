// Renderer.cpp
#include "renderer.h"
#include <cfloat>

bool g_showBoundingBox = false;
bool g_showWireframe = false;

void Renderer::setup() {
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);
	cameraManager.setup();
}

void Renderer::draw() {
	if (viewQuad) {
		drawQuadView();
	} else if (view3D) {
		draw3D();
	} else if (view2D) {
		sceneGraph.draw();
		if (currentShape != "none") {
			shapeManager.draw();
		}
	}
}

void Renderer::save() {
	sceneGraph.addShape(shapeManager.getCurrentShape());
	// NEW: Mark camera as needing update when scene changes
	cameraManager.markDirty();
}

void Renderer::deleteShape() {
	if (shapeSelected) {
		sceneGraph.removeSelectedShapes();
		shapeSelected = false;
		// NEW: Mark camera as needing update when scene changes
		cameraManager.markDirty();
	} else {
		cout << "no shape was selected" << endl;
	}
}

void Renderer::selectingModeOn() {
	selecting = true;
	shapeManager.deleteCurrentShapeToDraw();
}

void Renderer::selectingModeOff() {
	selecting = false;
}

void Renderer::viewQuadMode() {
	viewQuad = true;
	view3D = false;
	view2D = false;
	cameraManager.markDirty();
}

void Renderer::view3DMode() {
	view3D = true;
	view2D = false;
	viewQuad = false;
	cameraManager.markDirty();
}

void Renderer::view2DMode() {
	view2D = true;
	view3D = false;
	viewQuad = false;
}

// CHANGED: Only recalculate camera when scene has changed
void Renderer::draw3D() {
	// Convert all shapes to 3D first
	for (auto & s : sceneGraph.shapes) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s);
		}
	}

	// Update camera if needed
	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, false);
	}

	cameraManager.getCurrentCamera().begin();

	// Draw solid meshes
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		// Wireframe ou solide
		if (g_showWireframe) {
			s.mesh3D.drawWireframe();
		} else {
			s.mesh3D.draw();
		}

		// Bounding box
		if (g_showBoundingBox) {
			ofNoFill();
			ofSetColor(ofColor::green);
			ofSetLineWidth(1);
			ofRectangle bbox = getMeshBoundingBox(s.mesh3D);
			ofDrawRectangle(bbox);
		}
	}

	cameraManager.getCurrentCamera().end();
}

void Renderer::mousePressed(int x, int y, int button) {
	if (currentShape != "none") {
		startPoint.set(x, y);
		drawing = true;
	}
	if (selecting) {
		sceneGraph.selectShapeAt(x, y, ofGetKeyPressed(OF_KEY_CONTROL) || ofGetKeyPressed(OF_KEY_COMMAND));
		shapeSelected = !sceneGraph.selectedIndices.empty();
	}
}

void Renderer::mouseReleased(int x, int y, int button) {
	if (drawing) {
		endPoint.set(x, y);
		shapeManager.drawShape(currentShape, startPoint, endPoint);
		drawing = false;
	}
}

// NEW: Add keyboard controls for camera switching
void Renderer::keyPressed(int key) {
	if (viewQuad) {
		return; // Early exit
	}
	// Switch camera views with number keys
	if (key == '1') {
		cameraManager.setPerspectiveView(0); // Top view
		cout << "Camera: Top view" << endl;
	} else if (key == '2') {
		cameraManager.setPerspectiveView(1); // Front view
		cout << "Camera: Front view" << endl;
	} else if (key == '3') {
		cameraManager.setPerspectiveView(2); // Side view
		cout << "Camera: Side view" << endl;
	} else if (key == '4') {
		cameraManager.setPerspectiveView(3); // Bottom view
		cout << "Camera: Bottom view" << endl;
	} else if (key == '5') {
		cameraManager.setPerspectiveView(4); // Free rotation view
		cout << "Camera: Free view (drag to rotate)" << endl;
	}

	// You can add more keys for other functionality here
}

void Renderer::drawQuadView() {
	for (auto & s : sceneGraph.shapes) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s);
		}
	}

	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, true);
	}

	// FIX: Use width and height, not x and y!
	int w = drawingArea.width; // CHANGED from drawingArea.x
	int h = drawingArea.height; // CHANGED from drawingArea.y
	int halfW = w / 2;
	int halfH = h / 2;

	// FIX: Offset viewports by drawingArea position
	int offsetX = drawingArea.x;
	int offsetY = drawingArea.y;

	//camera top left
	ofViewport(offsetX, offsetY, halfW, halfH);
	cameraManager.setPerspectiveView(0);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	// Draw label
	ofSetColor(0);
	ofDrawBitmapString("Top View", offsetX + 10, offsetY + 20);

	//camera top right
	ofViewport(offsetX + halfW, offsetY, halfW, halfH);
	cameraManager.setPerspectiveView(1);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Front View", offsetX + halfW + 10, offsetY + 20);

	//camera bottom left
	ofViewport(offsetX, offsetY + halfH, halfW, halfH);
	cameraManager.setPerspectiveView(2);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Side View", offsetX + 10, offsetY + halfH + 20);

	//camera bottom right
	ofViewport(offsetX + halfW, offsetY + halfH, halfW, halfH);
	cameraManager.setPerspectiveView(3);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Bottom View", offsetX + halfW + 10, offsetY + halfH + 20);

	// Reset viewport to full screen
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());

	// Draw borders between viewports
	ofPushStyle();
	ofSetColor(100);
	ofSetLineWidth(2);
	ofDrawLine(offsetX + halfW, offsetY, offsetX + halfW, offsetY + h); // Vertical line
	ofDrawLine(offsetX, offsetY + halfH, offsetX + w, offsetY + halfH); // Horizontal line
	ofPopStyle();
}

ofRectangle Renderer::getMeshBoundingBox(const ofMesh & mesh) {
	if (mesh.getNumVertices() == 0) return ofRectangle();
	glm::vec3 min = mesh.getVertex(0);
	glm::vec3 max = mesh.getVertex(0);
	for (std::size_t i = 1; i < mesh.getNumVertices(); ++i) {
		const glm::vec3 & v = mesh.getVertex(i);
		min.x = std::min(min.x, v.x);
		min.y = std::min(min.y, v.y);
		min.z = std::min(min.z, v.z);
		max.x = std::max(max.x, v.x);
		max.y = std::max(max.y, v.y);
		max.z = std::max(max.z, v.z);
	}
	return ofRectangle(min.x, min.y, max.x - min.x, max.y - min.y);
}
