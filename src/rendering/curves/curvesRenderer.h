// CurvesRenderer.h
// Orchestrateur pour le rendu complet des courbes et points de contrôle
#pragma once

#include "../../objects/controlPointsManager.h"
#include "../../objects/curveManager.h"
#include "BezierCurveRenderer.h"
#include "ControlPointsRenderer.h"
#include "ofMain.h"

/**
 * @class CurvesRenderer
 * @brief Orchestrateur de rendu pour les courbes de Bézier et points de contrôle (VIEW)
 * 
 * Responsabilités :
 * - Coordonner BezierCurveRenderer et ControlPointsRenderer
 * - Fournir une interface unifiée pour le Renderer principal
 * - Gérer l'ordre de rendu (points de contrôle puis courbes)
 * - Appliquer les styles visuels cohérents
 */
class CurvesRenderer {
public:
	CurvesRenderer();
	~CurvesRenderer() = default;

	/**
	 * @brief Dessine les points de contrôle et les courbes de Bézier
	 * @param controlPointsManager Manager contenant les points de contrôle
	 * @param curveManager Manager contenant les courbes
	 */
	void render(const ControlPointsManager & controlPointsManager,
		const CurveManager & curveManager) const;

	/**
	 * @brief Dessine uniquement les points de contrôle
	 * @param controlPointsManager Manager contenant les points
	 */
	void renderControlPointsOnly(const ControlPointsManager & controlPointsManager) const;

	/**
	 * @brief Dessine uniquement les courbes de Bézier
	 * @param curveManager Manager contenant les courbes
	 */
	void renderCurvesOnly(const CurveManager & curveManager) const;

	// ========== CONFIGURATION DU STYLE ==========

	/**
	 * @brief Configure la couleur des points de contrôle
	 */
	void setControlPointsColor(const ofColor & color) { controlPointsColor = color; }

	/**
	 * @brief Configure la couleur des courbes
	 */
	void setCurvesColor(const ofColor & color) { curvesColor = color; }

	/**
	 * @brief Active/désactive l'affichage des numéros de points
	 */
	void setShowPointNumbers(bool show) { showPointNumbers = show; }

	/**
	 * @brief Configure le rayon des points de contrôle
	 */
	void setControlPointRadius(float radius) { controlPointRadius = radius; }

	/**
	 * @brief Configure l'épaisseur des lignes
	 */
	void setLineWidth(float width) { lineWidth = width; }

private:
	// Renderers spécialisés
	BezierCurveRenderer bezierRenderer;
	ControlPointsRenderer controlPointsRenderer;

	// Paramètres de style
	ofColor controlPointsColor = ofColor::red;
	ofColor curvesColor = ofColor::blue;
	float controlPointRadius = 4.0f;
	float lineWidth = 2.0f;
	bool showPointNumbers = true;
};
