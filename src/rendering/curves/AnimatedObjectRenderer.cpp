#include "AnimatedObjectRenderer.h"

void AnimatedObjectRenderer::render(const AnimatedObject & obj) const {
	renderTriangle(obj);

	if (showTrail) {
		renderTrail(obj);
	}
}

void AnimatedObjectRenderer::renderTriangle(const AnimatedObject & obj) const {
	ofPushMatrix();
	ofTranslate(obj.position);
	ofRotateDeg(obj.rotation);
	ofScale(obj.scale);

	// Triangle pointant dans la direction du mouvement
	ofPushStyle();
	ofSetColor(obj.color);
	ofFill();
	ofBeginShape();
	ofVertex(15, 0); // Pointe avant
	ofVertex(-10, 8); // Base haut
	ofVertex(-10, -8); // Base bas
	ofEndShape(true);

	// Contour
	ofNoFill();
	ofSetColor(255);
	ofSetLineWidth(2);
	ofBeginShape();
	ofVertex(15, 0);
	ofVertex(-10, 8);
	ofVertex(-10, -8);
	ofEndShape(true);
	ofPopStyle();

	ofPopMatrix();
}

void AnimatedObjectRenderer::renderTrail(const AnimatedObject & obj) const {
	trail.push_back(obj.position);
	if (trail.size() > MAX_TRAIL) {
		trail.erase(trail.begin());
	}

	if (trail.size() < 2) return;

	ofPushStyle();
	ofSetLineWidth(3);

	for (size_t i = 1; i < trail.size(); i++) {
		float alpha = 255.0f * (float)i / (float)trail.size();
		ofSetColor(obj.color, alpha * 0.6f);
		ofDrawLine(trail[i - 1], trail[i]);
	}

	ofPopStyle();
}
