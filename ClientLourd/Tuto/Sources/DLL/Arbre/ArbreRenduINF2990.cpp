///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "EtatOpenGL.h"
#include "Noeuds/NoeudTypes.h"


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
/// La chaîne représentant le type du robot.
const std::string ArbreRenduINF2990::NOM_ROBOT{ "robot" };
/// La chaîne représentant le type de la table
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La chaîne représentant le type de la flèche de départ
const std::string ArbreRenduINF2990::NOM_FLECHE{ "fleche" };
/// La chaîne représentant le type de la table
const std::string ArbreRenduINF2990::NOM_POTEAU{ "poteau" };
/// La chaîne représentant le type de le mur
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
/// La chaîne représentant le type de la ligne
const std::string ArbreRenduINF2990::NOM_LIGNE{ "ligne" };
/// La chaîne représentant le type du segment de ligne
const std::string ArbreRenduINF2990::NOM_SEGMENT{ "segment" };
/// La chaîne représentant le type de la roue gauche du robot
const std::string ArbreRenduINF2990::NOM_ROUE_GAUCHE{ "roue gauche" };
/// La chaîne représentant le type de la roue du robot
const std::string ArbreRenduINF2990::NOM_ROUE_DROITE{ "roue droite" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeud<NoeudAraignee>{ NOM_ARAIGNEE, std::string{ "media/spider.obj" } });
	ajouterUsine(NOM_CONECUBE, new UsineNoeud<NoeudConeCube>{ NOM_CONECUBE, std::string{ "media/cubecone.obj" } });
	ajouterUsine(NOM_ROBOT, new UsineNoeud<NoeudRobot>{ NOM_ROBOT, std::string{ "media/robot_sans_roue.obj" } });
	ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ "media/table.obj" } });
	ajouterUsine(NOM_FLECHE, new UsineNoeud<NoeudFleche>{ NOM_FLECHE, std::string{ "media/fleche.obj" } });
	ajouterUsine(NOM_POTEAU, new UsineNoeud<NoeudPoteau>{ NOM_POTEAU, std::string{ "media/poteau.obj" } });
	ajouterUsine(NOM_MUR, new UsineNoeud<NoeudMur>{ NOM_MUR, std::string{ "media/mur.obj" } });
	ajouterUsine(NOM_LIGNE, new UsineNoeud<NoeudLigne>{ NOM_LIGNE, std::string{ "" } });
	ajouterUsine(NOM_SEGMENT, new UsineNoeud<NoeudSegment>{ NOM_SEGMENT, std::string{ "media/segment.obj" } });
	ajouterUsine(NOM_ROUE_DROITE, new UsineNoeud<NoeudRoueDroite>{ NOM_ROUE_DROITE, std::string{ "media/roue.obj" } });
	ajouterUsine(NOM_ROUE_GAUCHE, new UsineNoeud<NoeudRoueGauche>{ NOM_ROUE_GAUCHE, std::string{ "media/roue.obj" } });
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	// Création du noeud de la table
	NoeudAbstrait* noeudTable{ creerNoeud(NOM_TABLE) };
	// Création des noeuds des murs invisibles des bords de la table
	NoeudAbstrait* noeudMurBordTable1{ creerNoeud(NOM_MUR) };
	NoeudAbstrait* noeudMurBordTable2{ creerNoeud(NOM_MUR) };
	NoeudAbstrait* noeudMurBordTable3{ creerNoeud(NOM_MUR) };
	NoeudAbstrait* noeudMurBordTable4{ creerNoeud(NOM_MUR) };
	

	
	noeudTable->ajouter(noeudMurBordTable1);
	noeudTable->ajouter(noeudMurBordTable2);
	noeudTable->ajouter(noeudMurBordTable3);
	noeudTable->ajouter(noeudMurBordTable4);
	

	// Emplacement relative de la table
	//noeudTable->assignerRotationRelative(glm::dvec4(90, 1.0, 0.0, 0.0));
	noeudTable->assignerPositionRelative(glm::dvec3(0.0, 0.0, -15.0));
	noeudTable->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));
	noeudTable->assignerEstEnregistrable(false);

	// Les 4 murs sont invisibles et non sélectionnable
	noeudMurBordTable1->assignerAffiche(false);
	noeudMurBordTable1->assignerEstSelectionnable(false);
	noeudMurBordTable1->assignerEstEnregistrable(false);

	noeudMurBordTable2->assignerAffiche(false);
	noeudMurBordTable2->assignerEstSelectionnable(false);
	noeudMurBordTable2->assignerEstEnregistrable(false);

	noeudMurBordTable3->assignerAffiche(false);
	noeudMurBordTable3->assignerEstSelectionnable(false);
	noeudMurBordTable3->assignerEstEnregistrable(false);

	noeudMurBordTable4->assignerAffiche(false);
	noeudMurBordTable4->assignerEstSelectionnable(false);
	noeudMurBordTable4->assignerEstEnregistrable(false);

	// Emplacement relative des 4 murs des bords de la table

	noeudMurBordTable1->assignerPositionRelative(glm::dvec3(0.0, -24.0, 0.0));
	noeudMurBordTable1->assignerRedimensionnementRelative(glm::dvec3(96.0, 1.0, 1.0));
	noeudMurBordTable2->assignerPositionRelative(glm::dvec3(0.0, 24.0, 0.0));
	noeudMurBordTable2->assignerRedimensionnementRelative(glm::dvec3(96.0, 1.0, 1.0));

	noeudMurBordTable3->assignerRotationRelative(glm::dvec4(90, 0.0, 0.0, 1.0));
	noeudMurBordTable4->assignerRotationRelative(glm::dvec4(90, 0.0, 0.0, 1.0));

	noeudMurBordTable3->assignerPositionRelative(glm::dvec3(-48.0, 0.0, 0.0));
	noeudMurBordTable3->assignerRedimensionnementRelative(glm::dvec3(48.0, 1.0, 1.0));
	noeudMurBordTable4->assignerPositionRelative(glm::dvec3(48.0, 0.0, 0.0));
	noeudMurBordTable4->assignerRedimensionnementRelative(glm::dvec3(48.0, 1.0, 1.0));

	glm::dvec3 point1 = glm::dvec3(-48.0, -24.0, 0.0);
	glm::dvec3 point2 = glm::dvec3(48.0, -24.0, 0.0);
	noeudMurBordTable1->setPoints(point1, point2);
	point1 = glm::dvec3(-48.0, 24.0, 0.0);
	point2 = glm::dvec3(48.0, 24.0, 0.0);
	noeudMurBordTable2->setPoints(point1, point2);
	point1 = glm::dvec3(-48.0, -24.0, 0.0);
	point2 = glm::dvec3(-48.0, 24.0, 0.0);
	noeudMurBordTable3->setPoints(point1, point2);
	point1 = glm::dvec3(48.0, -24.0, 0.0);
	point2 = glm::dvec3(48.0, 24.0, 0.0);
	noeudMurBordTable4->setPoints(point1, point2);
	
	assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));
	ajouter(noeudTable);
	if (!chargerFichierXMl_){
		NoeudAbstrait* noeudFleche = ajouterNouveauNoeud(NOM_TABLE, NOM_FLECHE);
		noeudFleche->assignerPositionRelative(glm::dvec3(44.0, 0.0, 1.0));
		noeudFleche->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));
	}

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
