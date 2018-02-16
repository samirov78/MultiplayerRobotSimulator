///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPoteau.h"
#include "Utilitaire.h"
#include <iostream>

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

int NoeudPoteau::compteurRed_ = 0;
int NoeudAbstrait::compteurPoteau_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	NoeudAbstrait::compteurPoteau_++;
	couleurPoteau_[0] = 0;
	couleurPoteau_[1] = 0;
	couleurPoteau_[2] = 255;
	couleurSelection_[1] = 0;
	attribuerCouleur();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(*this);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::~NoeudPoteau()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPoteau::~NoeudPoteau()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::afficherConcret(const bool& attribuerCouleur) const
{

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(90, 1.0, 0.0, 0.0);

	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurPoteau_[0];
	couleurObjet[1] = couleurPoteau_[1];
	couleurObjet[2] = couleurPoteau_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];
	// Affichage du modèle.
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection);
	
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
/// @fn bool NoeudPoteau::clickToucheNoeud(glm::dvec3 point)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] x, y, z : Les coordonnées du clic
///
/// @return bool : Vrai si on click sur l'objet Faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPoteau::clickToucheNoeud(glm::dvec3 point)
{
	utilitaire::CylindreEnglobant cylindre = utilitaire::calculerCylindreEnglobant(*modele_);
	return (sqrt(pow(point.x - obtenirPositionRelative().x, 2) + pow(point.y - obtenirPositionRelative().y, 2))
			<= (cylindre.rayon - 3.2)*obtenirRedimensionnementRelative().x);
}

