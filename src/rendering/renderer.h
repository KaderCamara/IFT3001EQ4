// Renderer.h
// Renderer principal MVC PUR (VIEW uniquement)
// ✅ AUCUNE référence aux Controllers
// ✅ Reçoit uniquement des RenderData préparées par Application

#pragma once

#include "RenderData.h"
#include "curves/CurvesRenderer.h"
#include "image/ImageRenderer.h"
#include "ofMain.h"
#include "scene/SceneRenderer.h"

/**
 * @class Renderer
 * @brief Orchestrateur principal de rendu MVC PUR (VIEW)
 * 
 * Responsabilités (VIEW PURE) :
 * - Coordonner les renderers spécialisés
 * - Dessiner le background
 * - Router vers le bon renderer selon les données reçues
 * - Appliquer les paramètres visuels globaux
 * - AUCUNE logique métier
 * - AUCUNE référence aux Controllers
 * 
 * Note : L'Application (CONTROLLER principal) est responsable de :
 * 1. Préparer les RenderData à partir des Controllers
 * 2. Pousser les RenderData au Renderer
 */
class Renderer {
public:
	Renderer();
	~Renderer() = default;

	void setup();

	// ========== MÉTHODES DE RENDU (VIEW PURE) ==========

	/**
	 * @brief Dessine la scène en mode 2D
	 * @param data Données pures préparées par Application
	 */
	void draw2D(const RenderData2D & data);

	/**
	 * @brief Dessine la scène en mode 3D
	 * @param data Données pures préparées par Application
	 */
	void draw3D(const RenderData3D & data);

	/**
	 * @brief Dessine la scène en vue quad (4 caméras)
	 * @param data Données pures préparées par Application
	 */
	void drawQuad(const RenderDataQuad & data);

	// ========== CONFIGURATION VISUELLE ==========

	void setDrawingArea(const ofRectangle & area) { drawingArea = area; }
	ofRectangle getDrawingArea() const { return drawingArea; }

	/**
	 * @brief Configure les paramètres visuels (appelé par Application)
	 */
	void setVisualParameters(
		float lineW,
		const ofColor & stroke,
		const ofColor & fill,
		const ofColor & bg);

	/**
	 * @brief Configure les options d'affichage 3D
	 */
	void set3DDisplayOptions(bool showBoundingBox, bool showWireframe);

	// Accesseurs
	ImageRenderer & getImageRenderer() { return imageRenderer; }

private:
	// ========== RENDERERS SPÉCIALISÉS (VIEW) ==========
	SceneRenderer sceneRenderer;
	CurvesRenderer curvesRenderer;
	ImageRenderer imageRenderer;

	// ========== ZONE DE RENDU ==========
	ofRectangle drawingArea;

	// ========== PARAMÈTRES VISUELS ==========
	float currentLineWidth = 2.0f;
	ofColor currentStrokeColor = ofColor::black;
	ofColor currentFillColor = ofColor::white;
	ofColor currentBgColor = ofColor(180, 200, 220);

	// Options 3D
	bool showBoundingBox3D = false;
	bool showWireframe3D = false;

	// ========== MÉTHODES PRIVÉES DE RENDU ==========

	/**
	 * @brief Dessine le background de la zone de dessin
	 */
	void drawBackground(const ofColor & bgColor);
};
