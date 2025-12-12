#pragma once

#include "glm/glm.hpp"
#include "ofMain.h"
#include <vector>

/**
 * @file controlPointsManager.h
 * @brief Management of control points used for drawing curves.
 * 
 * REFACTORISATION MVC :
 * - AVANT : ControlPointsManager::drawPointsForCurves() mélangeait MODEL + VIEW
 * - APRÈS : ControlPointsManager = MODEL pur (données + logique métier uniquement)
 * - Le rendu est délégué à ControlPointsRenderer (VIEW)
 */

/**
 * @class ControlPointsManager
 * @brief Manages a set of control points used to draw curves (MODEL)
 *
 * This class stores control points and provides operations to add, remove,
 * and query control points.
 * 
 * Responsabilités (MODEL) :
 * - Stocker les points de contrôle
 * - Ajouter/supprimer des points
 * - Fournir des accesseurs pour les données
 * - AUCUN rendu (délégué à ControlPointsRenderer)
 */
class ControlPointsManager {
public:
	/**
	 * @brief Default constructor.
	 */
	ControlPointsManager() = default;

	/**
	 * @brief Default destructor.
	 */
	~ControlPointsManager() = default;

	// ========== SUPPRIMÉ : drawPointsForCurves() const ==========
	// AVANT : void drawPointsForCurves() const;
	// APRÈS : Le rendu est délégué à ControlPointsRenderer
	// Utilisation : ControlPointsRenderer renderer;
	//               renderer.render(manager.getControlPoints());

	/**
	 * @brief Adds a control point at integer coordinates (x, y).
	 *
	 * @param x X coordinate of the point.
	 * @param y Y coordinate of the point.
	 *
	 * @note The caller should ensure the point lies within the drawing area
	 *       if that is required by the application.
	 */
	void addControlPoint(int x, int y);

	/**
	 * @brief Retrieves the list of control points.
	 *
	 * @return A copy of the internal vector of points. A copy is returned to
	 *         preserve encapsulation; if you need to avoid copies consider
	 *         adding a const-reference accessor.
	 */
	std::vector<glm::vec2> getControlPoints() const;

	/**
	 * @brief Removes the last added control point if any.
	 */
	void undoLastPoint();

	/**
	 * @brief Clears all control points.
	 */
	void clearPoints();

private:
	/// Internal vector storing the control points.
	std::vector<glm::vec2> controlPoints;

	/// Indicates whether a point preview is active (currently unused).
	bool hasPointPreview = false;

	/// Coordinates of the point preview (if used).
	glm::vec2 pointPreview;

	/// Optional start point (currently unused).
	glm::vec2 startPoint;
};
