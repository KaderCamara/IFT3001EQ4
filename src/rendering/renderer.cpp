// Renderer.cpp
#include "renderer.h"
#include <cfloat>
#include "ofMain.h"
#include "cameraManager.h"
#include "sceneGraph.h"
#include "../objects/shapeManager.h"
#include "../objects/shapeManager3D.h"
#include "../ui/uiWindow.h"


bool g_showBoundingBox = false;
bool g_showWireframe = false;

void Renderer::setup() {
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);
	cameraManager.setup();
}

void Renderer::draw() {
	ofPushStyle();
	ofSetColor(currentBgColor);
	ofDrawRectangle(drawingArea.x, drawingArea.y, drawingArea.width, drawingArea.height);
	ofPopStyle();

	if (viewQuad) {
		drawQuadView();
		return;
	}
	if (view3D) {
		draw3D();
		return;
	}
	if (!view2D) return;

	for (int i = 0; i < sceneGraph.shapes.size(); ++i) {
		auto & s = sceneGraph.shapes[i];
		if (s.type == "none" || s.type == "x") continue;

		bool isSelected = std::find(sceneGraph.selectedIndices.begin(),
							  sceneGraph.selectedIndices.end(), i)
			!= sceneGraph.selectedIndices.end();

		ofPushStyle();

		if (isSelected) {
			ofNoFill();
			ofSetColor(ofColor::yellow);
			ofSetLineWidth(3);
		} else {
			ofFill();
			ofSetColor(s.color);
			ofSetLineWidth(currentLineWidth);
		}

		if (s.type == "point") {
			ofDrawCircle(s.start, 3 * s.scale);
		} else if (s.type == "line") {
			ofDrawLine(s.start, s.end);
		} else if (s.type == "triangle") {
			ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
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
		} else if (s.mesh3D.getNumVertices() > 0) {
			s.mesh3D.drawWireframe();
		}

		if (isSelected && s.type != "line" && s.type != "point") {
			ofNoFill();
			ofSetColor(ofColor::yellow);
			ofSetLineWidth(2);

			if (s.type == "triangle") {
				ofDrawTriangle(s.start, ofPoint(s.end.x, s.start.y), s.end);
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
		}

		ofPopStyle();
	}

	// Dessiner la shape en cours de création
	if (currentShape != "none") {
		shapeManager.draw();
	}
}

void Renderer::save() {
	sceneGraph.addShape(shapeManager.getCurrentShape());
	cameraManager.markDirty();
}

void Renderer::deleteShape() {
	if (shapeSelected) {
		sceneGraph.removeSelectedShapes();
		shapeSelected = false;
		cameraManager.markDirty();
	} else {
		cout << "no shape was selected" << endl;
	}
}

void Renderer::selectingModeOn() {
	selecting = true;
	shapeManager.deleteCurrentShapeToDraw();
}

void Renderer::selectingModeOff() {
	selecting = false;
}

void Renderer::viewQuadMode() {
	viewQuad = true;
	view3D = false;
	view2D = false;

	for (auto & s : sceneGraph.shapes) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s);
		}
	}

	cameraManager.markDirty();
}

void Renderer::view3DMode() {
	view3D = true;
	view2D = false;
	viewQuad = false;

	for (auto & s : sceneGraph.shapes) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s);
		}
	}

	cameraManager.markDirty();
}

void Renderer::view2DMode() {
	view2D = true;
	view3D = false;
	viewQuad = false;

	cameraManager.markDirty();
}

void Renderer::draw3D() {


	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, false);
	}

	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);

	for (auto & s : sceneGraph.shapes) {
		ofMesh & mesh3D = s.mesh3D;

		if (g_showWireframe) {
			mesh3D.drawWireframe();
		} else {
			mesh3D.draw();
		}

		if (g_showBoundingBox) {
			glm::vec3 min(FLT_MAX), max(-FLT_MAX);
			for (auto & v : mesh3D.getVertices()) {
				min = glm::min(min, v);
				max = glm::max(max, v);
			}

			ofPushStyle();
			ofNoFill();
			ofSetColor(ofColor::green);
			ofDrawBox((min + max) * 0.5f, max.x - min.x, max.y - min.y, max.z - min.z);
			ofPopStyle();
		}
	}

	cameraManager.getCurrentCamera().end();
}

void Renderer::mousePressed(int x, int y, int button) {
	if (currentShape != "none") {
		startPoint.set(x, y);
		drawing = true;
	}
	if (selecting) {
		sceneGraph.selectShapeAt(x, y, ofGetKeyPressed(OF_KEY_CONTROL) || ofGetKeyPressed(OF_KEY_COMMAND));
		shapeSelected = !sceneGraph.selectedIndices.empty();
	}
}

void Renderer::mouseReleased(int x, int y, int button) {
	if (drawing) {
		endPoint.set(x, y);
		shapeManager.drawShape(currentShape, startPoint, endPoint);
		drawing = false;
	}

}


void Renderer::keyPressed(int key) {
	if (viewQuad) {
		return;
	}
	
	if (key == '1') {
		cameraManager.setPerspectiveView(0);
		cout << "Camera: Top view" << endl;
	} else if (key == '2') {
		cameraManager.setPerspectiveView(1);
		cout << "Camera: Front view" << endl;
	} else if (key == '3') {
		cameraManager.setPerspectiveView(2);
		cout << "Camera: Side view" << endl;
	} else if (key == '4') {
		cameraManager.setPerspectiveView(3);
		cout << "Camera: Bottom view" << endl;
	} else if (key == '5') {
		cameraManager.setPerspectiveView(4);
		cout << "Camera: Free view (drag to rotate)" << endl;
	}

	
}

