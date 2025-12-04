// curvesController.h
// Contrôleur responsable de la logique métier des courbes de Bézier
#pragma once

#include "../objects/controlPointsManager.h"
#include "../objects/curveManager.h"
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

private:
	// Managers (MODEL)
	ControlPointsManager controlPointsManager;
	CurveManager curveManager;

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
