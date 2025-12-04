// SceneController.cpp
// Implémentation du contrôleur de scène
#include "SceneController.h"
#include <iostream>

SceneController::SceneController() {
}

void SceneController::setup() {
	cameraManager.setup();
	ofLogNotice("SceneController") << "Setup complete";
}

// ========== GESTION DES VUES ==========

void SceneController::setView2DMode() {
	view2D = true;
	view3D = false;
	viewQuad = false;
	cameraManager.markDirty();

	ofLogNotice("SceneController") << "Switched to 2D view";
}

void SceneController::setView3DMode() {
	view3D = true;
	view2D = false;
	viewQuad = false;

	// Convertir toutes les formes 2D en 3D
	convertShapesTo3D();

	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Switched to 3D view";
}

void SceneController::setViewQuadMode() {
	viewQuad = true;
	view3D = false;
	view2D = false;

	// Convertir toutes les formes 2D en 3D
	convertShapesTo3D();

	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Switched to Quad view";
}

void SceneController::convertShapesTo3D() {
	for (auto & s : sceneGraph.shapes) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s);
		}
	}
}

// ========== GESTION DES MODES D'INTERACTION ==========

void SceneController::enableSelectingMode() {
	selecting = true;
	shapeManager.deleteCurrentShapeToDraw();
	ofLogNotice("SceneController") << "Selecting mode enabled";
}

void SceneController::disableSelectingMode() {
	selecting = false;
	ofLogNotice("SceneController") << "Selecting mode disabled";
}

// ========== OPÉRATIONS SUR LES FORMES ==========

void SceneController::saveCurrentShape() {
	sceneGraph.addShape(shapeManager.getCurrentShape());
	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Shape saved to scene";
}

void SceneController::deleteSelectedShapes() {
	if (shapeSelected) {
		sceneGraph.removeSelectedShapes();
		shapeSelected = false;
		cameraManager.markDirty();
		ofLogNotice("SceneController") << "Selected shapes deleted";
	} else {
		ofLogWarning("SceneController") << "No shape was selected for deletion";
	}
}

// ========== GESTION DES ENTRÉES ==========

void SceneController::handleMousePressed(int x, int y, int button, const ofRectangle & drawingArea) {
	// Vérifier si on est dans la zone de dessin
	if (!drawingArea.inside(x, y)) {
		return;
	}

	// Mode dessin de forme
	if (currentShape != "none") {
		startPoint.set(x, y);
		drawing = true;
		ofLogVerbose("SceneController") << "Started drawing shape at (" << x << ", " << y << ")";
	}

	// Mode sélection
	if (selecting) {
		bool multiSelect = ofGetKeyPressed(OF_KEY_CONTROL) || ofGetKeyPressed(OF_KEY_COMMAND);
		sceneGraph.selectShapeAt(x, y, multiSelect);
		shapeSelected = !sceneGraph.selectedIndices.empty();

		if (shapeSelected) {
			ofLogNotice("SceneController") << "Shape(s) selected: " << sceneGraph.selectedIndices.size();
		}
	}
}

void SceneController::handleMouseReleased(int x, int y, int button) {
	if (drawing) {
		endPoint.set(x, y);
		shapeManager.drawShape(currentShape, startPoint, endPoint);
		drawing = false;
		ofLogVerbose("SceneController") << "Finished drawing shape at (" << x << ", " << y << ")";
	}
}

void SceneController::handleKeyPressed(int key) {
	// Gestion des touches de caméra (uniquement si pas en vue quad)
	if (viewQuad) {
		return;
	}

	switch (key) {
	case '1':
		cameraManager.setPerspectiveView(0);
		ofLogNotice("SceneController") << "Camera: Top view";
		break;
	case '2':
		cameraManager.setPerspectiveView(1);
		ofLogNotice("SceneController") << "Camera: Front view";
		break;
	case '3':
		cameraManager.setPerspectiveView(2);
		ofLogNotice("SceneController") << "Camera: Side view";
		break;
	case '4':
		cameraManager.setPerspectiveView(3);
		ofLogNotice("SceneController") << "Camera: Bottom view";
		break;
	case '5':
		cameraManager.setPerspectiveView(4);
		ofLogNotice("SceneController") << "Camera: Free view (drag to rotate)";
		break;
	}
}

// ========== GESTION DES TRANSFORMATIONS ==========

void SceneController::applyTransformationToSelectedShape(float tx, float ty, float rot, float scale) {
	sceneGraph.updateSelectedTransform(tx, ty, rot, scale);
}

// ========== ACCESSEURS SCENEGRAPH ==========

void SceneController::addShapeToScene(const Shape & shape) {
	sceneGraph.addShape(shape);
	cameraManager.markDirty();
}

void SceneController::addShapesToScene(const std::vector<Shape> & shapes) {
	for (const auto & shape : shapes) {
		sceneGraph.addShape(shape);
	}
	cameraManager.markDirty();
	ofLogNotice("SceneController") << shapes.size() << " shapes added to scene";
}

std::vector<Shape> & SceneController::getAllShapes() {
	return sceneGraph.getAllShapes();
}

void SceneController::setAllShapes(const std::vector<Shape> & shapes) {
	sceneGraph.setShapes(shapes);
	cameraManager.markDirty();
}
