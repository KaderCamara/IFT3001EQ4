#include "ShapeManager3D.h"

ofMesh ShapeManager3D::to3DDraw(const Shape & shape) {
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	if (shape.type == "rectangle" or shape.type == "square") {
		return to3DCube(shape, mesh);
	}
	if (shape.type == "circle") {
		return to3DSphere(shape, mesh);
	}
	if (shape.type == "triangle") {
		return to3DCone(shape, mesh);
	}
}

ofMesh ShapeManager3D::to3DCube(const Shape & shape, ofMesh mesh) {
	//rectangle a boîte
	float width = shape.end.x - shape.start.x;
	float height = shape.end.y - shape.start.y;
	float z = std::min(width, height) / 2.0f;

	// 8 sommets
	mesh.addVertex({ shape.start.x, shape.start.y, -z });
	mesh.addVertex({ shape.end.x, shape.start.y, -z });
	mesh.addVertex({ shape.end.x, shape.end.y, -z });
	mesh.addVertex({ shape.start.x, shape.end.y, -z });

	mesh.addVertex({ shape.start.x, shape.start.y, z });
	mesh.addVertex({ shape.end.x, shape.start.y, z });
	mesh.addVertex({ shape.end.x, shape.end.y, z });
	mesh.addVertex({ shape.start.x, shape.end.y, z });

	// indices pour former les faces
	int faces[] = {
		0, 1, 2, 0, 2, 3, // face avant
		4, 5, 6, 4, 6, 7, // face arrière
		0, 1, 5, 0, 5, 4, // haut
		2, 3, 7, 2, 7, 6, // bas
		1, 2, 6, 1, 6, 5, // droite
		0, 3, 7, 0, 7, 4 // gauche
	};
	for (int i = 0; i < 36; i++)
		mesh.addIndex(faces[i]);

	return mesh;
}

ofMesh ShapeManager3D::to3DSphere(const Shape & shape, ofMesh mesh) {
	float radius = (shape.end.x - shape.start.x) / 2.0f;
	// Centre du cercle
	ofPoint center = {
		shape.start.x + radius,
		shape.start.y + radius,
		0
	};
	ofSpherePrimitive sphere(radius, 16);
	mesh = sphere.getMesh();
	for (auto & v : mesh.getVertices()) {
		v += center;
	}
	return mesh;
}

ofMesh ShapeManager3D::to3DCone(const Shape & shape, ofMesh mesh) {
	float width = shape.end.x - shape.start.x;
	float height = shape.end.y - shape.start.y;
	float radius = std::min(width, height) / 2.0f;
	ofPoint center = {
		shape.start.x + width / 2.0f,
		shape.start.y + height / 2.0f,
		0
	};
	ofConePrimitive cone(radius, height, 16, 4);
	mesh = cone.getMesh();
	for (auto & v : mesh.getVertices()) {
		v += center;
	}
	return mesh;
}
