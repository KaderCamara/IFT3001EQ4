# pragma once

#include "ofMain.h"
#include <vector>
#include "glm/glm.hpp"

/**
 * @file controlPointsManager.h
 * @brief Management of control points used for drawing curves.
 */

/**
 * @class ControlPointsManager
 * @brief Manages a set of control points used to draw curves.
 *
 * This class stores control points and provides helpers to draw them,
 * add new points, undo the last point, and clear all points.
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

	/**
	 * @brief Draws the control points and the segments between them.
	 *
	 * This method does not modify the internal state of the class.
	 */
	void drawPointsForCurves() const;

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
