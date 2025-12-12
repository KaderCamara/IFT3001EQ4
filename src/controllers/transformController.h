// transformController.h
// Contrôleur responsable de la logique métier des transformations
#pragma once

#include "../objects/sceneGraph.h"
#include "ofMain.h"
#include "../services/transformService.h"

/**
 * @class TransformController
 * @brief Contrôleur gérant la logique métier des transformations (CONTROLLER - MVC)
 * 
 * Responsabilités :
 * - Application des transformations (translation, rotation, scale)
 * - Validation des valeurs de transformation
 * - Gestion des limites et contraintes
 * - Coordination avec le SceneGraph
 */
class TransformController {
public:
	TransformController() = default;
	~TransformController() = default;

	void setup();

	/**
	 * @brief Injecte la référence au SceneGraph
	 */
	void setSceneGraph(SceneGraph * graph) { sceneGraph = graph; }

	// ========== APPLICATION DES TRANSFORMATIONS ==========

	/**
	 * @brief Applique une transformation aux formes sélectionnées
	 * @param tx Translation X
	 * @param ty Translation Y
	 * @param rotation Rotation en degrés
	 * @param scale Facteur d'échelle
	 */
	void applyTransformToSelected(float tx, float ty, float rotation, float scale);

	/**
	 * @brief Réinitialise les transformations des formes sélectionnées
	 */
	void resetSelectedTransforms();

	// ========== VALIDATION ==========

	/**
	 * @brief Valide et clamp les valeurs de transformation
	 * @param tx Translation X (sera modifiée si hors limites)
	 * @param ty Translation Y (sera modifiée si hors limites)
	 * @param rotation Rotation en degrés (sera normalisée à [-360, 360])
	 * @param scale Facteur d'échelle (sera clampé à [minScale, maxScale])
	 */
	void validateAndClampTransform(float & tx, float & ty, float & rotation, float & scale) const;

	// ========== CONFIGURATION DES LIMITES ==========

	void setTranslationLimits(float minX, float maxX, float minY, float maxY) {
		translationMinX = minX;
		translationMaxX = maxX;
		translationMinY = minY;
		translationMaxY = maxY;
	}

	void setRotationLimits(float min, float max) {
		rotationMin = min;
		rotationMax = max;
	}

	void setScaleLimits(float min, float max) {
		scaleMin = min;
		scaleMax = max;
	}

	// ========== ACCESSEURS ==========

	bool hasSelectedShapes() const {
		return sceneGraph && !sceneGraph->selectedIndices.empty();
	}

	int getSelectedCount() const {
		return sceneGraph ? sceneGraph->selectedIndices.size() : 0;
	}

private:
	// Référence au SceneGraph
	SceneGraph * sceneGraph = nullptr;

	// Limites de transformation (par défaut)
	float translationMinX = -2000.0f;
	float translationMaxX = 2000.0f;
	float translationMinY = -2000.0f;
	float translationMaxY = 2000.0f;
	float rotationMin = -720.0f;
	float rotationMax = 720.0f;
	float scaleMin = 0.1f;
	float scaleMax = 5.0f;

	// ========== HELPERS ==========

	/**
	 * @brief Normalise un angle à [-360, 360]
	 */
	float normalizeRotation(float rotation) const;

	/**
	 * @brief Clamp une valeur entre min et max
	 */
	float clamp(float value, float min, float max) const;

	TransformService transformService;
};
