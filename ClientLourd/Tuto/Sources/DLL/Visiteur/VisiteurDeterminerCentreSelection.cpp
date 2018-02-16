///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeterminerCentreSelection.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurDeterminerCentreSelection.h"
#include "FacadeModele.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeterminerCentreSelection::mettreAJourCentreSelection(NoeudAbstrait* noeud)
///
/// Cette methode permet de calculer le centre des noeuds selectionnes, pour
/// la diplucation, en parcourant l'arbre de rendu.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::mettreAJourCentreSelection(NoeudAbstrait* noeud)
{
	glm::dvec3 centre /*= noeud->obtenirCentre()*/;
	if (noeud->obtenirType() == "ligne")
	{
		glm::dvec3 centreLigne{ 0.0 };
		int nbSegments = noeud->obtenirNombreEnfants();
		if (nbSegments >= 1)
		{
			for (int i = 0; i < nbSegments; i++)
			{
				centreLigne += noeud->obtenirEnfants()->at(i)->obtenirPositionRelative();
			}
			centreLigne.x /= nbSegments;
			centreLigne.y /= nbSegments;
		}
		centre = centreLigne;
	}
	else
	{
		centre = noeud->obtenirPositionRelative();
	}
	if (minMax_)
	{
		if (centre.x < xMin_)
			xMin_ = centre.x;
		if (centre.x > xMax_)
			xMax_ = centre.x;
		if (centre.y < yMin_)
			yMin_ = centre.y;
		if (centre.y > yMax_)
			yMax_ = centre.y;
		centreSelection_.x = (xMin_ + xMax_) / 2.0;
		centreSelection_.y = (yMin_ + yMax_) / 2.0;
	}
	else
	{
		centreSelection_.x = (nbNoeudsSelectionnes_ * centreSelection_.x + centre.x) / (nbNoeudsSelectionnes_ + 1);
		centreSelection_.y = (nbNoeudsSelectionnes_ * centreSelection_.y + centre.y) / (nbNoeudsSelectionnes_ + 1);
		nbNoeudsSelectionnes_++;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeterminerCentreSelection::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de calcul du centre de 
/// selection d'un poteau selectionne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		mettreAJourCentreSelection(&noeud);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeterminerCentreSelection::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de calcul du centre de 
/// selection d'un mur selectionne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne())
	{
		mettreAJourCentreSelection(&noeud);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeterminerCentreSelection::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de calcul du centre de 
/// selection d'une table selectionne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::visiter(NoeudTable& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeterminerCentreSelection::visiter(NoeudLigne& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de calcul du centre de 
/// selection d'une ligne selectionne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::visiter(NoeudLigne& noeud)
{
	if (noeud.estSelectionne())
	{
		mettreAJourCentreSelection(&noeud);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeterminerCentreSelection::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de calcul du centre de 
/// selection d'un segment selectionne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::visiter(NoeudSegment& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeterminerCentreSelection::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de calcul du centre de 
/// selection d'une fleche selectionne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeterminerCentreSelection::visiter(NoeudFleche& noeud)
{
	if (!minMax_ && noeud.estSelectionne())
	{
		mettreAJourCentreSelection(&noeud);
	}
	
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////