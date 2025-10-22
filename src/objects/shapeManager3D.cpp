#include "ShapeManager3D.h"

ofMesh ShapeManager3D::to3DDraw(const Shape & shape, float depth) {
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	if (shape.type == "rectangle" or shape.type == "square") {
		return to3DCube(shape, depth, mesh);
	}
	if (shape.type == "circle") {
		return to3DSphere(shape, depth, mesh);
	}
	if (shape.type == "triangle") {
		return to3DCone(shape, depth, mesh);
	}
}

ofMesh ShapeManager3D::to3DCube(const Shape & shape, float depth, ofMesh mesh) {
	//rectangle a boîte
	float width = shape.end.x - shape.start.x;
	float height = shape.end.y - shape.start.y;
	float z = depth / 2.0f;

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

ofMesh ShapeManager3D::to3DSphere(const Shape & shape, float depth, ofMesh mesh) {
	return mesh;
}

ofMesh ShapeManager3D::to3DCone(const Shape & shape, float depth, ofMesh mesh) {
	return mesh;
}
