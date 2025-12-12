// SelectionService.cpp
// Implémentation du service de sélection (logique métier)
#include "SelectionService.h"
#include <algorithm>
#include <cfloat>
#include <cmath>

int SelectionService::findShapeAt(const std::vector<Shape> & shapes, float x, float y) const {
	// Parcourir les formes de la plus récente à la plus ancienne
	// (la plus récente est dessinée au-dessus)
	for (int i = static_cast<int>(shapes.size()) - 1; i >= 0; --i) {
		if (isInsideBounds(shapes[i], x, y)) {
			return i;
		}
	}

	return -1; // Aucune forme trouvée
}

void SelectionService::updateSelection(
	std::vector<int> & currentSelection,
	int clickedIndex,
	bool addToSelection) const {
	// Aucune forme cliquée
	if (clickedIndex < 0) {
		if (!addToSelection) {
			currentSelection.clear();
		}
		return;
	}

	// Mode sélection simple (remplacer la sélection)
	if (!addToSelection) {
		currentSelection.clear();
		currentSelection.push_back(clickedIndex);
		return;
	}

	// Mode multi-sélection (toggle)
	auto it = std::find(currentSelection.begin(), currentSelection.end(), clickedIndex);
	if (it != currentSelection.end()) {
		// Déjà sélectionné → désélectionner
		currentSelection.erase(it);
	} else {
		// Pas sélectionné → ajouter
		currentSelection.push_back(clickedIndex);
	}
}

bool SelectionService::isInsideBounds(const Shape & shape, float x, float y) const {
	// Router vers la bonne méthode de hit-testing selon le type
	if (shape.type == "point") {
		return hitTestPoint(shape, x, y);
	} else if (shape.type == "line") {
		return hitTestLine(shape, x, y);
	} else if (shape.type == "triangle") {
		return hitTestTriangle(shape, x, y);
	} else if (shape.type == "square") {
		return hitTestSquare(shape, x, y);
	} else if (shape.type == "rectangle") {
		return hitTestRectangle(shape, x, y);
	} else if (shape.type == "circle") {
		return hitTestCircle(shape, x, y);
	} else if (shape.is3D && shape.mesh3D.getNumVertices() > 0) {
		return hitTestMesh3D(shape, x, y);
	}

	return false;
}

// ========== HIT-TESTING PAR TYPE DE FORME ==========

bool SelectionService::hitTestPoint(const Shape & shape, float x, float y) const {
	return ofDist(x, y, shape.start.x, shape.start.y) <= 5;
}

bool SelectionService::hitTestLine(const Shape & shape, float x, float y) const {
	// Distance du point au segment de ligne
	float distToStart = ofDist(x, y, shape.start.x, shape.start.y);
	float distToEnd = ofDist(x, y, shape.end.x, shape.end.y);
	float lineLength = ofDist(shape.start.x, shape.start.y, shape.end.x, shape.end.y);

	// Si la somme des distances au début et à la fin est proche de la longueur de la ligne,
	// le point est sur la ligne
	return std::abs((distToStart + distToEnd) - lineLength) < 3.0f;
}

bool SelectionService::hitTestTriangle(const Shape & shape, float x, float y) const {
	// Points du triangle
	ofPoint a = shape.start;
	ofPoint b(shape.end.x, shape.start.y);
	ofPoint c = shape.end;

	// Coordonnées barycentriques
	float denom = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
	if (std::abs(denom) < 1e-6) {
		return false; // Triangle dégénéré
	}

	float alpha = ((b.y - c.y) * (x - c.x) + (c.x - b.x) * (y - c.y)) / denom;
	float beta = ((c.y - a.y) * (x - c.x) + (a.x - c.x) * (y - c.y)) / denom;
	float gamma = 1.0f - alpha - beta;

	return (alpha >= 0 && beta >= 0 && gamma >= 0);
}

bool SelectionService::hitTestSquare(const Shape & shape, float x, float y) const {
	float side = std::abs(shape.end.x - shape.start.x) * shape.scale;
	return (x >= shape.start.x && x <= shape.start.x + side && y >= shape.start.y && y <= shape.start.y + side);
}

bool SelectionService::hitTestRectangle(const Shape & shape, float x, float y) const {
	float x0 = std::min(shape.start.x, shape.end.x);
	float x1 = std::max(shape.start.x, shape.end.x);
	float y0 = std::min(shape.start.y, shape.end.y);
	float y1 = std::max(shape.start.y, shape.end.y);

	return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}

bool SelectionService::hitTestCircle(const Shape & shape, float x, float y) const {
	float radius = ofDist(shape.start.x, shape.start.y, shape.end.x, shape.end.y) * shape.scale;
	return ofDist(x, y, shape.start.x, shape.start.y) <= radius;
}

bool SelectionService::hitTestMesh3D(const Shape & shape, float x, float y) const {
	// Pour les meshes 3D, on teste la bounding box 2D projetée
	const ofMesh & mesh = shape.mesh3D;

	if (mesh.getNumVertices() == 0) {
		return false;
	}

	glm::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	glm::vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (const auto & v : mesh.getVertices()) {
		min = glm::min(min, v);
		max = glm::max(max, v);
	}

	return (x >= min.x && x <= max.x && y >= min.y && y <= max.y);
}
