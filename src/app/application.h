// Application.h - EXEMPLE CORRIGÉ MVC PUR
// L'Application est le CONTROLLER principal qui coordonne tout

#pragma once

#include "../controllers/curvesController.h"
#include "../controllers/ImageController.h"
#include "../controllers/SceneController.h"
#include "../controllers/TransformController.h"
#include "../rendering/RenderData.h"
#include "../rendering/Renderer.h"
#include "../ui/uiWindow.h"
#include "../controllers/lightingController.h" 
#include "../utils/Model3DImportManager.h"
#include "ofMain.h"

/**
 * @class Application
 * @brief Controller principal de l'application (MVC)
 * 
 * Responsabilités :
 * - Coordination entre tous les Controllers
 * - Gestion du cycle de vie de l'application
 * - Routage des événements utilisateur
 * - PRÉPARATION des RenderData pour le Renderer
 * - AUCUN rendu direct (délégué au Renderer)
 * 
 * REFACTORISATION MVC FINALE :
 * - AVANT : Renderer interrogeait les Controllers ❌
 * - APRÈS : Application PRÉPARE les RenderData et les POUSSE au Renderer ✅
 * 
 * Architecture :
 * 
 *   Application (CONTROLLER principal)
 *       ↓
 *       ├─> SceneController (logique de scène)
 *       ├─> CurvesController (logique courbes)
 *       ├─> ImageController (logique images)
 *       ├─> TransformController (logique transformations)
 *       │
 *       └─> Renderer (VIEW pure)
 *             ├─> SceneRenderer
 *             ├─> CurvesRenderer
 *             └─> ImageRenderer
 */
class Application : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void keyPressed(int key);
	void dragEvent(ofDragInfo dragInfo);
	void exit();

private:
	// ========== CONTROLLERS ==========
	SceneController sceneController; // Logique de scène
	CurvesController curvesController; // Logique courbes
	ImageController imageController; // Logique images
	TransformController transformController; // Logique transformations
	LightingController lightingController; // Logique lumiere et illumination

	// ========== VIEW ==========
	Renderer renderer; // Rendu (VIEW pure)
	UIWindow uiWindow; // Interface utilisateur (VIEW)

	// ========== MODELS/UTILITAIRES ==========
	Model3DImportManager model3DImportManager; // Import 3D

	// ========== MÉTHODES DE PRÉPARATION DES RENDERDATA ==========
	// ✅ L'Application (CONTROLLER) prépare les données
	// ✅ Le Renderer (VIEW) reçoit et dessine

	/**
	 * @brief Prépare les données pour le rendu 2D
	 * @return Structure RenderData2D prête à être passée au renderer
	 */
	RenderDataDraw2D prepareRenderDataDraw2D();

	/**
	 * @brief Prépare les données pour le rendu des courbes 2D
	 * @return Structure RenderDataCurves2D prête à être passée au renderer
	 */
	RenderDataCurves2D prepareRenderDataCurves2D();



	/**
	 * @brief Prépare les données pour le rendu 3D
	 * @return Structure RenderData3D prête à être passée au renderer
	 */
	RenderData3D prepareRenderData3D();

	/**
	 * @brief Prépare les données pour le rendu Quad
	 * @return Structure RenderDataQuad prête à être passée au renderer
	 */
	RenderDataQuad prepareRenderDataQuad();

	/**
	 * @brief Convertit un CameraManager en CameraData (données pures)
	 * @param camera Caméra OpenFrameworks
	 * @return Données pures de la caméra
	 */
	CameraData extractCameraData(ofEasyCam & camera);

	// Gestion du viewport 3D indépendant
	void setup3DViewport();
	void handle3DMousePressed(int x, int y, int button);
	void handle3DMouseDragged(int x, int y, int button);
	void handle3DMouseReleased();

	ofEasyCam threeDViewportCamera;
	bool isOrbiting3D = false;
	bool isPanning3D = false;
	glm::vec2 last3DMouse = { 0, 0 };
	float orbitSpeed = 0.25f;
	float panSpeed = 0.7f;
	bool lightingDataNeedsUpdate = true;
	LightingData cachedLightingData;
	bool wasQuadView = false;
	bool was3DView = false;
};
