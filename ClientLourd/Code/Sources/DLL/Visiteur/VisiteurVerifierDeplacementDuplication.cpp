///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerifierDeplacementDuplication.cpp
/// @author INF2990 Eq.11
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurVerifierDeplacementDuplication.h"
#include "FacadeModele.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurVerifierDeplacementDuplication::verifierPoint(glm::dvec3 point)
///
/// Cette methode permet de verifier si les objets dupliques vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Vrai si les objets sont a l'interieur, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurVerifierDeplacementDuplication::verifierPoint(glm::dvec3 point)
{
	return (utilitaire::DANS_LIMITESXY(point.x, -FacadeModele::obtenirInstance()->LONGUEUR_TABLE / 2.0,
		FacadeModele::obtenirInstance()->LONGUEUR_TABLE / 2.0, point.y, -FacadeModele::obtenirInstance()->LARGEUR_TABLE / 2.0,
		FacadeModele::obtenirInstance()->LARGEUR_TABLE / 2.0));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierDeplacementDuplication::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet de verifier si les objets poteaux vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierDeplacementDuplication::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 deplacementDuplication = deplacement_ + noeud.obtenirPositionRelative();
		glm::dvec3 ajoutRayon = glm::dvec3(FacadeModele::obtenirInstance()->RAYON_POTEAU * noeud.obtenirRedimensionnementRelative().x,
								FacadeModele::obtenirInstance()->RAYON_POTEAU * noeud.obtenirRedimensionnementRelative().y, 0.0);
		deplacementDuplication.x > 0 ? deplacementDuplication.x += ajoutRayon.x : deplacementDuplication.x -= ajoutRayon.x;
		deplacementDuplication.y > 0 ? deplacementDuplication.y += ajoutRayon.y : deplacementDuplication.y -= ajoutRayon.y;
		duplicationValide_ = duplicationValide_ && verifierPoint(deplacementDuplication);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierDeplacementDuplication::visiter(NoeudMur& noeud)
///
/// Cette methode permet de verifier si les objets murs vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierDeplacementDuplication::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne())
	{
		duplicationValide_ = duplicationValide_ && verifierPoint(deplacement_ + noeud.getPointDepart()) &&
			verifierPoint(deplacement_ + noeud.getPointFin());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierDeplacementDuplication::visiter(NoeudTable& noeud)
///
/// Cette methode permet de verifier si les objets tables vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierDeplacementDuplication::visiter(NoeudTable& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierDeplacementDuplication::visiter(NoeudLigne& noeud)
///
/// Cette methode permet de verifier si les objets lignes vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierDeplacementDuplication::visiter(NoeudLigne& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierDeplacementDuplication::visiter(NoeudSegment& noeud)
///
/// Cette methode permet de verifier si les objets segments vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierDeplacementDuplication::visiter(NoeudSegment& noeud)
{
	if (noeud.estSelectionne())
	{
		duplicationValide_ = duplicationValide_ && verifierPoint(deplacement_ + noeud.getPointDepart()) &&
			verifierPoint(deplacement_ + noeud.getPointFin());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierDeplacementDuplication::visiter(NoeudFleche& noeud)
///
/// Cette methode permet de verifier si les objets fleches vont etre a
/// l'interieur de la zone de dessin ou non.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierDeplacementDuplication::visiter(NoeudFleche& noeud)
{

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////