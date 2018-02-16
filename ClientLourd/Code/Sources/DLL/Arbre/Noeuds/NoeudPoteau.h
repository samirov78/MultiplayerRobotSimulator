///////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.h
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPOTEAU_H__
#define __ARBRE_NOEUDS_NOEUDPOTEAU_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudPoteau
/// @brief Classe qui représente un noeud poteau.
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudPoteau : public NoeudAbstrait
{
public:
	/// Constructeur du noeud poteau
	NoeudPoteau(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPoteau();

	/// Affiche le noeud poteau
	virtual void afficherConcret(const bool& attribuerCouleur) const;
	/// Effectue l'animation du noeud poteau
	virtual void animer(float temps);


	/// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	/// Methode permettant la detection d'un clic sur un noeud poteau.
	virtual bool clickToucheNoeud(glm::dvec3 point);
	/// permet de verifier si un mur a ete selectionn
	virtual bool verifierSelection(GLubyte couleurObjet[]);
	

	///Methode permettant le redimensionnement d'un noeud poteau.
	void changerScale(double scale);

	/// verifier si la noeud est dans la table apres le deplacement
	bool estDansLaTableApresDeplacement(glm::dvec3 deplacement);
	/// verifier si le noeud est dans la table apres le scale 
	bool estDansLaTableApresScale(double scale);
	///Methode permettant de verifier si un objet poteau est toujours sur la table.
	bool estDansLaTable();
	///Methode permettant de verifier si un objet poteau est dan la table si selectionne.
	bool dansLaTableSiSelectionne();
	///Methode permettant de reinitialiser le dimensionnement d'un objet poteau.
	void retournerAuScaleInitiale();
	/// Efface les enfants fantomes.
	virtual void effacerFantome();
	/// la chaine de caractere envoye au serveur
	//std::string toString();
private:
	/// Angle selon l'axe des X.
	////****float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	////****float angleY_{ 0.f };
	/// Angle de rotation.
	////****float angleRotation_{ 0.f };
	void attribuerCouleur();
	GLubyte couleurPoteau_[3];
	static int compteurRed_;
	
	//std::string chaineSelection; // pour contourner le probleme de Marshaling de char *
};



#endif // __ARBRE_NOEUDS_NOEUDPOTEAU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
