#pragma once
#include "BezierCurve.h"
#include "ofMain.h"

struct AnimatedObject {
	glm::vec2 position;
	float rotation;
	float scale;
	ofColor color;
};

class CurveAnimator {
public:
	CurveAnimator() = default;

	void setup(const BezierCurve & curve, float duration);
	void update(float deltaTime);
	void reset();

	AnimatedObject getAnimatedObject() const { return currentObject; }
	bool isPlaying() const { return playing; }
	bool isFinished() const { return currentTime >= duration; }
	float getProgress() const { return duration > 0 ? currentTime / duration : 0; }

	void play() { playing = true; }
	void pause() { playing = false; }
	void setLoop(bool loop) { looping = loop; }
	void setDuration(float dur) { duration = dur; }

private:
	BezierCurve curve;
	AnimatedObject currentObject;

	float currentTime = 0.0f;
	float duration = 3.0f;
	bool playing = false;
	bool looping = true;

	void updateObjectFromCurve(float t);
	glm::vec2 getTangent(float t);
	glm::vec2 getTangent(int index, const std::vector<glm::vec2> & points) const; // Surcharge helper
};
