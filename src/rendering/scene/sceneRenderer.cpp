// SceneRenderer.cpp
// Implmentation du renderer de scne MVC PUR (VIEW uniquement)
#include "SceneRenderer.h"
#include <algorithm>

void SceneRenderer::setup() {
	// 1. Initialiser le Shape3DRenderer pour charger le shader !
	shape3DRenderer.setup();

	ofLogNotice("SceneRenderer") << "Internal renderers initialized.";
}
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

		// Vrifier si la forme est survole
		bool isHovered = (static_cast<int>(i) == data.hoveredShapeIndex);

		// Dessiner la forme
		shape2DRenderer.drawShape2D(shape, isSelected, isHovered, data.lineWidth);
	}

	// Curves rendering is handled by the dedicated curves rendering path

	// Dessiner l'aperu de la forme en cours de cration
	if (data.hasPreview) {
		// If we have explicit visual parameters in RenderDataDraw2D, use them for preview so the UI controls affect it
		shape2DRenderer.drawPreviewShape2D(data.currentPreview, data.strokeColor, data.fillColor, data.lineWidth, data.hoveredShapeIndex == -1 ? false : false);
	}
}

// Helper to get the active camera (external if set, otherwise internal)
static ofEasyCam & getActiveCam(ofEasyCam & internalCam, ofEasyCam * externalCam) {
	return externalCam ? *externalCam : internalCam;
}

// ========== RENDU 3D ==========

/* void SceneRenderer::draw3D(const RenderData3D & data) {
	// Use the provided drawing area as the viewport for 3D rendering
	ofRectangle viewport = data.drawingArea;
	if (viewport.width <= 0 || viewport.height <= 0) {
		// fallback to full window
		viewport.set(0, 0, ofGetWidth(), ofGetHeight());
	}

	ofEasyCam & cam = getActiveCam(sceneCam, externalCam);

	// NOTE: We intentionally avoid overwriting external camera transforms to preserve user interactions
	// Ensure camera aspect matches viewport
	cam.setAspectRatio(viewport.width / viewport.height);

	// Set viewport so subsequent drawing occurs inside the drawing area
	ofViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	// Begin camera with explicit viewport
	cam.begin(viewport);

	/* if (data.enableLighting) {
		ofLight light;
		light.setDirectional();
		light.setDiffuseColor(data.lightColor);
		light.setSpecularColor(data.lightColor);
		light.setPosition(300, 400, 500);
		light.enable();
		ofSetGlobalAmbientColor(data.lightColor * data.lightIntensity);
	}

	// Adapt grid/axis size to viewport
	float viewSize = std::max(1.0f, std::min(viewport.width, viewport.height));
	if (data.showGrid) {
		ofPushStyle();
		ofSetColor(80, 90, 110);
		ofDrawGrid(viewSize, 10, true, true, true, true);
		ofPopStyle();
	}

	if (data.showAxes) {
		ofDrawAxis(viewSize * 0.5f);
	}

	// Couleur par dfaut pour les formes 3D
	ofSetColor(255);

	// Calculer la bounding box de la sc�ne pour adapter l'�chelle si n�cessaire
	bool hasVertices = false;
	glm::vec3 sceneMin(FLT_MAX), sceneMax(-FLT_MAX);
	for (const auto & shape : data.shapes) {
		const ofMesh & m = shape.mesh3D;
		for (std::size_t i = 0; i < m.getNumVertices(); ++i) {
			const glm::vec3 & v = m.getVertex(i);
			hasVertices = true;
			sceneMin = glm::min(sceneMin, v);
			sceneMax = glm::max(sceneMax, v);
		}
	}

	float scaleFactor = 1.0f;
	glm::vec3 sceneCenter(0.0f);
	if (hasVertices) {
		glm::vec3 extent = sceneMax - sceneMin;
		float maxExtent = std::max(std::max(extent.x, extent.y), extent.z);
		if (maxExtent > 0.0f) {
			// Choose a target size based on the viewport so the scene fits visually
			const float targetMaxSize = viewSize * 0.5f; // occupy about half of the viewport
			scaleFactor = std::min(1.0f, targetMaxSize / maxExtent);
			sceneCenter = (sceneMin + sceneMax) * 0.5f;
		}
	}

	ofVec3f viewPos = cam.getPosition();

	// Dessiner toutes les formes 3D (avec recentrage et mise � l'�chelle globale)
	if (hasVertices && scaleFactor != 1.0f) {
		ofPushMatrix();
		// Recentre la sc�ne autour de l'origine puis applique l'�chelle
		ofTranslate(-sceneCenter.x, -sceneCenter.y, -sceneCenter.z);
		ofScale(scaleFactor, scaleFactor, scaleFactor);

		for (const auto & shape : data.shapes) {
			shape3DRenderer.drawShape3D(shape, data.lighting, viewPos);
		}

		ofPopMatrix();
	} else {
		// Aucun ajustement n�cessaire
		for (const auto & shape : data.shapes) {
			shape3DRenderer.drawShape3D(shape, data.lighting, viewPos);
		}
	}

	/* if (data.enableLighting) {
		ofDisableLighting();
	}

	// End camera and restore full viewport
	cam.end();
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());
}*/

