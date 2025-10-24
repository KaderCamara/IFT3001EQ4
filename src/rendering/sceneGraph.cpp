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

int SceneGraph::selectShapeAt(float x, float y) {
	for (int i = 0; i < shapes.size(); ++i) {
		if (insideBounds(shapes[i], x, y)) {
			selectedIndex = i;
			return i;
		}
	}
	selectedIndex = -1;
	return -1;
}

void SceneGraph::updateSelectedAttributes(const ofColor & color, float size) {
	if(selectedIndex >= 0 && selectedIndex < shapes.size()) {
		Shape & selected = shapes[selectedIndex];
		// when you add color/size attributes to Shape, update them here
		// e.g., selected.color = color; selected.size = size;
	}
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
	for (const auto & s : shapes) {
		// JORDAN
		ofPushMatrix();
		ofTranslate(s.translation);
		ofTranslate((s.start.x + s.end.x) / 2, (s.start.y + s.end.y) / 2);
		ofRotateDeg(s.rotation);
		ofScale(s.scale, s.scale);
		ofTranslate(-(s.start.x + s.end.x) / 2, -(s.start.y + s.end.y) / 2);
		// END JORDAN
		if (s.type == "point") {
			ofDrawCircle(s.start, 2);
		} else if (s.type == "line") {
			ofDrawLine(s.start, s.end);
		} else if (s.type == "triangle") {
			ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
		} else if (s.type == "square") {
			float side = std::abs(s.end.x - s.start.x);
			ofDrawRectangle(s.start.x, s.start.y, side, side);
		} else if (s.type == "rectangle") {
			ofDrawRectangle(s.start.x, s.start.y,
				s.end.x - s.start.x, s.end.y - s.start.y);
		} else if (s.type == "circle") {
			float radius = ofDist(s.start.x, s.start.y, s.end.x, s.end.y);
			ofDrawCircle(s.start, radius);
		}
		ofPopMatrix(); // JORDAN
	}
	}

// JORDAN: transformation FUNCTIONS
	void SceneGraph::updateSelectedTransform(float tx, float ty, float rot, float scale) {
		if (selectedIndex >= 0 && selectedIndex < shapes.size()) {
			shapes[selectedIndex].translation.set(tx, ty);
			shapes[selectedIndex].rotation = rot;
			shapes[selectedIndex].scale = scale;
		}
	}

// 3D IMPORT FUNCTIONS
	void SceneGraph::setShapes(const std::vector<Shape> & newShapes) {
		shapes = newShapes;
	}

