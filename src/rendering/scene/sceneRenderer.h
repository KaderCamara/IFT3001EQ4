// SceneRenderer.h
// Renderer de scène MVC PUR (VIEW uniquement)
// ✅ AUCUNE référence aux Controllers
// ✅ Reçoit uniquement des données via RenderData

#pragma once

#include "../RenderData.h"
#include "../curves/CurvesRenderer.h"
#include "../shapes/Shape2DRenderer.h"
#include "../shapes/Shape3DRenderer.h"
#include "ofMain.h"

/**
 * @class SceneRenderer
 * @brief Renderer de scène MVC PUR (VIEW)
 * 
 * Responsabilités (VIEW PURE) :
 * - Dessiner la scène 2D à partir de données
 * - Dessiner la scène 3D à partir de données
 * - Dessiner la vue quad à partir de données
 * - AUCUNE logique métier
 * - AUCUNE référence aux Controllers
 * - AUCUN accès aux Managers
 * 
 * REFACTORISATION MVC :
 * - AVANT : Références à SceneController et CurvesController ❌
 * - APRÈS : Reçoit uniquement des RenderData (structures pures) ✅
 */
class SceneRenderer {
public:
	SceneRenderer() = default;
	~SceneRenderer() = default;

	// ========== MÉTHODES DE RENDU (VIEW PURE) ==========

	/**
	 * @brief Dessine la scène en mode 2D
	 * @param data Données pures nécessaires au rendu 2D
	 */
	void draw2D(const RenderDataDraw2D & data);

	/**
	 * @brief Dessine la scène en mode 3D
	 * @param data Données pures nécessaires au rendu 3D
	 */
	void draw3D(const RenderData3D & data);

	/**
	 * @brief Dessine la scène en vue quad (4 caméras)
	 * @param data Données pures nécessaires au rendu quad
	 */
	void drawQuadView(const RenderDataQuad & data);

	// ========== CONFIGURATION VISUELLE ==========

	/**
	 * @brief Configure les options d'affichage 3D
	 */
	void set3DDisplayOptions(bool showBoundingBox, bool showWireframe, bool showNormals);

private:
	// ========== RENDERERS SPÉCIALISÉS (VIEW) ==========
	Shape2DRenderer shape2DRenderer;
	Shape3DRenderer shape3DRenderer;
	CurvesRenderer curvesRenderer;

	// ========== OPTIONS D'AFFICHAGE ==========
	bool showBoundingBox3D = false;
	bool showWireframe3D = false;
	bool showNormals3D = false;

	// ========== MÉTHODES PRIVÉES DE RENDU ==========

	/**
	 * @brief Dessine une vue de caméra individuelle (pour mode quad)
	 */
	void drawSingleCameraView(
		const std::vector<Shape> & shapes,
		const CameraData & camera,
		const ofRectangle & viewport,
		const std::string & label);

	/**
	 * @brief Dessine les séparateurs de la vue quad
	 */
	void drawQuadViewSeparators(const RenderDataQuad & data);

	/**
	 * @brief Configure une caméra OpenFrameworks à partir de CameraData
	 */
	void applyCameraData(ofCamera & cam, const CameraData & data);
};
