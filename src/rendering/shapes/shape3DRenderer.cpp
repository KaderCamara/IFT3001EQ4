// Shape3DRenderer.cpp
#include "Shape3DRenderer.h"
#include <cfloat>


void Shape3DRenderer::drawShape3D(const Shape & s) const {
	ofMesh & mesh3D = const_cast<ofMesh &>(s.mesh3D);

	// Dessiner le mesh
	if (showWireframe) {
		mesh3D.drawWireframe();
	} else {
		mesh3D.draw();
	}

	// Dessiner la bounding box si activée
	if (showBoundingBox) {
		glm::vec3 min(FLT_MAX), max(-FLT_MAX);
		for (const auto & v : mesh3D.getVertices()) {
			min = glm::min(min, v);
			max = glm::max(max, v);
		}

		ofPushStyle();
		ofNoFill();
		ofSetColor(ofColor::green);
		ofDrawBox((min + max) * 0.5f,
			max.x - min.x,
			max.y - min.y,
			max.z - min.z);
		ofPopStyle();
	}
}

ofRectangle Shape3DRenderer::getMeshBoundingBox(const ofMesh & mesh) {
	if (mesh.getNumVertices() == 0) return ofRectangle();

	glm::vec3 min = mesh.getVertex(0);
	glm::vec3 max = mesh.getVertex(0);

	for (std::size_t i = 1; i < mesh.getNumVertices(); ++i) {
		const glm::vec3 & v = mesh.getVertex(i);
		min = glm::min(min, v);
		max = glm::max(max, v);
	}

	return ofRectangle(min.x, min.y, max.x - min.x, max.y - min.y);
}
