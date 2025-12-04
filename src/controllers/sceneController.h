// SceneController.h
// Contrôleur de scène MVC PUR (CONTROLLER)
// ✅ Coordonne les services et les models
// ✅ Gère la logique métier
// ❌ AUCUN rendu

#pragma once

#include "../objects/SceneGraph.h"
#include "../objects/shapeManager.h"
#include "../rendering/camera/cameraManager.h"
#include "../services/SelectionService.h"
#include "../services/TransformService.h"
#include "ofMain.h"

/**
 * @class SceneController
 * @brief Contrôleur de scène MVC PUR (CONTROLLER)
 * 
 * Responsabilités (CONTROLLER UNIQUEMENT) :
 * - Coordonner les models (SceneGraph, ShapeManager, CameraManager)
 * - Coordonner les services (SelectionService, TransformService)
 * - Gérer les modes de vue (2D, 3D, Quad)
 * - Gérer les modes d'interaction (dessin, sélection)
 * - Gérer les entrées utilisateur (souris, clavier)
 * - Déléguer la logique complexe aux services
 * - AUCUN rendu (délégué aux Renderers)
 * 
 * REFACTORISATION MVC :
 * - AVANT : SceneGraph contenait la logique de sélection et transformation ❌
 * - APRÈS : SceneController utilise SelectionService et TransformService ✅
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
	void handleMouseDragged(int x, int y, int button, const ofRectangle & drawingArea);
	void handleKeyPressed(int key);

	// ========== GESTION DES TRANSFORMATIONS ==========

	/**
	 * @brief Applique une transformation aux formes sélectionnées
	 * Utilise TransformService pour la logique
	 */
	void applyTransformationToSelected(float tx, float ty, float rot, float scale);

	/**
	 * @brief Réinitialise les transformations des formes sélectionnées
	 */
	void resetTransformationsForSelected();

	// ========== ACCESSEURS SCENEGRAPH ==========

	void addShapeToScene(const Shape & shape);
	void addShapesToScene(const std::vector<Shape> & shapes);
	std::vector<Shape> & getAllShapes();
	const std::vector<Shape> & getAllShapes() const;
	void setAllShapes(const std::vector<Shape> & shapes);

	// ========== ACCESSEURS POUR LE RENDERER ==========

	SceneGraph & getSceneGraph() { return sceneGraph; }
	const SceneGraph & getSceneGraph() const { return sceneGraph; }

	ShapeManager & getShapeManager() { return shapeManager; }
	const ShapeManager & getShapeManager() const { return shapeManager; }

	CameraManager & getCameraManager() { return cameraManager; }
	const CameraManager & getCameraManager() const { return cameraManager; }

	bool isDrawing() const { return drawing; }
	bool isShapeSelected() const { return !sceneGraph.selectedIndices.empty(); }
	bool hasUnsavedShape() const { return unsavedShapeExists; }

private:
	// ========== MODELS ==========
	SceneGraph sceneGraph; // Données de la scène
	ShapeManager shapeManager; // Gestion des formes 2D
	CameraManager cameraManager; // Gestion des caméras

	// ========== SERVICES ==========
	SelectionService selectionService; // Logique de sélection
	TransformService transformService; // Logique de transformation

	// ========== ÉTAT DU CONTRÔLEUR ==========

	// Modes de vue
	bool view2D = true;
	bool view3D = false;
	bool viewQuad = false;

	// Modes d'interaction
	bool selecting = false;
	bool drawing = false;
	bool unsavedShapeExists = false;

	// Forme en cours de création
	std::string currentShape = "none";
	ofPoint startPoint, endPoint;

	// ========== MÉTHODES PRIVÉES ==========

	/**
	 * @brief Convertit toutes les formes 2D en 3D
	 */
	void convertShapesTo3D();
};
