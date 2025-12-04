// transformController.cpp
// Implémentation du contrôleur de transformations
#include "transformController.h"

void TransformController::setup() {
	ofLogNotice("TransformController") << "Setup complete";
}

// ========== APPLICATION DES TRANSFORMATIONS ==========

void TransformController::applyTransformToSelected(float tx, float ty, float rotation, float scale) {
	// Vérifier qu'on a un SceneGraph et des formes sélectionnées
	if (!sceneGraph) {
		ofLogError("TransformController") << "No SceneGraph set";
		return;
	}

	if (!hasSelectedShapes()) {
		ofLogVerbose("TransformController") << "No shapes selected";
		return;
	}

	// Valider et clamper les valeurs
	validateAndClampTransform(tx, ty, rotation, scale);

	// Appliquer via le SceneGraph
	transformService.applyTransformToMultiple(
		sceneGraph->shapes, // Accès aux données
		sceneGraph->selectedIndices, // Accès aux données
		tx, ty, rotation, scale);

	ofLogVerbose("TransformController") << "Transform applied to " << getSelectedCount()
										<< " shape(s): T(" << tx << ", " << ty << ") R(" << rotation
										<< ") S(" << scale << ")";
}

void TransformController::resetSelectedTransforms() {
	if (!hasSelectedShapes()) {
		ofLogWarning("TransformController") << "No shapes selected to reset";
		return;
	}

	// Réinitialiser à l'identité
	applyTransformToSelected(0.0f, 0.0f, 0.0f, 1.0f);

	ofLogNotice("TransformController") << "Transforms reset for " << getSelectedCount() << " shape(s)";
}

// ========== VALIDATION ==========

void TransformController::validateAndClampTransform(float & tx, float & ty, float & rotation, float & scale) const {
	// Clamper la translation
	tx = clamp(tx, translationMinX, translationMaxX);
	ty = clamp(ty, translationMinY, translationMaxY);

	// Normaliser et clamper la rotation
	rotation = normalizeRotation(rotation);
	rotation = clamp(rotation, rotationMin, rotationMax);

	// Clamper le scale
	scale = clamp(scale, scaleMin, scaleMax);
}

// ========== HELPERS ==========

float TransformController::normalizeRotation(float rotation) const {
	// Normaliser à [-360, 360]
	while (rotation > 360.0f) {
		rotation -= 360.0f;
	}
	while (rotation < -360.0f) {
		rotation += 360.0f;
	}
	return rotation;
}

float TransformController::clamp(float value, float min, float max) const {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
