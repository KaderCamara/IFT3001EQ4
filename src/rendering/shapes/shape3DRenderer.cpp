// Shape3DRenderer.cpp
#include "Shape3DRenderer.h"
#include <algorithm>
#include <cfloat>

void Shape3DRenderer::setup() {
	// Adjust this path to match your project structure
	lightingShader.load("../../src/rendering/shaders/lighting.vert", "../../src/rendering/shaders/lighting.frag");
	if (lightingShader.isLoaded()) {
		ofLogNotice("Shape3DRenderer") << "Lighting shader loaded and compiled successfully";
	} else {
		// Cette erreur est critique et devrait apparaître dans la console si le shader crash
		ofLogError("Shape3DRenderer") << "ERROR: Lighting shader FAILED to load/compile!";
	}
	ofLogNotice("Shape3DRenderer") << "Lighting shader loaded";
}


void Shape3DRenderer::drawShape3D(const Shape & s, const LightingData & lighting, const ofVec3f & viewPos) const {
	if (!s.is3D || s.mesh3D.getNumVertices() == 0) return;

	ofMesh & mesh3D = const_cast<ofMesh &>(s.mesh3D);

	if (!mesh3D.hasTexCoords() || mesh3D.getNumTexCoords() == 0) {
		ofLogNotice("Shape3DRenderer") << "Generating automatic UVs for mesh...";

		// Calculer la bounding box
		glm::vec3 minBounds(FLT_MAX);
		glm::vec3 maxBounds(-FLT_MAX);

		for (const auto & v : mesh3D.getVertices()) {
			minBounds = glm::min(minBounds, v);
			maxBounds = glm::max(maxBounds, v);
		}

		glm::vec3 size = maxBounds - minBounds;

		// Éviter division par zéro
		if (size.x < 0.001f) size.x = 1.0f;
		if (size.y < 0.001f) size.y = 1.0f;
		if (size.z < 0.001f) size.z = 1.0f;

		// Générer des coordonnées UV basées sur la projection XY
		mesh3D.clearTexCoords();
		for (const auto & v : mesh3D.getVertices()) {
			float u = (v.x - minBounds.x) / size.x;
			float vCoord = (v.y - minBounds.y) / size.y;
			mesh3D.addTexCoord(glm::vec2(u, vCoord));
		}

		ofLogNotice("Shape3DRenderer") << "✅ Generated " << mesh3D.getNumTexCoords() << " UV coordinates";
	}

	ofPushMatrix();

	// Apply transformations
	ofTranslate(s.translation.x, s.translation.y, 0);
	ofRotateZDeg(s.rotation);
	ofScale(s.scale, s.scale, s.scale);

	bool useLightingShader = (lighting.currentModel != LightingData::ShadingModel::NONE);

	if (useLightingShader) {
		lightingShader.begin();
		lightingShader.setUniform1i("u_shadingModel", static_cast<int>(lighting.currentModel));

		glm::mat4 modelViewMatrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
		lightingShader.setUniformMatrix4f("modelViewMatrix", modelViewMatrix);

		glm::mat4 projectionMatrix = ofGetCurrentMatrix(OF_MATRIX_PROJECTION);
		glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
		lightingShader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);

		lightingShader.setUniformMatrix4f("modelViewMatrix", ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
		lightingShader.setUniformMatrix3f("normalMatrix", ofGetCurrentNormalMatrix());

		// Set lighting and material uniforms
		setLightingUniforms(lighting, viewPos);
		setMaterialUniforms(lighting.getCurrentMaterial());

		if (useProceduralTexture && proceduralTexture.isAllocated()) {
			proceduralTexture.bind(0);
			lightingShader.setUniform1i("uUseProceduralTexture", 1);
			lightingShader.setUniformTexture("uProceduralTexture", proceduralTexture, 0);

			ofLogNotice("Shape3DRenderer") << "✅ Texture BOUND: "
										   << proceduralTexture.getWidth() << "x" << proceduralTexture.getHeight()
										   << " | UVs: " << mesh3D.getNumTexCoords();
		} else {
			lightingShader.setUniform1i("uUseProceduralTexture", 0);
		}
	} else {
		ofSetColor(255);
	}

	// Draw the mesh
	if (showWireframe) {
		s.mesh3D.drawWireframe();
	} else {
		s.mesh3D.draw();
	}

	if (showNormals && mesh3D.hasNormals()) {
		ofPushStyle();
		ofSetColor(ofColor::cyan);
		const auto & normals = mesh3D.getNormals();
		const auto & verts = mesh3D.getVertices();
		std::size_t count = std::min(normals.size(), verts.size());
		for (std::size_t i = 0; i < count; ++i) {
			const glm::vec3 & v = verts[i];
			const glm::vec3 & n = glm::normalize(normals[i]);
			ofDrawLine(v, v + n * 10.0f);
		}
		ofPopStyle();
	}

	// Unbind texture and end shader
	if (useLightingShader) {
		if (useProceduralTexture && proceduralTexture.isAllocated()) {
			proceduralTexture.unbind();
		}
		lightingShader.end();
	}

	// Draw bounding box if enabled
	if (showBoundingBox) {
		glm::vec3 min(FLT_MAX), max(-FLT_MAX);
		for (const auto & v : mesh3D.getVertices()) {
			min = glm::min(min, v);
			max = glm::max(max, v);
		}
		ofPushStyle();
		ofNoFill();
		ofSetColor(ofColor::green);
		ofDrawBox((min + max) * 0.5f, max.x - min.x, max.y - min.y, max.z - min.z);
		ofPopStyle();
	}

	ofPopMatrix();
}