/* GOOD ONE !!
void SceneRenderer::draw3D(const RenderData3D & data) {
	// Use the provided drawing area as the viewport for 3D rendering
	ofRectangle viewport = data.drawingArea;
	if (viewport.width <= 0 || viewport.height <= 0) {
		// fallback to full window
		viewport.set(0, 0, ofGetWidth(), ofGetHeight());
	}

	ofEasyCam & cam = getActiveCam(sceneCam, externalCam);

	// Ensure camera aspect matches viewport
	cam.setAspectRatio(viewport.width / viewport.height);

	// Set viewport so subsequent drawing occurs inside the drawing area
	ofViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	// Begin camera with explicit viewport
	cam.begin(viewport);

	// --- ANCIEN BLOC D'�CLAIRAGE (RESTAUR�) ---
	// Note : Ce bloc utilise l'�clairage interne d'OpenFrameworks.
	if (data.enableLighting) {
		ofLight light;
		light.setDirectional();
		light.setDiffuseColor(data.lightColor);
		light.setSpecularColor(data.lightColor);
		light.setPosition(300, 400, 500);
		light.enable();
		ofSetGlobalAmbientColor(data.lightColor * data.lightIntensity);
	}
	// ------------------------------------------

	// Adapt grid/axis size to viewport
	float viewSize = std::max(1.0f, std::min(viewport.width, viewport.height));
	if (data.showGrid) {
		ofPushStyle();
		ofSetColor(80, 90, 110);
		ofDrawGrid(viewSize, 10, true, true, true, true);
		ofPopStyle();
	}

	if (data.showAxes) {
		ofDrawAxis(viewSize * 0.5f);
	}

	// Couleur par dfaut pour les formes 3D
	ofSetColor(255);

	// Calculer la bounding box de la sc�ne pour adapter l'�chelle si n�cessaire
	bool hasVertices = false;
	glm::vec3 sceneMin(FLT_MAX), sceneMax(-FLT_MAX);
	for (const auto & shape : data.shapes) {
		const ofMesh & m = shape.mesh3D;
		for (std::size_t i = 0; i < m.getNumVertices(); ++i) {
			const glm::vec3 & v = m.getVertex(i);
			hasVertices = true;
			sceneMin = glm::min(sceneMin, v);
			sceneMax = glm::max(sceneMax, v);
		}
	}

	float scaleFactor = 1.0f;
	glm::vec3 sceneCenter(0.0f);
	if (hasVertices) {
		glm::vec3 extent = sceneMax - sceneMin;
		float maxExtent = std::max(std::max(extent.x, extent.y), extent.z);
		if (maxExtent > 0.0f) {
			// Choose a target size based on the viewport so the scene fits visually
			const float targetMaxSize = viewSize * 0.5f; // occupy about half of the viewport
			scaleFactor = std::min(1.0f, targetMaxSize / maxExtent);
			sceneCenter = (sceneMin + sceneMax) * 0.5f;
		}
	}

	// Dessiner toutes les formes 3D (avec recentrage et mise � l'�chelle globale)
	if (hasVertices && scaleFactor != 1.0f) {
		ofPushMatrix();
		// Recentre la sc�ne autour de l'origine puis applique l'�chelle
		ofTranslate(-sceneCenter.x, -sceneCenter.y, -sceneCenter.z);
		ofScale(scaleFactor, scaleFactor, scaleFactor);

		for (const auto & shape : data.shapes) {
			// Appel � l'ancienne signature
			shape3DRenderer.drawShape3D(shape);
		}

		ofPopMatrix();
	} else {
		// Aucun ajustement n�cessaire
		for (const auto & shape : data.shapes) {
			// Appel � l'ancienne signature
			shape3DRenderer.drawShape3D(shape);
		}
	}

	// --- ANCIEN BLOC D'�CLAIRAGE (RESTAUR�) ---
	if (data.enableLighting) {
		ofDisableLighting();
	}
	// ------------------------------------------

	// End camera and restore full viewport
	cam.end();
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());
}*/

