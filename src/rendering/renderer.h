// IFT3100A25_BonjourMonde/renderer.h
// Classe responsable du rendu de l'application.  dessins etc
#pragma once
#include "ofMain.h"
#include "../objects/shapeManager.h"
#include "sceneGraph.h"

class Renderer
{
public:
  void setup();
  void draw();
  
  void setDrawingArea(const ofRectangle & area) { drawingArea = area; };
  void setCurrentShape(const std::string & shape) { currentShape = shape; }
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void draw3D();

  // MODIFICATIONS JORDAN
  void view2DMode();
  bool is3DView() const { return view3D; }
  void applyDrawingParameters(float lineW, const ofColor & stroke, const ofColor & fill, const ofColor & bg, bool useHSB, float hue, float saturation, float brightness);
  void updateShapeManagerParams(float lineW, ofColor stroke, ofColor fill);

  //mini-controller
  void save();
  void deleteShape();
  void selectingModeOn();
  void selectingModeOff();
  void view3DMode();
  ofEasyCam cam;

private:
  ofTrueTypeFont font;
  ofRectangle drawingArea;
  std::string currentShape = "none";
  bool drawing = false;
  bool selecting = false;
  ShapeManager shapeManager;
  SceneGraph sceneGraph;
  ofPoint startPoint, endPoint;
  bool shapeSelected = false;
  int shapeSelectedIndex = -1;
  bool view3D = false;
  // --- Parameters from UI ---
  float currentLineWidth = 2.0f;
  ofColor currentStrokeColor = ofColor::black;
  ofColor currentFillColor = ofColor::white;
  ofColor currentBgColor = ofColor::white;
  bool useHSBmode = false;
};
