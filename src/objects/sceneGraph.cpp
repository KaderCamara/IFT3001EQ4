// SceneGraph.cpp
// Implémentation du MODEL pur de la scène
#include "SceneGraph.h"
#include <algorithm>

// ========== OPÉRATIONS CRUD BASIQUES ==========

void SceneGraph::addShape(const Shape & shape) {
	shapes.push_back(shape);
}

void SceneGraph::removeShape(int index) {
	if (!isValidIndex(index)) {
		return;
	}

	// Supprimer la forme
	shapes.erase(shapes.begin() + index);

	// Mettre à jour les indices de sélection
	// - Retirer l'index supprimé
	// - Décrémenter les indices supérieurs
	std::vector<int> newSelection;
	for (int i : selectedIndices) {
		if (i < index) {
			newSelection.push_back(i);
		} else if (i > index) {
			newSelection.push_back(i - 1);
		}
		// Si i == index, on l'ignore (suppression)
	}
	selectedIndices = newSelection;
}

Shape * SceneGraph::getShape(int index) {
	if (isValidIndex(index)) {
		return &shapes[index];
	}
	return nullptr;
}

const Shape * SceneGraph::getShape(int index) const {
	if (isValidIndex(index)) {
		return &shapes[index];
	}
	return nullptr;
}

void SceneGraph::clear() {
	shapes.clear();
	selectedIndices.clear();
}

void SceneGraph::removeSelectedShapes() {
	if (selectedIndices.empty()) {
		return;
	}

	// Trier les indices en ordre décroissant pour supprimer du plus grand au plus petit
	std::sort(selectedIndices.begin(), selectedIndices.end(), std::greater<int>());

	for (int index : selectedIndices) {
		if (isValidIndex(index)) {
			shapes.erase(shapes.begin() + index);
		}
	}

	selectedIndices.clear();
}

void SceneGraph::deselectAll() {
	selectedIndices.clear();
}

std::vector<Shape> & SceneGraph::getAllShapes() {
	return shapes;
}

const std::vector<Shape> & SceneGraph::getAllShapes() const {
	return shapes;
}

void SceneGraph::setShapes(const std::vector<Shape> & newShapes) {
	shapes = newShapes;
	// Note : On garde la sélection actuelle (pourrait être vidée selon le cas d'usage)
}

bool SceneGraph::isValidIndex(int index) const {
	return index >= 0 && index < static_cast<int>(shapes.size());
}

bool SceneGraph::isSelected(int index) const {
	return std::find(selectedIndices.begin(), selectedIndices.end(), index) != selectedIndices.end();
}
