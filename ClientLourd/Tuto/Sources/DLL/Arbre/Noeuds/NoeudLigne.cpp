///////////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudLigne.h"
#include "Utilitaire.h"
#include <iostream>

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "visiteurRotationUnObjet.h"
#include "VisiteurDeterminerCentreSelection.h"


int NoeudAbstrait::compteurLigneRed_ = 0;
int NoeudAbstrait::compteurLigneGreen_ = 0;
int NoeudAbstrait::compteurLigne_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigne::NoeudLigne(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigne::NoeudLigne(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait::compteurLigne_++;
}

/*
void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(*this);
	std::cout << "accepterVisiteur ligne" << std::endl;
}

*/


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigne::~NoeudLigne()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigne::~NoeudLigne()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::afficherConcret(const bool& attribuerCouleur) const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(attribuerCouleur);
	// Sauvegarde de la matrice.
	//glPushMatrix();
	// Révolution autour du centre.
	//glRotated(90, 1.0, 0.0, 0.0);
	// Affichage du modèle.
	//vbo_->dessiner();
	// Restauration de la matrice.
	//glPopMatrix();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	if (visiteur->obtenirType() == VISITEUR_DUPLIQUER)
	{
		visiteur->visiter(*this);
	}
	for (unsigned int i = 0; i < obtenirNombreEnfants(); i++)
	{
		enfants_[i]->accepterVisiteur(visiteur);
	}
	if (visiteur->obtenirType() != VISITEUR_DUPLIQUER)
	{
		visiteur->visiter(*this);
	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	//angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	//	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	//	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::assignerCentre(glm::dvec3 centre)
///
/// Cette fonction l'assignation des coordonnees de centre a un objet
/// NoeudLigne.
///
/// @param[in] centre : Coordonnees xyz du centre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::assignerCentre(glm::dvec3 centre)
{
	glm::dvec3 deplacement = centre - obtenirCentre();
	for (NoeudAbstrait * enfant : enfants_){
		enfant->assignerPositionRelative(enfant->obtenirPositionRelative() + deplacement);
	}
	centre_ = centre;
}


//bool assignerRotation(double rotation)
//{
//	
//}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::mettreAjourCentre()
///
/// Cette fonction permet la mise a jour des coordonnees de centre
/// d'un objet NoeudLigne
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::mettreAjourCentre()
{
	unsigned int nbEnfants = obtenirNombreEnfants();
	if (nbEnfants != 0)
	{
		centre_ = glm::dvec3(0.0);
		for (unsigned int i = 0; i < nbEnfants; i++)
		{
			enfants_[i]->mettreAjourCentre();
			centre_ += enfants_[i]->obtenirCentre();
		}
		centre_ /= nbEnfants;
	}
}

void NoeudLigne::assignerRotation(double rotation)
{
	angleRotation_ = rotation;
}

double NoeudLigne::obtenirRotation()
{
	return angleRotation_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::effacerFantome()
///
/// Efface tous les noeuds fantomes situés sous ce noeud.  Elle
/// s'appelle donc récursivement sur tous les enfants, avant de retirer
/// les enfants fantomes.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::effacerFantome()
{

	// On efface les enfants fantomes.  On effectue ce traitement
	// dans une seconde boucle pour éviter de faire des assomptions
	// sur la robustesse des itérateurs lorsque le conteneur est
	// modifié pendant une itération.
	for (conteneur_enfants::iterator it{ enfants_.begin() };
		it != enfants_.end();
		) {
		if ((*it)->estFantome()) {
			NoeudAbstrait* enfant{ (*it) };
			enfants_.erase(it);
			delete enfant;

			// On ramène l'itération au début de la boucle, car le destructeur
			// de l'enfant pourrait éventuellement avoir retiré d'autres
			// enfants de l'arbre, ce qui briserait l'itération.  Pourrait
			// éventuellement être évité avec des itérateurs plus robustes.
			// Peut-être une liste chaînée?
			it = enfants_.begin();
		}
		else {
			++it;
		}
	}
	if (estFantome())
	{
		NoeudAbstrait::compteurLigne_--;
	}
}

std::string NoeudLigne::toString()
{
	std::string chaine = NoeudAbstrait::toString();
	std::vector<NoeudAbstrait*>* enfants = this->obtenirEnfants();
	for (int i = 0; i < enfants->size(); i++)
		chaine += separateurEnfants + enfants->at(i)->toString();
	return chaine;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
