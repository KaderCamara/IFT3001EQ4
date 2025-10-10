// IFT3100A25_BonjourMonde/application.h
// Classe principale de l'application.
//notre controller basically

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "../uiWindow.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  UIWindow uiWindow;

  void setup();

  void draw();

  void update();

  void exit();
};
