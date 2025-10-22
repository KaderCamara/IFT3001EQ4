#pragma once
#include "ofMain.h"
#include "shape.h"

class ShapeManager3D {
public:
	ofMesh to3DDraw(const Shape &shape, float depth);
	ofMesh to3DCube(const Shape &shape, float depth, ofMesh mesh);
	ofMesh to3DSphere(const Shape &shape, float depth, ofMesh mesh);
	ofMesh to3DCone(const Shape &shape, float depth, ofMesh mesh);
};
