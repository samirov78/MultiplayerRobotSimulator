///////////////////////////////////////////////////////////////////////////////
/// @file Avancer.h
/// @author Equipe 11
/// @date 2016-03-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ComportementAbstait.h"
//class NoeudRobot;

/* Classe sous etat de l'ètat "SuivideLigne".*/

class Avancer : public ComportementAbstrait
{
public:
	/// Constructeur par défaut.
	Avancer(NoeudRobot * contexte) :contexte_(contexte){};
	/// Destructeur.
	~Avancer() {};
	/// Effectuer un comportement.
	void executerComportement();
private:
	///Le robot en question.
	NoeudRobot * contexte_;


};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////