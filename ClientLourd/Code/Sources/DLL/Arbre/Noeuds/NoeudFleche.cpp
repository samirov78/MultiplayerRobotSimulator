///////////////////////////////////////////////////////////////////////////////
/// @file NoeudFleche.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudFleche.h"

#include "Utilitaire.h"
#include <iostream>

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudFleche::NoeudFleche(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudFleche::NoeudFleche(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	couleurFleche_[0] = 255;
	couleurFleche_[1] = 0;
	couleurFleche_[2] = 255;
	couleurSelection_[1] = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudFleche::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudFleche::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(*this);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudFleche::~NoeudFleche()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudFleche::~NoeudFleche()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudFleche::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudFleche::afficherConcret(const bool& attribuerCouleur) const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	////glRotatef(angleRotation_, 0, 0, 1);
	// Translation.
	////glTranslatef(10, 0, 0);
	// Rotation autour de l'axe des X.
	////glRotatef(angleX_, 1, 0, 0);
	// Rotation autour de l'axe des Y.
	////glRotatef(angleY_, 0, 1, 0);
	// Recentrage du cube.
	///glTranslatef(0, 0, -10);
	// Affichage du modèle.
	glRotated(90, 1.0, 0.0, 0.0);

	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurFleche_[0];
	couleurObjet[1] = couleurFleche_[1];
	couleurObjet[2] = couleurFleche_[2];
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
///
/// bool NoeudFleche::clickToucheNoeud(glm::dvec3 point)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] glm::dvec3 point : Les coordonnées du clic
///
/// @return Vrai si oui et faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudFleche::clickToucheNoeud(glm::dvec3 point)
{
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	glm::dvec3 vecteurEchelle({ 1 / obtenirRedimensionnementRelative().x, 0.075 / obtenirRedimensionnementRelative().y, 1 / obtenirRedimensionnementRelative().z });
	glm::dmat3 matriceRotation({ glm::cos(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), -glm::sin(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), glm::cos(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), 0 }, { 0, 0, 1 });
	glm::dvec3 vecteurPosition({ positionRelative_.x, (positionRelative_.y), positionRelative_.z });

	point = matriceRotation * (point - vecteurPosition);
	point *= vecteurEchelle;

	return (
		point.x >= hitbox.coinMin.x && point.x <= hitbox.coinMax.x
		&& point.y >= hitbox.coinMin.y && point.y <= hitbox.coinMax.y
		);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudFleche::estDansLaTable()
///
/// Cette fonction permet de verifier si le noeud est sur la table.
///
/// @return Vrai si l'objet le noeud est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudFleche::estDansLaTable()
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
/// @fn bool NoeudFleche::dansLaTableSiSelectionne()
///
/// Cette fonction verifie si un objet de type NoeudFleche est sur la table.
/// si selectionne
///
/// @return Vrai si l'objet NoeudFleche est sur la table si selectionne, 
/// faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudFleche::dansLaTableSiSelectionne()
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
/// @fn void NoeudFleche::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
/*void NoeudFleche::animer(float temps)
{
// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
// Le cube effectue une révolution à toutes les 15 secondes.
angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
}*/

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudFleche::tourner(double angle)
///
/// Cette fonction effectue la rotation d'un noeud de type fleche.
///
/// @param[in] angle : Angle d'incrementation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudFleche::tourner(double angle)
{ 
	assignerRotationRelative(obtenirRotationRelative() + glm::dvec4(angle, 0, 0, 1)); 
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudFleche::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction permet de vérifier si le noeud est selectionné 
///
/// @param[in] couleurObjet[] : Couleurs RGB du pixel.
///
/// @return booléan: true si le noeud est sélectionné ou false sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudFleche::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;

	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurFleche_[0] && couleurObjet[1] == couleurFleche_[1] && couleurObjet[2] == couleurFleche_[2])
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


std::string NoeudFleche::toString()
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
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////