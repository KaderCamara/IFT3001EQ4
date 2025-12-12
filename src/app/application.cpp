// Application.cpp
// L'Application (CONTROLLER principal) prépare les RenderData et les pousse au Renderer
#include "application.h"

void Application::setup() {
	ofSetWindowTitle("3D app");
	ofLog() << "<app::setup>";

	// Setup des composants
	sceneController.setup();
	renderer.setup();
	uiWindow.setup();
	imageController.setup();
	curvesController.setup();
	transformController.setup();
	lightingController.setup(); 

	// ✅ PLUS BESOIN d'injecter les Controllers dans le Renderer
	// Le Renderer est maintenant une VIEW pure

	// Configuration du TransformController
	transformController.setSceneGraph(&sceneController.getSceneGraph());
	const LightingPanel & lightingPanel = uiWindow.getLightingPanel();
	cachedLightingData = lightingController.prepareLightingData(lightingPanel);

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
	bool isQuadView = uiWindow.isQuadViewRequested();
	bool is3DView = uiWindow.is3DviewRequested();
	bool is2DView = uiWindow.is2DviewRequested();
	if (isQuadView && !wasQuadView) {
		sceneController.setViewQuadMode();
		lightingDataNeedsUpdate = true;
		wasQuadView = true;
		was3DView = false;
		ofLogNotice("Application") << "View changed to QUAD - lighting update scheduled";
	} else if (is3DView && !was3DView) {
		sceneController.setView3DMode();
		lightingDataNeedsUpdate = true;
		was3DView = true;
		wasQuadView = false;
		ofLogNotice("Application") << "View changed to 3D - lighting update scheduled";
	} else if (is2DView) {
		sceneController.setView2DMode();
		wasQuadView = false;
		was3DView = false;
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
		std::vector<Shape> importedShapes = model3DImportManager.import3DModelWithDialog();

		if (!importedShapes.empty()) {
			sceneController.addShapesToScene(importedShapes);
			sceneController.setView3DMode();
			lightingDataNeedsUpdate = true;  
			ofLogNotice("Application") << "Successfully imported "
									   << importedShapes.size() << " 3D shape(s)";
		}
	}

	if (uiWindow.isClear3DModelRequested()) {
		std::vector<Shape> currentShapes = sceneController.getAllShapes();
		std::vector<Shape> filteredShapes = model3DImportManager.removeAll3DModels(currentShapes);
		sceneController.setAllShapes(filteredShapes);
	}


	//////// check


	const LightingPanel & lightingPanel = uiWindow.getLightingPanel();

	// Track key lighting states
	static bool lastSunEnabled = false;
	static bool lastPointEnabled = false;
	static bool lastSpotEnabled = false;
	static bool lastPhongEnabled = false;
	static int lastMaterialCount = 0;

	bool sunEnabled = lightingPanel.isSunLightEnabled();
	bool pointEnabled = lightingPanel.isPointLightEnabled();
	bool spotEnabled = lightingPanel.isSpotLightEnabled();
	bool phongEnabled = lightingPanel.isPhongEnabled();
	int materialCount = lightingPanel.getMaterialCount();

	// Detect changes
	if (sunEnabled != lastSunEnabled || pointEnabled != lastPointEnabled || spotEnabled != lastSpotEnabled || phongEnabled != lastPhongEnabled || materialCount != lastMaterialCount) {

		lightingDataNeedsUpdate = true;

		ofLogNotice("Application") << "Lighting panel changed - update scheduled "
								   << "(Sun:" << sunEnabled << " Point:" << pointEnabled
								   << " Spot:" << spotEnabled << " Phong:" << phongEnabled
								   << " Material:" << materialCount << ")";

		// Update tracking
		lastSunEnabled = sunEnabled;
		lastPointEnabled = pointEnabled;
		lastSpotEnabled = spotEnabled;
		lastPhongEnabled = phongEnabled;
		lastMaterialCount = materialCount;
	}





	//////////////////

	// Clear des requêtes UI
	uiWindow.clearRequests();
}

