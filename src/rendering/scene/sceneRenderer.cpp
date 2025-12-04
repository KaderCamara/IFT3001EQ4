// SceneRenderer.cpp
#include "SceneRenderer.h"

void SceneRenderer::draw2D() {
	if (!sceneController) return;

	const SceneGraph & sceneGraph = sceneController->getSceneGraph();
	const ShapeManager & shapeManager = sceneController->getShapeManager();
	const ControlPointsManager & controlPointsManager = curvesController->getControlPointsManager();
	const CurveManager & curveManager = curvesController->getCurveManager();

	// Dessiner toutes les formes de la scène
	for (int i = 0; i < sceneGraph.shapes.size(); ++i) {
		const auto & s = sceneGraph.shapes[i];
		if (s.type == "none" || s.type == "x") continue;

		bool isSelected = std::find(sceneGraph.selectedIndices.begin(),
							  sceneGraph.selectedIndices.end(), i)
			!= sceneGraph.selectedIndices.end();

		shape2DRenderer.drawShape2D(s, isSelected, currentLineWidth);
	}

	// Rendu des courbes (si disponible)
	if (curvesRenderer) {
		curvesRenderer->render(controlPointsManager, curveManager);
	}

	// Dessiner la forme en cours de création
	if (sceneController->getCurrentShape() != "none" && (sceneController->isDrawing() || sceneController->hasUnsavedShape())) {
		const Shape & preview = shapeManager.getCurrentShapeToDraw();
		shape2DRenderer.drawShape2D(preview, false, currentLineWidth);
	}
}

void SceneRenderer::draw3D() {
	if (!sceneController) return;

	CameraManager & cameraManager = sceneController->getCameraManager();
	const SceneGraph & sceneGraph = sceneController->getSceneGraph();

	// Mettre à jour la caméra si nécessaire
	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, false);
	}

	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);

	for (const auto & s : sceneGraph.shapes) {
		shape3DRenderer.drawShape3D(s);
	}

	cameraManager.getCurrentCamera().end();
}

void SceneRenderer::drawQuadView() {
	if (!sceneController) return;

	CameraManager & cameraManager = sceneController->getCameraManager();
	const SceneGraph & sceneGraph = sceneController->getSceneGraph();

	// Mettre à jour les caméras si nécessaire
	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, true);
	}

	int w = drawingArea.width;
	int h = drawingArea.height;
	int halfW = w / 2;
	int halfH = h / 2;
	int offsetX = drawingArea.x;
	int offsetY = drawingArea.y;

	// Dessiner les 4 vues
	drawQuadViewCamera(0, offsetX, offsetY, halfW, halfH, "Top View");
	drawQuadViewCamera(1, offsetX + halfW, offsetY, halfW, halfH, "Front View");
	drawQuadViewCamera(2, offsetX, offsetY + halfH, halfW, halfH, "Side View");
	drawQuadViewCamera(3, offsetX + halfW, offsetY + halfH, halfW, halfH, "Bottom View");

	// Restaurer le viewport complet
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());

	// Séparateurs
	drawQuadViewSeparators();
}

void SceneRenderer::drawQuadViewCamera(int cameraIndex, int x, int y, int width, int height, const std::string & label) {
	if (!sceneController) return;

	CameraManager & cameraManager = sceneController->getCameraManager();
	const SceneGraph & sceneGraph = sceneController->getSceneGraph();

	ofViewport(x, y, width, height);

	cameraManager.setPerspectiveView(cameraIndex);
	cameraManager.getCurrentCamera().begin();

	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		shape3DRenderer.drawShape3D(s);
	}

	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString(label, x + 10, y + 20);
}

void SceneRenderer::drawQuadViewSeparators() {
	int w = drawingArea.width;
	int h = drawingArea.height;
	int halfW = w / 2;
	int halfH = h / 2;
	int offsetX = drawingArea.x;
	int offsetY = drawingArea.y;

	ofPushStyle();
	ofSetColor(100);
	ofSetLineWidth(2);
	ofDrawLine(offsetX + halfW, offsetY, offsetX + halfW, offsetY + h); // verticale
	ofDrawLine(offsetX, offsetY + halfH, offsetX + w, offsetY + halfH); // horizontale
	ofPopStyle();
}

void SceneRenderer::set3DDisplayOptions(bool showBoundingBox, bool showWireframe) {
	shape3DRenderer.setShowBoundingBox(showBoundingBox);
	shape3DRenderer.setShowWireframe(showWireframe);
}
