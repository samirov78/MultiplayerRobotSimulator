////////////////////////////////////////////////
/// @file   VisiteurVersXML.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURVERSXML_H
#define VISITEURVERSXML_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include "../../Commun/Externe/tinyxml2/include/tinyxml2.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurVersXML
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud en remplissat
///		   chaque elementXML et en l'ajoutant au root du document XML 
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car il possede des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
#include <iostream>
class VisiteurVersXML : public VisiteurAbstrait
{
public:

	///Constucteur 
	VisiteurVersXML(tinyxml2::XMLDocument* documentXML, tinyxml2::XMLElement* elementXML)
	{
		type_ = VISITEUR_DEFAULT;
		elementXML_ = elementXML;
		documentXML_ = documentXML;
	};
	 
	///Destructeur 
	~VisiteurVersXML(){};

	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudTable
	virtual void visiter(NoeudTable& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudLigne
	virtual void visiter(NoeudLigne& noeud);

private:
	///Element dans le xml.
	tinyxml2::XMLElement* elementXML_;
	///Document xml en question.
	tinyxml2::XMLDocument* documentXML_;

};

#endif

// VISITEURVERSXML_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
