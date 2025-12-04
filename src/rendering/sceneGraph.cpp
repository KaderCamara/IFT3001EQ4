#include "sceneGraph.h"

void SceneGraph::addShape(const Shape & shape) {
	shapes.push_back(shape);
}

void SceneGraph::removeShape(int index) {
	if (index >= 0 && index < (int)shapes.size()) {
		// Supprimer la shape
		shapes.erase(shapes.begin() + index);

		// Mettre à jour la sélection :
		// - retirer l'index supprimé,
		// - décrémenter ceux qui sont après
		for (auto & i : selectedIndices) {
			if (i > index) {
				i--;
			}
		}
		selectedIndices.erase(
			std::remove(selectedIndices.begin(), selectedIndices.end(), index),
			selectedIndices.end());
	}
}


Shape * SceneGraph::getShape(int index) {
	if (index >= 0 && index < shapes.size()) {
		return &shapes[index];
	}
	return nullptr;
}

void SceneGraph::clear() {
	shapes.clear();
	selectedIndices.clear();
}

void SceneGraph::selectShapeAt(float x, float y, bool addToSelection) {
	if (!addToSelection)
		selectedIndices.clear();

	for (int i = 0; i < shapes.size(); ++i) {
		if (insideBounds(shapes[i], x, y)) {
			auto it = std::find(selectedIndices.begin(), selectedIndices.end(), i);
			if (it != selectedIndices.end()) {
				selectedIndices.erase(it);
			} else {
				selectedIndices.push_back(i);
			}
			break;
		}
	}
}

void SceneGraph::deselectAll() {
	selectedIndices.clear();
}

void SceneGraph::updateSelectedAttributes(const ofColor & color, float size) {
	for (int i : selectedIndices) {
		if (i >= 0 && i < shapes.size()) {
			Shape & s = shapes[i];
			s.color = color;
			s.scale = size;
		}
	}
}

void SceneGraph::removeSelectedShapes() {
	if (selectedIndices.empty()) return;

	std::sort(selectedIndices.begin(), selectedIndices.end(), std::greater<int>());

	for (int index : selectedIndices) {
		if (index >= 0 && index < shapes.size()) {
			shapes.erase(shapes.begin() + index);
		}
	}

	selectedIndices.clear();
}

bool SceneGraph::insideBounds(const Shape & s, float x, float y) {
	if (s.type == "point") {
		return ofDist(x, y, s.start.x, s.start.y) <= 5;
	} else if (s.type == "line") {
		float dist = ofDist(x, y, s.start.x, s.start.y) + ofDist(x, y, s.end.x, s.end.y);
		float lineLen = ofDist(s.start.x, s.start.y, s.end.x, s.end.y);
		return std::abs(dist - lineLen) < 3;
	} else if (s.type == "triangle") {
		ofPoint a = s.start;
		ofPoint b(s.end.x, s.start.y);
		ofPoint c = s.end;
		float denom = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
		if (fabs(denom) < 1e-6) return false;
		float alpha = ((b.y - c.y) * (x - c.x) + (c.x - b.x) * (y - c.y)) / denom;
		float beta = ((c.y - a.y) * (x - c.x) + (a.x - c.x) * (y - c.y)) / denom;
		float gamma = 1.0f - alpha - beta;
		return (alpha >= 0 && beta >= 0 && gamma >= 0);
	} else if (s.type == "square") {
		float side = std::abs(s.end.x - s.start.x) * s.scale;
		return (x >= s.start.x && x <= s.start.x + side && y >= s.start.y && y <= s.start.y + side);
	} else if (s.type == "circle") {
		float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y) * s.scale;
		return ofDist(x, y, s.start.x, s.start.y) <= radius;
	} else if (s.type == "rectangle") {
		float x0 = std::min(s.start.x, s.end.x);
		float x1 = std::max(s.start.x, s.end.x);
		float y0 = std::min(s.start.y, s.end.y);
		float y1 = std::max(s.start.y, s.end.y);
		return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
	}

	if (s.is3D && s.mesh3D.getNumVertices() > 0) {
		glm::vec3 mn(FLT_MAX), mx(-FLT_MAX);
		for (auto & v : s.mesh3D.getVertices()) {
			mn = glm::min(mn, v);
			mx = glm::max(mx, v);
		}
		if (x >= mn.x && x <= mx.x && y >= mn.y && y <= mx.y) return true;
	}

	return false;
}

std::vector<Shape> & SceneGraph::getAllShapes() {
	return shapes;
}


// JORDAN: transformation FUNCTIONS
void SceneGraph::updateSelectedTransform(float tx, float ty, float rot, float scale) {
	for (int i : selectedIndices) {
		if (i >= 0 && i < (int)shapes.size()) {
			shapes[i].translation.set(tx, ty);
			shapes[i].rotation = rot;
			shapes[i].scale = scale;
		}
	}
}

// 3D IMPORT FUNCTIONS
	void SceneGraph::setShapes(const std::vector<Shape> & newShapes) {
		shapes = newShapes;
	}

