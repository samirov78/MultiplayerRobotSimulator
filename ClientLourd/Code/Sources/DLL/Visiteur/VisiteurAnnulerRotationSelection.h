////////////////////////////////////////////////
/// @file   VisiteurAnnulerRotationSelection.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#pragma once

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAnnulerRotationSelection
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud afin
///		   d'annuler une rotation.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurAnnulerRotationSelection : public VisiteurAbstrait
{
public:

	//Constucteur 
	VisiteurAnnulerRotationSelection() {} ;

	///Destructeur 
	~VisiteurAnnulerRotationSelection(){};



	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour un NoeudSegment
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudLigne
	virtual void visiter(NoeudLigne& noeud);
	//void setCentre(glm::dvec3 centre){ centre_ = centre; };


	//bool obtenirselectionExiste() { return selectionexiste_; };


private:

	//double rotation_;
	//glm::dvec3 centre_;
	//bool unObjetHorsTable{ false };

};
