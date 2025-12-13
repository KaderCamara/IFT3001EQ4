// Shape3DRenderer.h
// Renderer spécialisé pour les formes 3D (VIEW)

#pragma once

#include "../../rendering/renderData.h"
#include "../../objects/shape.h"
#include "ofMain.h"

/**
 * @class Shape3DRenderer
 * @brief Responsable du rendu des meshes 3D (VIEW pure)
 *
 * - Dessine les meshes 3D avec wireframe ou filled
 * - Dessine la bounding box si activée
 */
class Shape3DRenderer {
public:
	Shape3DRenderer() = default;
	~Shape3DRenderer() = default;

	/**
     * @brief Dessine une forme 3D (mesh) avec les options globales
     */
	void setup();
	void drawShape3D(const Shape & s,
		const LightingData & lighting,
		const ofVec3f & viewPos,
		bool enableGlobalIllumination = false,
		int lightBounces = 1) const;
	//void drawShape3D(const Shape & s) const;

	void setShowBoundingBox(bool show) { showBoundingBox = show; };
	void setShowWireframe(bool show) { showWireframe = show; };
	void setShowNormals(bool show) { showNormals = show; };

private:
	/**
     * @brief Calcule la bounding box d'un mesh (utilitaire)
     */

	bool showBoundingBox = false;
	bool showWireframe = false;
	bool showNormals = false;

	ofShader lightingShader;

	/**
     * @brief Set shader uniforms for lighting
     */
	void setLightingUniforms(const LightingData & lighting, const ofVec3f & viewPos) const;

	/**
     * @brief Set shader uniforms for material
     */
	void setMaterialUniforms(const Material & material) const;

	ofRectangle getMeshBoundingBox(const ofMesh & mesh) const;

};