void SceneRenderer::draw3D(const RenderData3D & data) {
	// Use the provided drawing area as the viewport for 3D rendering
	ofRectangle viewport = data.drawingArea;
	if (viewport.width <= 0 || viewport.height <= 0) {
		// fallback to full window
		viewport.set(0, 0, ofGetWidth(), ofGetHeight());
	}

	ofEasyCam & cam = getActiveCam(sceneCam, externalCam);

	// Ensure camera aspect matches viewport
	cam.setAspectRatio(viewport.width / viewport.height);

	// Set viewport so subsequent drawing occurs inside the drawing area
	ofViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	// Begin camera with explicit viewport
	cam.begin(viewport);


	// Adapt grid/axis size to viewport
	float viewSize = std::max(1.0f, std::min(viewport.width, viewport.height));
	if (data.showGrid) {
		ofPushStyle();
		ofSetColor(80, 90, 110);
		ofDrawGrid(viewSize, 10, true, true, true, true);
		ofPopStyle();
	}

	if (data.showAxes) {
		ofDrawAxis(viewSize * 0.5f);
	}

	// Couleur par dfaut pour les formes 3D
	ofSetColor(255);

	// Calculer la bounding box de la sc�ne pour adapter l'�chelle si n�cessaire
	bool hasVertices = false;
	glm::vec3 sceneMin(FLT_MAX), sceneMax(-FLT_MAX);
	for (const auto & shape : data.shapes) {
		const ofMesh & m = shape.mesh3D;
		for (std::size_t i = 0; i < m.getNumVertices(); ++i) {
			const glm::vec3 & v = m.getVertex(i);
			hasVertices = true;
			sceneMin = glm::min(sceneMin, v);
			sceneMax = glm::max(sceneMax, v);
		}
	}

	float scaleFactor = 1.0f;
	glm::vec3 sceneCenter(0.0f);
	if (hasVertices) {
		glm::vec3 extent = sceneMax - sceneMin;
		float maxExtent = std::max(std::max(extent.x, extent.y), extent.z);
		if (maxExtent > 0.0f) {
			// Choose a target size based on the viewport so the scene fits visually
			const float targetMaxSize = viewSize * 0.5f; // occupy about half of the viewport
			scaleFactor = std::min(1.0f, targetMaxSize / maxExtent);
			sceneCenter = (sceneMin + sceneMax) * 0.5f;
		}
	}
	//ofVec3f viewPos = ofVec3f(0.0f, 0.0f, 0.0f);
	ofVec3f viewPos =cam.getPosition();

	// Dessiner toutes les formes 3D (avec recentrage et mise � l'�chelle globale)
	if (hasVertices && scaleFactor != 1.0f) {
		ofPushMatrix();
		// Recentre la sc�ne autour de l'origine puis applique l'�chelle
		ofTranslate(-sceneCenter.x, -sceneCenter.y, -sceneCenter.z);
		ofScale(scaleFactor, scaleFactor, scaleFactor);

		for (const auto & shape : data.shapes) {
			// Appel � l'ancienne signature
			shape3DRenderer.drawShape3D(shape, data.lighting, viewPos);
		}

		ofPopMatrix();
	} else {
		// Aucun ajustement n�cessaire
		for (const auto & shape : data.shapes) {
			// Appel � l'ancienne signature
			shape3DRenderer.drawShape3D(shape, data.lighting, viewPos);
		}
	}

	// End camera and restore full viewport
	cam.end();
	ofViewport(0, 0, ofGetWidth(), ofGetHeight());
}

// ========== RENDU QUAD VIEW ==========

void SceneRenderer::drawQuadView(const RenderDataQuad & data) {
	// Dessiner les 4 vues de camra
	for (int i = 0; i < 4; ++i) {
		drawSingleCameraView(
			data.shapes,
			data.cameras[i],
			data.viewports[i],
			data.cameraLabels[i],
			data.lighting,
			data.showGrid,
			data.showAxes);
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
	const std::string & label,
	const LightingData & lighting,
	bool showGrid,
	bool showAxes) {
	// Configurer le viewport pour cette vue
	ofViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	// Crer et configurer la camra
	ofCamera camera;
	applyCameraData(camera, cameraData);
	camera.setAspectRatio(viewport.width / viewport.height);

	// Dessiner avec cette camra
	camera.begin(viewport);

	// Adapt grid/axis size to viewport
	float viewSize = std::max(1.0f, std::min(viewport.width, viewport.height));

	if (showGrid) {
		ofPushStyle();
		ofSetColor(80, 90, 110);
		ofDrawGrid(viewSize, 10, true, true, true, true);
		ofPopStyle();
	}

	if (showAxes) {
		ofDrawAxis(viewSize * 0.5f);
	}

	ofSetColor(255);

	for (const auto & shape : shapes) {
		//shape3DRenderer.drawShape3D(shape, lighting, camera.getPosition());
		shape3DRenderer.drawShape3D(shape, lighting, camera.getPosition());
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
