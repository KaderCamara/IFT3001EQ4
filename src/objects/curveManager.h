#pragma once

#include "BezierCurve.h"
#include <vector>

/**
 * @file curveManager.h
 * @brief Manages a collection of Bezier curves.
 */

/**
 * @class CurveManager
 * @brief Container for multiple BezierCurve instances.
 *
 * Provides operations to add new curves, clear the collection and draw all curves.
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

	/**
	 * @brief Draw all managed Bezier curves.
	 */
	void draw() const;

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
