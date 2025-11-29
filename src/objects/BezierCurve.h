#pragma once

#include "ofMain.h"
#include <vector>

/**
 * @file BezierCurve.h
 * @brief Representation of a Bezier curve built from control points.
 */

/**
 * @class BezierCurve
 * @brief Computes and stores a Bezier curve defined by control points.
 *
 * The class holds the control points and a sampled set of curve points
 * (samples) computed by the recompute() method.
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
	 * @brief Recompute the sampled points of the curve.
	 *
	 * This generates `segments` samples along the curve and stores them in
	 * the internal `curvePoints` vector. The default number of segments is 100.
	 *
	 * @param segments Number of segments/samples to compute along the curve.
	 */
	void recompute(int segments = 100);

	/**
	 * @brief Draw the computed Bezier curve (using the sampled points).
	 */
	void draw() const;

private:
	/// Control points that define the Bezier curve.
	std::vector<glm::vec2> controlPoints;

	/// Sampled points representing the evaluated curve.
	std::vector<glm::vec2> curvePoints;
};
