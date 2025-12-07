#include "cameraPanel.h"

CameraPanel::CameraPanel() {
}

CameraPanel::~CameraPanel() {
    detachListeners();
}

void CameraPanel::setup() {
    cameraPanel.setup("Camera Management");
    // make panel non-draggable so it's fixed in the UI
    cameraPanel.setDraggable(false);
    // remove visible name/title so it can sit flush against window edge
    cameraPanel.setName("");
    // remove border/background so it blends with the app background
    cameraPanel.setBorderColor(ofColor(0,0));
    cameraPanel.setBackgroundColor(ofColor(0,0,0,0));

    // Top: active camera display and navigation
    activeCameraName.set("Camera0");
    lblActiveCamera.setup(activeCameraName);
    btnPrevCamera.setup("Prev");
    btnNextCamera.setup("Next");
    btnAddCamera.setup("+ Add Camera");
    btnDeleteCamera.setup("Delete Camera");

    // Projection
    lblProjection.setup("-- Projection --", "");
    togglePerspective.setup("Perspective", true);
    fovSlider.setup("FOV", 60.0f, 1.0f, 179.0f);
    toggleOrthographic.setup("Orthographic", false);
    orthoScaleSlider.setup("Scale", 1.0f, 0.01f, 10.0f);

    nearPlaneSlider.setup("Near Plane", 0.1f, 0.001f, 1000.0f);
    farPlaneSlider.setup("Far Plane", 1000.0f, 1.0f, 10000.0f);

    // Transform
    lblTransform.setup("-- Transform --", "");
    posX.setup("Pos X", 0.0f, -10000.0f, 10000.0f);
    posY.setup("Pos Y", 0.0f, -10000.0f, 10000.0f);
    posZ.setup("Pos Z", 0.0f, -10000.0f, 10000.0f);
    rotPitch.setup("Pitch", 0.0f, -360.0f, 360.0f);
    rotYaw.setup("Yaw", 0.0f, -360.0f, 360.0f);
    rotRoll.setup("Roll", 0.0f, -360.0f, 360.0f);

    // Navigation
    lblNavigation.setup("-- Navigation --", "");
    toggleOrbitMode.setup("Orbit mode", true);
    mouseSensitivitySlider.setup("Mouse sensitivity", 1.0f, 0.01f, 10.0f);
    zoomSpeedSlider.setup("Zoom speed", 1.0f, 0.01f, 10.0f);

    // Display
    lblDisplay.setup("-- Display --", "");
    toggleGrid.setup("Grille", true);
    toggleAxes.setup("Axes", true);
    toggleWireframe.setup("Wireframe", false);
    toggleBoundingBoxes.setup("Bounding Boxes", false);

    // Shortcuts
    btnFocusSelection.setup("Focus on Selection");
    btnResetCamera.setup("Reset Camera");

    // Add to gui (add by pointer to avoid double-setup)
    cameraPanel.add(&lblActiveCamera);
    cameraPanel.add(&btnPrevCamera);
    cameraPanel.add(&btnNextCamera);
    cameraPanel.add(&btnAddCamera);
    cameraPanel.add(&btnDeleteCamera);

    cameraPanel.add(&lblProjection);
    cameraPanel.add(&togglePerspective);
    cameraPanel.add(&fovSlider);
    cameraPanel.add(&toggleOrthographic);
    cameraPanel.add(&orthoScaleSlider);

    cameraPanel.add(&nearPlaneSlider);
    cameraPanel.add(&farPlaneSlider);

    cameraPanel.add(&lblTransform);
    cameraPanel.add(&posX);
    cameraPanel.add(&posY);
    cameraPanel.add(&posZ);
    cameraPanel.add(&rotPitch);
    cameraPanel.add(&rotYaw);
    cameraPanel.add(&rotRoll);

    cameraPanel.add(&lblNavigation);
    cameraPanel.add(&toggleOrbitMode);
    cameraPanel.add(&mouseSensitivitySlider);
    cameraPanel.add(&zoomSpeedSlider);

    cameraPanel.add(&lblDisplay);
    cameraPanel.add(&toggleGrid);
    cameraPanel.add(&toggleAxes);
    cameraPanel.add(&toggleWireframe);
    cameraPanel.add(&toggleBoundingBoxes);

    cameraPanel.add(&btnFocusSelection);
    cameraPanel.add(&btnResetCamera);

    attachListeners();
}

void CameraPanel::setPosition(float x, float y) {
    enforcedX = x;
    enforcedY = y;
    cameraPanel.setPosition(enforcedX, enforcedY);
}

void CameraPanel::setWidth(float w) {
    enforcedWidth = w;
    cameraPanel.setWidthElements(enforcedWidth);
}

void CameraPanel::update() {
    // nothing for now - in a full integration you might pull camera transform etc.
}

