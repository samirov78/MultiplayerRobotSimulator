////////////////////////////////////////////////
/// @file   VisiteurVerifierDeplacementDuplication.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURVERIFIERDEPLACEMENTDUPLICATION_H
#define VISITEURVERIFIERDEPLACEMENTDUPLICATION_H

#include "VisiteurAbstrait.h"
#include "utilitaire.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurVerifierDeplacementDuplication
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   la duplication d'un objet.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurVerifierDeplacementDuplication : public VisiteurAbstrait
{
public:

	///Constucteur 

	VisiteurVerifierDeplacementDuplication(glm::dvec3 & deplacement)
	{
		type_ = VISITEUR_DEFAULT;
		deplacement_ = deplacement;
	};

	///Destructeur 
	~VisiteurVerifierDeplacementDuplication(){};

	///Surcharge de la méthode visiter de la classe VisiteurAbstrait 
	virtual void visiter(NoeudPoteau& noeud);
	virtual void visiter(NoeudMur& noeud);
	virtual void visiter(NoeudTable& noeud);
	virtual void visiter(NoeudFleche& noeud);
	virtual void visiter(NoeudSegment& noeud);
	virtual void visiter(NoeudLigne& noeud);
	///Verifie si la duplication est valide ou non.
	bool estValide() { return duplicationValide_; };


private:
	///Verifie si le point est valide ou non.
	bool verifierPoint(glm::dvec3 point);
	///Deplacement du point.
	glm::dvec3 deplacement_;
	///Duplication valide ou non.
	bool duplicationValide_{ true };
};

#endif

// VISITEURVERIFIERDEPLACEMENTDUPLICATION_H