void Application::draw() {
	// ========== CONFIGURATION DU RENDERER ==========
	renderer.setDrawDrawingArea(uiWindow.getDrawDrawingArea());
	renderer.setCurvesDrawingArea(uiWindow.getCurvesDrawingArea());

	// Appliquer les paramètres visuels
	renderer.setVisualParameters(
		uiWindow.getLineWidth(),
		uiWindow.getStrokeColor(),
		uiWindow.getFillColor(),
		uiWindow.getBackgroundColor());

	// Configurer les options 3D
	renderer.set3DDisplayOptions(
		uiWindow.isShowBoundingBoxEnabled(),
		uiWindow.isWireframeEnabled(),
		uiWindow.isNormalsEnabled());

	// ========== APPLIQUER LES TRANSFORMATIONS ==========
	transformController.applyTransformToSelected(
		uiWindow.getTranslateX(),
		uiWindow.getTranslateY(),
		uiWindow.getRotation(),
		uiWindow.getScale());

	// ========== PRÉPARER LES RENDERDATA ET POUSSER AU RENDERER ==========
	// ✅ L'Application (CONTROLLER) prépare les données
	// ✅ Le Renderer (VIEW) reçoit et dessine

	// Pousser camera interactive du CameraManager vers le renderer
	CameraManager & cameraManager = sceneController.getCameraManager();
	renderer.setExternalSceneCamera(&cameraManager.getCurrentCamera());

	if (sceneController.isQuadView()) {
		// Préparer les données pour le rendu Quad
		RenderDataQuad data = prepareRenderDataQuad();

		// Pousser au renderer
		renderer.drawQuad(data);

	} else if (sceneController.is3DView()) {
		// Préparer les données pour le rendu 3D
		RenderData3D data = prepareRenderData3D();

		// Pousser au renderer
		renderer.draw3D(data);

	} else if (sceneController.is2DView()) {
		if (uiWindow.isDrawModeActive()) {
			RenderDataDraw2D data = prepareRenderDataDraw2D();
			renderer.drawDrawCanvas(data);
		} else if (uiWindow.isCurvesModeActive()) {
			RenderDataCurves2D data = prepareRenderDataCurves2D();
			renderer.drawCurvesCanvas(data);
		}
	}


	// Dessiner l'UI par-dessus
	// Make sure 3D depth testing doesn't hide UI elements
	ofDisableDepthTest();
	uiWindow.draw();
	// restore depth test in case other code expects it
	ofEnableDepthTest();
}

// ========== PRÉPARATION DES RENDERDATA (CONTROLLER → VIEW) ==========

RenderDataDraw2D Application::prepareRenderDataDraw2D() {
	RenderDataDraw2D data;

	// Récupérer les données du SceneController
	const SceneGraph & sceneGraph = sceneController.getSceneGraph();
	const ShapeManager & shapeManager = sceneController.getShapeManager();

	// Formes de la scène
	data.shapes = sceneGraph.shapes;
	data.selectedIndices = sceneGraph.selectedIndices;

	// Forme en cours de création (preview)
	if (sceneController.getCurrentShape() != "none" && (sceneController.isDrawing() || sceneController.hasUnsavedShape())) {
		data.currentPreview = shapeManager.getCurrentShapeToDraw();
		data.hasPreview = true;
	} else {
		data.hasPreview = false;
	}

	 // Paramètres visuels
	data.lineWidth = uiWindow.getLineWidth();
	data.strokeColor = uiWindow.getStrokeColor();
	data.fillColor = uiWindow.getFillColor();
	data.backgroundColor = uiWindow.getBackgroundColor();

	return data;
}

RenderDataCurves2D Application::prepareRenderDataCurves2D() {
	RenderDataCurves2D data;

	// Courbes de Bézier
	const ControlPointsManager & cpm = curvesController.getControlPointsManager();
	const CurveManager & cm = curvesController.getCurveManager();
	data.controlPoints = cpm.getControlPoints();
	data.curves = cm.getCurves();

	// Paramètres visuels dédiés aux courbes (on conserve les paramètres de trait actuels)
	data.lineWidth = uiWindow.getLineWidth();
	data.strokeColor = uiWindow.getStrokeColor();
	data.backgroundColor = uiWindow.getBackgroundColor();

	return data;
}

