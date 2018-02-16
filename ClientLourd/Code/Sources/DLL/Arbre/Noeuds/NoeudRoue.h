///////////////////////////////////////////////////////////////////////////
/// @file NoeudRoue.h
/// @author INF2990 Eq.11
/// @date 2016-02-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDROUE_H__
#define __ARBRE_NOEUDS_NOEUDROUE_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"
#include <algorithm>

/// La chaîne représentant le type des araignées.
const double VITESSE_MAX{ 100.0 };
const double RAYON_ROUE{ 2.5 };
const double LONG_ESSIEU{ 10.5 };


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRoue
/// @brief Classe qui représente un noeud roue.
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudRoue : public NoeudAbstrait
{
public:
	/// Constructeur du noeud roue
	NoeudRoue(const std::string& typeNoeud){};
	/// Destructeur.
	~NoeudRoue(){};

	/// Affiche le noeud NoeudRoue (n'affiche rien)
	virtual void afficherConcret(const bool& attribuerCouleur) const{};
	/// Effectue l'animation du noeud roue (aucune animation)
	virtual void animer(float dt){};


	/// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur){};
	///Methode permettant l'obtention de l'acceleration du robot.
	virtual double getAcceleration() const { return acceleration_; };
	///Methode permettant l'obtention de la vitesse du robot.
	virtual double getVitesse() const { return vitesse_; };
	///Methode permettant l'obtention de la direction du robot.
	virtual Direction getDirection() const { return direction_; };
	///Methode permettant l'obtention du rapport de vitesse du robot.
	virtual double getRapportVitesse() const { return rapportVitesse_; };
	///Methode permettant l'obtention de l'angle de rotation du robot.
	virtual double getAngleRotation() const { return angleRotation_; };
	///Methode permettant l'obtention de l'increment d'acceleration du robot.
	virtual double getIncrAcceleration() const { return incrAcceleration_; };
	///Methode permettant l'assignation de l'increment d'acceleration du robot.
	virtual void setIncrAcceleration(double incrAcceleration){ incrAcceleration_ = incrAcceleration; };
	///Methode permettant l'assignation de l'acceleration du robot.
	virtual void setAcceleration(double acceleration){ acceleration_ = acceleration; };
	///Methode permettant l'assignation de la vitesse du robot.
	virtual void setVitesse(double vitesse){ vitesse_ = vitesse; };
	///Methode permettant l'assignation de la direction du robot.
	virtual void setDirection(Direction direction){ direction_ = direction; };
	///Methode permettant l'assignation du rapport de vitesse du robot.
	virtual void setRapportVitesse(double rapportVitesse) { rapportVitesse_ = rapportVitesse; };


protected:
	///Acceleration du robot.
	double acceleration_{ 0.0 };
	///Vitesse du robot.
	double vitesse_{ 0.0 };
	///Rapport de vitesse du robot.
	double rapportVitesse_{ 0.0 };
	///Angle de rotation du robot.
	double angleRotation_{ 0.0 };
	///Direction du robot.
	Direction direction_{ FORWARD };
	///Increment d'acceleration du robot.
	double incrAcceleration_{ 1.0 };

	/// Angle selon l'axe des X.
	////****float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	////****float angleY_{ 0.f };
	/// Angle de rotation.
	////****float angleRotation_{ 0.f };
};



#endif // __ARBRE_NOEUDS_NOEUDROUEDROITE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
