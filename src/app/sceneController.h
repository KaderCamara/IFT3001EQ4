// SceneController.h
// Contrôleur responsable de la logique métier de la scène
#pragma once

#include "../objects/controlPointsManager.h"
#include "../objects/curveManager.h"
#include "../objects/shape.h"
#include "../objects/shapeManager.h"
#include "../rendering/camera/cameraManager.h"
#include "ofMain.h"
#include "../rendering/sceneGraph.h"
#include <vector>

/**
 * @class SceneController
 * @brief Contrôleur gérant la logique métier de la scène
 * 
 * Responsabilités (CONTROLLER - MVC) :
 * - Gestion des modes de vue (2D, 3D, Quad)
 * - Gestion des modes d'interaction (dessin, sélection)
 * - Gestion des entrées utilisateur (souris, clavier)
 * - Coordination entre SceneGraph, ShapeManager, CameraManager
 * - Gestion des courbes de Bézier et points de contrôle
 * - Opérations CRUD sur les formes (Create, Read, Update, Delete)
 */
class SceneController {
public:
	SceneController();
	~SceneController() = default;

	void setup();

	// ========== GESTION DES VUES ==========

	void setView2DMode();
	void setView3DMode();
	void setViewQuadMode();

	bool is2DView() const { return view2D; }
	bool is3DView() const { return view3D; }
	bool isQuadView() const { return viewQuad; }

	// ========== GESTION DES MODES D'INTERACTION ==========

	void enableSelectingMode();
	void disableSelectingMode();
	bool isSelectingMode() const { return selecting; }

	void setCurrentShape(const std::string & shape) { currentShape = shape; }
	std::string getCurrentShape() const { return currentShape; }

	// ========== OPÉRATIONS SUR LES FORMES ==========

	void saveCurrentShape();
	void deleteSelectedShapes();

	// ========== GESTION DES ENTRÉES ==========

	void handleMousePressed(int x, int y, int button, const ofRectangle & drawingArea);
	void handleMouseReleased(int x, int y, int button);
	void handleKeyPressed(int key);

	// ========== GESTION DES TRANSFORMATIONS ==========

	void applyTransformationToSelectedShape(float tx, float ty, float rot, float scale);


	// ========== ACCESSEURS SCENEGRAPH ==========

	void addShapeToScene(const Shape & shape);
	void addShapesToScene(const std::vector<Shape> & shapes);
	std::vector<Shape> & getAllShapes();
	void setAllShapes(const std::vector<Shape> & shapes);

	// ========== ACCESSEURS POUR LE RENDERER ==========

	SceneGraph & getSceneGraph() { return sceneGraph; }
	const SceneGraph & getSceneGraph() const { return sceneGraph; }

	ShapeManager & getShapeManager() { return shapeManager; }
	const ShapeManager & getShapeManager() const { return shapeManager; }

	CameraManager & getCameraManager() { return cameraManager; }
	const CameraManager & getCameraManager() const { return cameraManager; }

	bool isDrawing() const { return drawing; }
	bool isShapeSelected() const { return shapeSelected; }

private:
	// ========== MANAGERS (MODEL) ==========
	SceneGraph sceneGraph;
	ShapeManager shapeManager;
	CameraManager cameraManager;

	// ========== ÉTAT DU CONTRÔLEUR ==========

	// Modes de vue
	bool view2D = true;
	bool view3D = false;
	bool viewQuad = false;

	// Modes d'interaction
	bool selecting = false;
	bool drawing = false;
	bool shapeSelected = false;

	// Forme en cours de création
	std::string currentShape = "none";
	ofPoint startPoint, endPoint;

	// ========== MÉTHODES PRIVÉES ==========

	void convertShapesTo3D();
};
