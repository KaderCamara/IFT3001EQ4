// Shape3DRenderer.cpp
#include "Shape3DRenderer.h"
#include <algorithm>
#include <cfloat>
#include "ofMain.h"

void Shape3DRenderer::drawShape3D(const Shape & s) const {
	ofMesh & mesh3D = const_cast<ofMesh &>(s.mesh3D);

	// Appliquer la texture procédurale si elle existe
	if (s.proceduralTexture.isAllocated()) {
		s.proceduralTexture.bind();
		mesh3D.draw();
		s.proceduralTexture.unbind();
	} else {
		mesh3D.draw();
	}

	// Wireframe
	if (showWireframe) mesh3D.drawWireframe();

	// Normales
	if (showNormals && mesh3D.hasNormals()) {
		ofPushStyle();
		ofSetColor(ofColor::cyan);
		const auto & normals = mesh3D.getNormals();
		const auto & verts = mesh3D.getVertices();
		std::size_t count = std::min(normals.size(), verts.size());
		for (std::size_t i = 0; i < count; ++i) {
			const glm::vec3 & v = verts[i];
			const glm::vec3 & n = glm::normalize(normals[i]);
			ofDrawLine(v, v + n * 10.0f);
		}
		ofPopStyle();
	}

	// Bounding box
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
