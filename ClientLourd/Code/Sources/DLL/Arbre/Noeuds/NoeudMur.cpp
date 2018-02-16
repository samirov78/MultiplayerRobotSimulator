///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#define _USE_MATH_DEFINES

int NoeudMur::compteurBlue_ = 0;
int NoeudAbstrait::compteurMur_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	NoeudAbstrait::compteurMur_++;
	couleurMur_[0] = 255;
	couleurMur_[1] = 0;
	couleurMur_[2] = 0;
	couleurSelection_[1] = 0;
	attribuerCouleur();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube et décrémenter 
/// la valeur du compteur d'instances du noeud mur.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction accepte le visiteur afin qu'il puisse effectuer
/// son algorithme de traitement.
///
/// @param[in] visiteur : Un pointeur vers le visiteur.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(*this);
}

////////////////////////////////////////////////////////////////////////
///
/// bool NoeudMur::clickToucheNoeud(glm::dvec3 point)
///
/// Vérifie si le clic de souris touche le modèle du noeud
///
/// @param[in] glm::dvec3 point : Les coordonnées du clic
///
/// @return Vrai si oui et faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::clickToucheNoeud(glm::dvec3 point)
{
	utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*modele_);

	glm::dvec3 vecteurEchelle({ 1 / obtenirRedimensionnementRelative().x, 47 / obtenirRedimensionnementRelative().y, 1 / obtenirRedimensionnementRelative().z });
	glm::dmat3 matriceRotation({ glm::cos(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), -glm::sin(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), 0 }, 
								{ glm::sin(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), glm::cos(utilitaire::DEG_TO_RAD(obtenirRotationRelative().x)), 0 }, { 0, 0, 1 });
	glm::dvec3 vecteurPosition({ positionRelative_.x, (positionRelative_.y), positionRelative_.z });


	point = matriceRotation * (point - vecteurPosition);
	point *= vecteurEchelle;
	
	return ((point.x >= boite.coinMin.x && point.x <= boite.coinMax.x) &&
			((point.y >= boite.coinMin.y && point.y <= boite.coinMax.y) || (point.y <= - boite.coinMin.y && point.y >= - boite.coinMax.y)));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret(const bool& attribuerCouleur) const
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
	couleurObjet[0] = couleurMur_[0];
	couleurObjet[1] = couleurMur_[1];
	couleurObjet[2] = couleurMur_[2];
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
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
/*void NoeudMur::animer(float temps)
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
/// @fn void NoeudMur::changerScale(double scale)
///
/// Cette fonction effectue le changement de dimension d'un objet mur.
///
/// @param[in] scale : facteur de dimensionnement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::changerScale(double scale)
{
	//if (estDansLaTableApresScale(scale))
	//{
		glm::dvec3 dimensionement = obtenirRedimensionnementRelative();
		double ancienneLongueur = dimensionement[0];
		assignerRedimensionnementRelative(glm::dvec3(scale * dimensionement[0], dimensionement[1], 1));
		glm::dvec3 pointDepart = this->getPointDepart();
		glm::dvec3 pointFin = this->getPointFin();
		glm::dvec3 position = this->obtenirPositionRelative();
		double nouvelleLongueur = obtenirRedimensionnementRelative()[0];
		//3pointDepart_ = position - ((pointFin - pointDepart) / ancienneLongueur) * (nouvelleLongueur / 2);
		//3pointFin_ = position + ((pointFin - pointDepart) / ancienneLongueur) * (nouvelleLongueur / 2);
		//return true;
	//}
	//else
		//return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::mettreAjourPosition()
///
/// Cette fonction effectue la mise a jour de la position d'un objet
/// NoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::mettreAjourPosition()
{

	utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*modele_);
	double longueur = boite.coinMax.y - boite.coinMin.y;

	glm::dvec3 base_Debut(0.0, longueur / 2.0, boite.coinMin.z);
	glm::dvec3 base_Fin(0.0, -longueur / 2.0, boite.coinMin.z);

	base_Debut.y *= redimensionnementRelative_.y;
	base_Fin.y *= redimensionnementRelative_.y;

	base_Debut.x *= redimensionnementRelative_.y;
	base_Fin.x *= redimensionnementRelative_.y;

	const double angle = utilitaire::DEG_TO_RAD(rotationRelative_[0]);

	//3pointDepart_.x = cos(angle) * (base_Debut.x) - sin(angle) * (base_Debut.y) + positionRelative_.x;
	//3pointDepart_.y = sin(angle) * (base_Debut.x) + cos(angle) * (base_Debut.y) + positionRelative_.y;

	//3pointFin_.x = cos(angle) * (base_Fin.x) - sin(angle) * (base_Fin.y) + positionRelative_.x;
	//3pointFin_.y = sin(angle) * (base_Fin.x) + cos(angle) * (base_Fin.y) + positionRelative_.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::mettreAjourPosition()
///
/// Cette fonction verifie si un objet NoeudMur est toujours sur la 
/// table apres un deplacement.
///
/// @param[in] deplacement : Coordonnees xyz du deplacement.
///
/// @return Vrai si l'objet est toujours sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
{	
	glm::dvec3 depart = this->getPointDepart();
	glm::dvec3 fin = this->getPointFin();
	depart = depart + deplacement;
	fin = fin + deplacement;
	bool reponse = false;
	if (depart[0] <= 48 && depart[0] >= -48 && depart[1] <= 24 && depart[1] >= -24
		&& 	fin[0] <= 48 && fin[0] >= -48 && fin[1] <= 24 && fin[1] >= -24 )
		reponse = true;
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMur::estDansLaTableApresScale(double scale)
///
/// Cette fonction verifie si un objet NoeudMur est toujours sur la 
/// table apres un redimensionnement.
///
/// @param[in] scale : Facteur de redimensionnement.
///
/// @return Vrai si l'objet est toujours sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::estDansLaTableApresScale(double scale)
{
	glm::dvec3 dimensionement = obtenirRedimensionnementRelative();
	double ancienneLongueur = dimensionement[0];
	double nouvelleLongueur = scale * dimensionement[0];

	glm::dvec3 pointDepart = this->getPointDepart();
	glm::dvec3 pointFin = this->getPointFin();

	glm::dvec3 position = this->obtenirPositionRelative();
	
	glm::dvec3 depart = position - ((pointFin - pointDepart) / ancienneLongueur) * (nouvelleLongueur / 2);
	glm::dvec3 fin = position + ((pointFin - pointDepart) / ancienneLongueur) * (nouvelleLongueur / 2);

	if (depart[0] <= 48 && depart[0] >= -48 && depart[1] <= 24 && depart[1] >= -24
		&& fin[0] <= 48 && fin[0] >= -48 && fin[1] <= 24 && fin[1] >= -24)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::tourner(double angle)
///
/// Cette fonction applique une rotation a un objet NoeudMur.
///
/// @param[in] angle : Angle de rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::tourner(double angle)
{
	double longueur = obtenirRedimensionnementRelative()[0];
	double rotation = obtenirRotationRelative()[0];
	glm::dvec3 position = obtenirPositionRelative();
	//3double demiLongeurFin = std::sqrt(std::pow((pointFin_[0] - position[0]), 2) + std::pow((pointFin_[1] - position[1]), 2));
	//3double demiLongeurDepart = std::sqrt(std::pow((pointDepart_[0] - position[0]), 2) + std::pow((pointDepart_[1] - position[1]), 2));
	
	glm::dvec3 depart;
	depart[0] = (longueur / 2.0) * std::sin(utilitaire::DEG_TO_RAD(angle));
	depart[1] = (longueur / 2.0) * std::cos(utilitaire::DEG_TO_RAD(angle));
	depart[2] = 0;

	double x = - std::sin( utilitaire::DEG_TO_RAD(rotation) ) * depart[0] + std::cos( utilitaire::DEG_TO_RAD(rotation) ) * depart[1];
	double y = std::cos( utilitaire::DEG_TO_RAD(rotation) ) * depart[0] + std::sin( utilitaire::DEG_TO_RAD(rotation) ) * depart[1];
	depart[0] = x;
	depart[1] = y;

	glm::dvec3 fin = - depart;
	depart = depart + position;
	fin = fin + position;
	this->assignerRotationRelative(this->obtenirRotationRelative() + glm::dvec4(angle, 0.0, 0.0, 0.0));
	//3pointDepart_ = depart;
	//3pointFin_ = fin;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMur::estDansLaTable()
///
/// Cette fonction verifie si un objet de type NoeudMur est sur la table.
///
/// @return Vrai si l'objet NoeudMur est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::estDansLaTable()
{
	glm::dvec3 depart = this->getPointDepart();
	glm::dvec3 fin = this->getPointFin();

	return utilitaire::rectangleDansUneZone(depart, fin, LARGEUR_MUR, LONGUEUR_TABLE, LARGEUR_TABLE);
	
	/*bool reponse = false;
	if (depart[0] <= 48 && depart[0] >= -48 && depart[1] <= 24 && depart[1] >= -24
		&& fin[0] <= 48 && fin[0] >= -48 && fin[1] <= 24 && fin[1] >= -24)
		reponse = true;
	return reponse;*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMur::dansLaTableSiSelectionne()
///
/// Cette fonction verifie si un objet de type NoeudMur est sur la table.
/// si il est selectionne
///
/// @return Vrai si l'objet NoeudMur est sur la table si il est selectionne, 
/// faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::dansLaTableSiSelectionne()
{
	bool reponse = true;
	if ( estSelectionne() )
	{
		if ( !estDansLaTable() )
			reponse = false;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::initialiserEnTraitement()
///
/// Cette fonction initialise des donnees d'un objet NoeudMur en 
/// traitement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::initialiserEnTraitement()
{
	initialiserPositionEnTraitement();
	pointDepartInitialEnTraitement_ = getPointDepart();
	pointFinInitialEnTraitement_ = getPointFin();
	rotationRelativeAvantraitement_ = obtenirRotationRelative();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::initialiserEnTraitement()
///
/// Cette fonction augmente la rotation relative d'un objet NoeudMur par
/// rapport a son parent.
///
/// @param[in] rotation : Angle incrementale.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::augmenterRotationRelative(double rotation)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::retournerAuScaleInitiale()
///
/// Cette fonction permet de reinitialiser le dimensionnement 
/// d'un objet NoeudMur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::retournerAuScaleInitiale()
{
	changerScale(obtenirScaleInitialeEnTraitement()[0]/obtenirRedimensionnementRelative()[0]);
}


void NoeudMur::attribuerCouleur()
{
	if (NoeudMur::compteurMur_ < 180)
	{
		couleurMur_[0] = 255 - NoeudMur::compteurMur_ + 1;
		couleurMur_[1] = 0;
		couleurMur_[2] = NoeudMur::compteurBlue_;
	}
	else
	{
		NoeudMur::compteurMur_ = 1;
		NoeudMur::compteurBlue_++;
		couleurMur_[0] = 255;
		couleurMur_[1] = 0;
		couleurMur_[2] = NoeudMur::compteurBlue_;
	}
}





////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction permet de vérifier si le noeud est selectionné 
///
/// @param[in] couleurObjet[] : Couleurs RGB du pixel.
///
/// @return booléan: true si le noeud est sélectionné ou false sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;

	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurMur_[0] && couleurObjet[1] == couleurMur_[1] && couleurObjet[2] == couleurMur_[2])
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
/// @fn void NoeudMur::effacerFantome()
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
void NoeudMur::effacerFantome()
{
	if (estFantome())
	{
		NoeudAbstrait::compteurMur_--;
	}
}



/*std::string NoeudMur::toString()
{
	std::string chaine = NoeudAbstrait::toString();
	/*glm::dvec3 pointDepart = getPointDepart();
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