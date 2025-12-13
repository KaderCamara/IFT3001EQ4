#include "ShapeManager3D.h"

ofMesh ShapeManager3D::to3DDraw(const Shape & shape) {
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	if (shape.type == "rectangle" || shape.type == "square") {
		return to3DCube(shape, mesh);
	}
	if (shape.type == "circle") {
		return to3DSphere(shape, mesh);
	}
	if (shape.type == "triangle") {
		return to3DCone(shape, mesh);
	}
	return mesh;
}

ofMesh ShapeManager3D::to3DCube(const Shape & shape, ofMesh mesh) {
	float width, height;
	if (shape.type == "square") {
		float side = abs(shape.end.x - shape.start.x);
		width = side;
		height = side;
	} else {
		width = abs(shape.end.x - shape.start.x);
		height = abs(shape.end.y - shape.start.y);
	}

	float centerX = (shape.start.x + shape.end.x) / 2.0f;
	float centerY = (shape.start.y + shape.end.y) / 2.0f;
	float depth = std::min(width, height);
	float halfZ = depth / 2.0f;
	float halfW = width / 2.0f;
	float halfH = height / 2.0f;

	// Vertices
	mesh.addVertex({ centerX - halfW, centerY - halfH, -halfZ });
	mesh.addVertex({ centerX + halfW, centerY - halfH, -halfZ });
	mesh.addVertex({ centerX + halfW, centerY + halfH, -halfZ });
	mesh.addVertex({ centerX - halfW, centerY + halfH, -halfZ });
	mesh.addVertex({ centerX - halfW, centerY - halfH, halfZ });
	mesh.addVertex({ centerX + halfW, centerY - halfH, halfZ });
	mesh.addVertex({ centerX + halfW, centerY + halfH, halfZ });
	mesh.addVertex({ centerX - halfW, centerY + halfH, halfZ });

	// ✅ AJOUT: Coordonnées UV pour chaque sommet
	// Mappage simple: chaque face va de (0,0) à (1,1)
	mesh.addTexCoord(glm::vec2(0, 0));
	mesh.addTexCoord(glm::vec2(1, 0));
	mesh.addTexCoord(glm::vec2(1, 1));
	mesh.addTexCoord(glm::vec2(0, 1));
	mesh.addTexCoord(glm::vec2(0, 0));
	mesh.addTexCoord(glm::vec2(1, 0));
	mesh.addTexCoord(glm::vec2(1, 1));
	mesh.addTexCoord(glm::vec2(0, 1));

	// Indices
	int faces[] = {
		0, 1, 2, 0, 2, 3, // front
		4, 7, 6, 4, 6, 5, // back
		0, 4, 5, 0, 5, 1, // bottom
		2, 6, 7, 2, 7, 3, // top
		1, 5, 6, 1, 6, 2, // right
		0, 3, 7, 0, 7, 4 // left
	};
	for (int i = 0; i < 36; i++)
		mesh.addIndex(faces[i]);

	// Normales (votre code existant)
	for (int i = 0; i < mesh.getNumVertices(); i++) {
		mesh.addNormal(glm::vec3(0, 0, 0));
	}

	for (int i = 0; i < mesh.getNumIndices(); i += 3) {
		int i0 = mesh.getIndex(i);
		int i1 = mesh.getIndex(i + 1);
		int i2 = mesh.getIndex(i + 2);

		glm::vec3 v0 = mesh.getVertex(i0);
		glm::vec3 v1 = mesh.getVertex(i1);
		glm::vec3 v2 = mesh.getVertex(i2);

		glm::vec3 normal = glm::normalize(glm::cross(v2 - v0, v1 - v0));
		mesh.getNormals()[i0] += normal;
		mesh.getNormals()[i1] += normal;
		mesh.getNormals()[i2] += normal;
	}

	for (auto & n : mesh.getNormals()) {
		n = glm::normalize(n);
	}

	return mesh;
}

ofMesh ShapeManager3D::to3DSphere(const Shape & shape, ofMesh mesh) {
	float radius = ofDist(shape.start.x, shape.start.y, shape.end.x, shape.end.y);
	if (radius < 1.0f) radius = 1.0f;

	ofPoint center = shape.start;

	ofSpherePrimitive sphere(radius, 16);
	mesh = sphere.getMesh(); // ✅ Les primitives OF ont déjà des UVs

	// ✅ VÉRIFICATION: Si pas de UVs, les générer
	if (mesh.getNumTexCoords() == 0) {
		ofLogWarning("ShapeManager3D") << "Sphere has no UVs, generating...";
		for (size_t i = 0; i < mesh.getNumVertices(); i++) {
			// UV sphérique simple basé sur la position
			glm::vec3 v = glm::normalize(mesh.getVertex(i) - glm::vec3(center.x, center.y, 0));
			float u = 0.5f + atan2(v.z, v.x) / (2.0f * PI);
			float vCoord = 0.5f - asin(v.y) / PI;
			mesh.addTexCoord(glm::vec2(u, vCoord));
		}
	}

	for (auto & v : mesh.getVertices()) {
		v += center;
	}

	return mesh;
}

ofMesh ShapeManager3D::to3DCone(const Shape & shape, ofMesh mesh) {
	float width = abs(shape.end.x - shape.start.x);
	float height = abs(shape.end.y - shape.start.y);
	float radius = std::min(width, height) / 2.0f;

	if (radius < 1.0f) radius = 1.0f;
	if (height < 1.0f) height = 1.0f;

	ofPoint center = {
		(shape.start.x + shape.end.x) / 2.0f,
		(shape.start.y + shape.end.y) / 2.0f,
		0
	};

	ofConePrimitive cone(radius, height, 16, 4);
	mesh = cone.getMesh(); // ✅ Devrait avoir des UVs

	// ✅ VÉRIFICATION
	if (mesh.getNumTexCoords() == 0) {
		ofLogWarning("ShapeManager3D") << "Cone has no UVs, generating...";
		for (size_t i = 0; i < mesh.getNumVertices(); i++) {
			glm::vec3 v = mesh.getVertex(i);
			float u = 0.5f + v.x / (radius * 2.0f);
			float vCoord = v.y / height;
			mesh.addTexCoord(glm::vec2(u, vCoord));
		}
	}

	for (auto & v : mesh.getVertices()) {
		v += center;
	}

	return mesh;
}
