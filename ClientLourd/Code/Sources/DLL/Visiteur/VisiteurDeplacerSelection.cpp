///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacerSelection.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurDeplacerSelection.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacerSelection::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de déplacement à un 
/// objet sélectionné de la classe NoeudPoteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacerSelection::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		noeud.assignerPositionRelative(glm::dvec3( position[0] + 
			deplacement_[0], position[1] + deplacement_[1], position[2] + deplacement_[2]));
		//if (!noeud.estDansLaTable())
		//	noeud.assignerPositionRelative(position);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacerSelection::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de déplacement à un 
/// objet sélectionné de la classe NoeudMur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacerSelection::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		//glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		noeud.assignerPositionRelative(glm::dvec3(position[0] +
			deplacement_[0], position[1] + deplacement_[1], position[2] + deplacement_[2]));

		glm::dvec3 depart = noeud.getPointDepartInitialEnTraitement();
		glm::dvec3 fin = noeud.getPointFinInitialEnTraitement();
		depart = depart + deplacement_;
		fin = fin + deplacement_;

//3		noeud.setPoints(depart, fin);
	}
}

/*void VisiteurDeplacerSelection::visiter(NoeudLigne& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		noeud.assignerPositionRelative(glm::dvec3(position[0] +
			deplacement_[0], position[1] + deplacement_[1], position[2] + deplacement_[2]));
	}
}*/

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacerSelection::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de déplacement à un 
/// objet sélectionné de la classe NoeudSegment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacerSelection::visiter(NoeudSegment& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		//glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		noeud.assignerPositionRelative(glm::dvec3(position[0] +
			deplacement_[0], position[1] + deplacement_[1], position[2] + deplacement_[2]));


		glm::dvec3 depart = noeud.getPointDepartInitialEnTraitement();
		glm::dvec3 fin = noeud.getPointFinInitialEnTraitement();
		depart = depart + deplacement_;
		fin = fin + deplacement_;

//3		noeud.setPoints(depart, fin);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacerSelection::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de déplacement à un 
/// objet sélectionné de la classe NoeudTable.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacerSelection::visiter(NoeudTable& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacerSelection::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de déplacement à un 
/// objet sélectionné de la classe NoeudFleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacerSelection::visiter(NoeudFleche& noeud)
{
	if (noeud.estSelectionne())
	{
		//glm::dvec3 position = noeud.obtenirPositionRelative();
		glm::dvec3 position = noeud.obtenirPositionInitialeEnTraitement();
		noeud.assignerPositionRelative(glm::dvec3(position[0] +
		deplacement_[0], position[1] + deplacement_[1], position[2] + deplacement_[2]));
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
