///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_MUR_H__
#define __ARBRE_NOEUDS_MUR_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMur
/// @brief Classe qui représente le noeud mur.
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudAbstrait
{
public:
	const double NoeudMur::LARGEUR_TABLE{ 48.0 };
	const double NoeudMur::LONGUEUR_TABLE{ 96.0 };
	const double NoeudMur::LARGEUR_MUR{ 0.25 };
	/// Constructeur du noeud mur
	NoeudMur(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMur();

	/// Affiche le cube.
	virtual void afficherConcret(const bool& attribuerCouleur) const;

	/// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	///Methode permettant la detection d'un clic sur le noeud.
	virtual bool clickToucheNoeud(glm::dvec3 point);

	virtual bool verifierSelection(GLubyte couleurObjet[]);

	///Methode permettant le redimensionnement du noeud.
	void changerScale(double scale);
	virtual void mettreAjourPosition();

	/// verifier si le noeud est dans la table
	bool estDansLaTableApresDeplacement(glm::dvec3 deplacement);
	/// verifier si le noeud est dans la table apres le scale 
	bool estDansLaTableApresScale(double scale);
	///Methode permettant d'effectuer une rotation a un objet de type mur.
	void tourner(double angle);
	///Methode permettant de verifier si l'objet de type mur est sur la table.
	bool estDansLaTable();
	///Methode permettant de verifier si l'objet de type mur est selectionne et sur la table.
	bool dansLaTableSiSelectionne();
	///Methode permettant d'initialiser des donnees d'un objet mur en traitement.
	void initialiserEnTraitement();
	///Methode permettant d'obtenir le point de depart initiale d'un objet de type mur en traitement.
	glm::dvec3 getPointDepartInitialEnTraitement() { return pointDepartInitialEnTraitement_; };
	///Methode permettant d'obtenir le point terminal initiale d'un objet de type mur en traitement.
	glm::dvec3 getPointFinInitialEnTraitement() { return pointFinInitialEnTraitement_; };
	///Methode permettant d'augmenter la l'angle de rotation d'un objet de type mur par rapport a son parent.
	void augmenterRotationRelative(double rotation);
	///Methode permettant de retourner au dimensionnement initiale d'un objet mur.
	void retournerAuScaleInitiale();
	/// Efface les enfants fantomes.
	virtual void effacerFantome();
	/// la chaine de caractere envoye au serveur
	//std::string toString();
	private:
	
		///Point de depart d'un noeud mur.
		glm::dvec3 pointDepartInitialEnTraitement_;
		///Point final d'un noeud mur.
		glm::dvec3 pointFinInitialEnTraitement_;
		/// Angle selon l'axe des X.
		float angleX_{ 0.f };
		/// Angle selon l'axe des Y.
		float angleY_{ 0.f };
		/// Angle de rotation.
		float angleRotation_{ 0.f };

		void attribuerCouleur();
		GLubyte couleurMur_[3];
		static int compteurBlue_;
		
};


#endif // __ARBRE_NOEUDS_MUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
