// RenderData.h
// Structures de données PURES pour le passage Controller → View
// Ces structures sont le contrat MVC entre les Controllers et les Renderers
#pragma once

#include "../objects/BezierCurve.h"
#include "../objects/shape.h"
#include "ofMain.h"
#include <vector>

// Forward declaration to avoid including curve animator header here
class CurveAnimator;

/**
* @struct RenderDataDraw2D
 * @brief Données nécessaires pour le rendu de la zone de dessin principale (MODEL pur)
 */
struct RenderDataDraw2D {
	// Formes de la scène
	std::vector<Shape> shapes;
	std::vector<int> selectedIndices;

	// Forme en cours de création (preview)
	Shape currentPreview;
	bool hasPreview = false;

	// Paramètres visuels
	float lineWidth = 2.0f;
	ofColor strokeColor = ofColor::black;
	ofColor fillColor = ofColor::white;
	ofColor backgroundColor = ofColor::white;
};

/**
 * @struct RenderDataCurves2D
 * @brief Données nécessaires pour le rendu de la zone dédiée aux courbes (MODEL pur)
 */
struct RenderDataCurves2D {
	// Courbes de Bézier
	std::vector<glm::vec2> controlPoints;
	std::vector<BezierCurve> curves;

	// Animateur de courbe (optionnel)

	const CurveAnimator * animator = nullptr;

	// Paramètres visuels
	float lineWidth = 2.0f;
	ofColor strokeColor = ofColor::black;
	ofColor backgroundColor = ofColor::white;
};

/**
 * @struct CameraData
 * @brief Données d'une caméra pour le rendu 3D
 */
struct CameraData {
	ofVec3f position;
	ofVec3f target;
	ofVec3f up;
	float fov = 60.0f;
	float nearClip = 0.1f;
	float farClip = 10000.0f;
	bool isOrtho = false;
};

/**
 * @struct RenderData3D
 * @brief Données nécessaires pour le rendu 3D (MODEL pur)
 */
struct RenderData3D {
	// Formes de la scène
	std::vector<Shape> shapes;

	// Caméra (données pures, pas de référence à CameraManager)
	CameraData camera;

	// Options d'affichage
	bool showBoundingBox = false;
	bool showWireframe = false;
	bool showGrid = true;
	bool showAxes = true;
	bool showNormals = false;

	// Options de shading / lighting
	bool enableLighting = false;
	float lightIntensity = 1.0f;
	ofColor lightColor = ofColor::white;

	// Zone de dessin
	ofRectangle drawingArea;
};

/**
 * @struct RenderDataQuad
 * @brief Données nécessaires pour le rendu en vue quad (4 caméras)
 */
struct RenderDataQuad {
	// Formes de la scène
	std::vector<Shape> shapes;

	// Les 4 caméras (données pures)
	CameraData cameras[4];
	std::string cameraLabels[4] = { "Top View", "Front View", "Side View", "Bottom View" };

	// Viewports pour chaque caméra
	ofRectangle viewports[4];

	// Options d'affichage
	bool showBoundingBox = false;
	bool showWireframe = false;
};

/**
 * @struct RenderDataImage
 * @brief Données nécessaires pour le rendu d'images
 */
struct RenderDataImage {
	const ofImage * image = nullptr; // Pointeur const vers l'image (pas de propriété)
	ofRectangle bounds;
	bool maintainAspectRatio = true;
};
