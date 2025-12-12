// SelectionService.h
// Service responsable de la logique de sélection de formes
// Cette logique était auparavant dans SceneGraph (violation MVC)

#pragma once

#include "../objects/shape.h"
#include "ofMain.h"
#include <vector>

/**
 * @class SelectionService
 * @brief Service gérant la logique de sélection de formes (CONTROLLER/SERVICE)
 * 
 * Responsabilités :
 * - Hit-testing (détection de clic sur forme)
 * - Logique de sélection (simple/multiple)
 * - Calcul des zones de sélection
 * 
 * REFACTORISATION MVC :
 * - AVANT : Cette logique était dans SceneGraph (MODEL) ❌
 * - APRÈS : Extraite dans un service dédié (CONTROLLER) ✅
 */
class SelectionService {
public:
	SelectionService() = default;
	~SelectionService() = default;

	/**
	 * @brief Détecte quelle forme (si aucune) est cliquée
	 * @param shapes Liste des formes
	 * @param x Coordonnée X du clic
	 * @param y Coordonnée Y du clic
	 * @return Index de la forme cliquée (-1 si aucune)
	 */
	int findShapeAt(const std::vector<Shape> & shapes, float x, float y) const;

	/**
	 * @brief Met à jour la sélection selon le mode
	 * @param currentSelection Indices actuellement sélectionnés (modifié)
	 * @param clickedIndex Index de la forme cliquée
	 * @param addToSelection true pour multi-sélection (Ctrl/Cmd)
	 */
	void updateSelection(
		std::vector<int> & currentSelection,
		int clickedIndex,
		bool addToSelection) const;

private:
	/**
	 * @brief Vérifie si un point (x, y) est à l'intérieur d'une forme
	 */
	bool isInsideBounds(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour un point
	 */
	bool hitTestPoint(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour une ligne
	 */
	bool hitTestLine(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour un triangle
	 */
	bool hitTestTriangle(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour un carré
	 */
	bool hitTestSquare(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour un rectangle
	 */
	bool hitTestRectangle(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour un cercle
	 */
	bool hitTestCircle(const Shape & shape, float x, float y) const;

	/**
	 * @brief Hit-testing pour un mesh 3D
	 */
	bool hitTestMesh3D(const Shape & shape, float x, float y) const;
};
