// Classe s'occupant de la gestion des images, import export etc de l'application.
#pragma once

#include "ofMain.h"

class ImageManager {
	public:

		void import();
		void update();
		void clear();
		void loadFromDrag(ofDragInfo dragInfo);
		bool isImageLoaded() const { return imageLoaded; }
		const ofImage & getImage() const { return importedImage; }

	private:
		ofImage importedImage;
		bool imageLoaded = false;
};