void Shape3DRenderer::clearProceduralTexture() {
	useProceduralTexture = false;
	proceduralTexture.clear();
}


void Shape3DRenderer::setLightingUniforms(const LightingData & lighting, const ofVec3f & viewPos) const {
	// Shading model
	lightingShader.setUniform1i("u_shadingModel", static_cast<int>(lighting.currentModel));

	// View position
	lightingShader.setUniform3f("u_viewPos", 0.0f, 0.0f, 0.0f);

	glm::mat4 viewMatrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);

	// Global ambient
	ofVec3f ambient = ofVec3f(lighting.globalAmbient.r, lighting.globalAmbient.g, lighting.globalAmbient.b) / 255.0f;
	lightingShader.setUniform3f("u_globalAmbient", ambient.x, ambient.y, ambient.z);

	// Number of lights
	int numLights = std::min(4, (int)lighting.lights.size());
	lightingShader.setUniform1i("u_numLights", numLights);

	// Set up to 4 lights
	for (int i = 0; i < numLights && i < 4; i++) {
		const Light & light = lighting.lights[i];
		std::string prefix = "u_light" + std::to_string(i);

		lightingShader.setUniform1i(prefix + "Type", static_cast<int>(light.type));

		ofVec3f color = ofVec3f(light.color.r, light.color.g, light.color.b) / 255.0f;
		lightingShader.setUniform3f(prefix + "Color", color.x, color.y, color.z);
		lightingShader.setUniform1f(prefix + "Intensity", light.intensity);

		glm::vec4 lightPositionViewSpace = viewMatrix * glm::vec4(glm::vec3(light.position), 1.0f);
		lightingShader.setUniform3f(prefix + "Position", lightPositionViewSpace.x, lightPositionViewSpace.y, lightPositionViewSpace.z);
		glm::vec4 lightDirectionViewSpace = viewMatrix * glm::vec4(glm::vec3(light.direction), 0.0f);
		lightingShader.setUniform3f(prefix + "Direction", lightDirectionViewSpace.x, lightDirectionViewSpace.y, lightDirectionViewSpace.z);

		lightingShader.setUniform1f(prefix + "ConstantAtt", light.constantAttenuation);
		lightingShader.setUniform1f(prefix + "LinearAtt", light.linearAttenuation);
		lightingShader.setUniform1f(prefix + "QuadraticAtt", light.quadraticAttenuation);

		lightingShader.setUniform1f(prefix + "SpotCutoff", light.spotCutoff);
		lightingShader.setUniform1f(prefix + "SpotExponent", light.spotExponent);
	}

	// Tone mapping
	lightingShader.setUniform1f("u_exposure", lighting.exposure);
	lightingShader.setUniform1f("u_contrast", lighting.contrast);

	// Non-realistic shading
	lightingShader.setUniform1i("u_celLevels", lighting.celShadingLevels);
	ofVec3f warm = ofVec3f(lighting.goochWarmColor.r, lighting.goochWarmColor.g, lighting.goochWarmColor.b);
	ofVec3f cool = ofVec3f(lighting.goochCoolColor.r, lighting.goochCoolColor.g, lighting.goochCoolColor.b);
	lightingShader.setUniform3f("u_goochWarmColor", warm.x, warm.y, warm.z);
	lightingShader.setUniform3f("u_goochCoolColor", cool.x, cool.y, cool.z);
}

void Shape3DRenderer::setMaterialUniforms(const Material & material) const {
	ofVec3f ambient = ofVec3f(material.ambient.r, material.ambient.g, material.ambient.b) / 255.0f;
	ofVec3f diffuse = ofVec3f(material.diffuse.r, material.diffuse.g, material.diffuse.b) / 255.0f;
	ofVec3f specular = ofVec3f(material.specular.r, material.specular.g, material.specular.b) / 255.0f;

	static bool loggedOnce = false;
	if (!loggedOnce) {
		ofLogNotice("Shape3DRenderer") << "Material values: "
									   << "Ambient(" << ambient.x << "," << ambient.y << "," << ambient.z << ") "
									   << "Diffuse(" << diffuse.x << "," << diffuse.y << "," << diffuse.z << ") "
									   << "Specular(" << specular.x << "," << specular.y << "," << specular.z << ") "
									   << "Shininess(" << material.shininess << ")";
		loggedOnce = true;
	}

	lightingShader.setUniform3f("u_materialAmbient", ambient.x, ambient.y, ambient.z);
	lightingShader.setUniform3f("u_materialDiffuse", diffuse.x, diffuse.y, diffuse.z);

	lightingShader.setUniform3f("u_materialSpecular", specular.x, specular.y, specular.z);
	lightingShader.setUniform1f("u_materialShininess", material.shininess);
}

ofRectangle Shape3DRenderer::getMeshBoundingBox(const ofMesh & mesh) const {
	if (mesh.getNumVertices() == 0) return ofRectangle();

	glm::vec3 min = mesh.getVertex(0);
	glm::vec3 max = mesh.getVertex(0);

	for (std::size_t i = 1; i < mesh.getNumVertices(); ++i) {
		const glm::vec3 & v = mesh.getVertex(i);
		min = glm::min(min, v);
		max = glm::max(max, v);
	}

	return ofRectangle(min.x, min.y, max.x - min.x, max.y - min.y);
}

void Shape3DRenderer::setProceduralTexture(const ofTexture & tex) {
	proceduralTexture = tex;
	useProceduralTexture = true;
}
