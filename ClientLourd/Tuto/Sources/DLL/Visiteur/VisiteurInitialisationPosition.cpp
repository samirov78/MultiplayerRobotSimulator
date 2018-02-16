///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurInitialisationPosition.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurInitialisationPosition.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationPosition::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation à un 
/// objet sélectionné de la classe NoeudPoteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationPosition::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserPositionEnTraitement();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationPosition::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation à un 
/// objet sélectionné de la classe NoeudMur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationPosition::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserPositionEnTraitement();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationPosition::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation à un 
/// objet sélectionné de la classe NoeudFleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationPosition::visiter(NoeudFleche& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserPositionEnTraitement();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationPosition::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation à un 
/// objet sélectionné de la classe NoeudSegment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationPosition::visiter(NoeudSegment& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserPositionEnTraitement();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
