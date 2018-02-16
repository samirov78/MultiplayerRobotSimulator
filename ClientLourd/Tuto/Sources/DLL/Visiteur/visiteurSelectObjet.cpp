///////////////////////////////////////////////////////////////////////////////
/// @file visiteurSelectObjet.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurSelectObjet.h"
#include <iostream>
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelectObjet::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudPoteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void  VisiteurSelectObjet::visiter(NoeudPoteau& noeud)
{
	if (initialiserVisite_)
	{
		noeud.assignerEstVisite(false);
	}
	else
	{
		if (noeud.estSelectionnable() && noeud.verifierSelection(couleurObjet_)) // si le noeud est touche
		{
			if (selectionunique_)
			{
				noeud.obtenirParent()->deselectionnerTout();

				//noeud.obtenirParent()->deselectIfSameColor(noeud);
				noeud.assignerSelection(true);

				selectionexiste_ = true;
			}
			else
				noeud.inverserSelection();
		}
	}
	//noeud.setCustomSelectColor(230, 0, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectObjet::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudMur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelectObjet::visiter(NoeudMur& noeud)
{
	if (initialiserVisite_)
	{
		noeud.assignerEstVisite(false);
	}
	else
	{
		if (noeud.estSelectionnable() && noeud.verifierSelection(couleurObjet_)) // si le noeud est touche
		{
			if (selectionunique_)
			{
				noeud.obtenirParent()->deselectionnerTout();
				noeud.assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud.inverserSelection();
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectObjet::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudFleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelectObjet::visiter(NoeudFleche& noeud)
{
	if (initialiserVisite_)
	{
		noeud.assignerEstVisite(false);
	}
	else
	{
		if (noeud.estSelectionnable() && noeud.verifierSelection(couleurObjet_)) // si le noeud est touche
		{
			if (selectionunique_)
			{
				noeud.obtenirParent()->deselectionnerTout();
				noeud.assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud.inverserSelection();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectObjet::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudSegment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelectObjet::visiter(NoeudSegment& noeud)
{
	if (initialiserVisite_)
	{
		noeud.assignerEstVisite(false);
	}
	else
	{
		if (noeud.estSelectionnable() && !noeud.estVisite() && noeud.verifierSelection(couleurObjet_)) // si le noeud est touche
		{
			//std::cout << "couleurSegment : (" << (int)noeud.couleurSegment_[0] << ", " << (int)noeud.couleurSegment_[1] << ", " << (int)noeud.couleurSegment_[2] << ")" << std::endl;
			if (selectionunique_)
			{
				noeud.obtenirParent()->obtenirParent()->deselectionnerTout();
				noeud.obtenirParent()->selectionnerTout();
				selectionexiste_ = true;
			}
			else
			{
				if (noeud.obtenirParent()->selectionExiste())
				{
					noeud.obtenirParent()->deselectionnerTout();
				}
				else
				{
					noeud.obtenirParent()->selectionnerTout();
					selectionexiste_ = true;
				}
			}
			noeud.obtenirParent()->assignerEstVisite(true);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectObjet::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudTable.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelectObjet::visiter(NoeudTable& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectObjet::visiter(NoeudLigne& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudLigne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelectObjet::visiter(NoeudLigne& noeud)
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
