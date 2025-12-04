// SceneGraph.h
// Structure de données de la scène (MODEL pur)
// ✅ Contient uniquement les données
// ✅ Opérations CRUD basiques
// ❌ AUCUNE logique complexe (sélection, hit-testing, etc.)

#pragma once

#include "../objects/shape.h"
#include "ofMain.h"
#include <vector>

/**
 * @class SceneGraph
 * @brief Structure de données représentant la scène (MODEL pur)
 * 
 * Responsabilités (MODEL UNIQUEMENT) :
 * - Stocker les formes
 * - Stocker les indices de sélection
 * - Opérations CRUD basiques (add, remove, get, clear)
 * - AUCUNE logique métier complexe
 * - AUCUN hit-testing (délégué au Controller)
 * - AUCUNE transformation (délégué au Controller)
 * 
 * REFACTORISATION MVC :
 * - AVANT : Mélangeait données + logique (selectShapeAt, updateSelectedTransform) ❌
 * - APRÈS : Données pures uniquement ✅
 * - La logique est déléguée au SceneController
 */
class SceneGraph {
public:
	SceneGraph() = default;
	~SceneGraph() = default;

	// ========== DONNÉES PUBLIQUES (MODEL) ==========
	// Note : Dans un MODEL pur, les données peuvent être publiques
	// ou accessibles via getters simples
	std::vector<Shape> shapes;
	std::vector<int> selectedIndices;

	// ========== OPÉRATIONS CRUD BASIQUES ==========

	/**
	 * @brief Ajoute une forme à la scène
	 */
	void addShape(const Shape & shape);

	/**
	 * @brief Supprime une forme par index
	 */
	void removeShape(int index);

	/**
	 * @brief Récupère une forme par index
	 * @return Pointeur vers la forme (nullptr si index invalide)
	 */
	Shape * getShape(int index);
	const Shape * getShape(int index) const;

	/**
	 * @brief Efface toutes les formes et sélections
	 */
	void clear();

	/**
	 * @brief Supprime toutes les formes sélectionnées
	 */
	void removeSelectedShapes();

	/**
	 * @brief Désélectionne toutes les formes
	 */
	void deselectAll();

	/**
	 * @brief Récupère toutes les formes
	 */
	std::vector<Shape> & getAllShapes();
	const std::vector<Shape> & getAllShapes() const;

	/**
	 * @brief Remplace toutes les formes par un nouveau vecteur
	 */
	void setShapes(const std::vector<Shape> & newShapes);

	/**
	 * @brief Vérifie si un index est valide
	 */
	bool isValidIndex(int index) const;

	/**
	 * @brief Récupère le nombre de formes
	 */
	size_t getShapeCount() const { return shapes.size(); }

	/**
	 * @brief Vérifie si une forme est sélectionnée
	 */
	bool isSelected(int index) const;
};
