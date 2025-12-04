// curvesController.cpp
// Implémentation du contrôleur de courbes
#include "curvesController.h"

void CurvesController::setup() {
	ofLogNotice("CurvesController") << "Setup complete";
}

// ========== GESTION DES POINTS DE CONTRÔLE ==========

bool CurvesController::addControlPoint(int x, int y, const ofRectangle & drawingArea) {
	// Valider que le point est dans la zone de dessin
	if (!isPointInDrawingArea(x, y, drawingArea)) {
		ofLogWarning("CurvesController") << "Control point outside drawing area: (" << x << ", " << y << ")";
		return false;
	}

	// Ajouter le point via le manager
	controlPointsManager.addControlPoint(x, y);

	ofLogVerbose("CurvesController") << "Control point added at (" << x << ", " << y << ")";
	return true;
}

void CurvesController::undoLastControlPoint() {
	int countBefore = getControlPointsCount();

	controlPointsManager.undoLastPoint();

	int countAfter = getControlPointsCount();

	if (countAfter < countBefore) {
		ofLogNotice("CurvesController") << "Last control point undone (remaining: " << countAfter << ")";
	} else {
		ofLogWarning("CurvesController") << "No control point to undo";
	}
}

void CurvesController::clearControlPoints() {
	int count = getControlPointsCount();

	controlPointsManager.clearPoints();

	ofLogNotice("CurvesController") << count << " control point(s) cleared";
}

// ========== GESTION DES COURBES ==========

bool CurvesController::generateBezierCurve() {
	// Valider qu'il y a assez de points
	if (!hasEnoughPointsForCurve()) {
		ofLogWarning("CurvesController") << "Need at least 2 control points to generate curve (have "
										 << getControlPointsCount() << ")";
		return false;
	}

	// Effacer les courbes précédentes
	clearCurves();

	// Générer la nouvelle courbe
	curveManager.addBezierCurve(controlPointsManager.getControlPoints());

	ofLogNotice("CurvesController") << "Bezier curve generated with "
									<< getControlPointsCount() << " control points";
	return true;
}

void CurvesController::clearCurves() {
	int count = getCurvesCount();

	curveManager.clear();

	if (count > 0) {
		ofLogNotice("CurvesController") << count << " curve(s) cleared";
	}
}

// ========== VALIDATION ==========

bool CurvesController::isPointInDrawingArea(int x, int y, const ofRectangle & drawingArea) const {
	return drawingArea.inside(x, y);
}

bool CurvesController::hasEnoughPointsForCurve() const {
	// Besoin d'au moins 2 points pour une courbe
	return getControlPointsCount() >= 2;
}
