////////////////////////////////////////////////
/// @file   VisiteSelectElastique.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURSELECTIONELASTIQUE_H
#define VISITEURSELECTIONELASTIQUE_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <vector>
#include "Utilitaire.h"
#include "Vue.h"
#include "Plan3D.h"

namespace vue {
	class Vue;
}

namespace math {
	class Plan3D;
}

///////////////////////////////////////////////////////////////////////////
/// @class visiteurSelectElastique
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud afin de
///		   permettre la selection par rectangle elastqiue
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
#include <iostream>
class visiteurSelectElastique : public VisiteurAbstrait
{
public:

	///Constucteur 
	visiteurSelectElastique(int xDebut, int xFin, int yDebut, int yFin, const bool& estEnfonce, vue::Vue* vue)
	{
		type_ = VISITEUR_DEFAULT;
		xDebut_ = xDebut;
		xFin_ = xFin;
		yDebut_ = yDebut;
		yFin_ = yFin;
		vue_ = vue;
		selectionCTRL_ = estEnfonce;
	};

	
	///Destructeur 
	~visiteurSelectElastique(){};

	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudTable
	virtual void visiter(NoeudTable& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudSegment
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudLigne
	virtual void visiter(NoeudLigne& noeud);


	//bool obtenirselectionExiste() { return selectionexiste_; };
private:
	
	///Selection avec le click CTRL ou non.
	bool selectionCTRL_;
	int xDebut_;
	int xFin_;
	int yDebut_;
	int yFin_;
	vue::Vue* vue_;

};

#endif
//VISITEURSELECTIONELASTIQUE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
