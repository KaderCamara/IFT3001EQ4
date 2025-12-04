// application.cpp
// Implémentation du controller principal
#include "application.h"

void Application::setup() {
	ofSetWindowTitle("3D app");
	ofLog() << "<app::setup>";

	// Setup des composants
	sceneController.setup();
	renderer.setup();
	uiWindow.setup();
	imageController.setup(); //
	curvesController.setup(); //
	transformController.setup(); //

	// Injection de dépendance : connecter le renderer au controller
	renderer.setSceneController(&sceneController);
	renderer.setCurvesController(&curvesController); //
	transformController.setSceneGraph(&sceneController.getSceneGraph());

	ofLogNotice("Application") << "Setup complete - MVC architecture initialized";
}

void Application::update() {
	uiWindow.update();

	// ========== GESTION DES FORMES ==========

	if (uiWindow.isSaveShapeRequested()) {
		sceneController.setCurrentShape(uiWindow.getCurrentShape());
		sceneController.saveCurrentShape();
	}

	if (uiWindow.isDeleteShapeRequested()) {
		sceneController.deleteSelectedShapes();
	}

	// ========== GESTION DES MODES ==========

	if (uiWindow.isSelectShapeRequested()) {
		sceneController.enableSelectingMode();
	} else {
		sceneController.disableSelectingMode();
	}

	// ========== GESTION DES VUES ==========

	if (uiWindow.isQuadViewRequested()) {
		sceneController.setViewQuadMode();
	} else if (uiWindow.is3DviewRequested()) {
		sceneController.setView3DMode();
	} else if (uiWindow.is2DviewRequested()) {
		sceneController.setView2DMode();
	}

	// ========== GESTION DES COURBES ==========

	if (uiWindow.isUndoPointRequested()) {
		curvesController.undoLastControlPoint();
		uiWindow.clearUndoPointRequest();
	}

	if (uiWindow.isClearPointsRequested()) {
		curvesController.clearControlPoints();
		uiWindow.clearClearPointsRequest();
	}

	if (uiWindow.isGenerateCurveRequested()) {
		curvesController.generateBezierCurve();
		uiWindow.clearGenerateCurveRequest();
	}

	if (uiWindow.isClearCurvesRequested()) {
		curvesController.clearCurves();
		uiWindow.clearClearCurvesRequest();
	}

	// ========== IMPORT 3D ==========

	if (uiWindow.isImport3DModelRequested()) {
		// Importer via le manager
		std::vector<Shape> importedShapes = model3DImportManager.import3DModelWithDialog();

		// Ajouter au contrôleur de scène
		if (!importedShapes.empty()) {
			sceneController.addShapesToScene(importedShapes);
			sceneController.setView3DMode();

			ofLogNotice("Application") << "Successfully imported "
									   << importedShapes.size() << " 3D shape(s)";
		}

		uiWindow.clearImport3DModelRequest();
	}

	if (uiWindow.isClear3DModelRequested()) {
		// Récupérer les shapes actuelles
		std::vector<Shape> currentShapes = sceneController.getAllShapes();

		// Filtrer via le manager
		std::vector<Shape> filteredShapes = model3DImportManager.removeAll3DModels(currentShapes);

		// Remettre les shapes filtrées
		sceneController.setAllShapes(filteredShapes);

		uiWindow.clearClear3DModelRequest();
	}

	// Clear des requêtes UI
	uiWindow.clearRequests();
}

void Application::draw() {
	// Configurer le renderer avec les paramètres UI
	renderer.setDrawingArea(uiWindow.getDrawingArea());

	renderer.applyDrawingParameters(
		uiWindow.getLineWidth(),
		uiWindow.getStrokeColor(),
		uiWindow.getFillColor(),
		uiWindow.getBackgroundColor(),
		uiWindow.isHSBMode(),
		uiWindow.getHue(),
		uiWindow.getSaturation(),
		uiWindow.getBrightness());

	renderer.updateShapeManagerParams(
		uiWindow.getLineWidth(),
		uiWindow.getStrokeColor(),
		uiWindow.getFillColor());

	renderer.set3DDisplayOptions(
		uiWindow.isShowBoundingBoxEnabled(),
		uiWindow.isWireframeEnabled());

	// Appliquer les transformations aux formes sélectionnées
	transformController.applyTransformToSelected(
		uiWindow.getTranslateX(),
		uiWindow.getTranslateY(),
		uiWindow.getRotation(),
		uiWindow.getScale());

	// Dessiner la scène et l'UI
	renderer.draw();
	uiWindow.draw();
}

void Application::keyPressed(int key) {
	// Gestion du mode placement de points (Curves)
	if (uiWindow.getPlacePointsModeState()) {
		if (key == 'p' || key == 'P') {
			uiWindow.placePointsMode = false;
			uiWindow.statusMessage = "Place Points Mode disabled.\n";
		}
	}

	// Déléguer au contrôleur de scène pour les touches de caméra
	sceneController.handleKeyPressed(key);
}

void Application::mousePressed(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		// Si on est en mode placement de points
		if (uiWindow.isPlacePointsMode()) {
			curvesController.addControlPoint(x, y, uiWindow.getDrawingArea());
		} else {
			// Sinon, mode dessin ou sélection normal
			sceneController.setCurrentShape(uiWindow.getCurrentShape());
			sceneController.handleMousePressed(x, y, button, uiWindow.getDrawingArea());
		}
	} else {
		// Clic dans l'UI
		uiWindow.mousePressed(x, y, button);
	}
}

void Application::mouseReleased(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		sceneController.handleMouseReleased(x, y, button);
	} else {
		uiWindow.mouseReleased(x, y, button);
	}
}

void Application::mouseDragged(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		if (sceneController.isDrawing()) {
			// Mettre à jour l'aperçu pendant le drag
			sceneController.handleMouseDragged(x, y, button, uiWindow.getDrawingArea());
		}
	}
}

void Application::dragEvent(ofDragInfo dragInfo) {
	// Déléguer au ImageController
	if (imageController.loadFromDragAndDrop(dragInfo)) { // ✅
		ofLogNotice("Application") << "Image loaded via drag & drop";
	}
}

void Application::exit() {
	ofLog() << "<app::exit>";
}
