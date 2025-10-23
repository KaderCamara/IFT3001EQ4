#include "sceneGraph.h"


void SceneGraph::addShape(const Shape &shape) {
	shapes.push_back(shape);
}

void SceneGraph::removeShape(int index) {
	if (selectedIndex >= 0) {
		shapes.erase(shapes.begin() + selectedIndex);
		selectedIndex = -1;
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
	selectedIndex = -1;
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

bool SceneGraph::insideBounds(const Shape& s, float x, float y) {
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
		float alpha = ((b.y - c.y) * (x - c.x) + (c.x - b.x) * (y - c.y)) / denom;
		float beta = ((c.y - a.y) * (x - c.x) + (a.x - c.x) * (y - c.y)) / denom;
		float gamma = 1.0f - alpha - beta;
		return (alpha >= 0 && beta >= 0 && gamma >= 0);
	} else if (s.type == "square") {
		float side = std::abs(s.end.x - s.start.x);
		return (x >= s.start.x && x <= s.start.x + side && y >= s.start.y && y <= s.start.y + side);
	} else if (s.type == "circle") {
		float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y);
		return ofDist(x, y, s.start.x, s.start.y) <= radius;
	} else if (s.type == "rectangle") {
		return (x >= s.start.x && x <= s.end.x && y >= s.start.y && y <= s.end.y);
	}
	return false;
}

std::vector<Shape> SceneGraph::getAllShapes() {
	return shapes;
}
void SceneGraph::draw() {
	for (int i = 0; i < shapes.size(); ++i) {
		const Shape & s = shapes[i];
		bool isSelected = std::find(selectedIndices.begin(), selectedIndices.end(), i) != selectedIndices.end();

		ofPushStyle();

		if (isSelected) {
			ofSetColor(ofColor::yellow);
			ofSetLineWidth(3);
		} else {
			ofSetColor(s.color);
			ofSetLineWidth(1);
		}

		if (!s.is3D) {
			if (s.type == "point") {
				ofDrawCircle(s.start, 3 * s.scale);
			} else if (s.type == "line") {
				ofDrawLine(s.start, s.end);
			} else if (s.type == "triangle") {
				ofPoint a = s.start;
				ofPoint b(s.end.x, s.start.y);
				ofPoint c = s.end;
				ofDrawTriangle(a, b, c);
			} else if (s.type == "square") {
				float side = std::abs(s.end.x - s.start.x) * s.scale;
				ofDrawRectangle(s.start.x, s.start.y, side, side);
			} else if (s.type == "rectangle") {
				float w = (s.end.x - s.start.x) * s.scale;
				float h = (s.end.y - s.start.y) * s.scale;
				ofDrawRectangle(s.start.x, s.start.y, w, h);
			} else if (s.type == "circle") {
				float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y) * s.scale;
				ofDrawCircle(s.start, radius);
			}
		} else {
			ofPushMatrix();
			ofScale(s.scale, s.scale, s.scale);
			s.mesh3D.drawWireframe();
			ofPopMatrix();
		}

		if (isSelected) {
			ofNoFill();
			ofSetColor(ofColor::yellow);
			if (!s.is3D) {
				if (s.type == "rectangle" || s.type == "square") {
					float w = (s.end.x - s.start.x) * s.scale;
					float h = (s.end.y - s.start.y) * s.scale;
					ofDrawRectangle(s.start.x, s.start.y, w, h);
				} else if (s.type == "circle") {
					float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y) * s.scale;
					ofDrawCircle(s.start, radius);
				}
			}
		}

		ofPopStyle();
	}
}
