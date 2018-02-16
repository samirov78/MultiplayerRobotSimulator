////////////////////////////////////////////////
/// @file   VisiteurDeterminerCentreSelection.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURDETERMINERCENTRESLECTION_H
#define VISITEURDETERMINERCENTRESLECTION_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeterminerCentreSelection
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud afin de determiner
///		   les coordonnees du centre du noeud.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurDeterminerCentreSelection : public VisiteurAbstrait
{
public:

	///Constucteur 

	VisiteurDeterminerCentreSelection(bool minMax)
	{
		minMax_ = minMax;
		type_ = VISITEUR_DEFAULT;
	};

	///Destructeur 
	~VisiteurDeterminerCentreSelection(){};

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
	///Methode permettant la mise a jour du centre d'un objet selectionne.
	void mettreAJourCentreSelection(NoeudAbstrait* noeud);
	///Methode permettant l'obtention du centre d'un objet selectionne.
	glm::dvec3 obtenirCentreSelection() { return centreSelection_; };


private:
	///Centre d'une selection.
	glm::dvec3 centreSelection_{ 0.0 };
	///Parametres de selection.
	double xMin_{ 50.0 };
	double yMin_{ 25.0 };
	double xMax_{ -50.0 };
	double yMax_{ -25.0 };
	bool minMax_{ true };
	///Nombre de noeud selectionnes.
	int nbNoeudsSelectionnes_{ 0 };
};

#endif

// VISITEURDETERMINERCENTRESLECTION_H