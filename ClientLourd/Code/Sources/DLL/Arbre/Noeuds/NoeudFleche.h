///////////////////////////////////////////////////////////////////////////
/// @file NoeudFleche.h
/// @author INF2990 - Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDFLECHE_H__
#define __ARBRE_NOEUDS_NOEUDFLECHE_H__

//#include "NoeudComposite.h"
#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudFleche
/// @brief Classe qui représente le noeud flèche
///
/// @author INF2990 - Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudFleche : public NoeudAbstrait
{
public:
	/// Constructeur du noeud flèche
	NoeudFleche(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudFleche();

	/// Affiche la flèche.
	virtual void afficherConcret(const bool& attribuerCouleur) const;
	///Detecte un clic de souris sur le noeud.
	virtual bool clickToucheNoeud(glm::dvec3 point);
	/// permet de 
	virtual bool verifierSelection(GLubyte couleurObjet[]);

	/// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	///Methode permettant de verifier si l'objet fleche est toujours sur la table.
	virtual bool estDansLaTable();
	///Methode permettant de verifier si un objet fleche est dans la table si selectionne.
	bool dansLaTableSiSelectionne();
	///Methode permettant d'effectuer une rotation a l'objet fleche.
	void tourner(double angle);
	/// la chaine de caractere envoye au serveur
	std::string toString();
//private:
//	//Angle selon l'axe des X.
//	float angleX_{ 0.f };
//	//Angle selon l'axe des Y.
//	float angleY_{ 0.f };
//	//Angle de rotation.
//	float angleRotation_{ 0.f };
	GLubyte couleurFleche_[3];
};


#endif // __ARBRE_NOEUDS_NOEUDFLECHE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