RenderData3D Application::prepareRenderData3D() {
	RenderData3D data;

	// Récupérer les formes
	const SceneGraph & sceneGraph = sceneController.getSceneGraph();
	data.shapes = sceneGraph.shapes;

	// Use CameraManager's current camera for the 3D view so CameraManager handles interactions
	CameraManager & cameraManager = sceneController.getCameraManager();
	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, false);
	}
	data.camera = extractCameraData(cameraManager.getCurrentCamera());

	// Options d'affichage
	data.showBoundingBox = uiWindow.isShowBoundingBoxEnabled();
	data.showWireframe = uiWindow.isWireframeEnabled();
	data.showGrid = uiWindow.isGridEnabled();
	data.showAxes = uiWindow.isAxesEnabled();
	data.showNormals = uiWindow.isNormalsEnabled();

	if (lightingDataNeedsUpdate) {
		const LightingPanel & lightingPanel = uiWindow.getLightingPanel();
		cachedLightingData = lightingController.prepareLightingData(lightingPanel);
		lightingDataNeedsUpdate = false;
	}
	data.lighting = cachedLightingData;

	//data.enableLighting = uiWindow.isLightingEnabled();
	//data.lightIntensity = uiWindow.getLightingIntensity();
	//data.lightColor = uiWindow.getLightingColor();

	// Zone de dessin
	data.drawingArea = uiWindow.getDrawingArea();

	return data;
}

RenderDataQuad Application::prepareRenderDataQuad() {
	RenderDataQuad data;

	// Récupérer les formes
	const SceneGraph & sceneGraph = sceneController.getSceneGraph();
	data.shapes = sceneGraph.shapes;

	// Récupérer le CameraManager
	CameraManager & cameraManager = sceneController.getCameraManager();

	// Mettre à jour les caméras si nécessaire
	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, true);
	}

	// Calculer les viewports pour les 4 vues
	ofRectangle drawingArea = uiWindow.getDrawingArea();
	int w = drawingArea.width;
	int h = drawingArea.height;
	int halfW = w / 2;
	int halfH = h / 2;
	int offsetX = drawingArea.x;
	int offsetY = drawingArea.y;

	data.viewports[0].set(offsetX, offsetY, halfW, halfH); // Top
	data.viewports[1].set(offsetX + halfW, offsetY, halfW, halfH); // Front
	data.viewports[2].set(offsetX, offsetY + halfH, halfW, halfH); // Side
	data.viewports[3].set(offsetX + halfW, offsetY + halfH, halfW, halfH); // Bottom

	// Extraire les données des 4 caméras
	for (int i = 0; i < 4; ++i) {
		int originalIndex = cameraManager.getCurrentCameraIndex();
		cameraManager.setPerspectiveView(i);
		data.cameras[i] = extractCameraData(cameraManager.getCurrentCamera());
		cameraManager.setPerspectiveView(originalIndex);
	}

	// Options d'affichage
	data.showBoundingBox = uiWindow.isShowBoundingBoxEnabled();
	data.showWireframe = uiWindow.isWireframeEnabled();
	data.showGrid = uiWindow.isGridEnabled(); // ✅ ADDED
	data.showAxes = uiWindow.isAxesEnabled(); // ✅ ADDED

	// Lighting data from panel
	if (lightingDataNeedsUpdate) {
		const LightingPanel & lightingPanel = uiWindow.getLightingPanel();
		cachedLightingData = lightingController.prepareLightingData(lightingPanel);
		lightingDataNeedsUpdate = false;
	}
	data.lighting = cachedLightingData;

	return data;
}

CameraData Application::extractCameraData(ofEasyCam & camera) {
	CameraData data;

	// Position et orientation
	data.position = camera.getPosition();
	data.target = camera.getTarget().getPosition();
	data.up = camera.getUpDir();

	// Paramètres de projection
	data.fov = camera.getFov();
	data.nearClip = camera.getNearClip();
	data.farClip = camera.getFarClip();
	data.isOrtho = camera.getOrtho();

	return data;
}

void Application::setup3DViewport() {
	threeDViewportCamera.disableMouseInput();
	threeDViewportCamera.setNearClip(0.1f);
	threeDViewportCamera.setFarClip(5000.0f);
	threeDViewportCamera.setFov(60.0f);
	threeDViewportCamera.setPosition(0, 0, 600);
	threeDViewportCamera.lookAt({ 0, 0, 0 });
}

