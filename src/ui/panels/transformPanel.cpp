// TransformPanel.cpp
// Implémentation du panel de transformations
#include "TransformPanel.h"

TransformPanel::TransformPanel() {
}

void TransformPanel::setup() {
	panel.setup("Transformations");
	panel.add(translateX.set("Translate X", 0.0, -2000, 2000));
	panel.add(translateY.set("Translate Y", 0.0, -2000, 2000));
	panel.add(rotation.set("Rotation", 0.0, -720, 720));
	panel.add(scaleFactor.set("Scale", 1.0, 0.1, 5.0));

	ofLogNotice("TransformPanel") << "Setup complete";
}

void TransformPanel::draw(float x, float y, float width, float windowWidth, float windowHeight) {
	if (!isVisible) return;

	// Ajuster dynamiquement les limites en fonction de la taille de la fenêtre
	translateX.setMin(-windowWidth / 2);
	translateX.setMax(windowWidth / 2);
	translateY.setMin(-windowHeight / 2);
	translateY.setMax(windowHeight / 2);

	panel.setPosition(x, y);
	panel.setSize(width, 180);
	panel.draw();
}
