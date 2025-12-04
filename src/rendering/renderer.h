// Renderer.h
// Classe responsable UNIQUEMENT du rendu visuel
#pragma once

#include "../app/sceneController.h"
#include "curves/CurvesRenderer.h"
#include "ofMain.h"
#include "scene/sceneRenderer.h"
#include "image/imageRenderer.h"


/**
 * @class Renderer
 * @brief Responsable UNIQUEMENT du rendu visuel (VIEW - MVC)
 * 
 * Responsabilités (VIEW PURE) :
 * - Dessiner la scène 2D
 * - Dessiner la scène 3D
 * - Dessiner la vue quad (4 caméras)
 * - Appliquer les paramètres visuels (couleurs, lignes)
 * - Coordonner les renderers spécialisés (CurvesRenderer, etc.)
 * - Aucune logique métier
 * - Aucune gestion d'entrées
 * 
 * REFACTORISATION MVC (Phase 1 - Problème 3) :
 * - AJOUT : CurvesRenderer pour le rendu des courbes de Bézier
 * - Les courbes sont maintenant rendues via un renderer spécialisé
 */
class Renderer {
public:
	Renderer();
	~Renderer() = default;

	void setup();

	/**
     * @brief Injecter le contrôleur de scène
     * @param controller Référence au SceneController
     */
	void setSceneController(SceneController * controller);

	// ========== MÉTHODES DE RENDU ==========

	/**
     * @brief Dessine la scène selon le mode de vue actif
     */
	void draw();

	// ========== CONFIGURATION DU RENDU ==========

	/**
     * @brief Définit la zone de dessin
     */
	void setDrawingArea(const ofRectangle & area) { drawingArea = area; }

	/**
     * @brief Récupère la zone de dessin
     */
	ofRectangle getDrawingArea() const { return drawingArea; }

	/**
     * @brief Applique les paramètres de dessin (couleurs, lignes, HSB)
     */
	void applyDrawingParameters(float lineW, const ofColor & stroke, const ofColor & fill,
		const ofColor & bg, bool useHSB, float hue, float saturation, float brightness);

	/**
     * @brief Met à jour les paramètres du ShapeManager
     */
	void updateShapeManagerParams(float lineW, ofColor stroke, ofColor fill);

	/**
	 * @brief Configure les options d'affichage 3D (boîte englobante, fil de fer)
	 */

	void set3DDisplayOptions(bool showBoundingBox, bool showWireframe);

	ImageRenderer & getImageRenderer() { return imageRenderer; }
	void setCurvesController(CurvesController * controller);

private:
	// ========== RÉFÉRENCE AU CONTRÔLEUR ==========
	SceneController * sceneController = nullptr;

	// ========== RENDERERS SPÉCIALISÉS ==========
	CurvesRenderer curvesRenderer; // Rendu des courbes de Bézier et points de contrôle
	SceneRenderer sceneRenderer; // Rendu des formes 2D et 3D sur la scène
	ImageRenderer imageRenderer; // Rendu des images (background, textures)

	// ========== ZONE DE RENDU ==========
	ofRectangle drawingArea;

	// ========== PARAMÈTRES VISUELS ==========
	float currentLineWidth = 2.0f;
	ofColor currentStrokeColor = ofColor::black;
	ofColor currentFillColor = ofColor::white;
	ofColor currentBgColor = ofColor::white;
	bool useHSBmode = false;

	// ========== MÉTHODES PRIVÉES DE RENDU ==========

	/**
     * @brief Dessine le background de la zone de dessin
     */
	void drawBackground();

};
