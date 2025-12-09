// SceneRenderer.cpp
// Implémentation du renderer de scène MVC PUR (VIEW uniquement)
#include "SceneRenderer.h"

// ========== RENDU 2D ==========

void SceneRenderer::draw2D(const RenderDataDraw2D & data) {
	// Dessiner toutes les formes de la scène
	for (size_t i = 0; i < data.shapes.size(); ++i) {
		const auto & shape = data.shapes[i];

		// Ignorer les formes invalides
		if (shape.type == "none" || shape.type == "x") {
			continue;
		}

		// Vérifier si la forme est sélectionnée
		bool isSelected = std::find(
							  data.selectedIndices.begin(),
							  data.selectedIndices.end(),
							  i)
			!= data.selectedIndices.end();

		// Dessiner la forme
		shape2DRenderer.drawShape2D(shape, isSelected, data.lineWidth);
	}

	// Curves rendering is handled by the dedicated curves rendering path

	// Dessiner l'aperçu de la forme en cours de création
	if (data.hasPreview) {
		shape2DRenderer.drawShape2D(data.currentPreview, false, data.lineWidth);
	}
}

// ========== RENDU 3D ==========

void SceneRenderer::draw3D(const RenderData3D & data) {
	// Créer et configurer une caméra temporaire
	ofCamera camera;
	applyCameraData(camera, data.camera);

	// Démarrer le rendu avec la caméra
	camera.begin();

	// Couleur par défaut pour les formes 3D
	ofSetColor(255);

	// Dessiner toutes les formes 3D
	for (const auto & shape : data.shapes) {
		shape3DRenderer.drawShape3D(shape);
	}

	camera.end();
}

// ========== RENDU QUAD VIEW ==========

void SceneRenderer::drawQuadView(const RenderDataQuad & data) {
	// Dessiner les 4 vues de caméra
	for (int i = 0; i < 4; ++i) {
		drawSingleCameraView(
			data.shapes,
			data.cameras[i],
			data.viewports[i],
			data.cameraLabels[i]);
	}

	// Restaurer le viewport complet
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());

	// Dessiner les séparateurs entre les vues
	drawQuadViewSeparators(data);
}

void SceneRenderer::drawSingleCameraView(
	const std::vector<Shape> & shapes,
	const CameraData & cameraData,
	const ofRectangle & viewport,
	const std::string & label) {
	// Configurer le viewport pour cette vue
	ofViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	// Créer et configurer la caméra
	ofCamera camera;
	applyCameraData(camera, cameraData);

	// Dessiner avec cette caméra
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
	// Calculer les positions des séparateurs
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

void SceneRenderer::set3DDisplayOptions(bool showBoundingBox, bool showWireframe) {
	showBoundingBox3D = showBoundingBox;
	showWireframe3D = showWireframe;

	// Configurer les renderers 3D
	shape3DRenderer.setShowBoundingBox(showBoundingBox);
	shape3DRenderer.setShowWireframe(showWireframe);
}

// ========== UTILITAIRES PRIVÉS ==========

void SceneRenderer::applyCameraData(ofCamera & cam, const CameraData & data) {
	// Position et orientation
	cam.setPosition(data.position);
	cam.lookAt(data.target, data.up);

	// Paramètres de projection
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
