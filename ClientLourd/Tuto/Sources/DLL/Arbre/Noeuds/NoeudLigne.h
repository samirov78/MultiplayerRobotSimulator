///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.h
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDLIGNE_H__
#define __ARBRE_NOEUDS_NOEUDLIGNE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudLigne
/// @brief Classe qui représente le noeud ligne
///
/// @author INF2990 Eq.11
/// @date 2016-02-12
///////////////////////////////////////////////////////////////////////////
class NoeudLigne : public NoeudComposite
{
public:
	/// Constructeur du noeud ligne
	NoeudLigne(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudLigne();

	/// Affiche le cube.
	virtual void afficherConcret(const bool& attribuerCouleur) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	/// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	///Methode permettant d'assigner une coordonnee de centre a un objet ligne.
	virtual void assignerCentre(glm::dvec3 centre);
	///Methode permettant la mise a jour du centre d'un objet ligne.
	virtual void mettreAjourCentre();
	/// permet d'assigner une rotation 
	void assignerRotation(double rotation);
	/// permet d'obtenir la rotation 
	double obtenirRotation();
	/// Efface les enfants fantomes.
	virtual void effacerFantome();
	std::string toString();


private:

	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	double angleRotation_{ 0.f };

	
	
};


#endif // __ARBRE_NOEUDS_NOEUDLIGNE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