////////////////////////////////////////////////////////////////////////
/// @fn void NoeudPoteau::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::animer(float temps)
{


	// L'araignée oscille selon une période de 4 secondes.
	//angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	//	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	//	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

////////////////////////////////////////////////////////////////////////
/// @fn void NoeudPoteau::changerScale(double scale)
///
/// Cette fonction effectue le changement de dimension d'un objet mur.
///
///@param[in] scale : facteur de dimensionnement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::changerScale(double facteur)
{
	//if ( estDansLaTableApresScale( scale ) )
	//{
		glm::dvec3 dimensionement = obtenirRedimensionnementRelative();
		assignerRedimensionnementRelative(glm::dvec3(facteur * dimensionement[0], facteur * dimensionement[1], dimensionement[2]));
		//if (!estDansLaTable())
		//{
			//glm::dvec3 dimensionement = obtenirRedimensionnementRelative();
			//assignerRedimensionnementRelative(glm::dvec3( dimensionement[0] / scale, dimensionement[1] / scale, 1));
			//return false;
		//}
		//else 
			//return true;
	//}
	//else
		//return false;
}

/// verifier si le noeud est dans la table

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPoteau::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
///
/// Cette fonction verifie si un objet NoeudPoteau est toujours sur la 
/// table apres un deplacement.
///
/// @param[in] deplacement : Coordonnees xyz du deplacement.
///
/// @return Vrai si l'objet est toujours sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPoteau::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
{
	glm::dvec3 position = obtenirPositionRelative() + deplacement;
	double xMax = position[0] + redimensionnementRelative_[0];
	double yMax = position[1] + redimensionnementRelative_[1];
		
	double xMin = position[0] - redimensionnementRelative_[0];
	double yMin = position[1] - redimensionnementRelative_[1];
	
	if (xMax <= 48 && xMin >= -48 && yMax <= 24 && yMin >= -24)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPoteau::estDansLaTableApresScale(double scale)
///
/// Cette fonction verifie si un objet NoeudPoteau est toujours sur la 
/// table apres un redimensionnement.
///
/// @param[in] scale : Facteur de redimensionnement.
///
/// @return Vrai si l'objet est toujours sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPoteau::estDansLaTableApresScale(double scale)
{
	glm::dvec3 position = obtenirPositionRelative();
	glm::dvec3 redimenstionnement = obtenirScaleInitialeEnTraitement();
	double xMax = position[0] + scale*redimenstionnement[0];
	double yMax = position[1] + scale*redimenstionnement[1];

	double xMin = position[0] - scale*redimenstionnement[0];
	double yMin = position[1] - scale*redimenstionnement[1];

	if (xMax <= 48 && xMin >= -48 && yMax <= 24 && yMin >= -24)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPoteau::estDansLaTable()
///
/// Cette fonction verifie si un objet de type NoeudPoteau est sur la table.
///
/// @return Vrai si l'objet NoeudMur est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPoteau::estDansLaTable()
{
	glm::dvec3 position = obtenirPositionRelative();
	double xMax = position[0] + redimensionnementRelative_[0];
	double yMax = position[1] + redimensionnementRelative_[1];

	double xMin = position[0] - redimensionnementRelative_[0];
	double yMin = position[1] - redimensionnementRelative_[1];

	if (xMax <= 48 && xMin >= -48 && yMax <= 24 && yMin >= -24)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPoteau::dansLaTableSiSelectionne()
///
/// Cette fonction verifie si un objet de type NoeudPoteau est sur la table.
/// et selectionne
///
/// @return Vrai si l'objet NoeudPoteau est sur la table et selectionne, 
/// faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPoteau::dansLaTableSiSelectionne()
{
	bool reponse = true;
	if (estSelectionne())
	{
		if (!estDansLaTable())
			reponse = false;
	}
	return reponse;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::retournerAuScaleInitiale()
///
/// Cette fonction permet de reinitialiser le dimensionnement 
/// d'un objet NoeudPoteau.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::retournerAuScaleInitiale()
{
	changerScale(obtenirScaleInitialeEnTraitement()[0] / obtenirRedimensionnementRelative()[0]);
}


void NoeudPoteau::attribuerCouleur()
{
	if (NoeudAbstrait::compteurPoteau_ < 180)
	{
		couleurPoteau_[0] = NoeudPoteau::compteurRed_;
		couleurPoteau_[1] = 0;
		couleurPoteau_[2] = 255 - NoeudAbstrait::compteurPoteau_ + 1;
	}
	else
	{
		NoeudAbstrait::compteurPoteau_ = 1;
		NoeudPoteau::compteurRed_++;
		couleurPoteau_[0] = NoeudPoteau::compteurRed_;
		couleurPoteau_[1] = 0;
		couleurPoteau_[2] = 255;
	}
}





////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction permet de vérifier si le noeud est selectionné 
///
/// @param[in] couleurObjet[] : Couleurs RGB du pixel.
///
/// @return booléan: true si le noeud est sélectionné ou false sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPoteau::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;

	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurPoteau_[0] && couleurObjet[1] == couleurPoteau_[1] && couleurObjet[2] == couleurPoteau_[2])
	{
		estPointe = true;
		if (couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			attribuerCouleurSelection();
		}
	}
	return estPointe;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::effacerFantome()
///
/// Cette fonction efface les noeuds qui sont designes fantomes 
/// parmi les enfants de ce noeud.
///
/// Elle permet de diminuer le nombre de noeud mur
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::effacerFantome()
{
	if (estFantome())
	{
		NoeudAbstrait::compteurPoteau_--;
	}
}


/*std::string NoeudPoteau::toString()
{
	std::string chaine = NoeudAbstrait::toString();
	glm::dvec3 pointDepart = getPointDepart();
	std::string depart = utilitaire::toString(pointDepart[0]) + separateurAttributs + utilitaire::toString(pointDepart[1])
		+ separateurAttributs + utilitaire::toString(pointDepart[2]);

	glm::dvec3 pointFin = getPointFin();
	std::string fin = utilitaire::toString(pointFin[0]) + separateurAttributs + utilitaire::toString(pointFin[1])
		+ separateurAttributs + utilitaire::toString(pointFin[2]);
	chaine = chaine + separateurAttributs + depart + separateurAttributs + fin;
	return chaine;
}*/
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
