// TransformService.cpp
// Implémentation du service de transformation
#include "TransformService.h"

void TransformService::applyTransform(
	Shape & shape,
	float tx,
	float ty,
	float rotation,
	float scale) const {
	// Valider et clamper les valeurs
	float validTx = tx;
	float validTy = ty;
	float validRot = rotation;
	float validScale = scale;

	validateAndClamp(validTx, validTy, validRot, validScale);

	// Appliquer les transformations
	shape.translation.set(validTx, validTy);
	shape.rotation = validRot;
	shape.scale = validScale;
}

void TransformService::applyTransformToMultiple(
	std::vector<Shape> & shapes,
	const std::vector<int> & indices,
	float tx,
	float ty,
	float rotation,
	float scale) const {
	// Valider et clamper une seule fois
	float validTx = tx;
	float validTy = ty;
	float validRot = rotation;
	float validScale = scale;

	validateAndClamp(validTx, validTy, validRot, validScale);

	// Appliquer à toutes les formes sélectionnées
	for (int index : indices) {
		if (index >= 0 && index < static_cast<int>(shapes.size())) {
			Shape & shape = shapes[index];
			shape.translation.set(validTx, validTy);
			shape.rotation = validRot;
			shape.scale = validScale;
		}
	}
}

void TransformService::resetTransform(Shape & shape) const {
	shape.translation.set(0, 0);
	shape.rotation = 0.0f;
	shape.scale = 1.0f;
}

void TransformService::validateAndClamp(
	float & tx,
	float & ty,
	float & rotation,
	float & scale) const {
	// Clamper la translation
	tx = clamp(tx, TRANSLATION_MIN_X, TRANSLATION_MAX_X);
	ty = clamp(ty, TRANSLATION_MIN_Y, TRANSLATION_MAX_Y);

	// Normaliser et clamper la rotation
	rotation = normalizeRotation(rotation);
	rotation = clamp(rotation, ROTATION_MIN, ROTATION_MAX);

	// Clamper le scale
	scale = clamp(scale, SCALE_MIN, SCALE_MAX);
}

float TransformService::normalizeRotation(float rotation) const {
	// Normaliser à [-360, 360]
	while (rotation > 360.0f) {
		rotation -= 360.0f;
	}
	while (rotation < -360.0f) {
		rotation += 360.0f;
	}
	return rotation;
}

float TransformService::clamp(float value, float min, float max) const {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
