///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurInitialisationScale.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurInitialisationScale.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationScale::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation du
/// redimensionnement sur un objet poteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationScale::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserScaleEnTraitement();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationScale::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation du
/// redimensionnement sur un objet Mur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationScale::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserScaleEnTraitement();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationScale::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation du
/// redimensionnement sur un objet fleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationScale::visiter(NoeudFleche& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserScaleEnTraitement();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurInitialisationScale::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme d'initialisation du
/// redimensionnement sur un objet segment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurInitialisationScale::visiter(NoeudSegment& noeud)
{
	if (noeud.estSelectionne())
	{
		noeud.initialiserScaleEnTraitement();
	}
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
