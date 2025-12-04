// CurvesRenderer.h
// Renderer de courbes MVC PUR (VIEW uniquement)
// ✅ AUCUNE référence aux Managers
// ✅ Reçoit uniquement des données pures

#pragma once

#include "../../objects/BezierCurve.h"
#include "BezierCurveRenderer.h"
#include "ControlPointsRenderer.h"
#include "ofMain.h"
#include <vector>

/**
 * @class CurvesRenderer
 * @brief Renderer de courbes de Bézier MVC PUR (VIEW)
 * 
 * Responsabilités (VIEW PURE) :
 * - Dessiner les points de contrôle
 * - Dessiner les courbes de Bézier
 * - Coordonner BezierCurveRenderer et ControlPointsRenderer
 * - AUCUNE logique métier
 * - AUCUNE référence aux Managers
 * 
 * REFACTORISATION MVC :
 * - AVANT : Références à ControlPointsManager et CurveManager ❌
 * - APRÈS : Reçoit uniquement des vecteurs de données pures ✅
 */
class CurvesRenderer {
public:
	CurvesRenderer();
	~CurvesRenderer() = default;

	// ========== MÉTHODES DE RENDU (VIEW PURE) ==========

	/**
	 * @brief Dessine les points de contrôle et les courbes
	 * @param controlPoints Points de contrôle (données pures)
	 * @param curves Courbes de Bézier (données pures)
	 */
	void render(
		const std::vector<glm::vec2> & controlPoints,
		const std::vector<BezierCurve> & curves) const;

	/**
	 * @brief Dessine uniquement les points de contrôle
	 * @param controlPoints Points de contrôle (données pures)
	 */
	void renderControlPointsOnly(const std::vector<glm::vec2> & controlPoints) const;

	/**
	 * @brief Dessine uniquement les courbes de Bézier
	 * @param curves Courbes de Bézier (données pures)
	 */
	void renderCurvesOnly(const std::vector<BezierCurve> & curves) const;

	// ========== CONFIGURATION DU STYLE ==========

	void setControlPointsColor(const ofColor & color) { controlPointsColor = color; }
	void setCurvesColor(const ofColor & color) { curvesColor = color; }
	void setShowPointNumbers(bool show) { showPointNumbers = show; }
	void setControlPointRadius(float radius) { controlPointRadius = radius; }
	void setLineWidth(float width) { lineWidth = width; }

private:
	// Renderers spécialisés (VIEW)
	BezierCurveRenderer bezierRenderer;
	ControlPointsRenderer controlPointsRenderer;

	// Paramètres de style (configuration visuelle)
	ofColor controlPointsColor = ofColor::red;
	ofColor curvesColor = ofColor::blue;
	float controlPointRadius = 4.0f;
	float lineWidth = 2.0f;
	bool showPointNumbers = true;
};
