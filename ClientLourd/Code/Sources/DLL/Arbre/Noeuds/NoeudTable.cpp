///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTable.h"
#include "Utilitaire.h"
#include <iostream>

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
//void NoeudTable::accepterVisiteur(VisiteurAbstrait* visiteur){
//
//	for (int i = 0; i < obtenirNombreEnfants(); i++)
//	{
//		enfants_[i]->accepterVisiteur(visiteur);
//	}
//
//}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret(const bool& attribuerCouleur) const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(attribuerCouleur);
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(90, 1.0, 0.0, 0.0);

	GLubyte couleur[3] = { 0, 0, 0 };
	// Affichage du modèle.
	vbo_->dessiner(estSelectionne(), false, couleur, couleur);

	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	//angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
//	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
//	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

//void NoeudTable::deselectIfSameColor(NoeudAbstrait & noeud)
//{
//	NoeudComposite::deselectIfSameColor(noeud);
//}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
