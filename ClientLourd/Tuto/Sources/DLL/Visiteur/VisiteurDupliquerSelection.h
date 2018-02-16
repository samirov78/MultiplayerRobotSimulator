////////////////////////////////////////////////
/// @file   VisiteurDupliquerSelection.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURDUPLIQUERSLECTION_H
#define VISITEURDUPLIQUERSELECTION_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDupliquerSelection
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   de dupliquer un ou plusieurs objets selectionnes.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurDupliquerSelection : public VisiteurAbstrait
{
public:

	///Constucteur 

	VisiteurDupliquerSelection(glm::dvec3 & deplacement, bool estFantome)
	{
		type_ = VISITEUR_DUPLIQUER;
		deplacement_ = deplacement;
		estFantome_ = estFantome;
		compteurDupliques = 1;
		srand(time(0));
	};

	///Destructeur 
	~VisiteurDupliquerSelection(){};

	///Algorithme de visite pour NoeudPoteau.
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur.
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudTable.
	virtual void visiter(NoeudTable& noeud);
	///Algorithme de visite pour NoeudFleche.
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudSegment.
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudLigne.
	virtual void visiter(NoeudLigne& noeud);



private:
	///Deplacement du noeud.
	glm::dvec3 deplacement_;
	///Dernier noeud ligne ajouter.
	NoeudAbstrait* dernierNoeudLigneAjoute_{ nullptr };
	///Noeud afficher ou non.
	bool estFantome_;
	int compteurDupliques;
};

#endif

// VISITEURDUPLIQUERSELECTION_H