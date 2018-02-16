///////////////////////////////////////////////////////////////////////////////
/// @file NoeudSegment.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudSegment.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"




////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudSegment::NoeudSegment(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudSegment::NoeudSegment(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	couleurSegment_[0] = 0;
	couleurSegment_[1] = 0;
	couleurSegment_[2] = 2;
	couleurSelection_[1] = 0;
	attribuerCouleur();
	//std::cout << "compteur Ligne :" << NoeudAbstrait::compteurLigne_ << std::endl;
	//std::cout << "couleur Ligne : (" << (int)couleurSegment_[0] << ", " << (int)couleurSegment_[1] << ", " << (int)couleurSegment_[2] << ")" << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(*this);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudSegment::clickToucheNoeud(glm::dvec3 point)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] glm::dvec3 point : Les coordonnées du clic
///
/// @return Vrai si oui et faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudSegment::clickToucheNoeud(glm::dvec3 point)
{
	utilitaire::BoiteEnglobante hitbox = utilitaire::calculerBoiteEnglobante(*modele_);

	glm::dvec3 vecteurEchelle({ 1 / obtenirRedimensionnementRelative().x, 0.13 / obtenirRedimensionnementRelative().y, 1 / obtenirRedimensionnementRelative().z });//x=1.03 y=0.1
	glm::dmat3 matriceRotation({ glm::cos(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), -glm::sin(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), 0 },
	{ glm::sin(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), glm::cos(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), 0 }, { 0, 0, 1 });
	glm::dvec3 vecteurPosition({ positionRelative_.x, positionRelative_.y, positionRelative_.z });

	point = matriceRotation * (point - vecteurPosition);
	point *= vecteurEchelle;

	return (
		point.x >= hitbox.coinMin.x && point.x <= hitbox.coinMax.x
		&& point.y >= hitbox.coinMin.y && point.y <= hitbox.coinMax.y
		);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudSegment::~NoeudSegment()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudSegment::~NoeudSegment()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::afficherConcret(const bool& attribuerCouleur) const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	////glRotatef(angleRotation_, 0, 0, 1);
	// Translation.
	////glTranslatef(10, 0, 0);
	// Rotation autour de l'axe des X.
	glRotated(90, 1.0, 0.0, 0.0);
	// Rotation autour de l'axe des Y.
	////glRotatef(angleY_, 0, 1, 0);
	// Recentrage du cube.
	///glTranslatef(0, 0, -10);
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurSegment_[0];
	couleurObjet[1] = couleurSegment_[1];
	couleurObjet[2] = couleurSegment_[2];
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
/// @fn bool NoeudSegment::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
///
/// Cette fonction verifie si un objet NoeudSegment est toujours sur la 
/// table apres un deplacement.
///
/// @param[in] deplacement : Coordonnees xyz du deplacement.
///
/// @return Vrai si l'objet est toujours sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudSegment::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
{
	glm::dvec3 depart = this->getPointDepart();
	glm::dvec3 fin = this->getPointFin();
	depart = depart + deplacement;
	fin = fin + deplacement;
	bool reponse = false;
	if (depart[0] <= 48 && depart[0] >= -48 && depart[1] <= 24 && depart[1] >= -24
		&& fin[0] <= 48 && fin[0] >= -48 && fin[1] <= 24 && fin[1] >= -24)
		reponse = true;
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPoteau::estDansLaTable()
///
/// Cette fonction verifie si un objet de type NoeudSegment est sur la table.
///
/// @return Vrai si l'objet NoeudMur est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudSegment::estDansLaTable()
{
	glm::dvec3 depart = this->getPointDepart();
	glm::dvec3 fin = this->getPointFin();

	return utilitaire::rectangleDansUneZone(depart, fin, LARGEUR_LIGNE, LONGUEUR_TABLE, LARGEUR_TABLE);
	/*
	if ( depart[0] <= LONGUEUR_TABLE / 2 && depart[0] >= - LONGUEUR_TABLE / 2 && depart[1] <= LARGEUR_TABLE / 2 
		&& depart[1] >= - LARGEUR_TABLE / 2 && fin[0] <= LONGUEUR_TABLE / 2 && fin[0] >= - LONGUEUR_TABLE / 2 
		&& fin[1] <= LARGEUR_TABLE / 2 && fin[1] >= - LARGEUR_TABLE / 2 )
		return true;
	else
		return false;*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudSegment::dansLaTableSiSelectionne()
///
/// Cette fonction verifie si un objet de type NoeudSegment est sur la table.
/// et selectionne
///
/// @return Vrai si l'objet NoeudSegment est sur la table et selectionne, 
/// faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudSegment::dansLaTableSiSelectionne()
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
/// @fn void NoeudSegment::initialiserEnTraitement()
///
/// Cette fonction initialise des donnees d'un objet NoeudSegment en 
/// traitement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::initialiserEnTraitement()
{
	initialiserPositionEnTraitement();
	//pointDepartInitialEnTraitement_ = pointDepart_;
	//pointFinInitialEnTraitement_ = pointFin_;
	rotationRelativeAvantraitement_ = obtenirRotationRelative();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::ligneTouchee(glm::dvec3 point, bool& estTouche) 
///
/// Vérifie si le point touche le noeud présent, s'il est une ligne.
///
/// @param[in] point : Les coordonnées du point
/// @param[out] estTouche : Vrai si le point touche la ligne, faux sinon
///
/// @return aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::ligneTouchee(glm::dvec3 point, bool& estTouche)
{
	if (clickToucheNoeud(point))
		estTouche = true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction permet de vérifier si le noeud est selectionné 
///
/// @param[in] couleurObjet[] : Couleurs RGB du pixel.
///
/// @return booléan: true si le noeud est sélectionné ou false sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudSegment::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	if (!estVisite())
	{
		if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
		{
			estPointe = true;
			obtenirParent()->assignerEstVisite(true);
		}
		else if (couleurObjet[0] == couleurSegment_[0] && couleurObjet[1] == couleurSegment_[1] && couleurObjet[2] == couleurSegment_[2])
		{
			estPointe = true;
			if (couleurSelection_[1] == 0)
			{
				NoeudAbstrait::compteurSelection_++;
				obtenirParent()->attribuerCouleurSelection();
			}
			obtenirParent()->assignerEstVisite(true);
		}
	}
	return estPointe;
}

void NoeudSegment::attribuerCouleur()
{
	if (NoeudAbstrait::compteurLigne_ <= 60)
	{
		couleurSegment_[0] = NoeudAbstrait::compteurLigneRed_;
		couleurSegment_[1] = NoeudAbstrait::compteurLigneGreen_;
		couleurSegment_[2] = NoeudAbstrait::compteurLigne_;
	}
	else if (NoeudAbstrait::compteurLigneRed_ <= 60)
	{
		NoeudAbstrait::compteurLigne_ = 2;
		NoeudAbstrait::compteurLigneRed_++;
		couleurSegment_[0] = NoeudAbstrait::compteurLigneRed_;
		couleurSegment_[1] = NoeudAbstrait::compteurLigneGreen_;
		couleurSegment_[2] = NoeudAbstrait::compteurLigne_;
	}
	else if (NoeudAbstrait::compteurLigneGreen_ <= 60)
	{
		NoeudAbstrait::compteurLigne_ = 2;
		NoeudAbstrait::compteurLigneRed_ = 1;
		NoeudAbstrait::compteurLigneGreen_++;
		couleurSegment_[0] = NoeudAbstrait::compteurLigneRed_;
		couleurSegment_[1] = NoeudAbstrait::compteurLigneGreen_;
		couleurSegment_[2] = NoeudAbstrait::compteurLigne_;
	}
	else
	{
		NoeudAbstrait::compteurLigne_ = 3;
		NoeudAbstrait::compteurLigneRed_ = 1;
		NoeudAbstrait::compteurLigneGreen_ = 1;
		couleurSegment_[0] = NoeudAbstrait::compteurLigneRed_;
		couleurSegment_[1] = NoeudAbstrait::compteurLigneGreen_;
		couleurSegment_[2] = NoeudAbstrait::compteurLigne_;
	}
}

/*std::string NoeudSegment::toString()
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