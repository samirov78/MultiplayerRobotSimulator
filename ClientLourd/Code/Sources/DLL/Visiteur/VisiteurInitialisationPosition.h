////////////////////////////////////////////////
/// @file   VisiteurInitialisationPosition.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEUR_INITIALISATION_POSITION_H
#define VISITEUR_INITIALISATION_POSITION_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurInitialisationPosition
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud en affectant sa
///		   position relatives a la position initiale au traitement.
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurInitialisationPosition : public VisiteurAbstrait
{
public:

	///Constucteur 

	VisiteurInitialisationPosition()
	{
		type_ = VISITEUR_DEFAULT;
	};

	///Destructeur 
	~VisiteurInitialisationPosition(){};

	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudSegment
	virtual void visiter(NoeudSegment& noeud);
};

#endif

// VISITEURDEPLACERSELECTION_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
