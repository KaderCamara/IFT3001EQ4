// RenderData.h
// Structures de données PURES pour le passage Controller → View
// Ces structures sont le contrat MVC entre les Controllers et les Renderers
#pragma once

#include "../objects/BezierCurve.h"
#include "../objects/shape.h"
#include "ofMain.h"
#include <vector>

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
 * @struct Material
 * @brief Material properties for shading
 */
struct Material {
	std::string name = "Default";
	ofColor ambient = ofColor(50, 50, 50);
	ofColor diffuse = ofColor(200, 200, 200);
	ofColor specular = ofColor(255, 255, 255);
	float shininess = 32.0f;

	// PBR properties
	float metallic = 0.0f;
	float roughness = 0.5f;
};

/**
 * @struct Light
 * @brief Light source data
 */
struct Light {
	enum class Type {
		AMBIENT,
		DIRECTIONAL,
		POINT,
		SPOT
	};

	Type type = Type::POINT;
	bool enabled = true;

	ofColor color = ofColor::white;
	float intensity = 1.0f;

	// Position (for point and spot lights)
	ofVec3f position = ofVec3f(0, 0, 0);

	// Direction (for directional and spot lights)
	ofVec3f direction = ofVec3f(0, -1, 0);

	// Attenuation (for point and spot lights)
	float constantAttenuation = 1.0f;
	float linearAttenuation = 0.09f;
	float quadraticAttenuation = 0.032f;

	// Spot light specific
	float spotCutoff = 30.0f; // in degrees
	float spotExponent = 2.0f;
};

/**
 * @struct LightingData
 * @brief Pure lighting data for rendering (MODEL)
 */
struct LightingData {
	// ========== 7.1 ILLUMINATION MODELS ==========
	enum class ShadingModel {
		NONE,
		LAMBERT,
		GOURAUD,
		PHONG,
		BLINN_PHONG,
		PBR,
		FLAT, // 7.5 Non-realistic
		CEL_SHADING, // 7.5 Non-realistic
		GOOCH // 7.5 Non-realistic
	};
	ShadingModel currentModel = ShadingModel::PHONG;

	// ========== 7.2 MATERIALS ==========
	// At least 4 different materials available
	std::vector<Material> availableMaterials;
	int currentMaterialIndex = 0;

	Material getCurrentMaterial() const {
		if (currentMaterialIndex >= 0 && currentMaterialIndex < availableMaterials.size()) {
			return availableMaterials[currentMaterialIndex];
		}
		return Material(); // default
	}

	// ========== 7.3 & 7.4 LIGHT TYPES & MULTIPLE LIGHTS ==========
	// Support for at least 4 light instances
	std::vector<Light> lights;

	// Global ambient light
	ofColor globalAmbient = ofColor(30, 30, 30);

	// ========== ADVANCED SETTINGS ==========
	bool useEnvironmentMap = false;
	bool useHDRI = false;
	bool castShadows = false;
	bool useAmbientOcclusion = false;
	bool useBloom = false;

	// Color/Tone
	float exposure = 1.0f;
	float temperature = 0.0f;
	float contrast = 1.0f;

	// 7.5 Non-realistic parameters
	int celShadingLevels = 3; // for toon shading
	float celOutlineThickness = 0.02f;
	ofColor goochWarmColor = ofColor(255, 200, 100);
	ofColor goochCoolColor = ofColor(100, 150, 255);
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
	LightingData lighting;

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
	LightingData lighting;
	bool showGrid;
	bool showAxes;
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


/**
 * @struct LightingData
 * @brief Pure lighting data for rendering (MODEL)
 */
/* struct LightingData {
	// Global settings
	bool useEnvironmentMap = true;
	bool useHDRI = true;
	bool castShadows = true;
	bool useAmbientOcclusion = true;
	bool useBloom = false;

	// Classic illumination models
	bool useLambert = true;
	bool useGouraud = true;
	bool usePhong = true;
	bool useBlinnPhong = true;
	int materialCount = 2;

	// Light types enabled
	bool usePointLights = true;
	bool useDirectionalLights = true;
	bool useSpotLights = true;
	bool useAreaLights = false;

	// Sun/Directional light
	bool sunEnabled = true;
	float sunIntensity = 1.0f;
	float sunAzimuth = 45.0f;
	float sunElevation = 35.0f;
	ofVec3f sunDirection; // calculated from azimuth/elevation

	// Point light
	bool pointLightEnabled = true;
	float pointIntensity = 0.7f;
	ofVec3f pointPosition = ofVec3f(200, 200, 200);

	// Spot light
	bool spotLightEnabled = false;
	float spotIntensity = 1.2f;
	float spotAngle = 30.0f;
	ofVec3f spotPosition = ofVec3f(0, 300, 0);
	ofVec3f spotDirection = ofVec3f(0, -1, 0);

	// PBR parameters
	bool usePBR = true;
	float metallic = 0.5f;
	float roughness = 0.4f;
	bool useMicrofacets = true;
	bool useEnvLighting = true;
	float ior = 1.45f;

	// Color/Tone
	float exposure = 1.0f;
	float temperature = 0.0f;
	float contrast = 1.0f;
};*/




