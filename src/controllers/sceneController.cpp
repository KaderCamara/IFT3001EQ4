// SceneController.cpp
// Implémentation du contrôleur de scène MVC PUR
#include "SceneController.h"

SceneController::SceneController() {
}

void SceneController::setup() {
	cameraManager.setup();
	ofLogNotice("SceneController") << "Setup complete";
}

// ========== GESTION DES VUES ==========

void SceneController::setView2DMode() {
	if (view2D) return; // Déjà en mode 2D

	view2D = true;
	view3D = false;
	viewQuad = false;
	cameraManager.markDirty();

	ofLogNotice("SceneController") << "Switched to 2D view";
}

void SceneController::setView3DMode() {
	if (view3D) return; // Déjà en mode 3D

	view3D = true;
	view2D = false;
	viewQuad = false;

	// Convertir toutes les formes 2D en 3D
	convertShapesTo3D();

	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Switched to 3D view";
}

void SceneController::setViewQuadMode() {
	if (viewQuad) return; // Déjà en mode Quad

	viewQuad = true;
	view3D = false;
	view2D = false;

	// Convertir toutes les formes 2D en 3D
	convertShapesTo3D();

	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Switched to Quad view";
}

void SceneController::convertShapesTo3D() {
	for (auto & shape : sceneGraph.shapes) {
		if (!shape.is3D) {
			shapeManager.convertTo3d(shape);
		}
	}
}

// ========== GESTION DES MODES D'INTERACTION ==========

void SceneController::enableSelectingMode() {
	if (selecting) return; // Déjà en mode sélection

	selecting = true;
	shapeManager.deleteCurrentShapeToDraw();
	ofLogNotice("SceneController") << "Selecting mode enabled";
}

void SceneController::disableSelectingMode() {
	if (!selecting) return; // Déjà désactivé

	selecting = false;
	ofLogNotice("SceneController") << "Selecting mode disabled";
}

// ========== OPÉRATIONS SUR LES FORMES ==========

void SceneController::saveCurrentShape() {
	sceneGraph.addShape(shapeManager.getCurrentShape());
	unsavedShapeExists = false;
	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Shape saved to scene";
}

void SceneController::deleteSelectedShapes() {
	if (sceneGraph.selectedIndices.empty()) {
		ofLogWarning("SceneController") << "No shape selected for deletion";
		return;
	}

	sceneGraph.removeSelectedShapes();
	cameraManager.markDirty();
	ofLogNotice("SceneController") << "Selected shapes deleted";
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
		unsavedShapeExists = false;
		ofLogVerbose("SceneController") << "Started drawing shape at (" << x << ", " << y << ")";
	}

	// Mode sélection - UTILISE SelectionService ✅
	if (selecting) {
		bool multiSelect = ofGetKeyPressed(OF_KEY_CONTROL) || ofGetKeyPressed(OF_KEY_COMMAND);

		// Déléguer au service de sélection
		int clickedIndex = selectionService.findShapeAt(sceneGraph.shapes, x, y);
		selectionService.updateSelection(sceneGraph.selectedIndices, clickedIndex, multiSelect);

		if (!sceneGraph.selectedIndices.empty()) {
			ofLogNotice("SceneController") << "Shape(s) selected: " << sceneGraph.selectedIndices.size();
		}
	}
}

void SceneController::handleMouseReleased(int x, int y, int button) {
	if (drawing) {
		endPoint.set(x, y);
		shapeManager.drawShape(currentShape, startPoint, endPoint);
		drawing = false;
		unsavedShapeExists = true;
		ofLogVerbose("SceneController") << "Finished drawing shape at (" << x << ", " << y << ")";
	}
}

void SceneController::handleMouseDragged(int x, int y, int button, const ofRectangle & drawingArea) {
	if (drawing && drawingArea.inside(x, y)) {
		// Mettre à jour le point de fin de la forme en cours
		endPoint.set(x, y);
		// Mettre à jour la forme dans shapeManager
		shapeManager.drawShape(currentShape, startPoint, endPoint);
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

void SceneController::handleMouseMoved(int x, int y) {
	// Détection du hover sur les formes 2D
	// Permettre le hover même pendant le dessin, sauf en mode sélection
	if (view2D && !selecting) {
		hoveredShapeIndex = selectionService.findShapeAt(sceneGraph.shapes, x, y);
	} else {
		hoveredShapeIndex = -1;
	}
}

// ========== GESTION DES PARAMÈTRES DE DESSIN ==========

void SceneController::setDrawingParameters(float lineWidth, ofColor strokeColor, ofColor fillColor) {
	shapeManager.setDrawingParameters(lineWidth, strokeColor, fillColor);
}

// ========== GESTION DES TRANSFORMATIONS - UTILISE TransformService ✅ ==========

void SceneController::applyTransformationToSelected(float tx, float ty, float rot, float scale) {
	if (sceneGraph.selectedIndices.empty()) {
		ofLogVerbose("SceneController") << "No shapes selected for transformation";
		return;
	}

	// Déléguer au service de transformation
	transformService.applyTransformToMultiple(
		sceneGraph.shapes,
		sceneGraph.selectedIndices,
		tx, ty, rot, scale);

	ofLogVerbose("SceneController") << "Transform applied to " << sceneGraph.selectedIndices.size()
									<< " shape(s): T(" << tx << ", " << ty << ") R(" << rot << ") S(" << scale << ")";
}

void SceneController::resetTransformationsForSelected() {
	if (sceneGraph.selectedIndices.empty()) {
		ofLogWarning("SceneController") << "No shapes selected to reset";
		return;
	}

	// Réinitialiser toutes les formes sélectionnées
	for (int index : sceneGraph.selectedIndices) {
		if (index >= 0 && index < static_cast<int>(sceneGraph.shapes.size())) {
			transformService.resetTransform(sceneGraph.shapes[index]);
		}
	}

	ofLogNotice("SceneController") << "Transforms reset for " << sceneGraph.selectedIndices.size() << " shape(s)";
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

const std::vector<Shape> & SceneController::getAllShapes() const {
	return sceneGraph.getAllShapes();
}

void SceneController::setAllShapes(const std::vector<Shape> & shapes) {
	sceneGraph.setShapes(shapes);
	cameraManager.markDirty();
}
