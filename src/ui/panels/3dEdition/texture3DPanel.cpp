#include "texture3DPanel.h"

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
	toggleProceduralTexture.setup("Procedural material", true);
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

	if (visible) texturePanel.draw();
}
