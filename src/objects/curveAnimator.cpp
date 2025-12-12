#include "CurveAnimator.h"

void CurveAnimator::setup(const BezierCurve & bezierCurve, float animDuration) {
	curve = bezierCurve;
	duration = animDuration;
	currentTime = 0.0f;
	playing = false;

	currentObject.position = glm::vec2(0, 0);
	currentObject.rotation = 0.0f;
	currentObject.scale = 1.0f;
	currentObject.color = ofColor::cyan;
}

void CurveAnimator::update(float deltaTime) {
	if (!playing) return;

	// Vérifier si la courbe a des points échantillonnés
	if (curve.getCurvePoints().empty()) return;

	currentTime += deltaTime;

	if (currentTime >= duration) {
		if (looping) {
			currentTime = fmod(currentTime, duration);
		} else {
			currentTime = duration;
			playing = false;
		}
	}

	float t = duration > 0 ? currentTime / duration : 0;
	updateObjectFromCurve(t);
}

void CurveAnimator::updateObjectFromCurve(float t) {
	const std::vector<glm::vec2> & points = curve.getCurvePoints();
	if (points.empty()) return;

	// Trouver l'index dans les points échantillonnés
	int numPoints = static_cast<int>(points.size());
	float floatIndex = t * (numPoints - 1);
	int index = static_cast<int>(floatIndex);

	// Clamp pour sécurité
	index = std::max(0, std::min(index, numPoints - 1));

	// Position sur la courbe
	currentObject.position = points[index];

	// Rotation basée sur tangente (direction du mouvement)
	glm::vec2 tangent = getTangent(index, points);
	currentObject.rotation = atan2(tangent.y, tangent.x) * RAD_TO_DEG;

	// Scale animé (oscillation sinusoïdale)
	currentObject.scale = 1.0f + 0.3f * sin(t * TWO_PI * 2.0f);

	// Couleur animée (cycle HSB)
	float hue = fmod(t * 360.0f, 360.0f);
	currentObject.color.setHsb(hue, 200, 255);
}

glm::vec2 CurveAnimator::getTangent(float t) {
	const std::vector<glm::vec2> & points = curve.getCurvePoints();
	if (points.empty()) return glm::vec2(1, 0);

	int numPoints = static_cast<int>(points.size());
	float floatIndex = t * (numPoints - 1);
	int index = static_cast<int>(floatIndex);
	index = std::max(0, std::min(index, numPoints - 1));

	return getTangent(index, points);
}

glm::vec2 CurveAnimator::getTangent(int index, const std::vector<glm::vec2> & points) const {
	if (points.size() < 2) return glm::vec2(1, 0);

	int numPoints = static_cast<int>(points.size());

	// Calculer la tangente en regardant les points voisins
	if (index == 0) {
		// Premier point : regarder vers l'avant
		glm::vec2 tangent = points[1] - points[0];
		float length = glm::length(tangent);
		return length > 0.0001f ? tangent / length : glm::vec2(1, 0);
	} else if (index >= numPoints - 1) {
		// Dernier point : regarder vers l'arrière
		glm::vec2 tangent = points[numPoints - 1] - points[numPoints - 2];
		float length = glm::length(tangent);
		return length > 0.0001f ? tangent / length : glm::vec2(1, 0);
	} else {
		// Point milieu : moyenne des deux directions
		glm::vec2 tangent = points[index + 1] - points[index - 1];
		float length = glm::length(tangent);
		return length > 0.0001f ? tangent / length : glm::vec2(1, 0);
	}
}

void CurveAnimator::reset() {
	currentTime = 0.0f;
	playing = false;
}
