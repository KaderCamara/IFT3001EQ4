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

	mesh.addVertex({ centerX - halfW, centerY - halfH, -halfZ });
	mesh.addVertex({ centerX + halfW, centerY - halfH, -halfZ });
	mesh.addVertex({ centerX + halfW, centerY + halfH, -halfZ });
	mesh.addVertex({ centerX - halfW, centerY + halfH, -halfZ });
	mesh.addVertex({ centerX - halfW, centerY - halfH, halfZ });
	mesh.addVertex({ centerX + halfW, centerY - halfH, halfZ });
	mesh.addVertex({ centerX + halfW, centerY + halfH, halfZ });
	mesh.addVertex({ centerX - halfW, centerY + halfH, halfZ });

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

	return mesh;
}

ofMesh ShapeManager3D::to3DSphere(const Shape & shape, ofMesh mesh) {
	float radius = ofDist(shape.start.x, shape.start.y, shape.end.x, shape.end.y);

	if (radius < 1.0f) radius = 1.0f;

	ofPoint center = shape.start; 
	ofSpherePrimitive sphere(radius, 16);
	mesh = sphere.getMesh();

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
	mesh = cone.getMesh();

	for (auto & v : mesh.getVertices()) {
		v += center;
	}

	return mesh;
}
