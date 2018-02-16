////////////////////////////////////////////////
/// @file   VisiteurDeplacerSelection.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURDEPLACERSLECTION_H
#define VISITEURDEPLACERSELECTION_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeplacerSelection
/// @brief Classe qui impl�mentante le visiteur concr�t permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud en mettant 
///		   a jour sa position relative
///
///		   Les visiteurs concr�ts pourront faire diff�rents tra�tements en 
///		   fonction du type de noeud visit�, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurDeplacerSelection : public VisiteurAbstrait
{
public:

	///Constucteur 
	VisiteurDeplacerSelection(glm::dvec3 deplacement)
	{
		type_ = VISITEUR_DEFAULT;
		deplacement_ = deplacement;
	};

	///Destructeur 
	~VisiteurDeplacerSelection(){};

	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudTable
	virtual void visiter(NoeudTable& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	//virtual void visiter(NoeudLigne& noeud);
	///Algorithme de visite pour NoeudSegment
	virtual void visiter(NoeudSegment& noeud);

private:
	///dvec3 representant le deplacement.
	glm::dvec3 deplacement_;

};

#endif

// VISITEURDEPLACERSELECTION_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
