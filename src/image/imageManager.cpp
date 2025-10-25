// Classe s'occupant de la gestion des images, import export etc de l'application.
#include "imageManager.h"

void ImageManager::import() {
    ofFileDialogResult result = ofSystemLoadDialog("Select an image to import");
    if (result.bSuccess) {
        importedImage.load(result.getPath());
        imageLoaded = true;
    }
}

void ImageManager::update() {
    // image update logic (if any)
}

void ImageManager::draw() {
    if (imageLoaded) {
        importedImage.draw(300, 50, importedImage.getWidth() * 0.5, importedImage.getHeight() * 0.5);
    }
}

void ImageManager::loadFromDrag(ofDragInfo dragInfo) {
	std::string path = dragInfo.files[0].string();
	ofFile file(path);

	std::string ext = ofToLower(file.getExtension());
	if (ext == "png" || ext == "jpg" || ext == "jpeg") {
		importedImage.load(path);
		imageLoaded = true;
	} else {
		std::cout << "Unsupported file type: " << ext << std::endl;
	}
}

void ImageManager::clear() {
	imageLoaded = false;
	importedImage.clear();
}
