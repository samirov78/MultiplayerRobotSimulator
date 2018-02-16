//////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobotTest.h
/// @author Equipe 11
/// @date 2016-03-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDROBOTTEST_H
#define _TESTS_NOEUDROBOTTEST_H
#include <cppunit\extensions\HelperMacros.h>

class NoeudRobot;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobotTest
/// @brief Classe qui effectue des tests sur le noeud robot.
///
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudRobotTest : public CppUnit::TestFixture
{
	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudRobotTest);
		CPPUNIT_TEST(testCoordonneesParRapportAOrigine);
	 	CPPUNIT_TEST(testObtenirNombreSenseursActifs);
	CPPUNIT_TEST_SUITE_END();
public:
	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: permet de v�rifier si au moins un senseur est actif 
	void testCoordonneesParRapportAOrigine();
	/// Cas de test: permet d'obtenir le nombre de senseurs actifs
	void testObtenirNombreSenseursActifs();

private:
	/// Instance d'un noeud robot
	NoeudRobot* noeudRobot_;
};

#endif // _TESTS_NOEUDROBOTTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////