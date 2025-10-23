// Classe s'occupant de la gestion des images, import export etc de l'application.
#pragma once

#include "ofMain.h"

class ImageManager {
	public:

		void import();
		void update();
		void draw();
		void clear();
		void loadFromDrag(ofDragInfo dragInfo);
		void exportImage(const std::string & path);

	private:
		ofImage importedImage;
		bool imageLoaded = false;
};


