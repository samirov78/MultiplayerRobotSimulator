////////////////////////////////////////////////
/// @file   visiteurRotationUnObjet.h
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
/// @class visiteurRotationUnObjet
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter le noeud selectionne en mettant 
///		   a jour son orientation relative
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class visiteurRotationUnObjet : public VisiteurAbstrait
{
public:

	///Constucteur 
	visiteurRotationUnObjet(double rotation, glm::dvec3 centre)
	{
		type_ = VISITEUR_DEFAULT;
		rotation_ = rotation;
		centre_ = centre;

	};

	///Destructeur 
	~visiteurRotationUnObjet(){};



	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudLigne& noeud);
	///Methode permettant l'assignation de la coordonnee de centre a un objet.
	void setCentre(glm::dvec3 centre){ centre_ = centre; };


	//bool obtenirselectionExiste() { return selectionexiste_; };


private:
	///Angle de rotation.
	double rotation_;
	///Centre.
	glm::dvec3 centre_;
	//bool unObjetHorsTable{ false };

};
