#pragma once

#include "ofMain.h"
#include <vector>

/**
 * @file BezierCurve.h
 * @brief Representation of a Bezier curve built from control points.
 * 
 * REFACTORISATION MVC :
 * - AVANT : BezierCurve::draw() mélangeait MODEL + VIEW
 * - APRÈS : BezierCurve = MODEL pur (données uniquement)
 * - Le rendu est délégué à BezierCurveRenderer (VIEW)
 */

/**
 * @class BezierCurve
 * @brief Computes and stores a Bezier curve defined by control points (MODEL)
 *
 * The class holds the control points and a sampled set of curve points
 * (samples) computed by the recompute() method.
 * 
 * Responsabilités (MODEL) :
 * - Stocker les points de contrôle
 * - Calculer les points échantillonnés de la courbe
 * - Fournir des accesseurs pour les données
 * - AUCUN rendu (délégué à BezierCurveRenderer)
 */
class BezierCurve {
public:
	/**
	 * @brief Default constructor.
	 */
	BezierCurve() = default;

	/**
	 * @brief Construct a Bezier curve from a set of control points.
	 *
	 * @param controlPts The control points defining the Bezier curve.
	 */
	explicit BezierCurve(const std::vector<glm::vec2> & controlPts);

	/**
	 * @brief Set the control points for this curve.
	 *
	 * @param controlPts New control points to use.
	 */
	void setControlPoints(const std::vector<glm::vec2> & controlPts);

	/**
	 * @brief Get the control points used by this Bezier curve.
	 *
	 * @return A const reference to the internal control points vector.
	 */
	const std::vector<glm::vec2> & getControlPoints() const { return controlPoints; }

	/**
	 * @brief Get the sampled curve points (échantillonnage de la courbe).
	 *
	 * @return A const reference to the internal curve points vector.
	 * 
	 * @note Ces points sont utilisés par BezierCurveRenderer pour le rendu
	 */
	const std::vector<glm::vec2> & getCurvePoints() const { return curvePoints; }

	/**
	 * @brief Recompute the sampled points of the curve.
	 *
	 * This generates `segments` samples along the curve and stores them in
	 * the internal `curvePoints` vector. The default number of segments is 100.
	 *
	 * @param segments Number of segments/samples to compute along the curve.
	 */
	void recompute(int segments = 100);

	// ========== SUPPRIMÉ : draw() ==========
	// AVANT : void draw() const;
	// APRÈS : Le rendu est délégué à BezierCurveRenderer
	// Utilisation : BezierCurveRenderer renderer; renderer.render(curve);

private:
	/// Control points that define the Bezier curve.
	std::vector<glm::vec2> controlPoints;

	/// Sampled points representing the evaluated curve.
	std::vector<glm::vec2> curvePoints;
};
