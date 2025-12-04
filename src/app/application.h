// application.h
// Classe principale de l'application (Controller principal)
#pragma once

#include "../rendering/Renderer.h"
#include "../app/SceneController.h"
#include "../ui/uiWindow.h"
#include "../utils/Model3DImportManager.h"
#include "ofMain.h"
#include "../app/imageController.h"
#include "../app/curvesController.h"
#include "../app/transformController.h"

/**
 * @class Application
 * @brief Controller principal de l'application (MVC)
 * 
 * Responsabilités :
 * - Coordination entre Renderer (View), SceneController (Controller métier) et UIWindow (View UI)
 * - Gestion du cycle de vie de l'application
 * - Routage des événements utilisateur
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
	// ========== COMPOSANTS MVC ==========
	Renderer renderer; // VIEW - Rendu
	SceneController sceneController; // CONTROLLER - Logique métier
	UIWindow uiWindow; // VIEW - Interface utilisateur

	// ========== UTILITAIRES ==========
	Model3DImportManager model3DImportManager; // MODEL - Import 3D

	ImageController imageController; //Logique images
	CurvesController curvesController; //Logique courbes
	TransformController transformController; //Logique transformations
};
