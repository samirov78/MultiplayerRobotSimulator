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

/// La cha�ne repr�sentant le type du Visiteur.
static const std::string VISITEUR_DUPLIQUER{ "visiteur dupliquer" };
static const std::string VISITEUR_DEFAULT{ "visiteur default" };


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
/// @brief Classe de base du patron visiteur qui permet de rajouter des 
///		   des fonctionnalit�s aux noeuds pr�sents dans l'arbre de rendu		
///        sans avoir � modifier la hi�rarchie elle-m�me. Donc on parcourt 
///        modifie les �l�ments pr�sents dans la l'arbre de rendu sans 
///        avoir � modifier leurs classes de base. Il convient d'impl�menter 
///		   diff�rents visiteurs concr�ts qui surchargeront la m�thode visiter()
///		   autant de fois qu'il y a d'objets � manipuler. 
///
///		   Les visiteurs concr�ts pourront faire diff�rents tra�tements en 
///		   fonction du type de noeud visit�. 
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

	/// surcharge de la m�thode virtuelle pure visiter() autant de fois qu'il y aura de noeuds sp�cifiques � visiter
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
