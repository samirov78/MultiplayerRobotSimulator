////////////////////////////////////////////////
/// @file   VisiteurAbstrait.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#pragma once

//#include "Arbre\Noeuds\NoeudAraignee.h"
#include <iostream>
class NoeudAbstrait;
class NoeudComposite;
class NoeudAraignee;
class NoeudTable;
class NoeudPoteau;
class NoeudMur;
class NoeudSegment;
class NoeudLigne;
class NoeudFleche;

/// La chaîne représentant le type du Visiteur.
static const std::string VISITEUR_DUPLIQUER{ "visiteur dupliquer" };
static const std::string VISITEUR_DEFAULT{ "visiteur default" };


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
/// @brief Classe de base du patron visiteur qui permet de rajouter des 
///		   des fonctionnalités aux noeuds présents dans l'arbre de rendu		
///        sans avoir à modifier la hiérarchie elle-même. Donc on parcourt 
///        modifie les éléments présents dans la l'arbre de rendu sans 
///        avoir à modifier leurs classes de base. Il convient d'implémenter 
///		   différents visiteurs concrêts qui surchargeront la méthode visiter()
///		   autant de fois qu'il y a d'objets à manipuler. 
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurAbstrait
{
public:
	//Constucteur 
	VisiteurAbstrait(){};

	//Destructeur 
	virtual ~VisiteurAbstrait() {};

	/// surcharge de la méthode virtuelle pure visiter() autant de fois qu'il y aura de noeuds spécifiques à visiter
	//virtual void visiter(NoeudAbstrait & noeud) {}
	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud){};
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud){};
	///Algorithme de visite pour NoeudTable
	virtual void visiter(NoeudTable& noeud){};
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud){};
	///Algorithme de visite pour NoeudLigne
	virtual void visiter(NoeudLigne& noeud){};
	///Algorithme de visite pour NoeudSegment
	virtual void visiter(NoeudSegment& noeud){};

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const { return type_; };

protected:
	/// Type de visiteur.
	std::string  type_;

};



// VISITEURABSTRAIT_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
