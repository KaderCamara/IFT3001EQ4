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

void ImageManager::clear() {
    imageLoaded = false;
    importedImage.clear();
}

void ImageManager::exportImage(const std::string& path) {
    if (imageLoaded) {
        bool success = importedImage.save(path);
        if (success) {
            ofLogNotice() << "Image exported successfully to: " << path;
        }
        else {
            ofLogError() << "Failed to export image to: " << path;
        }
    }
    else {
        ofSystemAlertDialog("No image loaded to export!");
        ofLogWarning() << "Tried to export but no image loaded.";
    }
}

