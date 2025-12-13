// Classe s'occupant de la gestion des images, import export etc de l'application.
#include "imageManager.h"

void ImageManager::import() {
    ofFileDialogResult result = ofSystemLoadDialog("Select an image to import");
    if (result.bSuccess) {
		loadFromPath(result.getPath());
        imageLoaded = true;
    }
}

bool ImageManager::loadFromPath(const std::string & path) {
	if (importedImage.load(path)) {
		imageLoaded = true;
		ofLogNotice("ImageManager") << "Image loaded: " << path;
		return true;
	} else {
		imageLoaded = false;
		ofLogError("ImageManager") << "Failed to load image: " << path;
		return false;
	}
}

void ImageManager::update() {
    // image update logic (if any)
}

void ImageManager::loadFromDrag(ofDragInfo dragInfo) {
	if (dragInfo.files.empty()) return;

	std::string path = dragInfo.files[0].string();
	ofFile file(path);
	std::string ext = ofToLower(file.getExtension());

	if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "bmp" || ext == "tif" || ext == "tiff") {
		loadFromPath(path);
	} else {
		ofLogError("ImageManager") << "Unsupported file type: " << ext;
	}
}

void ImageManager::clear() {
	imageLoaded = false;
	importedImage.clear();
}
