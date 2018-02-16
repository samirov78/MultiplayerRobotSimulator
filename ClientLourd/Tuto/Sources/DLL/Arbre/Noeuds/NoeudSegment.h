///////////////////////////////////////////////////////////////////////////
/// @file NoeudSegment.h
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_SEGMENT_H__
#define __ARBRE_NOEUDS_SEGMENT_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudSegment
/// @brief Classe qui représente un noeud segment.
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudSegment : public NoeudAbstrait
{
public:
	const double NoeudSegment::LARGEUR_LIGNE{ 0.75 };
	const double NoeudSegment::LARGEUR_TABLE{ 48.0 };
	const double NoeudSegment::LONGUEUR_TABLE{ 96.0 };
	
	/// Constructeur du noeud segment.
	NoeudSegment(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudSegment();

	/// Affiche le noeud segment
	virtual void afficherConcret(const bool& attribuerCouleur) const;

	/// appliquer l'algorithme du visiteur sur le noeud courant 
	void accepterVisiteur(VisiteurAbstrait* visiteur);
	///Methode permettant la detection d'un clic sur le noeud segment.
	virtual bool clickToucheNoeud(glm::dvec3 point);
	/// permet de verifier si un segment est selectionne
	virtual bool verifierSelection(GLubyte couleurObjet[]);

	/// verifier si la noeud est dans la table
	bool estDansLaTableApresDeplacement(glm::dvec3 deplacement);
	///Methode permettant de verifier si un objet de type segment est toujours sur la table.
	bool estDansLaTable();
	///Methode permettant de verifier si un objet de type segment est toujours sur la table.
	bool dansLaTableSiSelectionne();
	///Methode permettant d'initialiser des donnees d'un objet de type segment en traitement.
	void initialiserEnTraitement();
	///Methode permettant l'obtention du point de depart initial d'un objet de type segment.
	glm::dvec3 getPointDepartInitialEnTraitement() { return pointDepartInitialEnTraitement_; };
	///Methode permettant l'obtention du point final initial d'un objet de type segment.
	glm::dvec3 getPointFinInitialEnTraitement() { return pointFinInitialEnTraitement_; };
	/// permet de verifier si une ligne a ete touchee
	virtual void ligneTouchee(glm::dvec3 point, bool& estTouche);
	/// couleur du segment
	GLubyte couleurSegment_[3];
	std::string toString();
private:
	void attribuerCouleur();
	///Point de depart d'un noeud segment en traitement.
	glm::dvec3 pointDepartInitialEnTraitement_;
	///Point final d'un noeud segment en traitement.
	glm::dvec3 pointFinInitialEnTraitement_;
	/// Angle selon l'axe des X.
	/////float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	//////float angleY_{ 0.f };
	/// Angle de rotation.
	//////float angleRotation_{ 0.f };
	/*GLubyte couleurSegment_[3];*/
	
};


#endif // __ARBRE_NOEUDS_NOEUDSEGMENT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////