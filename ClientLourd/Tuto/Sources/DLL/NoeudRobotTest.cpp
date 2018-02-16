////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobotTest.cpp
/// @author Equipe 11
/// @date 2016-03-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudRobotTest.h"
#include "Arbre\ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "Arbre\Noeuds\NoeudTypes.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudRobotTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudRobotTest::setUp()
{
	noeudRobot_ = { new NoeudRobot{ ArbreRenduINF2990::NOM_ROBOT } };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobotTest::tearDown()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::testCoordonneesParRapportAOrigine()
///
/// Cas de test:  Permet de v�rifier si la conversion de points dans des r�ferentiels diff�rents est fonctionnelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobotTest::testCoordonneesParRapportAOrigine()
{
		
	glm::dvec2 positionOrigine(50.0, 50.0);
	
	// Cas 1 : Point reper� initialement par un rep�re R' centr� en (50.0, 50.0) et dont les axes sont perpendiculaires au rep�re R de base dont le centre est (0.0, 0.0)
		double theta = 0.0;
		glm::dvec2 point(5.0, 5.0);
	glm::dvec2 positionRetournee = noeudRobot_->coordonneesParRapportAOrigine(point, positionOrigine, theta);

		// On s'assure des bonnes coordonn�es de notre point par rapport au rep�re R
	CPPUNIT_ASSERT(positionRetournee.x == 55.0 && positionRetournee.y == 55.0);

	// Cas 2 : Point reper� initialement par un rep�re R' centr� en (50.0, 50.0) et dont les axes se situent � 90 degr�s du rep�re R de base centr� en (0.0, 0.0)
		theta = 90.0;
		positionRetournee = noeudRobot_->coordonneesParRapportAOrigine(point, positionOrigine, theta);
		// Formules de changement de base
			// positionRetournee.x = cos(theta) * point.x - sin(theta) * point.y + positionOrigine.x;
			//positionRetournee.y = sin(theta) * point.x + cos(theta) * point.y + positionOrigine.y;

		// On s'assure des bonnes coordonn�es de notre point par rapport au rep�re R
	CPPUNIT_ASSERT(positionRetournee.x == 45.0 && positionRetournee.y == 55.0);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::testObtenirNombreSenseursActifs()
///
/// Cas de test: Permet de v�rifier si le nombre de senseurs actifs est correct
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobotTest::testObtenirNombreSenseursActifs()
{
	// Cas 1:  On v�rifie qu'initialement, aucun senseur n'est actif
	CPPUNIT_ASSERT(noeudRobot_->obtenirNombreSenseursActifs() == 0);

	// Cas 2 : �valuation du nombre de senseurs actifs
		// Activation senseur extr�me gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(true);
		// Activation senseur gauche
		noeudRobot_->assignerSenseurDeLigneGauche(true);
		// R�activation senseur extr�me gauche 
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(true);

		int nombre; // renferme le nombre de senseurs actifs
		nombre = noeudRobot_->obtenirNombreSenseursActifs();

		// S'assurer que seuls les senseurs extr�me gauche et gauche sont actifs
	CPPUNIT_ASSERT(nombre == 2);

		// D�sactivation senseur extr�me gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(false);

		// S'assurer que seul le senseur gauche est actif
		nombre = noeudRobot_->obtenirNombreSenseursActifs();
	CPPUNIT_ASSERT(nombre == 1);

		// R�activation senseur extr�me gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(true);
		// Activation senseur central
		noeudRobot_->assignerSenseurDeLigneCentral(true);
		// Activation senseur droite
		noeudRobot_->assignerSenseurDeLigneDroite(true);
		// Activation senseur extr�me droite
		noeudRobot_->assignerSenseurDeLigneExtremeDroite(true);

		// S'assurer que tous les senseurs sont actifs 
		nombre = noeudRobot_->obtenirNombreSenseursActifs();
	CPPUNIT_ASSERT(nombre == 5);

		// D�sactivation senseur extr�me gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(false);
		// D�sactivation senseur gauche
		noeudRobot_->assignerSenseurDeLigneGauche(false);
		// D�sactivation senseur central
		noeudRobot_->assignerSenseurDeLigneCentral(false);
		// D�sactivation senseur droite
		noeudRobot_->assignerSenseurDeLigneDroite(false);
		// D�sactivation senseur extr�me droite
		noeudRobot_->assignerSenseurDeLigneExtremeDroite(false);

		// S'assurer que tous les senseurs sont inactifs 
		nombre = noeudRobot_->obtenirNombreSenseursActifs();
	CPPUNIT_ASSERT(nombre == 0);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////