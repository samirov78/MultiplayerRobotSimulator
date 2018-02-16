///////////////////////////////////////////////////////////////////////////
/// @file Debug.h
/// @author equipe INF2990-11
/// @date 2016-03-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once

#include "tinyxml2.h"
#include "utilitaire.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class Profil
/// @brief Classe qui représente le profil a adopter par le robot 
///
/// @author equipe INF2990-11
/// @date 2016-03-11
///////////////////////////////////////////////////////////////////////////

class Debug
{
public:

	/// Constructeur du noeud robot.
	Debug();
	/// Destructeur.
	~Debug() = default;
	/// permet de charger le bon profil
	void chargerParametresDebug();

	/// les gets des attribts
	bool getSortieConsole();
	bool getChangementComportement();
	bool getEtatEclairage();
	bool getSortieAlterationEffetsVisuel();
	bool getAfficherDetectionCapteurs();

	private:
		///Booleen representant les configuration du debugage affichage console.
		bool sortieConsole_;
		bool changementComportement_;
		bool etatEclairage_;
		bool sortieAlterationEffetsVisuel_;
		bool afficherDetectionCapteurs_;
	
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
