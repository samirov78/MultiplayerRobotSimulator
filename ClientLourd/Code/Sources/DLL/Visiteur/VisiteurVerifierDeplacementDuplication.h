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
/// @brief Classe qui impl�mentante le visiteur concr�t permettant de 
///		   la duplication d'un objet.
///
///		   Les visiteurs concr�ts pourront faire diff�rents tra�tements en 
///		   fonction du type de noeud visit�, car ils possedent des attributs differents. 
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

	///Surcharge de la m�thode visiter de la classe VisiteurAbstrait 
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