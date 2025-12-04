// TransformService.h
// Service responsable de l'application des transformations sur les formes
// Cette logique était auparavant dispersée entre SceneGraph et TransformController

#pragma once

#include "../objects/shape.h"
#include <vector>

/**
 * @class TransformService
 * @brief Service gérant l'application des transformations (CONTROLLER/SERVICE)
 * 
 * Responsabilités :
 * - Appliquer les transformations à des formes
 * - Valider les valeurs de transformation
 * - Calculer les transformations composées
 * 
 * REFACTORISATION MVC :
 * - AVANT : updateSelectedTransform() était dans SceneGraph (MODEL) ❌
 * - APRÈS : Logique extraite dans un service dédié (CONTROLLER) ✅
 */
class TransformService {
public:
	TransformService() = default;
	~TransformService() = default;

	/**
	 * @brief Applique une transformation à une forme
	 * @param shape Forme à transformer (modifiée)
	 * @param tx Translation X
	 * @param ty Translation Y
	 * @param rotation Rotation en degrés
	 * @param scale Facteur d'échelle
	 */
	void applyTransform(
		Shape & shape,
		float tx,
		float ty,
		float rotation,
		float scale) const;

	/**
	 * @brief Applique une transformation à plusieurs formes
	 * @param shapes Formes à transformer
	 * @param indices Indices des formes à transformer
	 * @param tx Translation X
	 * @param ty Translation Y
	 * @param rotation Rotation en degrés
	 * @param scale Facteur d'échelle
	 */
	void applyTransformToMultiple(
		std::vector<Shape> & shapes,
		const std::vector<int> & indices,
		float tx,
		float ty,
		float rotation,
		float scale) const;

	/**
	 * @brief Réinitialise les transformations d'une forme
	 * @param shape Forme à réinitialiser
	 */
	void resetTransform(Shape & shape) const;

	/**
	 * @brief Valide et clamp une transformation
	 * @param tx Translation X (sera modifiée si hors limites)
	 * @param ty Translation Y (sera modifiée si hors limites)
	 * @param rotation Rotation (sera normalisée)
	 * @param scale Scale (sera clampée)
	 */
	void validateAndClamp(
		float & tx,
		float & ty,
		float & rotation,
		float & scale) const;

private:
	// Limites par défaut
	static constexpr float TRANSLATION_MIN_X = -2000.0f;
	static constexpr float TRANSLATION_MAX_X = 2000.0f;
	static constexpr float TRANSLATION_MIN_Y = -2000.0f;
	static constexpr float TRANSLATION_MAX_Y = 2000.0f;
	static constexpr float ROTATION_MIN = -720.0f;
	static constexpr float ROTATION_MAX = 720.0f;
	static constexpr float SCALE_MIN = 0.1f;
	static constexpr float SCALE_MAX = 5.0f;

	/**
	 * @brief Normalise un angle à [-360, 360]
	 */
	float normalizeRotation(float rotation) const;

	/**
	 * @brief Clamp une valeur entre min et max
	 */
	float clamp(float value, float min, float max) const;
};
