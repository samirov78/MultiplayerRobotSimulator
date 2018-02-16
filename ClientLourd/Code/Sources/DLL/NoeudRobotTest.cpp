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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test:  Permet de vérifier si la conversion de points dans des réferentiels différents est fonctionnelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobotTest::testCoordonneesParRapportAOrigine()
{
		
	glm::dvec2 positionOrigine(50.0, 50.0);
	
	// Cas 1 : Point reperé initialement par un repère R' centré en (50.0, 50.0) et dont les axes sont perpendiculaires au repère R de base dont le centre est (0.0, 0.0)
		double theta = 0.0;
		glm::dvec2 point(5.0, 5.0);
	glm::dvec2 positionRetournee = noeudRobot_->coordonneesParRapportAOrigine(point, positionOrigine, theta);

		// On s'assure des bonnes coordonnées de notre point par rapport au repère R
	CPPUNIT_ASSERT(positionRetournee.x == 55.0 && positionRetournee.y == 55.0);

	// Cas 2 : Point reperé initialement par un repère R' centré en (50.0, 50.0) et dont les axes se situent à 90 degrés du repère R de base centré en (0.0, 0.0)
		theta = 90.0;
		positionRetournee = noeudRobot_->coordonneesParRapportAOrigine(point, positionOrigine, theta);
		// Formules de changement de base
			// positionRetournee.x = cos(theta) * point.x - sin(theta) * point.y + positionOrigine.x;
			//positionRetournee.y = sin(theta) * point.x + cos(theta) * point.y + positionOrigine.y;

		// On s'assure des bonnes coordonnées de notre point par rapport au repère R
	CPPUNIT_ASSERT(positionRetournee.x == 45.0 && positionRetournee.y == 55.0);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::testObtenirNombreSenseursActifs()
///
/// Cas de test: Permet de vérifier si le nombre de senseurs actifs est correct
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobotTest::testObtenirNombreSenseursActifs()
{
	// Cas 1:  On vérifie qu'initialement, aucun senseur n'est actif
	CPPUNIT_ASSERT(noeudRobot_->obtenirNombreSenseursActifs() == 0);

	// Cas 2 : Évaluation du nombre de senseurs actifs
		// Activation senseur extrême gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(true);
		// Activation senseur gauche
		noeudRobot_->assignerSenseurDeLigneGauche(true);
		// Réactivation senseur extrême gauche 
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(true);

		int nombre; // renferme le nombre de senseurs actifs
		nombre = noeudRobot_->obtenirNombreSenseursActifs();

		// S'assurer que seuls les senseurs extrême gauche et gauche sont actifs
	CPPUNIT_ASSERT(nombre == 2);

		// Désactivation senseur extrême gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(false);

		// S'assurer que seul le senseur gauche est actif
		nombre = noeudRobot_->obtenirNombreSenseursActifs();
	CPPUNIT_ASSERT(nombre == 1);

		// Réactivation senseur extrême gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(true);
		// Activation senseur central
		noeudRobot_->assignerSenseurDeLigneCentral(true);
		// Activation senseur droite
		noeudRobot_->assignerSenseurDeLigneDroite(true);
		// Activation senseur extrême droite
		noeudRobot_->assignerSenseurDeLigneExtremeDroite(true);

		// S'assurer que tous les senseurs sont actifs 
		nombre = noeudRobot_->obtenirNombreSenseursActifs();
	CPPUNIT_ASSERT(nombre == 5);

		// Désactivation senseur extrême gauche
		noeudRobot_->assignerSenseurDeLigneExtremeGauche(false);
		// Désactivation senseur gauche
		noeudRobot_->assignerSenseurDeLigneGauche(false);
		// Désactivation senseur central
		noeudRobot_->assignerSenseurDeLigneCentral(false);
		// Désactivation senseur droite
		noeudRobot_->assignerSenseurDeLigneDroite(false);
		// Désactivation senseur extrême droite
		noeudRobot_->assignerSenseurDeLigneExtremeDroite(false);

		// S'assurer que tous les senseurs sont inactifs 
		nombre = noeudRobot_->obtenirNombreSenseursActifs();
	CPPUNIT_ASSERT(nombre == 0);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////