void CameraPanel::draw() {
    // re-apply enforced layout each frame to ensure fixed placement
    cameraPanel.setPosition(enforcedX, enforcedY);
    cameraPanel.setWidthElements(enforcedWidth);

    if (visible) cameraPanel.draw();
}

void CameraPanel::attachListeners() {
    btnAddCamera.addListener(this, &CameraPanel::onBtnAddCamera);
    btnDeleteCamera.addListener(this, &CameraPanel::onBtnDeleteCamera);
    btnPrevCamera.addListener(this, &CameraPanel::onBtnPrevCamera);
    btnNextCamera.addListener(this, &CameraPanel::onBtnNextCamera);
    togglePerspective.addListener(this, &CameraPanel::onTogglePerspectiveChanged);
    toggleOrthographic.addListener(this, &CameraPanel::onToggleOrthoChanged);
    btnFocusSelection.addListener(this, &CameraPanel::onBtnFocusSelection);
    btnResetCamera.addListener(this, &CameraPanel::onBtnResetCamera);
    activeCameraIndex.addListener(this, &CameraPanel::onActiveCameraIndexChanged);
}

void CameraPanel::detachListeners() {
    btnAddCamera.removeListener(this, &CameraPanel::onBtnAddCamera);
    btnDeleteCamera.removeListener(this, &CameraPanel::onBtnDeleteCamera);
    btnPrevCamera.removeListener(this, &CameraPanel::onBtnPrevCamera);
    btnNextCamera.removeListener(this, &CameraPanel::onBtnNextCamera);
    togglePerspective.removeListener(this, &CameraPanel::onTogglePerspectiveChanged);
    toggleOrthographic.removeListener(this, &CameraPanel::onToggleOrthoChanged);
    btnFocusSelection.removeListener(this, &CameraPanel::onBtnFocusSelection);
    btnResetCamera.removeListener(this, &CameraPanel::onBtnResetCamera);
    activeCameraIndex.removeListener(this, &CameraPanel::onActiveCameraIndexChanged);
}

void CameraPanel::setCameraNames(const std::vector<std::string>& names) {
    cameraNames = names;
    if (cameraNames.empty()) {
        activeCameraName.set("none");
        activeCameraIndex = 0;
    } else {
        refreshActiveCameraLabel();
    }
}

void CameraPanel::setActiveCameraIndex(int idx) {
    if (idx < 0) idx = 0;
    if (!cameraNames.empty()) {
        if (idx >= (int)cameraNames.size()) idx = cameraNames.size()-1;
    }
    activeCameraIndex = idx;
}

int CameraPanel::getActiveCameraIndex() const {
    return activeCameraIndex.get();
}

void CameraPanel::show() { visible = true; }
void CameraPanel::hide() { visible = false; }
void CameraPanel::toggle() { visible = !visible; }
bool CameraPanel::isVisible() const { return visible; }

// --- Handlers ---
void CameraPanel::onBtnAddCamera() {
    if (onAddCamera) onAddCamera();
}

void CameraPanel::onBtnDeleteCamera() {
    int idx = activeCameraIndex.get();
    if (onDeleteCamera) onDeleteCamera(idx);
}

void CameraPanel::onBtnPrevCamera() {
    int idx = activeCameraIndex.get();
    if (idx > 0) activeCameraIndex = idx - 1;
}

void CameraPanel::onBtnNextCamera() {
    int idx = activeCameraIndex.get();
    if (!cameraNames.empty() && idx < (int)cameraNames.size()-1) activeCameraIndex = idx + 1;
}

void CameraPanel::onActiveCameraIndexChanged(int & newIndex) {
    refreshActiveCameraLabel();
    if (onActiveCameraChanged) onActiveCameraChanged(newIndex);
}

void CameraPanel::onTogglePerspectiveChanged(bool & val) {
    if (val) {
        toggleOrthographic = false;
    }
    if (onProjectionChanged) onProjectionChanged();
}

void CameraPanel::onToggleOrthoChanged(bool & val) {
    if (val) {
        togglePerspective = false;
    }
    if (onProjectionChanged) onProjectionChanged();
}

void CameraPanel::onBtnFocusSelection() {
    if (onFocusSelection) onFocusSelection();
}

void CameraPanel::onBtnResetCamera() {
    if (onResetCamera) onResetCamera();
}

std::string CameraPanel::getActiveCameraLabel() const {
    if (cameraNames.empty()) return "none";
    int idx = activeCameraIndex.get();
    if (idx < 0) idx = 0;
    if (idx >= (int)cameraNames.size()) idx = cameraNames.size()-1;
    return cameraNames[idx];
}

void CameraPanel::refreshActiveCameraLabel() {
    std::string label = getActiveCameraLabel();
    // update parameter used by ofxLabel
    activeCameraName.set(label);
}
