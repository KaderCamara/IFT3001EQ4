// curvesController.h
// Contrôleur responsable de la logique métier des courbes de Bézier
#pragma once

#include "../objects/controlPointsManager.h"
#include "../objects/curveManager.h"
#include "../objects/CurveAnimator.h"
#include "ofMain.h"

/**
 * @class CurvesController
 * @brief Contrôleur gérant la logique métier des courbes de Bézier (CONTROLLER - MVC)
 * 
 * Responsabilités :
 * - Gestion des points de contrôle
 * - Génération des courbes de Bézier
 * - Validation des opérations
 * - Coordination entre ControlPointsManager et CurveManager
 * - AUCUN rendu (délégué à CurvesRenderer)
 * 
 * REFACTORISATION :
 * Code extrait de SceneController pour alléger ses responsabilités
 */
class CurvesController {
public:
	CurvesController() = default;
	~CurvesController() = default;

	void setup();

	// ========== GESTION DES POINTS DE CONTRÔLE ==========

	/**
	 * @brief Ajoute un point de contrôle
	 * @param x Coordonnée X
	 * @param y Coordonnée Y
	 * @param drawingArea Zone de dessin pour validation
	 * @return true si le point a été ajouté
	 */
	bool addControlPoint(int x, int y, const ofRectangle & drawingArea);

	/**
	 * @brief Annule le dernier point de contrôle ajouté
	 */
	void undoLastControlPoint();

	/**
	 * @brief Efface tous les points de contrôle
	 */
	void clearControlPoints();

	/**
	 * @brief Récupère le nombre de points de contrôle
	 */
	int getControlPointsCount() const {
		return controlPointsManager.getControlPoints().size();
	}

	// ========== GESTION DES COURBES ==========

	/**
	 * @brief Génère une courbe de Bézier à partir des points de contrôle actuels
	 * @return true si la courbe a été générée avec succès
	 */
	bool generateBezierCurve();

	/**
	 * @brief Efface toutes les courbes générées
	 */
	void clearCurves();

	/**
	 * @brief Récupère le nombre de courbes générées
	 */
	int getCurvesCount() const {
		return curveManager.getCurves().size();
	}

	// ========== ACCESSEURS POUR LE RENDERER ==========

	ControlPointsManager & getControlPointsManager() { return controlPointsManager; }
	const ControlPointsManager & getControlPointsManager() const { return controlPointsManager; }

	CurveManager & getCurveManager() { return curveManager; }
	const CurveManager & getCurveManager() const { return curveManager; }

	const CurveAnimator & getAnimator() const { return animator; }
	bool isAnimationPlaying() const { return animator.isPlaying(); }

	// ========== ANIMATIONS ==========
	void startAnimation();
	void stopAnimation();
	void toggleAnimation();
	void updateAnimation(float deltaTime);


private:
	// Managers (MODEL)
	ControlPointsManager controlPointsManager;
	CurveManager curveManager;
	CurveAnimator animator;

	// ========== VALIDATION ==========

	/**
	 * @brief Valide qu'un point est dans la zone de dessin
	 */
	bool isPointInDrawingArea(int x, int y, const ofRectangle & drawingArea) const;

	/**
	 * @brief Valide qu'il y a assez de points pour générer une courbe
	 */
	bool hasEnoughPointsForCurve() const;
};

// Inline implementations moved from curvesController.cpp to ensure linkage

inline void CurvesController::setup() {
	ofLogNotice("CurvesController") << "Setup complete";
}

inline bool CurvesController::addControlPoint(int x, int y, const ofRectangle & drawingArea) {
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

inline void CurvesController::undoLastControlPoint() {
	int countBefore = getControlPointsCount();

	controlPointsManager.undoLastPoint();

	int countAfter = getControlPointsCount();

	if (countAfter < countBefore) {
		ofLogNotice("CurvesController") << "Last control point undone (remaining: " << countAfter << ")";
	} else {
		ofLogWarning("CurvesController") << "No control point to undo";
	}
}

inline void CurvesController::clearControlPoints() {
	int count = getControlPointsCount();

	controlPointsManager.clearPoints();

	ofLogNotice("CurvesController") << count << " control point(s) cleared";
}

inline bool CurvesController::generateBezierCurve() {
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

	// Setup animator avec la dernière courbe générée
	if (!curveManager.getCurves().empty()) {
		animator.setup(curveManager.getCurves().back(), 3.0f);
	}

	ofLogNotice("CurvesController") << "Bezier curve generated with "
				<< getControlPointsCount() << " control points";


	return true;
}

inline void CurvesController::clearCurves() {
	int count = getCurvesCount();

	curveManager.clear();

	if (count > 0) {
		ofLogNotice("CurvesController") << count << " curve(s) cleared";
	}
}

inline bool CurvesController::isPointInDrawingArea(int x, int y, const ofRectangle & drawingArea) const {
	return drawingArea.inside(x, y);
}

inline bool CurvesController::hasEnoughPointsForCurve() const {
	// Besoin d'au moins 2 points pour une courbe
	return getControlPointsCount() >= 2;
}

inline void CurvesController::startAnimation() {
	if (!curveManager.getCurves().empty()) {
		animator.setup(curveManager.getCurves().back(), 3.0f);
		animator.play();
		ofLogNotice("CurvesController") << "Animation started";
	} else {
		ofLogWarning("CurvesController") << "Cannot start animation: no curves available";
	}
}

inline void CurvesController::stopAnimation() {
	animator.pause();
	animator.reset();
	ofLogNotice("CurvesController") << "Animation stopped";
}

inline void CurvesController::toggleAnimation() {
	if (animator.isPlaying()) {
		animator.pause();
		ofLogNotice("CurvesController") << "Animation paused";
	} else {
		animator.play();
		ofLogNotice("CurvesController") << "Animation resumed";
	}
}

inline void CurvesController::updateAnimation(float deltaTime) {
	animator.update(deltaTime);
}
