#include "CurveManager.h"

/**
 * @file curveManager.cpp
 * @brief Implementation of CurveManager: manage multiple Bezier curves.
 * 
 * REFACTORISATION MVC :
 * - SUPPRIMÉ : draw() (maintenant dans CurvesRenderer)
 * - CONSERVÉ : Toute la logique de gestion de collection (MODEL)
 */

void CurveManager::addBezierCurve(const std::vector<glm::vec2> & controlPoints) {
	// Construct a BezierCurve from the provided control points and store it.
	BezierCurve curve(controlPoints);
	bezierCurves.push_back(curve);
}

void CurveManager::clear() {
	// Remove all stored curves.
	bezierCurves.clear();
}

// ========== SUPPRIMÉ : draw() const ==========
// AVANT :
// void CurveManager::draw() const {
//     for (const auto & curve : bezierCurves) {
//         curve.draw();
//     }
// }
//
// APRÈS : Le rendu est délégué à CurvesRenderer::renderCurvesOnly()
// ================================================================
