///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRoueGauche.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRoueGauche.h"
#include "Utilitaire.h"
#include <iostream>

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRoueGauche::NoeudRoueGauche(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRoueGauche::NoeudRoueGauche(const std::string& typeNoeud)
: NoeudRoue{ typeNoeud }
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRoueGauche::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudRoueGauche::accepterVisiteur(VisiteurAbstrait* visiteur){

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRoueGauche::~NoeudRoueGauche()
///
/// Ce destructeur désallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRoueGauche::~NoeudRoueGauche()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoueGauche::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoueGauche::afficherConcret(const bool& attribuerCouleur) const
{

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(90, 1.0, 0.0, 0.0);
	glRotated(180, 0.0, 0.0, 1.0);
	
	GLubyte couleur[3] = { 0, 0, 0 };
	// Affichage du modèle.
	vbo_->dessiner(estSelectionne(), false, couleur, couleur);

	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudRoueGauche::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoueGauche::animer(float dt)
{
	double vitesseMax = rapportVitesse_ * VITESSE_MAX;
	if (getVitesse() < vitesseMax)
	{
		setAcceleration(getAcceleration() + getIncrAcceleration());
		setVitesse(getVitesse() + getAcceleration() * dt);
	}
	if (getVitesse() > vitesseMax)
	{
		setVitesse(vitesseMax);
	}

	angleRotation_ = getVitesse() * dt;
	if (getDirection() == FORWARD)
	{
		assignerRotationRelative(glm::dvec4(rotationRelative_[0] + angleRotation_, 1.0, 0.0, 0.0));
	}
	else
	{
		assignerRotationRelative(glm::dvec4(rotationRelative_[0] - angleRotation_, 1.0, 0.0, 0.0));
	}
	this->oldDirection_ = getDirection();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
