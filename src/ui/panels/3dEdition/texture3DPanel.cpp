#include "texture3DPanel.h"
#include "rendering/ProceduralTexture.h"
#include "rendering/Renderer.h" // <-- Ajoutez cette ligne pour inclure la définition complète de Renderer

void Texture3DPanel::setup() {
	texturePanel.setup("Textures & Tone mapping");
	texturePanel.setBorderColor(ofColor(0, 0));
	texturePanel.setBackgroundColor(ofColor(0, 0, 0, 0));

	// Collapsible dropdown
	texturePanel.enableHeader();
	texturePanel.minimize();

	lblCoordinates.setup("-- Coordonnees --", "");
	toggleUVs.setup("Use UV coordinates", true);
	toggleTriplanar.setup("Triplanar mapping", false);

	lblFiltering.setup("-- Filtrage --", "");
	toggleNearest.setup("Nearest", false);
	toggleLinear.setup("Linear", true);
	toggleMipMap.setup("MipMap", true);

	lblToneMapping.setup("-- Tone Mapping --", "");
	toggleToneMapping.setup("Enable tone mapping", true);
	toggleACES.setup("ACES curve", false);

	lblCubemap.setup("-- Cubemap --", "");
	toggleCubemapReflection.setup("Cubemap reflection", true);
	toggleCubemapRefraction.setup("Cubemap refraction", true);

	lblProcedural.setup("-- Procedural --", "");
	toggleProceduralTexture.setup("Procedural material", false);
	toggleTextureNoise.setup("Noise layers", false);

	texturePanel.add(&lblCoordinates);
	texturePanel.add(&toggleUVs);
	texturePanel.add(&toggleTriplanar);

	texturePanel.add(&lblFiltering);
	texturePanel.add(&toggleNearest);
	texturePanel.add(&toggleLinear);
	texturePanel.add(&toggleMipMap);

	texturePanel.add(&lblToneMapping);
	texturePanel.add(&toggleToneMapping);
	texturePanel.add(&toggleACES);

	texturePanel.add(&lblCubemap);
	texturePanel.add(&toggleCubemapReflection);
	texturePanel.add(&toggleCubemapRefraction);

	texturePanel.add(&lblProcedural);
	texturePanel.add(&toggleProceduralTexture);
	texturePanel.add(&toggleTextureNoise);
}

void Texture3DPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	texturePanel.setPosition(enforcedX, enforcedY);
}

void Texture3DPanel::setWidth(float w) {
	enforcedWidth = w;
	texturePanel.setWidthElements(enforcedWidth);
}

float Texture3DPanel::getHeight() {
	return texturePanel.getHeight();
}

void Texture3DPanel::draw() {
	texturePanel.setPosition(enforcedX, enforcedY);
	texturePanel.setWidthElements(enforcedWidth);

	if (visible) {
		texturePanel.draw();

		// Pour debug : afficher la texture générée à côté du panel
		bool isProceduralActive = toggleProceduralTexture;
		if (isProceduralActive && proceduralTexture.isAllocated()) {
			proceduralTexture.draw(enforcedX + enforcedWidth + 10, enforcedY, 128, 128);
		}
	}
}

void Texture3DPanel::update() {
	bool isProceduralActive = toggleProceduralTexture;

	if (isProceduralActive) {
		// Générer si pas encore active
		if (!proceduralTextureActivePrev) {
			proceduralTexture = generateSimpleProceduralTexture(128, 128);
			ofLogNotice("Texture3DPanel") << "Procedural texture generated (128x128)";
		}

		if (renderer) {
			renderer->setProceduralTexture3D(proceduralTexture);
		} else {
			ofLogWarning("Texture3DPanel") << "Renderer not connected - cannot send texture!";
		}
	} else {
		// Si toggle décoché, désactiver l'utilisation
		if (renderer) {
			ofTexture emptyTex;
			renderer->setProceduralTexture3D(emptyTex);
			ofLogNotice("Texture3DPanel") << "Procedural texture disabled";
		}
	}

	proceduralTextureActivePrev = isProceduralActive;
}
