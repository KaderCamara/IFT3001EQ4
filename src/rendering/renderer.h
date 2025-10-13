// IFT3100A25_BonjourMonde/renderer.h
// Classe responsable du rendu de l'application.  dessins etc

#include "ofMain.h"
#include "../ui/uiWindow.h"
#include "../objects/shapeManager.h"

class Renderer
{
public:
  void setup();
  void draw();
  void setDrawingArea(const ofRectangle & area) { drawingArea = area; };
  void setCurrentShape(const std::string & shape) { currentShape = shape; }
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);

private:
  ofTrueTypeFont font;
  ofRectangle drawingArea;
  std::string currentShape = "none";
  bool drawing = false;
  ShapeManager shapeManager;
  ofPoint startPoint, endPoint;
};
