// Renderer.cpp
#include "renderer.h"

void Renderer::setup() {
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);
	cameraManager.setup();
}

void Renderer::draw() {
	if (view3D) {
		draw3D();
	}
	else if (view2D) {
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
		sceneGraph.removeShape(shapeSelectedIndex);
		shapeSelectedIndex = -1;
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

void Renderer::view3DMode() {
	view3D = true;
	view2D = false; // ADD THIS - turn off 2D when entering 3D
	cameraManager.markDirty();
}

void Renderer::view2DMode() {
	view2D = true;
	view3D = false;
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
		cameraManager.lookAtScene(sceneGraph.shapes);
	}

	cameraManager.getCurrentCamera().begin();

	// Draw solid meshes
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw(); // Changed from drawWireframe()
	}

	cameraManager.getCurrentCamera().end();
}

void Renderer::mousePressed(int x, int y, int button) {
	if (currentShape != "none") {
		startPoint.set(x, y);
		drawing = true;
	}
	if (selecting) {
		shapeSelectedIndex = sceneGraph.selectShapeAt(x, y);
		if (shapeSelectedIndex != -1) {
			shapeSelected = true;
		}
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