void Renderer::drawQuadView() {


	if (cameraManager.needsUpdate()) {
		cameraManager.lookAtScene(sceneGraph.shapes, true);
	}

	int w = drawingArea.width; 
	int h = drawingArea.height;
	int halfW = w / 2;
	int halfH = h / 2;

	int offsetX = drawingArea.x;
	int offsetY = drawingArea.y;

	//camera top left
	ofViewport(offsetX, offsetY, halfW, halfH);
	cameraManager.setPerspectiveView(0);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Top View", offsetX + 10, offsetY + 20);

	//camera top right
	ofViewport(offsetX + halfW, offsetY, halfW, halfH);
	cameraManager.setPerspectiveView(1);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Front View", offsetX + halfW + 10, offsetY + 20);

	//camera bottom left
	ofViewport(offsetX, offsetY + halfH, halfW, halfH);
	cameraManager.setPerspectiveView(2);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Side View", offsetX + 10, offsetY + halfH + 20);

	//camera bottom right
	ofViewport(offsetX + halfW, offsetY + halfH, halfW, halfH);
	cameraManager.setPerspectiveView(3);
	cameraManager.getCurrentCamera().begin();
	ofSetColor(255);
	for (const auto & s : sceneGraph.shapes) {
		s.mesh3D.draw();
	}
	cameraManager.getCurrentCamera().end();

	ofSetColor(0);
	ofDrawBitmapString("Bottom View", offsetX + halfW + 10, offsetY + halfH + 20);

	ofViewport(0, 0, ofGetWidth(), ofGetHeight());

	// les lignes de separation
	ofPushStyle();
	ofSetColor(100);
	ofSetLineWidth(2);
	ofDrawLine(offsetX + halfW, offsetY, offsetX + halfW, offsetY + h); //vertical
	ofDrawLine(offsetX, offsetY + halfH, offsetX + w, offsetY + halfH); // horizontal 
	ofPopStyle();
}



void Renderer::applyDrawingParameters(float lineW, const ofColor & stroke, const ofColor & fill, const ofColor & bg, bool useHSB, float hue, float saturation, float brightness) {
	currentLineWidth = lineW;
	useHSBmode = useHSB;
	if (useHSBmode) {
		currentStrokeColor = ofColor::fromHsb(hue, saturation, brightness);
		currentFillColor = ofColor::fromHsb(hue, saturation, brightness);
		currentBgColor = ofColor::fromHsb(hue, saturation, brightness);
	} else {
		currentStrokeColor = stroke;
		currentFillColor = fill;
		currentBgColor = bg;
	}
}
void Renderer::updateShapeManagerParams(float lineW, ofColor stroke, ofColor fill) {
	shapeManager.setDrawingParameters(lineW, stroke, fill);
}


ofRectangle Renderer::getMeshBoundingBox(const ofMesh & mesh) {
	if (mesh.getNumVertices() == 0) return ofRectangle();
	glm::vec3 min = mesh.getVertex(0);
	glm::vec3 max = mesh.getVertex(0);
	for (std::size_t i = 1; i < mesh.getNumVertices(); ++i) {
		const glm::vec3 & v = mesh.getVertex(i);
		min.x = std::min(min.x, v.x);
		min.y = std::min(min.y, v.y);
		min.z = std::min(min.z, v.z);
		max.x = std::max(max.x, v.x);
		max.y = std::max(max.y, v.y);
		max.z = std::max(max.z, v.z);
	}
	return ofRectangle(min.x, min.y, max.x - min.x, max.y - min.y);
}
// Transformation functions
void Renderer::applyTransformationToSelectedShape(float tx, float ty, float rot, float scale) {
	sceneGraph.updateSelectedTransform(tx, ty, rot, scale);
}


// 3D IMPORT FUNCTIONS: HARDCODED FOR NOW
void Renderer::import3DModel() {
	// Ouvre le sélecteur de fichiers
	ofFileDialogResult result = ofSystemLoadDialog("Select a 3D model (.obj, .ply, .stl)", false);
	if (!result.bSuccess) return;

	std::string path = result.getPath();
	std::string extension = ofFilePath::getFileExt(path);

	// Convertir en minuscules (version C++ standard)
	std::transform(extension.begin(), extension.end(), extension.begin(),
		[](unsigned char c) { return std::tolower(c); });

	// Vérifie les formats pris en charge
	if (extension != "obj" && extension != "ply" && extension != "stl" && extension != "fbx") {
		return; // format non pris en charge
	}

	// Charger le modèle avec Assimp
	ofxAssimpModelLoader loader;
	if (!loader.loadModel(path)) return;

	// Ajouter chaque mesh du modele dans la scene
	int numMeshes = loader.getMeshCount();
	for (int i = 0; i < numMeshes; i++) {
		Shape newShape;
		newShape.type = "3DModel";
		newShape.is3D = true;
		newShape.mesh3D = loader.getMesh(i);
		sceneGraph.addShape(newShape);
	}

	// Activer directement la vue 3D
	view3D = true;
}
void Renderer::clear3DModels() {
	auto shapes = sceneGraph.getAllShapes(); // copie
	shapes.erase(
		std::remove_if(shapes.begin(), shapes.end(),
			[](const Shape & s) { return s.is3D; }),
		shapes.end());
	sceneGraph.setShapes(shapes); //ajouter dans SceneGraph
}
