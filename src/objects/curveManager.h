#pragma once

#include "BezierCurve.h"
#include <vector>

/**
 * @file curveManager.h
 * @brief Manages a collection of Bezier curves.
 * 
 * REFACTORISATION MVC :
 * - AVANT : CurveManager::draw() mélangeait MODEL + VIEW
 * - APRÈS : CurveManager = MODEL pur (gestion de collection uniquement)
 * - Le rendu est délégué à CurvesRenderer (VIEW)
 */

/**
 * @class CurveManager
 * @brief Container for multiple BezierCurve instances (MODEL)
 *
 * Provides operations to add new curves, clear the collection and
 * provide access to the curves.
 * 
 * Responsabilités (MODEL) :
 * - Stocker une collection de courbes de Bézier
 * - Ajouter/supprimer des courbes
 * - Fournir des accesseurs pour les données
 * - AUCUN rendu (délégué à CurvesRenderer)
 */
class CurveManager {
public:
	/**
	 * @brief Add a new Bezier curve constructed from the given control points.
	 *
	 * @param controlPoints Control points used to construct the new curve.
	 */
	void addBezierCurve(const std::vector<glm::vec2> & controlPoints);

	/**
	 * @brief Remove all curves from the manager.
	 */
	void clear();

	// ========== SUPPRIMÉ : draw() const ==========
	// AVANT : void draw() const;
	// APRÈS : Le rendu est délégué à CurvesRenderer
	// Utilisation : CurvesRenderer renderer;
	//               renderer.renderCurvesOnly(manager);

	/**
	 * @brief Get the list of managed Bezier curves.
	 *
	 * @return A const reference to the internal vector of BezierCurve objects.
	 */
	const std::vector<BezierCurve> & getCurves() const { return bezierCurves; }

private:
	/// Internal storage of BezierCurve objects.
	std::vector<BezierCurve> bezierCurves;
};
