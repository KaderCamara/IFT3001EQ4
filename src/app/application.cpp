// IFT3100A25_BonjourMonde/application.cpp
// Classe principale de l'application.
//notre controller basically il va uniquement se charger de la communication entre renderer et uiWindow
//de ce fait ces instances sont créés une seule fois ( un seul cycle de vie )

#include "application.h"

// fonction appelée à l'initialisation de l'application
void Application::setup()
{
  ofSetWindowTitle("3D app");

  ofLog() << "<app::setup>";

  renderer.setup();
  uiWindow.setup();
}

void Application::update() {
	uiWindow.update();

	if (uiWindow.isSaveShapeRequested()) {
		renderer.setCurrentShape(uiWindow.getCurrentShape());
		renderer.save();
	}

	if (uiWindow.isDeleteShapeRequested()) {
		renderer.deleteShape();
	}

	if (uiWindow.isSelectShapeRequested()) {
		renderer.selectingModeOn();
	} else {
		renderer.selectingModeOff();
	}

	if (uiWindow.isQuadViewRequested()) {
		renderer.viewQuadMode();
	} else if (uiWindow.is3DviewRequested()) {
		renderer.view3DMode();
	} else if (uiWindow.is2DviewRequested()) {
		renderer.view2DMode();
	}

	// Undo dernier point de contrôle
	if (uiWindow.isUndoPointRequested()) {
		renderer.undoLastControlPoint();
		uiWindow.clearUndoPointRequest();
	}

	// Clear tous les points de contrôle
	if (uiWindow.isClearPointsRequested()) {
		renderer.clearControlPoints();
		uiWindow.clearClearPointsRequest();
	}

	// 3D IMPORT
	// ========== REFACTORISATION 3D IMPORT ==========
	// AVANT : renderer.import3DModel() faisait tout
	// APRÈS : Le controller délègue au Model3DImportManager

	if (uiWindow.isImport3DModelRequested()) {
		// 1. Déléguer l'import au manager (MODEL)
		std::vector<Shape> importedShapes = model3DImportManager.import3DModelWithDialog();

		// 2. Ajouter les shapes au SceneGraph via les accesseurs publics du Renderer
		if (!importedShapes.empty()) {
			renderer.addShapesToScene(importedShapes);

			// 3. Activer la vue 3D
			renderer.view3DMode();

			ofLogNotice("Application") << "Successfully imported "
									   << importedShapes.size() << " 3D shape(s)";
		}

		uiWindow.clearImport3DModelRequest();
	}

	if (uiWindow.isClear3DModelRequested()) {
		// 1. Récupérer les shapes actuelles via l'accesseur
		std::vector<Shape> currentShapes = renderer.getAllShapes();

		// 2. Filtrer via le manager (MODEL)
		std::vector<Shape> filteredShapes = model3DImportManager.removeAll3DModels(currentShapes);

		// 3. Remettre les shapes filtrées via l'accesseur
		renderer.setAllShapes(filteredShapes);

		uiWindow.clearClear3DModelRequest();
	}
	// ===============================================
	if (uiWindow.isGenerateCurveRequested()) {
		renderer.generateBezierCurveFromControlPoints();
		uiWindow.clearGenerateCurveRequest();
	}
	if (uiWindow.isClearCurvesRequested()) {
		renderer.clearCurves();
		uiWindow.clearClearCurvesRequest();
	}
	uiWindow.clearRequests();
}

void Application::draw() {
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
	uiWindow.getBackgroundColor();

	renderer.applyTransformationToSelectedShape(
		uiWindow.getTranslateX(),
		uiWindow.getTranslateY(),
		uiWindow.getRotation(),
		uiWindow.getScale());

  renderer.draw();
  uiWindow.draw();
}


void Application::keyPressed(int key) {
	if (uiWindow.getPlacePointsModeState()) {
		// if we are in place points mode, when entering P key
		if (key == 'p' || key == 'P') {
			// we unable place points mode
			uiWindow.placePointsMode= false;
			uiWindow.statusMessage = "Place Points Mode disabled.\n";
		}
	}
		
	//renderer.keyPressed(key);
}

void Application::mousePressed(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		// if we are in place points mode, we add control points to the curve
		if (uiWindow.isPlacePointsMode()) {
			renderer.addControlPoint(x, y);
		} else {

			renderer.setCurrentShape(uiWindow.getCurrentShape());
			renderer.mousePressed(x, y, button);
		}
	}
	// else we passed the event to the uiWindow
	else {
		uiWindow.mousePressed(x, y, button);
	}

}

void Application::mouseReleased(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		renderer.mouseReleased(x, y, button);
	} else {
		uiWindow.mouseReleased(x, y, button);
	}
}



void Application::dragEvent(ofDragInfo dragInfo) {
	uiWindow.handleFileDragAndDrop(dragInfo);
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}