void Application::handle3DMousePressed(int x, int y, int button) {
	last3DMouse = { static_cast<float>(x), static_cast<float>(y) };
	if (button == OF_MOUSE_BUTTON_LEFT) {
		isOrbiting3D = true;
	} else if (button == OF_MOUSE_BUTTON_RIGHT) {
		isPanning3D = true;
	}
}

void Application::handle3DMouseDragged(int x, int y, int button) {
	(void)button;
	glm::vec2 current(static_cast<float>(x), static_cast<float>(y));
	glm::vec2 delta = current - last3DMouse;

	if (isOrbiting3D) {
		const auto target = threeDViewportCamera.getTarget().getPosition();
		float distance = threeDViewportCamera.getDistance();
		threeDViewportCamera.orbitDeg(delta.x * orbitSpeed, delta.y * orbitSpeed, distance, target);
	}

	if (isPanning3D) {
		threeDViewportCamera.truck(-delta.x * panSpeed);
		threeDViewportCamera.boom(delta.y * panSpeed);
	}

	last3DMouse = current;
}

void Application::handle3DMouseReleased() {
	isOrbiting3D = false;
	isPanning3D = false;
}

// ========== GESTION DES ENTRÉES ==========

void Application::keyPressed(int key) {
	if (uiWindow.isPlacePointsMode()) {
		if (key == 'p' || key == 'P') {
			uiWindow.disablePlacePointsMode();
			uiWindow.statusMessage = "Place Points Mode disabled.\n";
		}
	}

	sceneController.handleKeyPressed(key);
}
void Application::mousePressed(int x, int y, int button) {

	if (uiWindow.isDrawModeActive() && uiWindow.getDrawDrawingArea().inside(x, y)) {
		sceneController.setCurrentShape(uiWindow.getCurrentShape());
		sceneController.handleMousePressed(x, y, button, uiWindow.getDrawDrawingArea());
	} else if (uiWindow.isCurvesModeActive() && uiWindow.getCurvesDrawingArea().inside(x, y)) {
		if (uiWindow.isPlacePointsMode()) {
			curvesController.addControlPoint(x, y, uiWindow.getCurvesDrawingArea());
		}
	} else if (uiWindow.is3DTabActive() && uiWindow.getDrawingArea().inside(x, y)) {
		// If CameraManager's free interactive camera is active (index 4), allow ofEasyCam to receive events
		CameraManager & cameraManager = sceneController.getCameraManager();
		if (cameraManager.getCurrentCameraIndex() == 4) {
			// do nothing: ofEasyCam will handle mouse input via events
		} else {
			handle3DMousePressed(x, y, button);
		}
	} else {
		uiWindow.mousePressed(x, y, button);
	}
}

void Application::mouseReleased(int x, int y, int button) {
	if (uiWindow.isDrawModeActive() && uiWindow.getDrawDrawingArea().inside(x, y)) {
		sceneController.handleMouseReleased(x, y, button);
	} else if (uiWindow.is3DTabActive() && uiWindow.getDrawingArea().inside(x, y)) {
		CameraManager & cameraManager = sceneController.getCameraManager();
		if (cameraManager.getCurrentCameraIndex() == 4) {
			// let ofEasyCam handle
		} else {
			handle3DMouseReleased();
		}
	} else {
		uiWindow.mouseReleased(x, y, button);
	}
}

void Application::mouseDragged(int x, int y, int button) {
	if (uiWindow.isDrawModeActive() && uiWindow.getDrawDrawingArea().inside(x, y)) {
		if (sceneController.isDrawing()) {
			sceneController.handleMouseDragged(x, y, button, uiWindow.getDrawDrawingArea());
		}
	} else if (uiWindow.is3DTabActive() && uiWindow.getDrawingArea().inside(x, y)) {
		CameraManager & cameraManager = sceneController.getCameraManager();
		if (cameraManager.getCurrentCameraIndex() == 4) {
			// let ofEasyCam handle dragging
		} else {
			handle3DMouseDragged(x, y, button);
		}
	}
}

void Application::dragEvent(ofDragInfo dragInfo) {
	if (imageController.loadFromDragAndDrop(dragInfo)) {
		ofLogNotice("Application") << "Image loaded via drag & drop";
	}
}

void Application::exit() {
	ofLog() << "<app::exit>";
}
