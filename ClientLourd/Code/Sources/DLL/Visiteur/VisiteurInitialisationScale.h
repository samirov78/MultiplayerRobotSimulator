////////////////////////////////////////////////
/// @file   VisiteurInitiatlisationScale.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEUR_INITIALISATION_SCALE_H
#define VISITEUR_INITIALISATION_SCALE_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurInitialisationScale
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud en affectant son
///		   scale relatif au scale initial au traitement
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurInitialisationScale : public VisiteurAbstrait
{
public:
	std::string Scales ; //contient ID;scalex;scaley:...
	///Constucteur 

	VisiteurInitialisationScale()
	{
		type_ = VISITEUR_DEFAULT;
	};

	///Destructeur 
	~VisiteurInitialisationScale(){};

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

// VISITEURINITIALISATIONSCALE_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
