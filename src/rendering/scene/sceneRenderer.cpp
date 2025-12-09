// SceneRenderer.cpp
// Implmentation du renderer de scne MVC PUR (VIEW uniquement)
#include "SceneRenderer.h"
#include <algorithm>

// ========== RENDU 2D ==========

void SceneRenderer::draw2D(const RenderDataDraw2D & data) {
	// Dessiner toutes les formes de la scne
	for (size_t i = 0; i < data.shapes.size(); ++i) {
		const auto & shape = data.shapes[i];

		// Ignorer les formes invalides
		if (shape.type == "none" || shape.type == "x") {
			continue;
		}

		// Vrifier si la forme est slectionne
		bool isSelected = std::find(
							  data.selectedIndices.begin(),
							  data.selectedIndices.end(),
							  i)
			!= data.selectedIndices.end();

		// Dessiner la forme
		shape2DRenderer.drawShape2D(shape, isSelected, data.lineWidth);
	}

	// Curves rendering is handled by the dedicated curves rendering path

	// Dessiner l'aperu de la forme en cours de cration
	if (data.hasPreview) {
		shape2DRenderer.drawShape2D(data.currentPreview, false, data.lineWidth);
	}
}

// ========== RENDU 3D ==========

void SceneRenderer::draw3D(const RenderData3D & data) {
	// Crer et configurer une camra temporaire
	ofCamera camera;
	applyCameraData(camera, data.camera);

	// Dmarrer le rendu avec la camra
	camera.begin();

	if (data.enableLighting) {
		ofLight light;
		light.setDirectional();
		light.setDiffuseColor(data.lightColor);
		light.setSpecularColor(data.lightColor);
		light.setPosition(300, 400, 500);
		light.enable();
		ofSetGlobalAmbientColor(data.lightColor * data.lightIntensity);
	}

	if (data.showGrid) {
		ofPushStyle();
		ofSetColor(80, 90, 110);
		ofDrawGrid(200.0f, 10, true, true, true, true);
		ofPopStyle();
	}

	if (data.showAxes) {
		ofDrawAxis(75.0f);
	}

	// Couleur par dfaut pour les formes 3D
	ofSetColor(255);

	// Dessiner toutes les formes 3D
	for (const auto & shape : data.shapes) {
		shape3DRenderer.drawShape3D(shape);
	}

	if (data.enableLighting) {
		ofDisableLighting();
	}

	camera.end();
}

// ========== RENDU QUAD VIEW ==========

void SceneRenderer::drawQuadView(const RenderDataQuad & data) {
	// Dessiner les 4 vues de camra
	for (int i = 0; i < 4; ++i) {
		drawSingleCameraView(
			data.shapes,
			data.cameras[i],
			data.viewports[i],
			data.cameraLabels[i]);
	}

	// Restaurer le viewport complet
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());

	// Dessiner les sparateurs entre les vues
	drawQuadViewSeparators(data);
}

void SceneRenderer::drawSingleCameraView(
	const std::vector<Shape> & shapes,
	const CameraData & cameraData,
	const ofRectangle & viewport,
	const std::string & label) {
	// Configurer le viewport pour cette vue
	ofViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	// Crer et configurer la camra
	ofCamera camera;
	applyCameraData(camera, cameraData);

	// Dessiner avec cette camra
	camera.begin();
	ofSetColor(255);

	for (const auto & shape : shapes) {
		shape3DRenderer.drawShape3D(shape);
	}

	camera.end();

	// Dessiner le label de la vue
	ofPushStyle();
	ofSetColor(0);
	ofDrawBitmapString(label, viewport.x + 10, viewport.y + 20);
	ofPopStyle();
}

void SceneRenderer::drawQuadViewSeparators(const RenderDataQuad & data) {
	// Calculer les positions des sparateurs
	float centerX = data.viewports[0].width;
	float centerY = data.viewports[0].height;
	float totalWidth = data.viewports[0].width + data.viewports[1].width;
	float totalHeight = data.viewports[0].height + data.viewports[2].height;
	float offsetX = data.viewports[0].x;
	float offsetY = data.viewports[0].y;

	ofPushStyle();
	ofSetColor(100);
	ofSetLineWidth(2);

	// Ligne verticale
	ofDrawLine(
		offsetX + centerX, offsetY,
		offsetX + centerX, offsetY + totalHeight);

	// Ligne horizontale
	ofDrawLine(
		offsetX, offsetY + centerY,
		offsetX + totalWidth, offsetY + centerY);

	ofPopStyle();
}

// ========== CONFIGURATION ==========

void SceneRenderer::set3DDisplayOptions(bool showBoundingBox, bool showWireframe, bool showNormals) {
	showBoundingBox3D = showBoundingBox;
	showWireframe3D = showWireframe;
	showNormals3D = showNormals;

	// Configurer les renderers 3D
	shape3DRenderer.setShowBoundingBox(showBoundingBox);
	shape3DRenderer.setShowWireframe(showWireframe);
	shape3DRenderer.setShowNormals(showNormals);
}

// ========== UTILITAIRES PRIVS ==========

void SceneRenderer::applyCameraData(ofCamera & cam, const CameraData & data) {
	// Position et orientation
	cam.setPosition(data.position);
	cam.lookAt(data.target, data.up);

	// Paramtres de projection
	cam.setNearClip(data.nearClip);
	cam.setFarClip(data.farClip);
	cam.setFov(data.fov);

	// Mode orthographique ou perspective
	if (data.isOrtho) {
		cam.enableOrtho();
	} else {
		cam.disableOrtho();
	}
}
