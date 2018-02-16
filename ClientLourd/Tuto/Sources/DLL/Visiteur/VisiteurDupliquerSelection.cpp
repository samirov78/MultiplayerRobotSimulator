///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDupliquerSelection.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurDupliquerSelection.h"
#include "FacadeModele.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

static const char alphanum[] =
"0123456789"
"!-$^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{
	return alphanum[rand() % stringLength];
}

std::string getNewGuid()
{
	std::string ID;
	for (unsigned int i = 0; i < 20; ++i)
	{
		ID += genRandom();
	}
	return ID;
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDupliquerSelection::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de duplication d'un
/// objet poteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDupliquerSelection::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionRelative() + deplacement_;
		double scale = noeud.obtenirRedimensionnementRelative().x;
		double angleRotation = noeud.obtenirRotationRelative().x;
		NoeudAbstrait* parent = noeud.obtenirParent();
		NoeudAbstrait* noeudPoteau = FacadeModele::obtenirInstance()->ajouterNoeudDuplique("poteau", parent,
													position, scale, angleRotation, glm::dvec3(0.0), glm::dvec3(0.0), estFantome_);
		//noeudPoteau->ID = noeud.ID +"P"+ std::to_string(FacadeModele::obtenirInstance()->compteurDupliques++);
		noeudPoteau->ID = getNewGuid();
		//std::cout << "facade Model compteur : " << FacadeModele::obtenirInstance()->compteurDupliques<<std::endl;

	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDupliquerSelection::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de duplication d'un
/// objet mur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDupliquerSelection::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionRelative() + deplacement_;
		double scale = noeud.obtenirRedimensionnementRelative().x;
		double angleRotation = noeud.obtenirRotationRelative().x;
		glm::dvec3 pointDepart = noeud.getPointDepart() + deplacement_;
		glm::dvec3 pointFin = noeud.getPointFin() + deplacement_;
		NoeudAbstrait* parent = noeud.obtenirParent();
		NoeudAbstrait* noeudMur = FacadeModele::obtenirInstance()->ajouterNoeudDuplique("mur", parent, 
												position, scale, angleRotation, pointDepart, pointFin, estFantome_);
		noeudMur->ID = getNewGuid();
		//std::cout << "facade Model compteur : " << FacadeModele::obtenirInstance()->compteurDupliques << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDupliquerSelection::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de duplication d'un
/// objet table.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDupliquerSelection::visiter(NoeudTable& noeud)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDupliquerSelection::visiter(NoeudLigne& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de duplication d'un
/// objet ligne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDupliquerSelection::visiter(NoeudLigne& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 position = noeud.obtenirPositionRelative();
		double scale = noeud.obtenirRedimensionnementRelative().x;
		double angleRotation = noeud.obtenirRotationRelative().x;
		glm::dvec3 pointDepart = noeud.getPointDepart() + deplacement_;
		glm::dvec3 pointFin = noeud.getPointFin() + deplacement_;
		NoeudAbstrait* parent = noeud.obtenirParent();
		dernierNoeudLigneAjoute_ = FacadeModele::obtenirInstance()->ajouterNoeudDuplique("ligne", parent, 
												position, scale, angleRotation, glm::dvec3(0.0), glm::dvec3(0.0), estFantome_);
		dernierNoeudLigneAjoute_->ID = getNewGuid();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDupliquerSelection::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de duplication d'un
/// objet segment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDupliquerSelection::visiter(NoeudSegment& noeud)
{
	if (noeud.estSelectionne() && (dernierNoeudLigneAjoute_ != nullptr))
	{
		glm::dvec3 position = noeud.obtenirPositionRelative() + deplacement_;
		double scale = noeud.obtenirRedimensionnementRelative().x;
		double angleRotation = noeud.obtenirRotationRelative().x;
		glm::dvec3 pointDepart = noeud.getPointDepart() + deplacement_;
		glm::dvec3 pointFin = noeud.getPointFin() + deplacement_;
		NoeudAbstrait* parent = dernierNoeudLigneAjoute_;
		NoeudAbstrait* noeudSegment = FacadeModele::obtenirInstance()->ajouterNoeudDuplique("segment", parent,
													position, scale, angleRotation, pointDepart, pointFin, estFantome_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDupliquerSelection::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de duplication d'un
/// objet fleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDupliquerSelection::visiter(NoeudFleche& noeud)
{
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////