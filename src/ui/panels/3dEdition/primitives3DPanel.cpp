#include "primitives3DPanel.h"

void Primitives3DPanel::setup() {
	primitivesPanel.setup("Primitives 3D");
	primitivesPanel.setBorderColor(ofColor(0, 0));
	primitivesPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	primitivesPanel.enableHeader();
	primitivesPanel.minimize();

	// Section Primitives
	lblPrimitives.setup("-- Primitives OpenGL/OF --", "");
	btnSphere.setup("Sphere");
	btnBox.setup("Box / Cube");
	btnCylinder.setup("Cylinder");
	btnCone.setup("Cone");
	btnPlane.setup("Plane");
	btnIcosahedron.setup("Icosahedron");

	// Paramètres de primitive
	lblPrimitiveParams.setup("-- Parameters --", "");
	primitiveSize.set("Size", 50.0, 10.0, 200.0);
	primitiveResolution.set("Resolution", 32, 3, 128);

	// Section Textures
	lblTextures.setup("-- Textures --", "");
	enableTexture.set("Enable Texture", false);
	btnCheckerTexture.setup("Checker Pattern");
	btnGradientTexture.setup("Gradient");
	btnNoiseTexture.setup("Perlin Noise");
	btnLoadTexture.setup("Load Image...");

	// Section Matériaux
	lblMaterials.setup("-- Materials (PBR) --", "");
	diffuseColor.set("Diffuse Color", ofColor(200, 200, 200));
	specularColor.set("Specular Color", ofColor(255, 255, 255));
	shininess.set("Shininess", 32.0, 0.0, 128.0);
	metallic.set("Metallic", 0.0, 0.0, 1.0);
	roughness.set("Roughness", 0.5, 0.0, 1.0);

	// Ajouter les éléments au panel
	primitivesPanel.add(&lblPrimitives);
	primitivesPanel.add(&btnSphere);
	primitivesPanel.add(&btnBox);
	primitivesPanel.add(&btnCylinder);
	primitivesPanel.add(&btnCone);
	primitivesPanel.add(&btnPlane);
	primitivesPanel.add(&btnIcosahedron);

	primitivesPanel.add(&lblPrimitiveParams);
	primitivesPanel.add(primitiveSize);
	primitivesPanel.add(primitiveResolution);

	primitivesPanel.add(&lblTextures);
	primitivesPanel.add(enableTexture);
	primitivesPanel.add(&btnCheckerTexture);
	primitivesPanel.add(&btnGradientTexture);
	primitivesPanel.add(&btnNoiseTexture);
	primitivesPanel.add(&btnLoadTexture);

	primitivesPanel.add(&lblMaterials);
	primitivesPanel.add(diffuseColor);
	primitivesPanel.add(specularColor);
	primitivesPanel.add(shininess);
	primitivesPanel.add(metallic);
	primitivesPanel.add(roughness);

	// Connecter les listeners
	btnSphere.addListener(this, &Primitives3DPanel::onSpherePressed);
	btnBox.addListener(this, &Primitives3DPanel::onBoxPressed);
	btnCylinder.addListener(this, &Primitives3DPanel::onCylinderPressed);
	btnCone.addListener(this, &Primitives3DPanel::onConePressed);
	btnPlane.addListener(this, &Primitives3DPanel::onPlanePressed);
	btnIcosahedron.addListener(this, &Primitives3DPanel::onIcosahedronPressed);

	btnCheckerTexture.addListener(this, &Primitives3DPanel::onCheckerTexturePressed);
	btnGradientTexture.addListener(this, &Primitives3DPanel::onGradientTexturePressed);
	btnNoiseTexture.addListener(this, &Primitives3DPanel::onNoiseTexturePressed);
	btnLoadTexture.addListener(this, &Primitives3DPanel::onLoadTexturePressed);
}

void Primitives3DPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	primitivesPanel.setPosition(enforcedX, enforcedY);
}

void Primitives3DPanel::setWidth(float w) {
	enforcedWidth = w;
	primitivesPanel.setWidthElements(enforcedWidth);
}

float Primitives3DPanel::getHeight() {
	return primitivesPanel.getHeight();
}

void Primitives3DPanel::draw() {
	primitivesPanel.setPosition(enforcedX, enforcedY);
	primitivesPanel.setWidthElements(enforcedWidth);

	if (visible) primitivesPanel.draw();
}

// Callbacks pour les primitives
void Primitives3DPanel::onSpherePressed() {
	selectedPrimitive = "sphere";
	drawPrimitiveRequested = true;
	ofLogNotice("Primitives3DPanel") << "Sphere requested";
}

void Primitives3DPanel::onBoxPressed() {
	selectedPrimitive = "box";
	drawPrimitiveRequested = true;
	ofLogNotice("Primitives3DPanel") << "Box requested";
}

void Primitives3DPanel::onCylinderPressed() {
	selectedPrimitive = "cylinder";
	drawPrimitiveRequested = true;
	ofLogNotice("Primitives3DPanel") << "Cylinder requested";
}

void Primitives3DPanel::onConePressed() {
	selectedPrimitive = "cone";
	drawPrimitiveRequested = true;
	ofLogNotice("Primitives3DPanel") << "Cone requested";
}

void Primitives3DPanel::onPlanePressed() {
	selectedPrimitive = "plane";
	drawPrimitiveRequested = true;
	ofLogNotice("Primitives3DPanel") << "Plane requested";
}

void Primitives3DPanel::onIcosahedronPressed() {
	selectedPrimitive = "icosahedron";
	drawPrimitiveRequested = true;
	ofLogNotice("Primitives3DPanel") << "Icosahedron requested";
}

// Callbacks pour les textures
void Primitives3DPanel::onCheckerTexturePressed() {
	textureType = "checker";
	ofLogNotice("Primitives3DPanel") << "Checker texture selected";
}

void Primitives3DPanel::onGradientTexturePressed() {
	textureType = "gradient";
	ofLogNotice("Primitives3DPanel") << "Gradient texture selected";
}

void Primitives3DPanel::onNoiseTexturePressed() {
	textureType = "noise";
	ofLogNotice("Primitives3DPanel") << "Noise texture selected";
}

void Primitives3DPanel::onLoadTexturePressed() {
	// Ouvrir un dialogue de fichier pour charger une texture
	ofFileDialogResult result = ofSystemLoadDialog("Load texture image");
	if (result.bSuccess) {
		textureType = "file:" + result.getPath();
		ofLogNotice("Primitives3DPanel") << "Custom texture loaded: " << result.getPath();
	}
}
