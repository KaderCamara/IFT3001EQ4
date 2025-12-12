#pragma once
#include "../../objects/CurveAnimator.h"
#include "ofMain.h"

class AnimatedObjectRenderer {
public:
	AnimatedObjectRenderer() = default;

	void render(const AnimatedObject & obj) const;
	void setShowTrail(bool show) { showTrail = show; }
	void clearTrail() const { trail.clear(); }

private:
	bool showTrail = true;
	mutable std::vector<glm::vec2> trail;
	static constexpr int MAX_TRAIL = 100;

	void renderTriangle(const AnimatedObject & obj) const;
	void renderTrail(const AnimatedObject & obj) const;
};
