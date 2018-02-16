///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bissonobtenir
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

*/

#include <windows.h>
#include <cassert>
#include <iostream>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"

#include "VueOrtho.h"
#include "../../Commun/Utilitaire/Vue/VueOrbite.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include <cmath>
#include "ConfigScene.h"
#include "CompteurAffichage.h"

#include <vector>
#include <algorithm>

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml2.h"

#include "../Visiteur/VisiteurVersXML.h"
#include "../Visiteur/VisiteurSelectObjet.h"
#include "../Visiteur/VisiteurRotateSelection.h"
#include "../Visiteur/VisiteurScaleSelection.h"
#include "../Visiteur/VisiteurDeplacerSelection.h"
#include "../Visiteur/visiteurSelectElastique.h"
#include "../Visiteur/visiteurInitialisationPosition.h"
#include "../Visiteur/visiteurInitialisationScale.h"
#include "../Visiteur/visiteurDupliquerSelection.h"
#include "../Visiteur/visiteurDeterminerCentreSelection.h"
#include "../Visiteur/VisiteurVerifierDeplacementDuplication.h"
#include "../Visiteur/VisiteurAnnulerRotationSelection.h"
#include "../Visiteur/visiteurRotationUnObjet.h"
#include "../Visiteur/visiteurVerifierCollision.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

int FacadeModele::compteurZoom_ = 0;
int FacadeModele::compteurAjouts = 0;
/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };



////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new FacadeModele;
	}
	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
/// @author equipe 11 INF2990 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
/// @author equipe 11 INF2990 
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	if (arbre_ != nullptr)
		delete arbre_;
	if (vueOrbite_ != nullptr)
		delete vueOrbite_;
	if (vueOrtho_ != nullptr)
		delete vueOrtho_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::	initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	// assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	//*******chargerConfiguration();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumières
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Lumière ambiante "globale"
	// Attention :
	//La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glm::vec4 ambiant{ 0.2f, 0.2, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));

	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;

	NoeudAbstrait::compteurPoteau_ = 0;
	NoeudAbstrait::compteurMur_ = 0;
	NoeudAbstrait::compteurLigne_ = 0;

	arbre_->initialiser();
	vueOrtho_ = new vue::VueOrtho{
		vue::Camera{ 
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0), false},
		vue::ProjectionOrtho{ 
				0, 500, 0, 500,
				1, 1000, 1, 10000, 1.25,
				-25, 25, -25, 25 }
	};
	// On crée une vue par défaut.
	vue_ = vueOrtho_;

	vueOrbite_ = new vue::VueOrbite
	{
		vue::Camera{
		//				z
		//				|  
		//				| 
		//				|------x
		//				 \
					//			      \
					//			       -y
		glm::dvec3(0, -200, 200), glm::dvec3(0, 0, 0),
		glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0), true },
		vue::ProjectionPerspective{
			0, 500, 0, 500,
			1, 1000, 1, 10000, 1.25,
			-25, 25, -25, 25 }, false
	};

	//std::cout << "FacadeModel->initialiserOpenGL" << std::endl;

	//std::cout << modeApplication_ << std::endl;

	if (modeApplication_ == 'S')
	{
		skyboxSimulation[0] = "Media/skybox/desert/posx.jpg";
		skyboxSimulation[1] = "Media/skybox/desert/negx.jpg";
		skyboxSimulation[2] = "Media/skybox/desert/negz.jpg";
		skyboxSimulation[3] = "Media/skybox/desert/posz.jpg";
		skyboxSimulation[4] = "Media/skybox/desert/negy.jpg";
		skyboxSimulation[5] = "Media/skybox/desert/posy.jpg";
		skybox_ = new utilitaire::BoiteEnvironnement(skyboxSimulation[0], skyboxSimulation[1], skyboxSimulation[2],
			skyboxSimulation[3], skyboxSimulation[4], skyboxSimulation[5]);
	}
	else if (modeApplication_ == 'T')
	{
		skyboxSimulation[0] = "Media/skybox/skansen/posx.jpg";
		skyboxSimulation[1] = "Media/skybox/skansen/negx.jpg";
		skyboxSimulation[2] = "Media/skybox/skansen/negz.jpg";
		skyboxSimulation[3] = "Media/skybox/skansen/posz.jpg";
		skyboxSimulation[4] = "Media/skybox/skansen/negy.jpg";
		skyboxSimulation[5] = "Media/skybox/skansen/posy.jpg";
		skybox_ = new utilitaire::BoiteEnvironnement(skyboxSimulation[0], skyboxSimulation[1], skyboxSimulation[2],
			skyboxSimulation[3], skyboxSimulation[4], skyboxSimulation[5]);
	}
	
	typeVue_ = ORTHO;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les différentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);

	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// Écrire la déclaration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les différentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// Écrire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();
	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };

	assert(succes && "Le contexte OpenGL n'a pu être détruit.");
	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher(double temps) const
{
	if (!rectangleElastiqueTrace_){
		// Efface l'ancien rendu
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Ne devrait pas être nécessaire
		vue_->appliquerProjection();

		// Positionne la caméra
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		vue_->appliquerCamera();

		// Afficher la scène
		afficherBase();

		//texte_->afficher("Mehdi");
	
		afficherProfilEtChrono(temps);
		// Compte de l'affichage
		utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

		// Échange les tampons pour que le résultat du rendu soit visible.
		::SwapBuffers(hDC_);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	if (lumiereAmbiante_)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	if (lumiereDirectionnelle_)
	{
		glEnable(GL_LIGHT2);
	}
	else
	{
		glDisable(GL_LIGHT2);
	}

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };
	glm::vec4 contributionFaible{ 0.15, 0.15, 0.15, 1.0 };
	glm::vec4 const positionAmbiante{ 0, 0, 70, 0 };
	glm::vec4 const positionDirectionnelle{ -60, -60, 70, 0 };


	GLfloat spotRobotContributionAmbiante[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat spotRobotContributionDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat spotRobotContributionSpeculaire[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat spotDirection[] = { 0.0f, 0.0f, -1.0f };

	const GLfloat* spotExponent = new GLfloat(10);
	const GLfloat* spotCutOffGyrophare = new GLfloat(50);
	glm::vec3 spotGyrophareDirection{ glm::cos(utilitaire::DEG_TO_RAD(0.72 * millisecondes_)), glm::sin(utilitaire::DEG_TO_RAD(0.72 * millisecondes_)), -1.0 };
	glm::vec4 const contributionGyrophare{ 1.0, 0.0, 0.0, 1.0 };

	// lumiere ambiante
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(positionAmbiante));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	//glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(contributionFaible));
	// On sature les objets de lumière
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionFaible));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));


	// lumiere directionnelle
	glLightfv(GL_LIGHT2, GL_POSITION, glm::value_ptr(positionDirectionnelle));
	//glLightfv(GL_LIGHT2, GL_AMBIENT, glm::value_ptr(contributionFaible));
	glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	glLightfv(GL_LIGHT2, GL_SPECULAR, glm::value_ptr(contributionMaximale));


	if (leRobot_ != nullptr){

		//glm::dvec3 positionRobot = leRobot_->obtenirPositionRelative();
		glm::dvec3 positionRobot = leRobot_->getPositionSpot_();
		GLfloat spotPosition[] = { GLfloat(positionRobot.x), GLfloat(positionRobot.y), 40.0f, 1.0f };
	
		if (leRobot_->getSpotsActives())
		{
			glEnable(GL_LIGHT1);
		}
		else 
		{
			glDisable(GL_LIGHT1);
		}
		
		glLightfv(GL_LIGHT1, GL_POSITION, spotPosition);
		glLightfv(GL_LIGHT1, GL_AMBIENT, spotRobotContributionAmbiante);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, spotRobotContributionDiffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spotRobotContributionSpeculaire);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128.0);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 9.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);

		if (!leRobot_->getModeAutomatique() && leRobot_->getSpotsActives())
		{
			glEnable(GL_LIGHT4);
		}
		else
		{
			glDisable(GL_LIGHT4);
		}

		glm::vec4 positionGyrophare{ positionRobot.x, positionRobot.y, -8.0, 1 };

		glLightfv(GL_LIGHT4, GL_POSITION, glm::value_ptr(positionGyrophare));
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, glm::value_ptr(spotGyrophareDirection));
		glLightfv(GL_LIGHT4, GL_AMBIENT, glm::value_ptr(contributionGyrophare));
		glLightfv(GL_LIGHT4, GL_DIFFUSE, glm::value_ptr(contributionGyrophare));
		glLightfv(GL_LIGHT4, GL_SPECULAR, glm::value_ptr(contributionGyrophare));
		glLightfv(GL_LIGHT4, GL_SPOT_EXPONENT, spotExponent);
		glLightfv(GL_LIGHT4, GL_SPOT_CUTOFF, spotCutOffGyrophare);

	}

	glm::dvec3 positionCamera = vue_->obtenirCamera().obtenirPosition();


	// afficher la boite d'environnement
	//skybox_->afficher(glm::dvec3(0.0, 0.0, 0.0), 120);
	if (skybox_ != nullptr)
		skybox_->afficher(glm::dvec3(positionCamera.x, positionCamera.y, positionCamera.z), 250);

	bool attribuerCouleur = false;
	if (modeApplication_ == 'E')
		attribuerCouleur = true;
	// Afficher la scène.
	arbre_->afficher(attribuerCouleur);


	double phiCam = vue_->obtenirCamera().obtenirPhiCam();
	double thetaCam = vue_->obtenirCamera().obtenirThetaCam();
	//std::cout << phiCam << " " << thetaCam << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	NoeudAbstrait::compteurPoteau_ = 0;
	NoeudAbstrait::compteurMur_ = 0;
	NoeudAbstrait::compteurLigne_ = 0;
	arbre_->initialiser();
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::verifierCurseur(int x, int y)
///
/// Cette fonction permet de vérifier si le curseur est dans la limite
///	des dimensions de la table.
///
/// @param[in] x : Position en coordonnées de cloture en x.
///
/// @param[in] y : Position en coordonnées de cloture en y.
///
/// @return Faux si le curseur est en dehors des dimensions de la table,
///			vrai autrement.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::verifierCurseur(int x, int y)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);
	bool estDansLimites = utilitaire::DANS_LIMITESXY(point.x, -48, 48, point.y, -24, 24);
	return estDansLimites;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::verifierCursorPoteau(int x, int y)
///
/// Methode permettant la verification de la position du curseur pour
/// l'edition du poteau
/// 
/// @param[in] x : Position x de la souris en coordonnee de cloture.
/// 
/// @param[in] y : Position y de la souris en coordonnee de cloture.
/// 
/// @return Vrai lorsque le curseur est dans la bonne position pour editer
/// un poteau, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::verifierCurseurPoteau(int x, int y)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);
	bool estDansLimites = utilitaire::DANS_LIMITESXY(point.x - RAYON_POTEAU, -48, 48, point.y - RAYON_POTEAU, -24, 24)
		&& utilitaire::DANS_LIMITESXY(point.x + RAYON_POTEAU, -48, 48, point.y + RAYON_POTEAU, -24, 24);
	return estDansLimites;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin)
///
/// Methode permettant la verification de la position du curseur pour
/// l'edition d'un mur
/// 
/// @param[in] x : Position x de la souris en coordonnee de cloture.
/// 
/// @param[in] y : Position y de la souris en coordonnee de cloture.
/// 
/// @return Vrai lorsque le curseur est dans la bonne position pour tracer
/// un mur, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin)
{
	if (xDebut == xFin && yDebut == yFin)
		return true;
	else
	{
		glm::dvec3 pointDebut, pointFin;
		vue_->convertirClotureAVirtuelle(xDebut, yDebut, pointDebut);
		vue_->convertirClotureAVirtuelle(xFin, yFin, pointFin);

		return utilitaire::rectangleDansUneZone(pointDebut, pointFin, LARGEUR_MUR, LONGUEUR_TABLE, LARGEUR_TABLE);
		/*glm::dvec3 vecteurDirecteur = utilitaire::vecteurUnitaire(pointFin - pointDebut);
		
		glm::dvec3 point1 = vecteurDirecteur;
		rotaterPointAutourDecentre(0, 0, 90, point1);
		point1 = point1 * (LARGEUR_MUR / 2.0);
		glm::dvec3 point2 = -point1;

		glm::dvec3 point3 = vecteurDirecteur;
		rotaterPointAutourDecentre(0, 0, 90, point3);
		point3 = point3 * (LARGEUR_MUR / 2.0);
		glm::dvec3 point4 = -point3;
		
		point1 = point1 + pointDebut;
		point2 = point2 + pointDebut;
		point3 = point3 + pointFin;
		point4 = point4 + pointFin;
		
		bool point1DansLaTable = utilitaire::DANS_LIMITESXY(point1.x, -48, 48, point1.y, -24, 24);
		bool point2DansLaTable = utilitaire::DANS_LIMITESXY(point2.x, -48, 48, point2.y, -24, 24);
		bool point3DansLaTable = utilitaire::DANS_LIMITESXY(point3.x, -48, 48, point3.y, -24, 24);
		bool point4DansLaTable = utilitaire::DANS_LIMITESXY(point4.x, -48, 48, point4.y, -24, 24);
		
		return (point1DansLaTable && point2DansLaTable && point3DansLaTable && point4DansLaTable);*/
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin)
///
/// Methode permettant la verification de la position du curseur pour
/// l'edition d'une ligne
/// 
/// @param[in] x : Position x de la souris en coordonnee de cloture.
/// 
/// @param[in] y : Position y de la souris en coordonnee de cloture.
/// 
/// @return Vrai lorsque le curseur est dans la bonne position pour tracer
/// une ligne, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin)
{
	if (xDebut == xFin && yDebut == yFin)
		return true;
	else
	{
		glm::dvec3 pointDebut, pointFin;
		vue_->convertirClotureAVirtuelle(xDebut, yDebut, pointDebut);
		vue_->convertirClotureAVirtuelle(xFin, yFin, pointFin);

		return utilitaire::rectangleDansUneZone(pointDebut, pointFin, LARGEUR_LIGNE, LONGUEUR_TABLE, LARGEUR_TABLE);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimerDernierNoeud()
///
/// Cette fonction permet de supprimer le dernier noeud ajouté à 
///	la table.

/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerDernierNoeud()
{
	if (dernierNoeudEnfantAjoute_ != nullptr)
	{
		if (dernierNoeudEnfantAjoute_->obtenirType() == arbre_->NOM_MUR)
		{
			NoeudAbstrait::compteurMur_--;
		}
		arbre_->chercher(arbre_->NOM_TABLE)->effacer(dernierNoeudEnfantAjoute_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimerDerniereLigne()
///
/// Cette fonction permet de supprimer la dernière ligne ajouté à la
///	table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerDerniereLigne()
{
	if (dernierNoeudCompositeAjoute_ != nullptr)
	{
		dernierNoeudCompositeAjoute_->vider();
	}
	arbre_->chercher(arbre_->NOM_TABLE)->effacer(dernierNoeudCompositeAjoute_);
	NoeudAbstrait::compteurLigne_--;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec3 FacadeModele::calculerDimensions(double& longueur, double& angle, const glm::dvec3& point1, const glm::dvec3& point2)
///
/// Cette fonction permet de calculer les dimensions d'un segment de ligne.
///
/// @param[in, out] longueur	: Longueur du segment de ligne tracé
///
/// @param[in, out] angle		: Angle du segment
///
/// @param[in]		point1		: Coordonnées x,y du premier point du segment
///
/// @param[in]		point2		: Coordonnées x,y du second point du segment
///
/// @return Un vecteur x,y,z de double représentant le centre.
///
////////////////////////////////////////////////////////////////////////

glm::dvec3 FacadeModele::calculerDimensions(double& longueur, double& angle, const glm::dvec3& point1, const glm::dvec3& point2)
{
	glm::dvec3 centre;
	centre.x = 0.5 * (point1.x + point2.x);
	centre.y = 0.5 * (point1.y + point2.y);
	longueur = std::sqrt((point2.x - point1.x)*(point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
	angle = utilitaire::PI / 2.0;
	if (!utilitaire::EGAL_ZERO(point2.x - point1.x))
	{
		angle = std::atan((point2.y - point1.y) / (point2.x - point1.x));
	}
	angle = utilitaire::RAD_TO_DEG(angle);
	return centre;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::calculerPointsSegment(const double& longueur, const double& angle, const glm::dvec3& centre, glm::dvec3& point1, glm::dvec3& point2)
///
/// Cette fonction permet de calculer les quatres points associés à un segment.
///
/// @param[in]		longueur	: Longueur du segment de ligne tracé
///
/// @param[in]		angle		: Angle du segment
///
/// @param[in]		centre		: Coordonnées x,y du centre segment
///
/// @param[in,out]	point1		: Coordonnées x,y du second point du segment
///
/// @param[in,out]	point2		: Coordonnées x,y du second point du segment
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::calculerPointsSegment(const double& longueur, const double& angle, const glm::dvec3& centre, glm::dvec3& point1, glm::dvec3& point2)
{
	point1.x = centre.x - 0.5 * longueur * std::cos(utilitaire::DEG_TO_RAD(angle));
	point1.y = centre.x - 0.5 * longueur * std::sin(utilitaire::DEG_TO_RAD(angle));
	point2.x = centre.x + 0.5 * longueur * std::cos(utilitaire::DEG_TO_RAD(angle));
	point2.y = centre.x + 0.5 * longueur * std::sin(utilitaire::DEG_TO_RAD(angle));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::calculerPointsSegment(const double& longueur, const double& angle, const glm::dvec3& centre, glm::dvec3& point1, glm::dvec3& point2)
///
/// Cette fonction permet l'ajout d'un noeud à l'arbre de rendu
///
/// @param[in]		nom		: Nom du noeud à ajouté à l'arbre de rendu.
///
/// @param[in]		x		: Position x en coordonnée de cloture.
///
/// @param[in]		y		: Position y en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::ajouterNoeudSimple(char* nom, int x, int y, bool enLigne, char* id)
{
	chaineDeSauvegarde = "";
	glm::dvec3 point;
	std::string idString(id);
	vue_->convertirClotureAVirtuelle(x, y, point);
	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, nom, idString);
	//noeud->ID = id;
	if (std::string(nom) == arbre_->NOM_POTEAU)
	{
		dernierNoeudEnfantAjoute_ = noeud;
		noeud->assignerPositionRelative(glm::dvec3(point.x, point.y, 5.0));
		noeud->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));
		noeud->assignerRotationRelative(glm::dvec4(0, 0, 0, 1));
		//NoeudPoteau* poteau = new NoeudPoteau(arbre_->NOM_POTEAU);// memory leak
		//mettre a jour l ID du poteau
		//int nombrePoteaux = obtenirNbreNoeudsParType(arbre_->NOM_POTEAU);
		//****noeud->ID = "P" + std::to_string(noeud->compteurPoteau_);
		//noeud->ID = id;
		//****chaineDeSauvegarde = ((NoeudPoteau*)noeud)->toString();
		//****std::cout << "poteaux numero :" << noeud->ID << std::endl;
	}
	else
	{
		dernierNoeudCompositeAjoute_ = noeud;
		noeud->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
		noeud->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));
		angleDernierSegment_ = 0.0;
	}
	noeud->mettreAjourCentre();
	chaineDeSauvegarde = noeud->toString();
	//if (enLigne)
	//	arbre_->effacer(noeud);
	return chaineDeSauvegarde.c_str();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeudAvecScale(char* nom, int x1, int y1, int x2, int y2)
///
/// Cette fonction permet l'ajout d'un noeud à l'arbre de rendu avec
///	un certain redimensionnement.
///
/// @param[in]		nom		: Nom du noeud à ajouté à l'arbre de rendu.
///
/// @param[in]		x1		: Position x du premier point en coordonnée de cloture.
///
/// @param[in]		y1		: Position y du premier point en coordonnée de cloture.
///
/// @param[in]		x2		: Position x du second point en coordonnée de cloture.
///
/// @param[in]		y2		: Position y du second point en coordonnée de cloture.
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::ajouterNoeudAvecScale(char* nom, int x1, int y1, int x2, int y2, 
	bool estConcret, bool enLigne, char* id)
{
	std::string idString(id);
	glm::dvec3 point1, point2;
	double longueurObjet, angleObjet;
	vue_->convertirClotureAVirtuelle(x1, y1, point1);
	vue_->convertirClotureAVirtuelle(x2, y2, point2);
	glm::dvec3 centre = calculerDimensions(longueurObjet, angleObjet, point1, point2);

	if (std::string(nom) == arbre_->NOM_SEGMENT)
	{
		if (dernierNoeudCompositeAjoute_->obtenirNombreEnfants() >= 1)
		{
			double deltateta = std::abs(angleObjet - angleDernierSegment_);
			double deplacement = 0.5 * LARGEUR_LIGNE * std::abs(std::sin(utilitaire::DEG_TO_RAD(180 - deltateta)));
			double coefCorrection = 1.0;
			if ((deltateta > 20 && deltateta < 45) || (deltateta >= 70 && deltateta < 85) ||
				(deltateta >= 95 && deltateta < 110) || (deltateta >= 130 && deltateta < 150))
			{
				coefCorrection = 0.95;
			}
			else if ((deltateta >= 45 && deltateta < 70) || (deltateta >= 110 && deltateta < 130))
			{
				coefCorrection = 0.90;
			}
			if (point1.x < point2.x)
			{
				point1.x = point1.x - coefCorrection * deplacement * std::cos(utilitaire::DEG_TO_RAD(angleObjet));
				point1.y = point1.y - coefCorrection * deplacement * std::sin(utilitaire::DEG_TO_RAD(angleObjet));
			}
			else
			{
				point1.x = point1.x + coefCorrection * deplacement * std::cos(utilitaire::DEG_TO_RAD(angleObjet));
				point1.y = point1.y + coefCorrection * deplacement * std::sin(utilitaire::DEG_TO_RAD(angleObjet));
			}
			centre = calculerDimensions(longueurObjet, angleObjet, point1, point2);
		}
	}
	NoeudAbstrait* noeud;
	if (std::string(nom) != arbre_->NOM_SEGMENT)
	{
		noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, nom, idString);
		noeud->assignerPositionRelative(glm::dvec3(centre.x, centre.y, 1.0));
		noeud->assignerRedimensionnementRelative(glm::dvec3(longueurObjet, 1.0, 1.0));
		noeud->assignerRotationRelative(glm::dvec4(angleObjet, 0.0, 0.0, 1.0));
		noeud->mettreAjourCentre();
		noeud->setPoints(point1, point2);
		chaineDeSauvegarde = noeud->toString();
		//si c un noeudMur mettre a jour l ID du Mur
		/*if (noeud->obtenirType() == arbre_->NOM_MUR)
		{
			noeud->ID = "M" + std::to_string(noeud->compteurMur_);
		}*/
		/*std::cout << "Type mur: " << noeud->obtenirType();*/
	}
	else
	{
		noeud = arbre_->creerNoeud(nom);
		noeud->ID = idString;
		noeud->assignerPositionRelative(glm::dvec3(centre.x, centre.y, 1.0));
		noeud->assignerRedimensionnementRelative(glm::dvec3(longueurObjet, 1.0, 1.0));
		noeud->assignerRotationRelative(glm::dvec4(angleObjet, 0.0, 0.0, 1.0));
		//if (!enLigne)
		{
			dernierNoeudCompositeAjoute_->ajouter(noeud);
			dernierNoeudCompositeAjoute_->mettreAjourCentre();
			noeud->setPoints(point1, point2);
			if (estConcret)
			{
				angleDernierSegment_ = angleObjet;
				dernierNoeudEnfantConcretAjoute_ = noeud;
			}
		}
		/*else
		{
			NoeudAbstrait* ligne = GetNodeByID(idString);
			ligne->ajouter(noeud);
			ligne->mettreAjourCentre();
			noeud->setPoints(point1, point2);
			chaineDeSauvegarde = ligne->toString();
			if (estConcret)
			{
				angleDernierSegment_ = angleObjet;
				dernierNoeudEnfantConcretAjoute_ = noeud;
			}
		}*/
		chaineDeSauvegarde = dernierNoeudCompositeAjoute_->toString();
	}
	dernierNoeudEnfantAjoute_ = noeud;
	//if (enLigne && std::string(nom) != arbre_->NOM_SEGMENT)
	//	arbre_->effacer(noeud);
	//std::cout << "Chaine de sauvegarde : " << chaineDeSauvegarde << std::endl;
	return chaineDeSauvegarde.c_str();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerZoneDeSimulation(char* nomFichier)
///
/// Cette fonction la sauvegarde de la zone de simulation dans un fichier XML
///
/// @param[in]		nomFichier		: Nom du fichier dans lequel la sauvegarde sera effectuée. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerZoneDeSimulation(char* nomFichier)
{
	tinyxml2::XMLDocument document;
	// Écrire la déclaration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	// Créer le noeud 'configuration'
	tinyxml2::XMLElement* elementConfiguration{ document.NewElement("configuration") };

	// Créer le noeud scene et définir ses attributs
	tinyxml2::XMLElement* elementScene{ document.NewElement("CScene") };
	elementScene->SetAttribute("CALCULS_PAR_IMAGE", ConfigScene::CALCULS_PAR_IMAGE);

	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementScene);

	// http://stackoverflow.com/questions/8162207/xml-document-cannot-contain-multiple-root-level-elements

	// creation du visiteur
	VisiteurVersXML* visiteurXML = new VisiteurVersXML(&document, elementScene);

	// parcours de l'arbre et application de l'algorithme en fonction
	arbre_->accepterVisiteur(visiteurXML);

	
	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de libérer la mémoire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	document.LinkEndChild(elementConfiguration);

	// Écrire dans le fichier
	document.SaveFile(nomFichier);
	delete visiteurXML;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerZoneDeSimulation(char* nomFichier)
///
/// Cette fonction permet le chargement de la zone de simulation à partir d'un fichier XML.
///
/// @param[in]		nomFichier		: Nom du fichier depuis lequel le chargement sera effectuée. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerZoneDeSimulation(char* nomFichier)
{
	NoeudAbstrait::compteurPoteau_ = 0;
	NoeudAbstrait::compteurMur_ = 0;
	NoeudAbstrait::compteurLigne_ = 0;
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(nomFichier)) {
		enregistrerZoneDeSimulation(nomFichier);
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(nomFichier);

		// On lit les différentes configurations.
		// ConfigScene::obtenirInstance()->lireDOM(document);
		int elementApresScene = 0;

		// Tenter d'obtenir le noeud 'Configuration'
		const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
		if (elementConfiguration != nullptr) {
			// Tenter d'obtenir l'élément CScene, puis l'attribut CALCULS_PAR_IMAGE
			const tinyxml2::XMLElement* elementScene{ elementConfiguration->FirstChildElement("CScene") };
			if (elementScene != nullptr) {
				if (elementScene->QueryIntAttribute("CALCULS_PAR_IMAGE", &ConfigScene::CALCULS_PAR_IMAGE) != tinyxml2::XML_SUCCESS){
					std::cerr << "Erreur : CALCULS_PAR_IMAGE : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
				}
				
	// source :: http://stackoverflow.com/questions/15606842/getting-the-child-elements-in-tinyxml2 //  fonctionne environ comme ca !
				arbre_->chargerFichierXMl_ = true; 

				arbre_->initialiser();

				arbre_->chargerFichierXMl_ = false; 

				//while (elementXMLCourantLecture_ != NULL){
				for (const tinyxml2::XMLElement* elementXMLCourantLecture_ = elementScene->FirstChildElement();
					elementXMLCourantLecture_ != NULL;
					elementXMLCourantLecture_ = elementXMLCourantLecture_->NextSiblingElement())
				{
					// traitement du noeud courant
					bool affiche, enregistrable, selectionnable/*, selectionne*/;
					const char* typeNoeud;
					const char*  id;

					typeNoeud = elementXMLCourantLecture_->Value();
					/////****elementXMLCourantLecture_->
					std::string typeNoeudString(typeNoeud);

					if (typeNoeudString == arbre_->NOM_LIGNE) {

						NoeudAbstrait* noeudLigne = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, typeNoeudString);
						dernierNoeudCompositeAjoute_ = noeudLigne;
						//dernierNoeudEnfantAjoute_ = noeudLigne;

						glm::dvec3 PositionRelative;
						elementXMLCourantLecture_->QueryDoubleAttribute("Pos_x", &PositionRelative[0]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Pos_y", &PositionRelative[1]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Pos_z", &PositionRelative[2]);

						elementXMLCourantLecture_->QueryBoolAttribute("Affiche", &affiche);
						elementXMLCourantLecture_->QueryBoolAttribute("Enregistrable", &enregistrable);
						elementXMLCourantLecture_->QueryBoolAttribute("Selectionnable", &selectionnable);
						id = elementXMLCourantLecture_->Attribute("ID");


						glm::dvec4 RotatioRelative;
						elementXMLCourantLecture_->QueryDoubleAttribute("Angle", &RotatioRelative[0]);
						elementXMLCourantLecture_->QueryDoubleAttribute("x", &RotatioRelative[1]);
						elementXMLCourantLecture_->QueryDoubleAttribute("y", &RotatioRelative[2]);
						elementXMLCourantLecture_->QueryDoubleAttribute("z", &RotatioRelative[3]);


						glm::dvec3 RedimensionnementRelative;
						elementXMLCourantLecture_->QueryDoubleAttribute("Redim_x", &RedimensionnementRelative[0]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Redim_y", &RedimensionnementRelative[1]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Redim_z", &RedimensionnementRelative[2]);


						noeudLigne->assignerPositionRelative(PositionRelative);
						noeudLigne->assignerRedimensionnementRelative(RedimensionnementRelative);
						noeudLigne->assignerRotationRelative(RotatioRelative);

						noeudLigne->assignerAffiche(affiche);
						noeudLigne->assignerEstSelectionnable(selectionnable);
						noeudLigne->assignerEstEnregistrable(enregistrable);
						noeudLigne->ID = id;

					
						// lecture des segments 
						for (const tinyxml2::XMLElement* elementXMLSegment_ = elementXMLCourantLecture_->FirstChildElement();
							elementXMLSegment_ != NULL;
							elementXMLSegment_ = elementXMLSegment_->NextSiblingElement())
						{
							const char* typeNoeudSegment;
							typeNoeudSegment = elementXMLSegment_->Value();
							/////****elementXMLCourantLecture_->
							std::string typeNoeudStringSegment(typeNoeudSegment);

							///////////////////

							glm::dvec3 PositionRelativeSegment;
							elementXMLSegment_->QueryDoubleAttribute("Pos_x", &PositionRelativeSegment[0]);
							elementXMLSegment_->QueryDoubleAttribute("Pos_y", &PositionRelativeSegment[1]);
							elementXMLSegment_->QueryDoubleAttribute("Pos_z", &PositionRelativeSegment[2]);

							elementXMLSegment_->QueryBoolAttribute("Affiche", &affiche);
							elementXMLSegment_->QueryBoolAttribute("Enregistrable", &enregistrable);
							elementXMLSegment_->QueryBoolAttribute("Selectionnable", &selectionnable);
							


							glm::dvec4 RotatioRelativeSegment;
							elementXMLSegment_->QueryDoubleAttribute("Angle", &RotatioRelativeSegment[0]);
							elementXMLSegment_->QueryDoubleAttribute("x", &RotatioRelativeSegment[1]);
							elementXMLSegment_->QueryDoubleAttribute("y", &RotatioRelativeSegment[2]);
							elementXMLSegment_->QueryDoubleAttribute("z", &RotatioRelativeSegment[3]);


							glm::dvec3 RedimensionnementRelativeSegment;
							elementXMLSegment_->QueryDoubleAttribute("Redim_x", &RedimensionnementRelativeSegment[0]);
							elementXMLSegment_->QueryDoubleAttribute("Redim_y", &RedimensionnementRelativeSegment[1]);
							elementXMLSegment_->QueryDoubleAttribute("Redim_z", &RedimensionnementRelativeSegment[2]);

							//ecriture du point de depart et de fin de la ligne 
							
							glm::dvec3 pointDepartLu;
							glm::dvec3 pointFinLu;

							elementXMLSegment_->QueryDoubleAttribute("Depart_x", &pointDepartLu.x);
							elementXMLSegment_->QueryDoubleAttribute("Depart_y", &pointDepartLu.y);
							elementXMLSegment_->QueryDoubleAttribute("Depart_z", &pointDepartLu.z);

							elementXMLSegment_->QueryDoubleAttribute("Fin_x", &pointFinLu.x);
							elementXMLSegment_->QueryDoubleAttribute("Fin_y", &pointFinLu.y);
							elementXMLSegment_->QueryDoubleAttribute("Fin_z", &pointFinLu.z);

							NoeudAbstrait* noeudSegment = arbre_->creerNoeud("segment");
							
							// noeudSegment = arbre_->creerNoeud(typeNoeudStringSegment);
							dernierNoeudCompositeAjoute_->ajouter(noeudSegment);
							
							// dernierNoeudEnfantAjoute_ = noeudSegment;

							noeudSegment->assignerPositionRelative(PositionRelativeSegment);
							noeudSegment->assignerRedimensionnementRelative(RedimensionnementRelativeSegment);
							noeudSegment->assignerRotationRelative(RotatioRelativeSegment);

							noeudSegment->assignerAffiche(affiche);
							noeudSegment->assignerEstSelectionnable(selectionnable);
							noeudSegment->assignerEstEnregistrable(enregistrable);
							//noeudSegment->assignerSelection(selectionne);
							noeudSegment->setPoints(pointDepartLu, pointFinLu);
							
							////////////////////////
						}

					}

					else{

						glm::dvec3 PositionRelative;
						elementXMLCourantLecture_->QueryDoubleAttribute("Pos_x", &PositionRelative[0]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Pos_y", &PositionRelative[1]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Pos_z", &PositionRelative[2]);

						elementXMLCourantLecture_->QueryBoolAttribute("Affiche", &affiche);
						elementXMLCourantLecture_->QueryBoolAttribute("Enregistrable", &enregistrable);
						elementXMLCourantLecture_->QueryBoolAttribute("Selectionnable", &selectionnable);
						id = elementXMLCourantLecture_->Attribute("ID");


						glm::dvec4 RotatioRelative;
						elementXMLCourantLecture_->QueryDoubleAttribute("Angle", &RotatioRelative[0]);
						elementXMLCourantLecture_->QueryDoubleAttribute("x", &RotatioRelative[1]);
						elementXMLCourantLecture_->QueryDoubleAttribute("y", &RotatioRelative[2]);
						elementXMLCourantLecture_->QueryDoubleAttribute("z", &RotatioRelative[3]);


						glm::dvec3 RedimensionnementRelative;
						elementXMLCourantLecture_->QueryDoubleAttribute("Redim_x", &RedimensionnementRelative[0]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Redim_y", &RedimensionnementRelative[1]);
						elementXMLCourantLecture_->QueryDoubleAttribute("Redim_z", &RedimensionnementRelative[2]);

						glm::dvec3 pointDepartLuMurPoteau;
						glm::dvec3 pointFinLuMurPoteau;

						elementXMLCourantLecture_->QueryDoubleAttribute("Depart_x", &pointDepartLuMurPoteau.x);
						elementXMLCourantLecture_->QueryDoubleAttribute("Depart_y", &pointDepartLuMurPoteau.y);
						elementXMLCourantLecture_->QueryDoubleAttribute("Depart_z", &pointDepartLuMurPoteau.z);

						elementXMLCourantLecture_->QueryDoubleAttribute("Fin_x", &pointFinLuMurPoteau.x);
						elementXMLCourantLecture_->QueryDoubleAttribute("Fin_y", &pointFinLuMurPoteau.y);
						elementXMLCourantLecture_->QueryDoubleAttribute("Fin_z", &pointFinLuMurPoteau.z);


						NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, typeNoeudString);

						dernierNoeudEnfantAjoute_ = noeud;

						noeud->assignerPositionRelative(PositionRelative);
						noeud->assignerRedimensionnementRelative(RedimensionnementRelative);
						noeud->assignerRotationRelative(RotatioRelative);

						noeud->assignerAffiche(affiche);
						noeud->assignerEstSelectionnable(selectionnable);
						noeud->assignerEstEnregistrable(enregistrable);
						noeud->ID = id;
						noeud->setPoints(pointDepartLuMurPoteau, pointFinLuMurPoteau);

						elementApresScene++;
						// elementXMLCourantLecture_ = elementXMLCourantLecture_->FirstChildElement();
					}

					//arbre_->afficherConcret();
				}
			}
		}
	}
}


void ajouterNoeudArbre(const tinyxml2::XMLElement* elementXML)
{
	/*
	double x, y, z = 0;
	bool affiche, enregistrable, selectionnable, selectionne;

	glm::dvec3 PositionRelative;
	elementXML->QueryDoubleAttribute("Pos_x", &PositionRelative[0]);
	elementXML->QueryDoubleAttribute("Pos_y", &PositionRelative[1]);
	elementXML->QueryDoubleAttribute("Pos_z", &PositionRelative[2]);

	//std::cout << " x= " << x  << "y= " << y << std::endl << std::endl;

	elementXML->QueryBoolAttribute("Affiche", &affiche);
	elementXML->QueryBoolAttribute("Enregistrable", &enregistrable);
	elementXML->QueryBoolAttribute("Selectionnable", &selectionnable);
	elementXML->QueryBoolAttribute("Selectionne", &selectionne);


	glm::dvec4 RotatioRelative;
	elementXML->QueryDoubleAttribute("Angle",&RotatioRelative[0]);
	elementXML->QueryDoubleAttribute("x",&RotatioRelative[1]);
	elementXML->QueryDoubleAttribute("y",&RotatioRelative[2]);
	elementXML->QueryDoubleAttribute("z",&RotatioRelative[3]);


	glm::dvec3 RedimensionnementRelative;
	elementXML->QueryDoubleAttribute("Pos_x", &RedimensionnementRelative[0]);
	elementXML->QueryDoubleAttribute("Pos_y", &RedimensionnementRelative[1]);
	elementXML->QueryDoubleAttribute("Pos_z", &RedimensionnementRelative[2]);



	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud("table", nom);
	dernierNoeudAjoute_ = noeud;
	noeud->assignerPositionRelative(glm::dvec3(point.x, point.y, 4.9));
	noeud->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));

	*/
	/*
		tinyxml2::XMLElement* noeudPoteauXML{ (documentXML_->NewElement("Poteau")) };
	// ecrire type du noeud visite 
	noeudPoteauXML->SetAttribute("Type", noeud.obtenirType().c_str());
	*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerHaut()
///
/// Cette fonction permet l'appel de la fonction permettant le deplacement de la 
/// fenetre vers le haut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerHaut()
{
	vue_->deplacerFenetreVirtuelleClavierHaut();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerBas()
///
/// Cette fonction permet l'appel de la fonction permettant le deplacement de la 
/// fenetre vers le bas
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerBas()
{
	vue_->deplacerFenetreVirtuelleClavierBas();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerDroite()
///
/// Cette fonction permet l'appel de la fonction permettant le deplacement de la 
/// fenetre vers la droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerDroite()
{
	vue_->deplacerFenetreVirtuelleClavierDroite();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerGauche()
///
/// Cette fonction permet l'appel de la fonction permettant le deplacement de la 
/// fenetre vers la gauche
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerGauche()
{
	vue_->deplacerFenetreVirtuelleClavierGauche();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerFenetreVirtuelleSouris()
///
/// Cette fonction permet l'appel de la fonction permettant le deplacement de la 
/// fenetre avec la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerFenetreVirtuelleSouris(int x, int y)
{
	glm::dvec3 positionActuelle;
	vue_->convertirClotureAVirtuelle(x, y, positionActuelle);
	glm::dvec3 deltaSouris;
	deltaSouris.x = double(positionSourisClick_.x - positionActuelle.x);
	deltaSouris.y = double(positionSourisClick_.y - positionActuelle.y);
	deltaSouris.z = 0.0;
	vue_->deplacerSouris(deltaSouris,x,y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::sauverPositionSouris(int x, int y)
///
/// Cette fonction permet la sauvegarde de la position de la souris, 
///	après un clic, en coordonnées de cloture.
///
/// @param[in]		x		: Position x de la souris en coordonnée de cloture.
///
/// @param[in]		y		: Position y de la souris en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sauverPositionSouris(int x, int y)
{
	glm::dvec3 posSouris;
	vue_->convertirClotureAVirtuelle(x, y, posSouris);
	positionSourisClick_ = posSouris;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimerNoeudsDupliques()
///
/// Cette fonction permet de supprimer le ou les noeud(s) duplique(s).
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerNoeudsDupliques()
{
	arbre_->effacerFantome();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* FacadeModele::ajouterNoeudDuplique(char* nom, NoeudAbstrait* parent, glm::dvec3 position, double scale, double angleRotation, glm::dvec3 pointDepart, glm::dvec3 pointFin, bool estFantome)
///
/// Cette fonction permet d'ajouter un noeud duplique a l'arbre de rendu.
///
/// @param[in]		nom				: Nom identifiant le type du noeud a duplique
///
/// @param[in]		parent			: Le pere du noeud a ajoute a l'arbre de rendu.
///
/// @param[in]		position		: Position xyz relatif au pere du noeud.
///
/// @param[in]		scale			: Redimensionnement relatif au pere du noeud.
///
/// @param[in]		angleRotation	: Angle de rotation relatif au pere du noeud.
///
/// @param[in]		pointDepart		: Point xyz de depart du noeud.
///
/// @param[in]		pointFin		: Point xyz de terminaison du noeud.
///
/// @param[in]		estFantome		: Booleen permettant de determiner si le noeud doit etre afficher a l'utilisateur ou non.
///
/// @return Un pointeur vers le noeud en question.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* FacadeModele::ajouterNoeudDuplique(char* nom, NoeudAbstrait* parent, glm::dvec3 position, double scale, 
												double angleRotation, glm::dvec3 pointDepart, glm::dvec3 pointFin, bool estFantome)
{
	NoeudAbstrait* noeud;
	noeud = arbre_->creerNoeud(nom);
	parent->ajouter(noeud);
	noeud->assignerPositionRelative(position);
	if (std::string(nom) == arbre_->NOM_POTEAU)
		noeud->assignerRedimensionnementRelative(glm::dvec3(scale, scale, 1.0));
	else
		noeud->assignerRedimensionnementRelative(glm::dvec3(scale, 1.0, 1.0));
	noeud->assignerRotationRelative(glm::dvec4(angleRotation, 0.0, 0.0, 1.0));
	noeud->mettreAjourCentre();
	parent->mettreAjourCentre();
	noeud->assignerEstFantome(estFantome);
	noeud->setPoints(pointDepart, pointFin);
	return noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::dupliquerSelection(int mouseX, int mouseY, bool estFantome)
///
/// Cette fonction permet de dupliquer un objet selectionne.
///
/// @param[in]		mouseX		: Position x de la souris en coordonnée de cloture.
///
/// @param[in]		mouseY		: Position y de la souris en coordonnée de cloture.
///
/// @param[in]		estFantome	: Booleen permettant de determiner si le noeud doit etre afficher a l'utilisateur ou non.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::dupliquerSelection(int mouseX, int mouseY, bool estFantome)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(mouseX, mouseY, point);
	auto visiteurDeterminerCentreSelection = new VisiteurDeterminerCentreSelection(true);
	arbre_->accepterVisiteur(visiteurDeterminerCentreSelection);
	//  glm::dvec3(0, 0, 14) ajouter pour palier au probleme de niveau de la table
	glm::dvec3 deplacementDuplicata = point - visiteurDeterminerCentreSelection->obtenirCentreSelection() + glm::dvec3(0, 0, 14);
	auto visiteurVerifierDeplacementDuplication = new VisiteurVerifierDeplacementDuplication(deplacementDuplicata);
	arbre_->accepterVisiteur(visiteurVerifierDeplacementDuplication);
	bool reponse = false;
	if (visiteurVerifierDeplacementDuplication->estValide())
	{
		auto visiteurDupliquerSelection = new VisiteurDupliquerSelection(deplacementDuplicata, estFantome);
		arbre_->accepterVisiteur(visiteurDupliquerSelection);
		reponse = true;
		delete visiteurDupliquerSelection;
	}
	delete visiteurVerifierDeplacementDuplication;
	delete visiteurDeterminerCentreSelection;
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::intialiserRectangleElastique(int x, int y)
///
/// Cette fonction permet l'initialisation d'un rectangle élastique en
///	ajustant son point d'ancrage et le point suivant.
///
/// @param[in]		x		: Position x de la souris en coordonnée de cloture.
///
/// @param[in]		y		: Position y de la souris en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::intialiserRectangleElastique(int x, int y)
{
	/// initialise le mode de rendu du rectangle élastique en mode XOR
	rectangleElastiqueTrace_ = true;
	//glm::dvec3 point;
	//vue_->convertirClotureAVirtuelle(x, y, point);

	pointAncrage_.x = x;
	pointAncrage_.y= y;

	aidegl::initialiserRectangleElastique(pointAncrage_, 0x3333, 1);
	
	pointAvant_.x = pointAncrage_.x;
	pointAvant_.y = pointAncrage_.y;

	pointApres_.x = pointAncrage_.x;
	pointApres_.y = pointAncrage_.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::intialiserRectangleElastique(int x, int y)
///
/// Cette fonction permet de mettre à jour les coordonnées du rectangle
///	élastique.
///
/// @param[in]		x		: Position x de la souris en coordonnée de cloture.
///
/// @param[in]		y		: Position y de la souris en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::mettreAjourRectangleElastique(int x, int y)
{	
	pointApres_.x = x;
	pointApres_.y = y; 
	aidegl::mettreAJourRectangleElastique(pointAncrage_,pointAvant_,pointApres_);
	pointAvant_ = pointApres_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::terminerRectangleElastique(int x, int y)
///
/// Cette fonction permet de mettre fin au rectangle élastique
///
/// @param[in]		x		: Position x de la souris en coordonnée de cloture.
///
/// @param[in]		y		: Position y de la souris en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::terminerRectangleElastique(int x, int y)
{
	rectangleElastiqueTrace_ = false;
	pointFinal_.x = x;
	pointFinal_.y = y;
	aidegl::terminerRectangleElastique(pointAncrage_,pointFinal_);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::tracerRectangleElastique(int x, int y)
///
/// Cette fonction permet de tracer le rectangle élastique à l'écran
///
/// @param[in]		x		: Position x de la souris en coordonnée de cloture.
///
/// @param[in]		y		: Position y de la souris en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::tracerRectangleElastique(int x, int y)
{
	if (rectangleElastiqueTrace_ == false)
	{
		intialiserRectangleElastique(x,y);
	}
	
	// le rectangle elastique a ete initialise on met donc ses dimensions a jour
	if (rectangleElastiqueTrace_ = true)
	{
		mettreAjourRectangleElastique(x,y);
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionnerObjet(int mouseX, int mouseY, bool selectionUnique)
///
/// Cette fonction permet d'effectuer la sélection d'un objet.
///
/// @param[in]	mouseX				: Position x de la souris en coordonnée de cloture.
///
/// @param[in]	mouseY				: Position y de la souris en coordonnée de cloture.
///
/// @param[in]	selectionUnique		: Booleen représentant si l'usager effectue une sélection unique ou non.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const char * FacadeModele::selectionnerObjet(int mouseX, int mouseY, bool selectionUnique)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(mouseX, mouseY, point);

	GLubyte  couleurPixel[3];
	determinerCouleurPixel(mouseX, mouseY, couleurPixel);
	//std::cout << "couleurPixelSelectObject : (" << (int)couleurPixel[0] << ", " << (int)couleurPixel[1] << ", " << (int)couleurPixel[2] << ")" << std::endl;
	bool estAlExterieurTable = couleurPixel[0] == 0 && couleurPixel[1] == 0 && couleurPixel[2] == 0;
	if (!estAlExterieurTable)
	{
		auto visiteurSelObj = new VisiteurSelectObjet(point, selectionUnique, couleurPixel, true);
		arbre_->accepterVisiteur(visiteurSelObj);
		delete visiteurSelObj;
		visiteurSelObj = new VisiteurSelectObjet(point, selectionUnique, couleurPixel, false);
		arbre_->accepterVisiteur(visiteurSelObj);
		if (!visiteurSelObj->obtenirselectionExiste() && selectionUnique)
			arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
		delete visiteurSelObj;
	}
	else if (selectionUnique)
	{
		arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout(); //A revoir
	}
	chaineSelection = obtenirIDsNoeudsSelectionnes(); //ID1:ID2...
    std::cout << "noeuds selectionnes c++: " << chaineSelection << std::endl;
	return chaineSelection.c_str();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectRectElastique(int xDebut, int yDebut, int xFin, int yFin, bool estEnfonce)
///
/// Cette fonction permet d'effectuer la sélection des objets à l'aide d'un rectangle élastique.
///
/// @param[in]	X_debut				: Position x initiale de la souris en coordonnée de cloture.
///
/// @param[in]	Y_debut				: Position y initiale de la souris en coordonnée de cloture.
///
/// @param[in]	X_fin				: Position x finale de la souris en coordonnée de cloture.
///
/// @param[in]	Y_fin				: Position y finale de la souris en coordonnée de cloture.
///
/// @param[in]	estEnfonce			: Booleen représentant si l'usager effectue une sélection multiple ou non
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const char * FacadeModele::selectRectElastique(int xDebut, int yDebut, int xFin, int yFin, bool estEnfonce)
{
	if (!estEnfonce)
	{
		arbre_->deselectionnerTout();
	}
	auto visSelElastique = new visiteurSelectElastique(xDebut, xFin, yDebut, yFin, estEnfonce, vue_);
	arbre_->accepterVisiteur(visSelElastique);
	chaineSelection = obtenirIDsNoeudsSelectionnes(); //ID1:ID2...
	std::cout << "noeuds selectionnes c++: " << chaineSelection << std::endl;
	delete visSelElastique;
	return chaineSelection.c_str();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomInRectangle(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture)
///
/// Cette fonction permet l'appel de la fonction permettant le zoom in de 
/// la fenetre virtuelle avec le rectangle elastique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomInRectangle(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture)
{
	glm::ivec2 pointMin;
	glm::ivec2 pointMax;
	pointMin.x = xMinCloture;
	pointMax.x = xMaxCloture;
	pointMin.y = yMaxCloture;
	pointMax.y = yMinCloture;
	vue_->zoomerInElastique(pointMin, pointMax);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomInRectangle(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture)
///
/// Cette fonction permet l'appel de la fonction permettant le zoom in de 
/// la fenetre virtuelle avec le rectangle elastique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomOutRectangle(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture)
{

	glm::ivec2 pointMin;
	glm::ivec2 pointMax;
	pointMin.x = xMinCloture;
	pointMax.x = xMaxCloture;
	pointMin.y = yMaxCloture;
	pointMax.y = yMinCloture;
	vue_->zoomerOutElastique(pointMin, pointMax);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimerSelection()
///
/// Cette fonction permet l'arret d'une sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerSelection()
{
	arbre_->effacerSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerPositionPourObjetSelectionne(double x, double y, double z)
///
/// Cette fonction permet l'assignation d'une position relative à un autre objet d'un objet sélectionné.
///
/// @param[in]	xDebut	: Position x relative à un autre objet en coordonnée virtuelle.
///
/// @param[in]	yDebut	: Position y relative à un autre objet en coordonnée virtuelle.
///
/// @param[in]	xFin	: Position z relative à un autre objet en coordonnée virtuelle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerPositionPourObjetSelectionne(double x, double y, double z)
{
	bool retour = false;
	int nombreNoeud = 0;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombreNoeud);
	if (nombreNoeud == 1)
	{
		initialiserEnTraitement();
		noeud->mettreAjourCentre();
		glm::dvec3 position = noeud->obtenirCentre();
		z = position[2];
		VisiteurDeplacerSelection* visiteur = new VisiteurDeplacerSelection(glm::dvec3(x, y, z) - position);
		noeud->accepterVisiteur(visiteur);
		if (visiteur != nullptr)
		{
			delete visiteur;
		}
		///*if ( !noeud->estDansLaTable() )
		//{
		//	initialiserEnTraitement();
		//	VisiteurDeplacerSelection* visiteur = new VisiteurDeplacerSelection(position - glm::dvec3(x, y, z));
		//	noeud->accepterVisiteur(visiteur);
		//	if (visiteur != nullptr)
		//	{
		//		delete visiteur;
		//	}
		//	retour = false;
		//}
		//else
		//{*/
			noeud->mettreAjourCentre();
		///*	retour = true;
		//}*/
	}
	////return retour;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerRotationPourObjetSelectionne(double rotation)
///
/// Cette fonction permet d'assigner une rotation relative à un autre objet d'un objet sélectionné.
///
/// @param[in]	rotation	: Angle de rotation relative à un autre objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerRotationPourObjetSelectionne(double rotation)
{
	int nombreNoeud = 0;
	NoeudAbstrait* noeud = chercherNouedSelectionne( nombreNoeud );
	if ( nombreNoeud == 1 )
	{
		if ( noeud->obtenirType() != arbre_->NOM_LIGNE )
		{
			dynamic_cast<NoeudLigne*>(noeud)->assignerRotation(rotation);
		}
		else
		{
			glm::dvec4 rotationR = noeud->obtenirRotationRelative();
			glm::dvec4 rotationRN = rotationR;
			rotationRN.x = rotation;
			noeud->assignerRotationRelative(rotationRN);
			if (!noeud->estDansLaTable())
				noeud->assignerRotationRelative(rotationR);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::changerScalePourObjetSelectionne(double scale)
///
/// Cette fonction permet le redimensionnement d'un objet sélectionné.
///
/// @param[in]	scale	: Facteur de redimensionnement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changerScalePourObjetSelectionne(double facteur)
{
	bool reponse = false;
	int nombreNoeud = 0;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombreNoeud);
	if (nombreNoeud == 1)
	{
		noeud->changerScale(facteur);
		///*if (!noeud->estDansLaTable())
		//{
		//	noeud->changerScale(1 / facteur);
		//	reponse = false;
		//}
		//else
		//	reponse = true;*/
	}
	//return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* FacadeModele::chercheNouedSelectionne(int& nombre)
///
/// Cette fonction effectue le parcours de l'arbre de rendu à la recherche
/// du noeud sélectionné.
///
/// @param[in, out]	nombre	: numéro du noeud sélectionné.
///
/// @return Le noeud sélectionné.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* FacadeModele::chercherNouedSelectionne(int& nombre)
{
	nombre = obtenirNombreNoeudsSelectionnes();
	NoeudAbstrait* noued = NULL;
	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	for ( int i = 0; i < nombreEnfants; i++ )
	{
		NoeudAbstrait* nouedTemp = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants()->at(i);
		if ( nouedTemp->estSelectionne() )
		{
			noued = nouedTemp;
		}
	}
	return noued;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* FacadeModele::chercheNouedSelectionne(int& nombre)
///
/// Cette fonction permet l'initialisation du positionnement d'un noeud
/// en traitement par rapport à son parent.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserEnTraitement()
{
	//VisiteurInitialisationPosition* visiteur = new VisiteurInitialisationPosition();
	arbre_ -> initialiserEnTraitement();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* FacadeModele::chercheNouedSelectionne(int& nombre)
///
/// Cette fonction permet l'initialisation du redimensionnement d'un noeud
/// en traitement par rapport à son parent.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserScaleEnTraitement()
{
	VisiteurInitialisationScale* visiteur = new VisiteurInitialisationScale();
	arbre_->accepterVisiteur(visiteur);
	if (visiteur != nullptr)
	{
		delete visiteur;
	}
	std::cout << "fin initscaleEn traitement" << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::scaleSelection(double facteurScale)
///
/// Cette fonction permet le redimensionnement des noeuds sélectionnés.
///
/// @param[in]	facteurScale	: facteur de redimensionnement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::scaleSelection(double facteur)
{
//	if ( arbre_->estDansLaTableApresScale( facteur ) )
	//{
		//VisiteurScaleSelection* visiteurScale= new VisiteurScaleSelection(facteurScale);
		//arbre_->accepterVisiteur(visiteurScale);
//	}

	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	std::vector<NoeudAbstrait*> * vecteur = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants();
	std::vector<double> scales(nombreEnfants); //= new  std::vector<double>(nombreEnfants);
		for (int i = 0; i < nombreEnfants; i++)
		{
			if (vecteur->at(i)->estSelectionne())
			{
				scales[i] = vecteur->at(i)->obtenirRedimensionnementRelative()[0];
				vecteur->at(i)->changerScale(facteur * vecteur->at(i)->obtenirScaleInitialeEnTraitement()[0] / scales[i]);
			}
		}
		bool scaleCorrect = true;
		for (int i = 0; i < nombreEnfants; i++)
		{
			if ( vecteur->at(i)->estSelectionne() )
			{
				if ( vecteur->at(i)->obtenirRedimensionnementRelative()[0] < 0.05 )
					scaleCorrect = false;
			}
		}
		if (!scaleCorrect)
		{
			for (int i = 0; i < nombreEnfants; i++)
			{
				if (vecteur->at(i)->estSelectionne())
				{
					vecteur->at(i)->changerScale( scales[i] / (facteur * vecteur->at(i)->obtenirScaleInitialeEnTraitement()[0]));
				}
			}
		}
		std::string factorStr;
		factorStr = std::to_string(facteur);
		std::cout << "factor == " << factorStr.c_str() << std::endl;
		return factorStr.c_str();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionnerObjet(int mouseX, int mouseY, bool selectionUnique)
///
/// Cette fonction permet le déplacement d'un objet sélectionné.
///
/// @param[in]	xDebut				: Position x initiale de la souris en coordonnée de cloture.
///
/// @param[in]	yDebut				: Position y initiale de la souris en coordonnée de cloture.
///
/// @param[in]	xFin				: Position x finale de la souris en coordonnée de cloture.
///
/// @param[in]	yFin				: Position y finale de la souris en coordonnée de cloture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
const char * FacadeModele::deplacerSelection(int xDebut, int yDebut, int xFin, int yFin)
{
	chaineDeDeplacement = ""; //attribut ajoute contre le problem de Marshaling
	glm::dvec3 debut;
	glm::dvec3 fin;
	obtenirVue()->convertirClotureAVirtuelle(xDebut, yDebut, debut);
	obtenirVue()->convertirClotureAVirtuelle(xFin, yFin, fin);
	chaineDeDeplacement += std::to_string(debut[0]) + ";" + std::to_string(debut[1]) + ";" + std::to_string(debut[2])+":";
	chaineDeDeplacement += std::to_string(fin[0]) + ";" + std::to_string(fin[1]) + ";" + std::to_string(fin[2]);
	//if (arbre_->estDansLaTableApresDeplacement(fin - debut))
	//{
	VisiteurDeplacerSelection* visiteurDeplacerSelection = new VisiteurDeplacerSelection(fin - debut);
	arbre_->accepterVisiteur(visiteurDeplacerSelection);
	delete visiteurDeplacerSelection;
	//}
	return chaineDeDeplacement.c_str();
}

const char * FacadeModele::deplacerSelNoAction(int xDebut, int yDebut, int xFin, int yFin)
{
	chaineDeDeplacement = ""; //attribut ajoute contre le problem de Marshaling
	glm::dvec3 debut;
	glm::dvec3 fin;
	obtenirVue()->convertirClotureAVirtuelle(xDebut, yDebut, debut);
	obtenirVue()->convertirClotureAVirtuelle(xFin, yFin, fin);
	chaineDeDeplacement += std::to_string(debut[0]) + ";" + std::to_string(debut[1]) + ";" + std::to_string(debut[2]) + ":";
	chaineDeDeplacement += std::to_string(fin[0]) + ";" + std::to_string(fin[1]) + ";" + std::to_string(fin[2]);

	return chaineDeDeplacement.c_str();
}






////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirNmbreNoeudsSelectionnes()
///
/// Cette fonction permet le retour du nombre de noeud sélectionné par
/// l'utilisateur
///
/// @return Le nombre de noeud sélectionné.
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirNombreNoeudsSelectionnes()
{
	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	int nombre = 0;
	std::vector<NoeudAbstrait*> * vecteur = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants();
	for (int i = 0; i < nombreEnfants; i++)
	{
		if (vecteur->at(i)->estSelectionne())
		{
			nombre++;
		}
	}
	return nombre;
}

//obtenir les IDs des noeus selectionnes


////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirNmbreNoeudsSelectionnes()
///
/// Cette fonction permet d'effectuer la rotation d'un objet sélectionné
///
/// @param[in]	rotation	: angle de rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::PivoterObjetSelectionne(double deltaY)
{
	deltaY /= 2;
	int nombreNoeud = 0;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombreNoeud);
	if ((nombreNoeud == 1 ) )
	{

		//glm::dvec4 rotationInitiale = noeud->obtenirRotationRelative();
		//glm::dvec3 centreLigne = noeud->obtenirPositionRelative(); //tjrs 0,0,0 par defaut
		glm::dvec3 centreSelection;
		auto visiteurDeterminerCentreSelection = new VisiteurDeterminerCentreSelection(false);
		arbre_->accepterVisiteur(visiteurDeterminerCentreSelection);
		centreSelection = visiteurDeterminerCentreSelection->obtenirCentreSelection();
		auto visiteur = new visiteurRotationUnObjet(deltaY,centreSelection);
		arbre_->accepterVisiteur(visiteur);
		delete visiteurDeterminerCentreSelection;
		delete visiteur;
		if (noeud->obtenirType() == arbre_->NOM_LIGNE)
			dynamic_cast<NoeudLigne*>(noeud)->assignerRotation(deltaY + dynamic_cast<NoeudLigne*>(noeud)->obtenirRotation());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::PivoterObjetsMultiples(double rotation)
///
/// Cette fonction permet d'effectuer la rotation de plusieurs objets
/// selectionnes.
///
/// @param[in]	rotation	: angle de rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::PivoterObjetsMultiples(double rotation)
{

	int n = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	glm::dvec3 centre;
	/*int nombreSelectionnes = 0;
	for (int i = 0; i < n; i++)
	{
		if (arbre_->chercher("table")->obtenirEnfants()->at(i)->estSelectionne())
		{
			centre.x += arbre_->chercher("table")->obtenirEnfants()->at(i)->obtenirPositionRelative().x;
			centre.y += arbre_->chercher("table")->obtenirEnfants()->at(i)->obtenirPositionRelative().y;
			centre.z += arbre_->chercher("table")->obtenirEnfants()->at(i)->obtenirPositionRelative().z;
			nombreSelectionnes++;
		}
	}
	centre.x /= nombreSelectionnes; centre.y /= nombreSelectionnes; centre.z /= nombreSelectionnes;*/
	auto visiteurDeterminerCentreSelection = new VisiteurDeterminerCentreSelection(true);
	arbre_->accepterVisiteur(visiteurDeterminerCentreSelection);
	centre = visiteurDeterminerCentreSelection->obtenirCentreSelection();
	VisiteurRotateSelection visiteur(rotation);
	visiteur.setCentre(centre);
	arbre_->accepterVisiteur(&visiteur);
	delete visiteurDeterminerCentreSelection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rotaterPointAutourDecentre(double centreX, double centreY, double angle, glm::dvec3 & point)
///
/// Cette fonction permet d'effectuer une rotation d'un point autour du centre.
///
/// @param[in]	centreX				: Position x du centre.
///
/// @param[in]	centreY				: Position y du centre.
///
/// @param[in]	angle				: Angle de rotation
///
/// @param[in, out]	point			: Nouveau point rotater.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::rotaterPointAutourDecentre(double centreX, double centreY, double angle, glm::dvec3 & point)
{
	// effectuer une translation vers le centre
	point.x -= centreX;
	point.y -= centreY;

	// effectuer la rotation
	double nouveauX = point.x * cos(utilitaire::DEG_TO_RAD(angle)) - point.y * sin(utilitaire::DEG_TO_RAD(angle));
	double nouveauY = point.x * sin(utilitaire::DEG_TO_RAD(angle)) + point.y * cos(utilitaire::DEG_TO_RAD(angle));

	//effectuer une translation
	point.x = nouveauX + centreX;
	point.y = nouveauY + centreY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::objetsSurLaTable()
///
/// Cette fonction permet de verifier si un objet est sur la table ou non.
///
/// @return Vrai si l'objet est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::objetsSelectionnesSurLaTable()
{
	return (arbre_->objetsSelectionnesSurLaTable());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::objetsSurLaTable()
///
/// Cette fonction permet d'effectuer une rotation sur un objet selectionne.
///
/// @param[in]	angle	: Angle de rotation.
///
/// @return Vrai si une rotation a ete effectuee, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::tournerObjetSelectionne(double angle)
{
	int nombreNoeud = 0;
	bool reponse = false;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombreNoeud);
	if (nombreNoeud == 1)
	{
		//noeud->obtenirPositionRelative()
		noeud->tourner(angle);
		if (!noeud->estDansLaTable())
		{
			noeud->tourner(-angle);
			reponse = false;
		}
		else
			reponse = true;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::annulerRotationSelection()
///
/// Cette fonction d'annuler la rotation d'un objet selectionne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::annulerRotationSelection()
{
	VisiteurAnnulerRotationSelection * visiteur  = new VisiteurAnnulerRotationSelection;
	arbre_->accepterVisiteur(visiteur);
	delete visiteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::retournerAuScaleInitiale()
///
/// Cette fonction de reinitialiser le dimensionnement de l'objet en court
/// de traitement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::retournerAuScaleInitiale()
{
	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	std::vector<NoeudAbstrait*> * vecteur = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants();
	for (int i = 0; i < nombreEnfants; i++)
	{
		if (vecteur->at(i)->estSelectionne())
		{
			vecteur->at(i)->retournerAuScaleInitiale();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRobot()
///
/// Cette fonction permet de créer le noeud robot, le positionner à la position de départ (flèche),
/// créer deux noeuds de type roue pour la roue droite et gauche et les positionner à leur place
/// au niveau de l'essieu du robot
/// 
/// @param Aucun.
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserRobot(bool vuePemierePersonne)
{
	leRobot_ = (NoeudRobot*)arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, arbre_->NOM_ROBOT);
	glm::dvec3 positionRobot = arbre_->chercher(arbre_->NOM_FLECHE)->obtenirPositionRelative();
	//positionRobot.z = 4.0;
	leRobot_->assignerPositionRelative(positionRobot);

	leRobot_->assignerRedimensionnementRelative(glm::dvec3(SCALE_ROBOT, SCALE_ROBOT, SCALE_ROBOT));

	double angleDepart = arbre_->chercher(arbre_->NOM_FLECHE)->obtenirRotationRelative()[0] - 90;
	leRobot_->assignerRotationRelative(glm::dvec4(angleDepart, 0.0, 0.0, 1.0));

	NoeudAbstrait* noeudRoueD = arbre_->ajouterNouveauNoeud(arbre_->NOM_ROBOT, arbre_->NOM_ROUE_DROITE);
	NoeudAbstrait* noeudRoueG = arbre_->ajouterNouveauNoeud(arbre_->NOM_ROBOT, arbre_->NOM_ROUE_GAUCHE);
	noeudRoueD->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));
	noeudRoueG->assignerRedimensionnementRelative(glm::dvec3(1.0, 1.0, 1.0));

	noeudRoueD->assignerPositionRelative(glm::dvec3(-3.8, 0.1, 3.0));
	noeudRoueG->assignerPositionRelative(glm::dvec3(4.3, 0.1, 3.0));

	leRobot_->setRoueDroite(noeudRoueD);
	leRobot_->setRoueGauche(noeudRoueG);
	leRobot_->bteEnglobante_ = new utilitaire::BteEnglobanteRobot;
	leRobot_->mettreAjourBteEnglobante();
	leRobot_->visiteurVerifierCollision_ = new VisiteurVerifierCollision();
	leRobot_->typeCollision_ = AUCUNE;
	leRobot_->objetCollision_ = AUCUN;
	visiteurDetectionNoeud = new VisiteurDetectionNoeud(leRobot_);
	millisecondes_ = 0;
	compteurAffichageChrono_ = 0;
	//start = clock() ;

	if (vuePremierePersonneFacadeModele_)
	{
		activerVuePremierePersonne();
	}

	son_->initialiser();
	if (modeApplication_ == 'T')
	{
		initialiserSonEditeur();
	}
	else if (modeApplication_ == 'S')
	{
		jouerMusiqueSimulation();
	}
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererRobot()
///
/// Cette fonction permet de détruire le noeud Robot et ses enfants (les 2 noeuds Roue)
/// 
/// @param Aucun.
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererRobot()
{
	NoeudRobot * lerobot = dynamic_cast<NoeudRobot *>(leRobot_);
	

	if (leRobot_->visiteurVerifierCollision_ != nullptr)
		delete leRobot_->visiteurVerifierCollision_;
	if (leRobot_->bteEnglobante_ != nullptr)
		delete leRobot_->bteEnglobante_;
	if (visiteurDetectionNoeud != nullptr)
	{
		delete visiteurDetectionNoeud;
		visiteurDetectionNoeud = nullptr;
	}
	if (leRobot_ != nullptr)
	{
		leRobot_->vider();
	}
	arbre_->chercher(arbre_->NOM_TABLE)->effacer(leRobot_);
	son_->liberer();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::arreterRobot()
///
/// Methode permettant l'arret du robot.
/// 
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::arreterRobot()
{
	leRobot_->arreterMoteurs();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::actionnerRobot()
///
/// Cette fonction permet de d'actionner le robot dans tous les sens
/// 
/// @param
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::actionnerRobot(double rapportVitesseGauche, double rapportVitesseDroit, bool sensDirect)
{
	if (sensDirect)
		leRobot_->actionnerMoteurs(rapportVitesseGauche, rapportVitesseDroit, FORWARD);
	else
		leRobot_->actionnerMoteurs(rapportVitesseGauche, rapportVitesseDroit, REVERSE);
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::actionnerModeAutomatique()
///
/// Methode permettant d'actionner le mode automatique du robot.
/// 
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::actionnerModeAutomatique()
{
	son_->jouer9();
	leRobot_->modeAutomatique_ = true;
	leRobot_->definirComportement(new Defaut(leRobot_));
	if (obtenirAffichageDebougage() && leRobot_->obtenirDebug()->getSortieConsole() && leRobot_->obtenirDebug()->getChangementComportement() && estLeTourModeAutomatique_)
	{
		std::cout << timestamps() << " - " << "Mode automatique" << std::endl;
		estLeTourModeAutomatique_ = false;
	}
		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::stopperModeAutomatique()
///
/// Methode permettant d'arreter le mode automatique du robot.
/// 
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::stopperModeAutomatique()
{
	leRobot_->modeAutomatique_ = false;
	leRobot_->arreterMoteurs();
	if (leRobot_->getComportementCourant() != nullptr)
	{
		delete leRobot_->getComportementCourant();
	}
	leRobot_->setAffichageDebogageCapteurDangerDroit(true);
	leRobot_->setAffichageDebogageCapteurDangerMilieu(true);
	leRobot_->setAffichageDebogageCapteurDangerGauche(true);
	leRobot_->setAffichageDebogageCapteurSecuritaireDroit(true);
	leRobot_->setAffichageDebogageCapteurSecuritaireMilieu(true);
	leRobot_->setAffichageDebogageCapteurSecuritaireGauche(true);
	leRobot_->setAffichageDebogageSuiviLigne(true);
	leRobot_->setEtat(DEFAUT);

	son_->setPause(2, true);
	son_->setPause(3, true);
	son_->setPause(4, true);
	son_->jouer8();


	if (obtenirAffichageDebougage() && leRobot_->obtenirDebug()->getSortieConsole() && leRobot_->obtenirDebug()->getChangementComportement() && !estLeTourModeAutomatique_)
	{
		std::cout << timestamps() << " - " << "Mode manuel" << std::endl;
		estLeTourModeAutomatique_ = true;
	}
		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::debuterSimulation()
///
/// Methode permettant de debuter une simulation.
/// 
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::debuterSimulation()
{
	initialiserRobot(false);

	
}

/*
void FacadeModele::detectionCapteurs()
{
	unsigned int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	std::vector<NoeudAbstrait*> * elementSurLaTable = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants();
	bool estEnCollisionSecuritaireDroit = false;
	bool estEnCollisionDangerDroit = false;
	bool estEnCollisionSecuritaireMilieu = false;
	bool estEnCollisionDangerMilieu = false;
	bool estEnCollisionSecuritaireGauche = false;
	bool estEnCollisionDangerGauche = false;
	bool etatActifCapteurDroit = leRobot_->obtenirEtatCapteurDroit();
	bool etatActifCapteurMilieu = leRobot_->obtenirEtatCapteurMilieu();
	bool etatActifCapteurGauche = leRobot_->obtenirEtatCapteurGauche();
	//Donnee du capteur droit.
	glm::dvec2 p1CapteurDangerDroit = leRobot_->obtenirP1CapteurDangerDroit();
	glm::dvec2 p2CapteurDangerDroit = leRobot_->obtenirP2CapteurDangerDroit();
	glm::dvec2 p3CapteurDangerDroit = leRobot_->obtenirP3CapteurDangerDroit();
	glm::dvec2 p4CapteurDangerDroit = leRobot_->obtenirP4CapteurDangerDroit();
	glm::dvec2 p2CapteurSecuritaireDroit = leRobot_->obtenirP2CapteurSecuritaireDroit();
	glm::dvec2 p3CapteurSecuritaireDroit = leRobot_->obtenirP3CapteurSecuritaireDroit();

	//Donnee du capteur milieu
	glm::dvec2 p1CapteurDangerMilieu = leRobot_->obtenirP1CapteurDangerMilieu();
	glm::dvec2 p2CapteurDangerMilieu = leRobot_->obtenirP2CapteurDangerMilieu();
	glm::dvec2 p3CapteurDangerMilieu = leRobot_->obtenirP3CapteurDangerMilieu();
	glm::dvec2 p4CapteurDangerMilieu = leRobot_->obtenirP4CapteurDangerMilieu();
	glm::dvec2 p2CapteurSecuritaireMilieu = leRobot_->obtenirP2CapteurSecuritaireMilieu();
	glm::dvec2 p3CapteurSecuritaireMilieu = leRobot_->obtenirP3CapteurSecuritaireMilieu();

	//Donnee du capteur gauche
	glm::dvec2 p1CapteurDangerGauche= leRobot_->obtenirP1CapteurDangerGauche();
	glm::dvec2 p2CapteurDangerGauche = leRobot_->obtenirP2CapteurDangerGauche();
	glm::dvec2 p3CapteurDangerGauche = leRobot_->obtenirP3CapteurDangerGauche();
	glm::dvec2 p4CapteurDangerGauche = leRobot_->obtenirP4CapteurDangerGauche();
	glm::dvec2 p2CapteurSecuritaireGauche = leRobot_->obtenirP2CapteurSecuritaireGauche();
	glm::dvec2 p3CapteurSecuritaireGauche = leRobot_->obtenirP3CapteurSecuritaireGauche();
	aidecollision::DetailsCollision detailP1P2DangerDroit;
	aidecollision::DetailsCollision detailP2P3DangerDroit;
	aidecollision::DetailsCollision detailP3P4DangerDroit;
	aidecollision::DetailsCollision detailP2P2SecuritaireDroit;
	aidecollision::DetailsCollision detailP2P3SecuritaireDroit;
	aidecollision::DetailsCollision detailP3P3SecuritaireDroit;
	aidecollision::DetailsCollision detailP1P2DangerMilieu;
	aidecollision::DetailsCollision detailP2P3DangerMilieu;
	aidecollision::DetailsCollision detailP3P4DangerMilieu;
	aidecollision::DetailsCollision detailP2P2SecuritaireMilieu;
	aidecollision::DetailsCollision detailP2P3SecuritaireMilieu;
	aidecollision::DetailsCollision detailP3P3SecuritaireMilieu;
	aidecollision::DetailsCollision detailP1P2DangerGauche;
	aidecollision::DetailsCollision detailP2P3DangerGauche;
	aidecollision::DetailsCollision detailP3P4DangerGauche;
	aidecollision::DetailsCollision detailP2P2SecuritaireGauche;
	aidecollision::DetailsCollision detailP2P3SecuritaireGauche;
	aidecollision::DetailsCollision detailP3P3SecuritaireGauche;

	for (unsigned int i = 0; i < nombreEnfants && !estEnCollisionSecuritaireDroit && !estEnCollisionDangerDroit && !estEnCollisionSecuritaireMilieu 
		&& !estEnCollisionDangerMilieu && !estEnCollisionSecuritaireGauche && !estEnCollisionDangerGauche; i++)
	{
		//std::cout << "je rentre dans for" << std::endl;
		//std::cout << (*it)->obtenirType() << std::endl;
		if ( elementSurLaTable->at(i)->obtenirType()  == arbre_->NOM_POTEAU)
		{
			//std::cout << "if 1" << std::endl;
			double rayon = elementSurLaTable->at(i)->obtenirRedimensionnementRelative().x;
			glm::dvec2 position = glm::dvec2(elementSurLaTable->at(i)->obtenirPositionRelative());
			
			if (etatActifCapteurDroit)
			{
				///Detection capteur droit zone danger
				detailP1P2DangerDroit = aidecollision::calculerCollisionSegment(p1CapteurDangerDroit, p2CapteurDangerDroit, position, rayon);
				detailP2P3DangerDroit = aidecollision::calculerCollisionSegment(p2CapteurDangerDroit, p3CapteurDangerDroit, position, rayon);
				detailP3P4DangerDroit = aidecollision::calculerCollisionSegment(p3CapteurDangerDroit, p4CapteurDangerDroit, position, rayon);

				///Detection capteur droit zone securitaire
				detailP2P2SecuritaireDroit = aidecollision::calculerCollisionSegment(p2CapteurDangerDroit, p2CapteurSecuritaireDroit, position, rayon);
				detailP2P3SecuritaireDroit = aidecollision::calculerCollisionSegment(p2CapteurSecuritaireDroit, p3CapteurSecuritaireDroit, position, rayon);
				detailP3P3SecuritaireDroit = aidecollision::calculerCollisionSegment(p3CapteurSecuritaireDroit, p3CapteurDangerDroit, position, rayon);
				///Verification s'il y a collision au niveau de la zone de danger du capteur droit.
				if (detailP1P2DangerDroit.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerDroit.type != aidecollision::COLLISION_AUCUNE || detailP3P4DangerDroit.type != aidecollision::COLLISION_AUCUNE)
				{
					estEnCollisionDangerDroit = true;
					std::cout << "Zone danger capteur droit je detecte un poteau" << std::endl;
				}
				///Verification s'il y a collision au niveau de la zone securitaire du capteur droit.
				else if (detailP2P2SecuritaireDroit.type != aidecollision::COLLISION_AUCUNE || detailP2P3SecuritaireDroit.type != aidecollision::COLLISION_AUCUNE || detailP3P3SecuritaireDroit.type != aidecollision::COLLISION_AUCUNE)
				{
					estEnCollisionSecuritaireDroit = true;
					std::cout << "Zone securitaire capteur droit je detecte un poteau" << std::endl;
				}
			}

			if (etatActifCapteurMilieu)
			{
				///Detection capteur milieu zone danger
				detailP1P2DangerMilieu = aidecollision::calculerCollisionSegment(p1CapteurDangerMilieu, p2CapteurDangerMilieu, position, rayon);
				detailP2P3DangerMilieu = aidecollision::calculerCollisionSegment(p2CapteurDangerMilieu, p3CapteurDangerMilieu, position, rayon);
				detailP3P4DangerMilieu = aidecollision::calculerCollisionSegment(p3CapteurDangerMilieu, p4CapteurDangerMilieu, position, rayon);

				///Detection capteur milieu zone securitaire
				detailP2P2SecuritaireMilieu = aidecollision::calculerCollisionSegment(p2CapteurDangerMilieu, p2CapteurSecuritaireMilieu, position, rayon);
				detailP2P3SecuritaireMilieu = aidecollision::calculerCollisionSegment(p2CapteurSecuritaireMilieu, p3CapteurSecuritaireMilieu, position, rayon);
				detailP3P3SecuritaireMilieu = aidecollision::calculerCollisionSegment(p3CapteurSecuritaireMilieu, p3CapteurDangerMilieu, position, rayon);
				//std::cout << "if etat actif capteur milieu" << std::endl;
				///Verification s'il y a collision au niveau de la zone de danger du capteur milieu.
				if (detailP1P2DangerMilieu.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerMilieu.type != aidecollision::COLLISION_AUCUNE || detailP3P4DangerMilieu.type != aidecollision::COLLISION_AUCUNE)
				{
					estEnCollisionDangerMilieu = true;
					std::cout << "Zone danger capteur milieu je detecte un poteau" << std::endl;
				}
				///Verification s'il y a collision au niveau de la zone securitaire du capteur milieu.
				else if (detailP2P2SecuritaireMilieu.type != aidecollision::COLLISION_AUCUNE || detailP2P3SecuritaireMilieu.type != aidecollision::COLLISION_AUCUNE || detailP3P3SecuritaireMilieu.type != aidecollision::COLLISION_AUCUNE)
				{
					estEnCollisionSecuritaireMilieu = true;
					std::cout << "Zone securitaire capteur milieu je detecte un poteau" << std::endl;
				}
			}

			if (etatActifCapteurGauche)
			{
				///Detection capteur gauche zone danger
				detailP1P2DangerGauche = aidecollision::calculerCollisionSegment(p1CapteurDangerGauche, p2CapteurDangerGauche, position, rayon);
				detailP2P3DangerGauche = aidecollision::calculerCollisionSegment(p2CapteurDangerGauche, p3CapteurDangerGauche, position, rayon);
				detailP3P4DangerGauche = aidecollision::calculerCollisionSegment(p3CapteurDangerGauche, p4CapteurDangerGauche, position, rayon);

				///Detection capteur gauche zone securitaire
				detailP2P2SecuritaireGauche = aidecollision::calculerCollisionSegment(p2CapteurDangerGauche, p2CapteurSecuritaireGauche, position, rayon);
				detailP2P3SecuritaireGauche = aidecollision::calculerCollisionSegment(p2CapteurSecuritaireGauche, p3CapteurSecuritaireGauche, position, rayon);
				detailP3P3SecuritaireGauche = aidecollision::calculerCollisionSegment(p3CapteurSecuritaireGauche, p3CapteurDangerGauche, position, rayon);
				//std::cout << "if etat actif capteur gauche" << std::endl;
				///Verification s'il y a collision au niveau de la zone de danger du capteur gauche.
				if (detailP1P2DangerGauche.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerGauche.type != aidecollision::COLLISION_AUCUNE || detailP3P4DangerGauche.type != aidecollision::COLLISION_AUCUNE)
				{
					estEnCollisionDangerGauche = true;
					std::cout << "Zone danger capteur gauche je detecte un poteau" << std::endl;
				}

				///Verification s'il y a collision au niveau de la zone securitaire du capteur gauche.
				else if (detailP2P2SecuritaireGauche.type != aidecollision::COLLISION_AUCUNE || detailP2P3SecuritaireGauche.type != aidecollision::COLLISION_AUCUNE || detailP3P3SecuritaireGauche.type != aidecollision::COLLISION_AUCUNE)
				{
					estEnCollisionSecuritaireGauche = true;
					std::cout << "Zone securitaire capteur gauche je detecte un poteau" << std::endl;
				}
			}
		}
		else if (elementSurLaTable->at(i)->obtenirType() == arbre_->NOM_MUR && elementSurLaTable->at(i)->estAffiche())
		{
			//Verification des collisions sur un objet de type mur.
			//Segment zone danger droit.
			math::SegmentDroite2D segP1P2DangerDroit(p1CapteurDangerDroit, p2CapteurDangerDroit);
			math::SegmentDroite2D segP2P3DangerDroit(p2CapteurDangerDroit, p3CapteurDangerDroit);
			math::SegmentDroite2D segP3P4DangerDroit(p3CapteurDangerDroit, p4CapteurDangerDroit);
			//segment zone securitaire droit
			math::SegmentDroite2D segP2P2SecuritaireDroit(p2CapteurSecuritaireDroit, p2CapteurDangerDroit);
			math::SegmentDroite2D segP2P3SecuritaireDroit(p2CapteurSecuritaireDroit, p3CapteurSecuritaireDroit);
			math::SegmentDroite2D segP3P3SecuritaireDroit(p3CapteurSecuritaireDroit, p3CapteurDangerDroit);
			//segment zone danger milieu
			math::SegmentDroite2D segP1P2DangerMilieu(p1CapteurDangerMilieu, p2CapteurDangerMilieu);
			math::SegmentDroite2D segP2P3DangerMilieu(p2CapteurDangerMilieu, p3CapteurDangerMilieu);
			math::SegmentDroite2D segP3P4DangerMilieu(p3CapteurDangerMilieu, p4CapteurDangerMilieu);
			//segment zone securitaire milieu
			math::SegmentDroite2D segP2P2SecuritaireMilieu(p2CapteurSecuritaireMilieu, p2CapteurDangerMilieu);
			math::SegmentDroite2D segP2P3SecuritaireMilieu(p2CapteurSecuritaireMilieu, p3CapteurSecuritaireMilieu);
			math::SegmentDroite2D segP3P3SecuritaireMilieu(p3CapteurSecuritaireMilieu, p3CapteurDangerMilieu);
			//segment zone danger gauche
			math::SegmentDroite2D segP1P2DangerGauche(p1CapteurDangerGauche, p2CapteurDangerGauche);
			math::SegmentDroite2D segP2P3DangerGauche(p2CapteurDangerGauche, p3CapteurDangerGauche);
			math::SegmentDroite2D segP3P4DangerGauche(p3CapteurDangerGauche, p4CapteurDangerGauche);
			//segment zone securitaire gauche
			math::SegmentDroite2D segP2P2SecuritaireGauche(p2CapteurSecuritaireGauche, p2CapteurDangerGauche);
			math::SegmentDroite2D segP2P3SecuritaireGauche(p2CapteurSecuritaireGauche, p3CapteurSecuritaireGauche);
			math::SegmentDroite2D segP3P3SecuritaireGauche(p3CapteurSecuritaireGauche, p3CapteurDangerGauche);

			glm::dvec2 pointDepartMur = glm::dvec2(elementSurLaTable->at(i)->getPointDepart());
			glm::dvec2 pointFinMur = glm::dvec2(elementSurLaTable->at(i)->getPointFin());
			double rotationMur = elementSurLaTable->at(i)->obtenirRotationRelative()[0];
			glm::dvec2 coin1Mur;
			glm::dvec2 coin2Mur;
			glm::dvec2 coin3Mur;
			glm::dvec2 coin4Mur;
			//std::cout << rotationMur << std::endl;
			calculerCoinMur(pointDepartMur,pointFinMur,coin1Mur,coin2Mur,coin3Mur,coin4Mur,rotationMur);
			/*std::cout << "pointDepartMur x :" << pointDepartMur.x << "\t y: " << pointDepartMur.y << std::endl;
			std::cout << "pointFinMur x :" << pointFinMur.x << "\t y: " << pointFinMur.y << std::endl;
			//std::cout << "pointDepartMur x :" << pointDepartMur.x << "\t y: " << pointDepartMur.y << std::endl;
			if (etatActifCapteurDroit)
			{
				///Verification s'il y a collision au niveau de la zone de danger du capteur droit.
				if (segP1P2DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) || 
					segP1P2DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) || 
					segP1P2DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP1P2DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

					segP2P3DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP2P3DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP2P3DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP2P3DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur) || 

					segP3P4DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP3P4DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP3P4DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP3P4DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur))
				{
					estEnCollisionDangerDroit = true;
					std::cout << "Detection d'un mur dans la zone danger du capteur droit" << std::endl;
				}
				///Verification s'il y a collision au niveau de la zone securitaire du capteur droit
				else if (segP2P2SecuritaireDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP2P2SecuritaireDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP2P2SecuritaireDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP2P2SecuritaireDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

						segP2P3SecuritaireDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP2P3SecuritaireDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP2P3SecuritaireDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP2P3SecuritaireDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

						segP3P3SecuritaireDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP3P3SecuritaireDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP3P3SecuritaireDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP3P3SecuritaireDroit.intersectionAvecSegment(coin4Mur, coin1Mur))
					{
						estEnCollisionSecuritaireDroit = true;
						std::cout << "Detection d'un mur dans la zone securitaire du capteur droit" << std::endl;
					}
			}
			if (etatActifCapteurMilieu)
			{
				///Detection capteur milieu zone danger
				if (segP1P2DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP1P2DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP1P2DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP1P2DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

					segP2P3DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP2P3DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP2P3DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP2P3DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

					segP3P4DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP3P4DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP3P4DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP3P4DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur))
				{
					estEnCollisionDangerMilieu = true;
					std::cout << "Detection d'un mur dans la zone danger du capteur milieu" << std::endl;
				}
				///Verification s'il y a collision au niveau de la zone securitaire du capteur milieu.
				else if (segP2P2SecuritaireMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP2P2SecuritaireMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP2P2SecuritaireMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP2P2SecuritaireMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

						segP2P3SecuritaireMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP2P3SecuritaireMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP2P3SecuritaireMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP2P3SecuritaireMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

						segP3P3SecuritaireMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP3P3SecuritaireMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP3P3SecuritaireMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP3P3SecuritaireMilieu.intersectionAvecSegment(coin4Mur, coin1Mur))
					{
						estEnCollisionSecuritaireMilieu = true;
						std::cout << "Detection d'un mur dans la zone securitaire du capteur milieu" << std::endl;
					}
			}

			if (etatActifCapteurGauche)
			{
				///Detection capteur gauche zone danger
				if (segP1P2DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP1P2DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP1P2DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP1P2DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

					segP2P3DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP2P3DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP2P3DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP2P3DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

					segP3P4DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
					segP3P4DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
					segP3P4DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
					segP3P4DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur))
				{
					estEnCollisionDangerGauche = true;
					std::cout << "Detection d'un mur dans la zone danger du capteur gauche" << std::endl;
				}
				///Verification s'il y a collision au niveau de la zone securitaire du capteur gauche.
				else if (segP2P2SecuritaireGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP2P2SecuritaireGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP2P2SecuritaireGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP2P2SecuritaireGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

						segP2P3SecuritaireGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP2P3SecuritaireGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP2P3SecuritaireGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP2P3SecuritaireGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

						segP3P3SecuritaireGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
						segP3P3SecuritaireGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
						segP3P3SecuritaireGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
						segP3P3SecuritaireGauche.intersectionAvecSegment(coin4Mur, coin1Mur))
					{
						estEnCollisionSecuritaireGauche = true;
						std::cout << "Detection d'un mur dans la zone securitaire du capteur Gauche" << std::endl;
					}
			}
		}
	}

	if (estEnCollisionSecuritaireDroit)
	{
		//algo du profil
		//
	}
	else if (estEnCollisionDangerDroit)
	{
		//algo du profil
		//
	}
	else if (estEnCollisionSecuritaireMilieu)
	{
		//algo du profil
		//
	}
	else if (estEnCollisionDangerMilieu)
	{
		//algo du profil
		//
	}
	else if (estEnCollisionSecuritaireGauche)
	{
		//algo du profil
		//
	}
	else if (estEnCollisionDangerGauche)
	{
		//algo du profil
		//
	}
}

void FacadeModele::calculerCoinMur(glm::dvec2 pointInitial, glm::dvec2 pointFinal, glm::dvec2& p1, glm::dvec2& p2, glm::dvec2& p3, glm::dvec2& p4, const double& theta)
{
	double largeurMur = 0.25;
	p1.x = pointInitial.x + (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p1.y = pointInitial.y - (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));

	p2.x = pointFinal.x + (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p2.y = pointFinal.y - (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));

	p3.x = pointFinal.x - (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p3.y = pointFinal.y + (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));
	
	p4.x = pointInitial.x - (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p4.y = pointInitial.y + (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));
}
*/
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerProfilRobot(char* nomProfil)
///
/// Methode permettant le chargement d'un profil robot.
/// 
/// @param[in] nomProfil: nom du profil a charger.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerProfilRobot(char* nomProfil)
{
	leRobot_->chargerProfil(nomProfil);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerProfilRobot(char* nomProfil)
///
/// Methode permettant l'affichage d'un timestamps en format HH:MM:SS:mmm
/// 
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
std::string FacadeModele::timestamps()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::string heure = std::to_string(time.wHour);
	std::string minute = std::to_string(time.wMinute);
	std::string secondes = std::to_string(time.wSecond);
	std::string ms = std::to_string(time.wMilliseconds);
	if (heure.size() < 2)
		heure = "0" + heure;
	if (minute.size() < 2)
		minute = "0" + minute;
	if (secondes.size() < 2)
		secondes = "0" + secondes;
	if (ms.size() < 2)
		ms = "00" + ms;
	else if (ms.size() < 3)
		ms = "0" + ms;
	return (heure + ":" + minute + ":" + secondes + ":" + ms);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void basculerActivationLumiereAmbiante()
///
/// Cette fonction permet de changer l'etat d'activation de la lumiere ambiante.
/// @author equipe 11 INF2990 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::basculerActivationLumiereAmbiante()
{
	leRobot_->basculerActivationLumiereAmbiante(timestamps());
	lumiereAmbiante_ = !lumiereAmbiante_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void basculerActivationLumiereDirectionnelle()
///
/// Cette fonction permet de changer l'etat d'activation de la lumiere directionnelle.
/// @author equipe 11 INF2990 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::basculerActivationLumiereDirectionnelle()
{
	leRobot_->basculerActivationLumiereDirectionnelle(timestamps());
	lumiereDirectionnelle_ = !lumiereDirectionnelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void basculerActivationSpots()
///
/// Cette fonction permet de changer l'etat d'activation de la lumiere spots.
/// @author equipe 11 INF2990 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::basculerActivationSpots()
{
	leRobot_->basculerActivationSpots(timestamps());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string FacadeModele::etatToString(const ETATS& etat)
///
/// Methode permettant l'affichage de l'etat de comportement d'un robot.
/// 
/// @param[in] etat: L'etat de comportement du robot.
///
/// @return Un string representant l'etat du robot.
///
////////////////////////////////////////////////////////////////////////
std::string FacadeModele::etatToString(const ETATS& etat)
{
	std::string retour = "";
	switch (etat)
	{
	case DEVIATION_DROITE: retour = "deviation vers la droite";
		break;
	case DEVIATION_GAUCHE: retour = "deviation vers la gauche";
		break;
	case EVITER_DROITE: retour = "evitement par la droite";
		break;
	case EVITER_GAUCHE: retour = "evitement par la gauche";
		break;
	case SUIVI_LIGNE: retour = "suivi de ligne";
		break;
	case BALAYAGE_180ETAPE1: retour = "balayage sur 180 degres";
		break;
	case DEFAUT: retour = "defaut";
		break;
	default: retour = "defaut";
		break;
	}
	return retour;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void basculerActivationDebougage()
///
/// Cette fonction permet de changer l'etat d'activation de l'affichage du debougage.
/// @author equipe 11 INF2990 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::basculerActivationDebougage()
{
	if (affichageDebougageActivee_)
		affichageDebougageActivee_ = false;
	else
		affichageDebougageActivee_ = true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::activerVueOrbite()
///
/// Methode permettant d'activer la vue en orbite.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::activerVueOrbite()
{
	//vue::Vue* vue = vue_;
	vue_ = vueOrbite_;
	//vue_ = new vue::VueOrbite
	//{
	//	vue::Camera{
	//		//				z
	//		//				|  
	//		//				| 
	//		//				|------x
	//		//				 \
	//		//			      \
	//		//			       -y
	//		glm::dvec3(0, -200, 200), glm::dvec3(0, 0, 0),
	//		glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0), true },
	//		vue::ProjectionPerspective{
	//			0, 500, 0, 500,
	//			1, 1000, 1, 10000, 1.25,
	//			-25, 25, -25, 25 }, false
	//};
	//delete vue;

	vuePremierePersonneFacadeModele_ = false;
	typeVue_ = ORBITE;
	compteurZoom_ = 0;
}

/// permet de modifier la vue, projection courante a projection orthographique
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::activerVueOrthographique()
///
/// Methode permettant d'activer la vue orthographique
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::activerVueOrthographique()
{
	//vue::Vue* vue = vue_;
	vue_ = vueOrtho_;
	/*vue_ = new vue::VueOrtho{
		vue::Camera{
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0), false },
			vue::ProjectionOrtho{
				0, 500, 0, 500,
				1, 1000, 1, 10000, 1.25,
				-25, 25, -25, 25 }
	};*/
	//delete vue;
	vuePremierePersonneFacadeModele_ = false;
	typeVue_ = ORTHO;
	compteurZoom_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::activerVuePremierePersonne()
///
/// Methode permettant d'activer la vue premiere personne
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::activerVuePremierePersonne()
{
	//std::cout << "premier personne " << std::endl;

	vuePremierePersonneFacadeModele_ = true;

	vue_ = leRobot_->obtenirVuePremierePersonne();
	typeVue_ = PREM_PERSONNE;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherTexteEcran(const std::string& texte, const glm::fvec4& color, const FTPoint& coordDebut,const FTPoint& espacement, const int& taille, const std::string& police) const
///
/// Methode permettant d'afficher a l'ecran le profil actif et le chrono.
///
/// @param[in] texte : Le texte a afficher a l'ecran.
///
/// @param[in] color : Couleur du texte affiche a l'ecran
///
/// @param[in] coordDebut : Coord pixel du premier charactere a afficher.
///
/// @param[in] espacement : espacement x,y,z entre les characteres.
///
/// @param[in] taille: Taille de la police.
///
/// @param[in] police : Nom de la police, necessaire d'avoir un fichier .ttf
/// dans le repertoire de l'executable.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherTexteEcran(const std::string& texte, const glm::fvec4& color, const FTPoint& coordDebut,const FTPoint& espacement, const int& taille, const std::string& police) const
{
	FTGLPixmapFont font(police.c_str());
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPixelTransferf(GL_RED_BIAS, -1.0f + color.r);
	glPixelTransferf(GL_GREEN_BIAS, -1.0f + color.g);
	glPixelTransferf(GL_BLUE_BIAS, -1.0f + color.b);
	glPixelTransferf(GL_ALPHA_BIAS, -1.0f + color.a);
	font.FaceSize(taille);
	font.Render(texte.c_str(), -1, coordDebut, espacement);
	glPopAttrib();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::redimensionnerFenetre(int largeur, int hauteur)
///
/// Methode permettant le redimensionnement de la fenetre.
///
/// @param[in] largeur : Largeur de la fenetre en pixel.
///
/// @param[in] hauteur : Hauteur de la fenetre en pixel.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::redimensionnerFenetre(int largeur, int hauteur)
{
	FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
		glm::ivec2{ 0, 0 },
		glm::ivec2{ largeur, hauteur }
	);
	FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().mettreAJourCloture(); //POURQUOI
	width_ = largeur;
	height_ = hauteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherProfilEtChrono() const
///
/// Methode permettant d'afficher a l'ecran le profil actif et le chrono.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::afficherProfilEtChrono(double tempsAccumule) const
{
	if (compteurAffichageChrono_ >= 2)
		millisecondes_ += tempsAccumule * 1000;
	else
		compteurAffichageChrono_++;

	if (leRobot_ != nullptr && leRobot_->obtenirProfil() != nullptr )
	{
		//Met a jour le chronometre.
		//clock_t end = clock();
		//clock_t difference = end - start;
		//(double)difference; //Attribut necessaire pour la rotation du spot pour le mehdi.
		double seconde = millisecondes_ / 1000;//difference / (double)CLOCKS_PER_SEC;
		int nombreDeSecondes = (int)seconde % 3600;
		int min = nombreDeSecondes / 60;
		int sec = nombreDeSecondes % 60;
		std::string minute = std::to_string(min);
		std::string secondes = std::to_string(sec);
		if (minute.size() < 2)
			minute = "0" + minute;
		if (secondes.size() < 2)
			secondes = "0" + secondes;

		//Tien en compte de la taille de l'affichage pour la fenetre.
		double heightVoulu = 800.0;
		double widthVoulu = 1500.0;
		double facteurRedimensionnementFontHeight = double(height_) / heightVoulu;
		double facteurRedimensionnementFontWidth = double(width_) / widthVoulu;
		int fontSize = int((floor(facteurRedimensionnementFontHeight * 32) + floor(facteurRedimensionnementFontWidth * 32))) / 2;

		//Portion affichage.
		//" Chronometre : " + minute + ":" + secondes

		//if (modeApplication_ == 'S')
		//{
		//	afficherTexteEcran("Profil : " + leRobot_->obtenirProfil()->_profilActif, glm::fvec4(1.0, 0.0, 1.0, 1.0), FTPoint(0.025*width_, 0.1 * height_, 0.0), FTPoint(5.0, 0.0, 0.0), fontSize, "Media/OpenSans-Regular.ttf");
		//	afficherTexteEcran(minute + ":" + secondes, glm::fvec4(1.0, 0.0, 1.0, 1.0), FTPoint(0.025*width_, 0.025 * height_, 0.0), FTPoint(5.0, 0.0, 0.0), fontSize, "Media/OpenSans-Regular.ttf");
		//}
		//else
		//{
		afficherTexteEcran("Profil : " + leRobot_->obtenirProfil()->_profilActif, glm::fvec4(1.0, 1.0, 0.0, 1.0), FTPoint(0.025*width_, 0.1 * height_, 0.0), FTPoint(5.0, 0.0, 0.0), fontSize, "Media/OpenSans-Regular.ttf");
		afficherTexteEcran(minute + ":" + secondes, glm::fvec4(1.0, 1.0, 0.0, 1.0), FTPoint(0.025*width_, 0.04 * height_, 0.0), FTPoint(5.0, 0.0, 0.0), fontSize, "Media/OpenSans-Regular.ttf");
		//}
		//std::cout << "width : " << width_ << "\t" << "height : " << height_ << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::changerModeApplication(char mode)
///
/// Methode permettant de changer le mode de l'application
///
/// @param[in] mode : le mode de l'application 'T' test 'E' edition 'S'
/// simulation.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changerModeApplication(char mode)
{
	modeApplication_ = mode;
	//std::cout << "\nMode change : " << mode << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::playMusicSimulation()
///
/// initie le son dans le mode simulation
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::jouerMusiqueSimulation()
{
	son_->initSimulation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::playMusicEditor()
///
/// initie le son dans le mode edition
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserSonEditeur()
{
	son_->initRobot();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::jouerSonTourner(bool pause))
///
/// toggle pause sur le chanel 4 
///
/// @param[] bool pause 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::jouerSonTourner(bool pause)
{
	son_->setPause(4, pause);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::unloadFmod()
///
/// unload le module Fmod.
///
/// @param[] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererFmod()
{
	son_->liberer();
}

bool FacadeModele::obstacleDetecte()
{
	return leRobot_->obstacleDetecte();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirPositionXElementSelectionne()
///
/// Methode permettant l'obtention de la position X d'un element selectionne.
///
/// @return La position X de l'element selectionne.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirPositionXElementSelectionne()
{
	int nombre;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	double x;
	if (noeud->obtenirType() != arbre_->NOM_LIGNE)
	{
		glm::dvec3 position = noeud->obtenirPositionRelative();
		x = position.x;
	}
	else
	{
		dynamic_cast<NoeudLigne*>(noeud)->mettreAjourCentre();
		glm::dvec3 centre = noeud->obtenirCentre();
		x = centre.x;
	}
	return x;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirPositionYElementSelectionne()
///
/// Methode permettant l'obtention de la position Y d'un element selectionne.
///
/// @return La position Y de l'element selectionne.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirPositionYElementSelectionne()
{
	int nombre;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	double y;
	if (noeud->obtenirType() != arbre_->NOM_LIGNE)
	{
		glm::dvec3 position = noeud->obtenirPositionRelative();
		y = position.y;
	}
	else
	{
		dynamic_cast<NoeudLigne*>(noeud)->mettreAjourCentre();
		glm::dvec3 centre = noeud->obtenirCentre();
		y = centre.y;
	}
	return y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirRotationElementSelectionne()
///
/// Methode permettant l'obtention de la rotation d'un objet selectione.
///
/// @return Angle de rotation de l'element selectionne.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirRotationElementSelectionne()
{
	int nombre;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	double reponse;
	if (noeud->obtenirType() == arbre_->NOM_LIGNE)
	{
		reponse = dynamic_cast<NoeudLigne*>(noeud)->obtenirRotation();
	}
	else
		reponse = noeud->obtenirRotationRelative().x;
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirEchelleElementSelectionne()
///
/// Methode permettant l'obtention de l'echelle d'un objet selectione.
///
/// @return Echelle de l'element selectionne.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirEchelleElementSelectionne()
{
	int nombre;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	return noeud->obtenirRedimensionnementRelative().x;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::noeudSelectionneEstFleche()
///
/// Methode permettant de savoir si l'objet selectionnee est une fleche.
///
/// @return Vrai si l'element selectionne est une fleche. Faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::noeudSelectionneEstFleche()
{
	int nombre;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	std::string type = noeud->obtenirType();
	bool reponse = false;
	if (type == arbre_->NOM_FLECHE)
		reponse = true;
	else
		reponse = false;
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::noeudSelectionneEstLigne()
///
/// Methode permettant de savoir si l'objet selectionnee est une ligne.
///
/// @return Vrai si l'element selectionne est une ligne. Faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::noeudSelectionneEstLigne()
{
	int nombre;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	std::string type = noeud->obtenirType();
	bool reponse = false;
	if (type == arbre_->NOM_LIGNE)
		reponse = true;
	else
		reponse = false;
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::determinerCouleurPixel(int mouseX, int mouseY, GLubyte  couleurPixel[])
///
/// Methode permettant de determiner la couleur du pixel a la position X,Y.
///
/// @param[in] mouseX : Position X de la souris en coordonnee de cloture.
///
/// @param[in] mouseY : Position Y de la souris en coordonnee de cloture.
///
/// @param[in] couleurPixel : Table contenant la couleur du pixel.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::determinerCouleurPixel(int mouseX, int mouseY, GLubyte  couleurPixel[])
{
	GLubyte couleurDuPixel[3];
	for (unsigned int i = 0; i < 3; i++)
		couleurDuPixel[i] = couleurPixel[i];
	glFlush();
	glFinish();
	GLint cloture[4]; glGetIntegerv(GL_VIEWPORT, cloture);
	GLint posX = mouseX, posY = cloture[3] - mouseY;
	glReadBuffer(GL_BACK);
	glReadPixels(posX, posY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, couleurDuPixel);
	for (unsigned int i = 0; i < 3; i++)
		couleurPixel[i] = couleurDuPixel[i];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomIn()
///
/// Cette fonction applique un zoom avant sur le présent volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomIn()
{
	vue_->zoomerIn();
	compteurZoom_++;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomOut()
///
/// Cette fonction applique un zoom arrière sur le présent volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomOut()
{
	 vue_->zoomerOut();
	 compteurZoom_--;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::pauseSonSimulation()
///
/// Cette fonction permet de mettre en pause le son de la simulation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::pauseSonSimulation()
{
	son_->pauseSonSimulation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::UnPauseSonSimulation()
///
/// Cette fonction permet de mettre en marche le son de la simulation apres
/// une pause.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::UnPauseSonSimulation()
{
	son_->UnPauseSonSimulation();
}

//cette methode parcourt l arbre de rendu pour chercher un noeud possedant un certain ID
NoeudAbstrait * FacadeModele::GetNodeByID(std::string id)
{
	NoeudAbstrait* noeud = NULL;
	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	std::vector<NoeudAbstrait*> * children = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants();
		for (int i = 0; i < nombreEnfants; i++)
	{
		NoeudAbstrait* noeudTemp = children->at(i);
		if (!noeudTemp->ID.compare(id) )
		{
			noeud = noeudTemp;
		}
	}
	return noeud;
}

void FacadeModele::CreatePoteau(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, '#');

	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, arbre_->NOM_POTEAU, tokens[0]);
	//noeud->ID = tokens[Id];
	noeud->assignerAffiche(tokens[Affiche] == "1" ? true : false);
	noeud->assignerAffiche(tokens[Enregistrable] == "1" ? true : false);
	noeud->assignerAffiche(tokens[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(tokens[Angle].c_str()), std::atof(tokens[x].c_str()),
		std::atof(tokens[y].c_str()), std::atof(tokens[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(tokens[Pos_x].c_str()), std::atof(tokens[Pos_y].c_str()),
		std::atof(tokens[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(tokens[Redim_x].c_str()),
		std::atof(tokens[Redim_y].c_str()), std::atof(tokens[Redim_z].c_str())));
	noeud->setPoints(glm::dvec3(std::atof(tokens[Depart_x].c_str()), std::atof(tokens[Depart_y].c_str()),
		std::atof(tokens[Depart_z].c_str())), glm::dvec3(std::atof(tokens[Fin_x].c_str()),
		std::atof(tokens[Fin_y].c_str()), std::atof(tokens[Fin_z].c_str())));
}

void FacadeModele::CreateMur(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, '#');

	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, arbre_->NOM_MUR, tokens[0]);
	//noeud->ID = tokens[Id];
	noeud->assignerAffiche(tokens[Affiche] == "1" ? true : false);
	noeud->assignerAffiche(tokens[Enregistrable] == "1" ? true : false);
	noeud->assignerAffiche(tokens[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(tokens[Angle].c_str()), std::atof(tokens[x].c_str()), 
		std::atof(tokens[y].c_str()), std::atof(tokens[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(tokens[Pos_x].c_str()), std::atof(tokens[Pos_y].c_str()),
		std::atof(tokens[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(tokens[Redim_x].c_str()), 
		std::atof(tokens[Redim_y].c_str()), std::atof(tokens[Redim_z].c_str())));
	noeud->setPoints(glm::dvec3(std::atof(tokens[Depart_x].c_str()), std::atof(tokens[Depart_y].c_str()), 
		std::atof(tokens[Depart_z].c_str())), glm::dvec3(std::atof(tokens[Fin_x].c_str()), 
		std::atof(tokens[Fin_y].c_str()), std::atof(tokens[Fin_z].c_str())));

	noeud->mettreAjourCentre();
}

NoeudAbstrait* FacadeModele::CreateSegment(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, '#');

	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, arbre_->NOM_SEGMENT, tokens[0]);
	//noeud->ID = tokens[Id];
	noeud->assignerAffiche(tokens[Affiche] == "1" ? true : false);
	noeud->assignerAffiche(tokens[Enregistrable] == "1" ? true : false);
	noeud->assignerAffiche(tokens[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(tokens[Angle].c_str()), std::atof(tokens[x].c_str()),
		std::atof(tokens[y].c_str()), std::atof(tokens[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(tokens[Pos_x].c_str()), std::atof(tokens[Pos_y].c_str()),
		std::atof(tokens[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(tokens[Redim_x].c_str()),
		std::atof(tokens[Redim_y].c_str()), std::atof(tokens[Redim_z].c_str())));
	noeud->setPoints(glm::dvec3(std::atof(tokens[Depart_x].c_str()), std::atof(tokens[Depart_y].c_str()),
		std::atof(tokens[Depart_z].c_str())), glm::dvec3(std::atof(tokens[Fin_x].c_str()),
			std::atof(tokens[Fin_y].c_str()), std::atof(tokens[Fin_z].c_str())));

	noeud->mettreAjourCentre();
	return noeud;
}

void FacadeModele::CreateLine(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, ':');
	std::vector<std::string> root = utilitaire::split(tokens[0], '#');

	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud(arbre_->NOM_TABLE, arbre_->NOM_LIGNE, root[0]);
	///noeud->ID = tokens[Id];
	noeud->assignerAffiche(root[Affiche] == "1" ? true : false);
	noeud->assignerAffiche(root[Enregistrable] == "1" ? true : false);
	noeud->assignerAffiche(root[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(root[Angle].c_str()), std::atof(root[x].c_str()),
		std::atof(root[y].c_str()), std::atof(root[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(root[Pos_x].c_str()), std::atof(root[Pos_y].c_str()),
		std::atof(root[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(root[Redim_x].c_str()),
		std::atof(root[Redim_y].c_str()), std::atof(root[Redim_z].c_str())));
	
	for (int i = 1; i < tokens.size(); i++)
	{
		(NoeudPoteau*)noeud->ajouter(CreateSegment(tokens[i].c_str()));
	}
	noeud->mettreAjourCentre();
}

void FacadeModele::ModifyPoteau(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, '#');
	NoeudAbstrait* noeud = GetNodeByID(tokens[0]); 
	
	//noeud->assignerAffiche(tokens[Affiche] == "1" ? true : false);
	//noeud->assignerAffiche(tokens[Enregistrable] == "1" ? true : false);
	//noeud->assignerAffiche(tokens[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(tokens[Angle].c_str()), std::atof(tokens[x].c_str()),
		std::atof(tokens[y].c_str()), std::atof(tokens[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(tokens[Pos_x].c_str()), std::atof(tokens[Pos_y].c_str()),
		std::atof(tokens[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(tokens[Redim_x].c_str()),
		std::atof(tokens[Redim_y].c_str()), std::atof(tokens[Redim_z].c_str())));
	noeud->setPoints(glm::dvec3(std::atof(tokens[Depart_x].c_str()), std::atof(tokens[Depart_y].c_str()),
		std::atof(tokens[Depart_z].c_str())), glm::dvec3(std::atof(tokens[Fin_x].c_str()),
			std::atof(tokens[Fin_y].c_str()), std::atof(tokens[Fin_z].c_str())));
}

void FacadeModele::ModifyMur(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, '#');
	NoeudAbstrait* noeud = GetNodeByID(tokens[0]);

	//noeud->assignerAffiche(tokens[Affiche] == "1" ? true : false);
	//noeud->assignerAffiche(tokens[Enregistrable] == "1" ? true : false);
	//noeud->assignerAffiche(tokens[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(tokens[Angle].c_str()), std::atof(tokens[x].c_str()),
		std::atof(tokens[y].c_str()), std::atof(tokens[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(tokens[Pos_x].c_str()), std::atof(tokens[Pos_y].c_str()),
		std::atof(tokens[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(tokens[Redim_x].c_str()),
		std::atof(tokens[Redim_y].c_str()), std::atof(tokens[Redim_z].c_str())));
	noeud->setPoints(glm::dvec3(std::atof(tokens[Depart_x].c_str()), std::atof(tokens[Depart_y].c_str()),
		std::atof(tokens[Depart_z].c_str())), glm::dvec3(std::atof(tokens[Fin_x].c_str()),
			std::atof(tokens[Fin_y].c_str()), std::atof(tokens[Fin_z].c_str())));

	noeud->mettreAjourCentre();
}

void FacadeModele::ModifyLine(const char* data)
{
	std::string dataString(data);
	std::vector<std::string> tokens = utilitaire::split(data, ':');
	std::vector<std::string> root = utilitaire::split(tokens[0], '#');
	NoeudLigne* noeud = (NoeudLigne*)GetNodeByID(root[0]);

	//noeud->assignerAffiche(root[Affiche] == "1" ? true : false);
	//noeud->assignerAffiche(root[Enregistrable] == "1" ? true : false);
	//noeud->assignerAffiche(root[Selectionnable] == "1" ? true : false);

	noeud->assignerRotationRelative(glm::dvec4(std::atof(root[Angle].c_str()), std::atof(root[x].c_str()),
		std::atof(root[y].c_str()), std::atof(root[z].c_str())));
	noeud->assignerPositionRelative(glm::dvec3(std::atof(root[Pos_x].c_str()), std::atof(root[Pos_y].c_str()),
		std::atof(root[Pos_z].c_str())));
	noeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(root[Redim_x].c_str()),
		std::atof(root[Redim_y].c_str()), std::atof(root[Redim_z].c_str())));

	//noeud->vider();
	int nbreSegments = noeud->obtenirNombreEnfants();
	std::vector<NoeudAbstrait*>* segments = noeud->obtenirEnfants();
	int min = (nbreSegments < tokens.size() - 1) ? nbreSegments : tokens.size() - 1;
	int max = (nbreSegments > tokens.size() - 1) ? nbreSegments : tokens.size() - 1;
	//cout
	for (int i = 0; i < min; i++)
	{
		std::vector<std::string> segmentData = utilitaire::split(tokens[i + 1], '#');
		NoeudSegment* segmentNoeud = (NoeudSegment*)segments->at(i);
		segmentNoeud->assignerRotationRelative(glm::dvec4(std::atof(segmentData[Angle].c_str()), std::atof(segmentData[x].c_str()),
			std::atof(segmentData[y].c_str()), std::atof(segmentData[z].c_str())));
		segmentNoeud->assignerPositionRelative(glm::dvec3(std::atof(segmentData[Pos_x].c_str()), std::atof(segmentData[Pos_y].c_str()),
			std::atof(segmentData[Pos_z].c_str())));
		segmentNoeud->assignerRedimensionnementRelative(glm::dvec3(std::atof(segmentData[Redim_x].c_str()),
			std::atof(segmentData[Redim_y].c_str()), std::atof(segmentData[Redim_z].c_str())));
		segmentNoeud->setPoints(glm::dvec3(std::atof(segmentData[Depart_x].c_str()), std::atof(segmentData[Depart_y].c_str()),
			std::atof(segmentData[Depart_z].c_str())), glm::dvec3(std::atof(segmentData[Fin_x].c_str()),
				std::atof(segmentData[Fin_y].c_str()), std::atof(segmentData[Fin_z].c_str())));

		segmentNoeud->mettreAjourCentre();
	}
	for (int i = min; i < nbreSegments; i++)
		noeud->effacer(segments->at(i));
	for(int i = min; i < tokens.size() - 1; i++)
		noeud->ajouter(CreateSegment(tokens[i + 1].c_str()));
	noeud->mettreAjourCentre();
}

bool FacadeModele::ChangerConfigurationObjetSelectionne(double x, double y, double angle, double scale)
{
	int nombre = true;
	NoeudAbstrait* noeud = chercherNouedSelectionne(nombre);
	glm::dvec3 position = noeud->obtenirPositionRelative();
	glm::dvec4 rotation = noeud->obtenirRotationRelative();
	glm::dvec3 echelle = noeud->obtenirRedimensionnementRelative();

	assignerPositionPourObjetSelectionne(x, y, 0);
	changerScalePourObjetSelectionne(scale / echelle[0]);
	PivoterObjetSelectionne(2 * (angle - rotation[0]));
	bool retour = true;
	if (!noeud->estDansLaTable())
	{
		assignerPositionPourObjetSelectionne(position[0], position[1], position[2]);
		changerScalePourObjetSelectionne(echelle[0] / scale);
		PivoterObjetSelectionne(2 * (rotation[0] - angle));
		retour = false;
	}
	return retour;
}

///
/// @fn int FacadeModele::obtenirNmbreNoeudsSelectionnes()
///
/// Cette fonction permet le retour du nombre de noeud sélectionné par
/// l'utilisateur
///
/// @return Le nombre de noeud sélectionné.
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirNbreNoeudsParType(std::string type)
{
	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	int nombre = 0;
	std::vector<NoeudAbstrait*> * vecteur = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants();
	for (int i = 0; i < nombreEnfants; i++)
	{
		if (vecteur->at(i)->obtenirType()== type)
		{
			nombre++;
		}
	}
	return nombre;
}

//Obtenir les IDs des noeuds selectionnes
std::string FacadeModele::obtenirIDsNoeudsSelectionnes()
{
	std::string retour = "";
	int	nombre = obtenirNombreNoeudsSelectionnes();
	std::vector<NoeudAbstrait*> noeudSelectionnes;
	NoeudAbstrait* noued = NULL;
	int nombreEnfants = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	for (int i = 0; i < nombreEnfants; i++)
	{
		noued = arbre_->chercher(arbre_->NOM_TABLE)->obtenirEnfants()->at(i);
		if (noued->estSelectionne())
		{
			//retour += ((NoeudPoteau*)noued)->ID + ";";
			noeudSelectionnes.push_back(noued);
		}
	}
	if (nombre > 1)
	{
		for (int i = 0; i < nombre - 1; i++)
		{
			retour += noeudSelectionnes[i]->ID + ";";
		}
		retour += noeudSelectionnes[nombre - 1]->ID;
	}
	else if (nombre == 1)
	{
		retour += noeudSelectionnes[0]->ID;
	}
	return retour;
}

//Methode utilisee pour la selection en ligne, elle recoit une liste des IDs noeuds
//selectionnes des autres utilisateurs ainsi que la couleur de selection et fait le necessaire apres
void FacadeModele::SelectNodes(char * broadcastElements)
{
	//std::cout << "reception from server de : " << broadcastElements << std::endl;
	//Tout deselectionner
	std::string broadcastElements1(broadcastElements);
	if (broadcastElements1 == "d")
	{
		arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
		return;
	}
	arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
	NoeudAbstrait * noeud = NULL;
	//recuperer les IDs et les couleurs de selection pour tous les noeuds
	std::string dataString(broadcastElements);
	std::vector<std::string> nodes = utilitaire::split(dataString, '@');
	//traiter les noeuds
	std::string tempString = "";
	std::vector<std::string> idsTemp;
	std::vector<std::string> results;
	std::string colorTemp;
	std::vector<std::string> rgbStringValues;
	int r, g, b;
	for (int i = 0; i < nodes.size(); i++)
	{
		tempString = nodes[i]; //string representant le noeud
		results = utilitaire::split(tempString, ';');
		colorTemp = results[results.size() - 1]; //results contains IDs;r:g:b
		rgbStringValues = utilitaire::split(colorTemp, ':');
		r = std::stoi(rgbStringValues[0]);
		g = std::stoi(rgbStringValues[1]);
		b = std::stoi(rgbStringValues[2]);
		for (int j = 0; j < results.size() - 1;j++)
		{
			noeud = GetNodeByID(results[j]);
			if (noeud->obtenirType() == arbre_->NOM_LIGNE)
			{
				std::vector<NoeudAbstrait*> * children = noeud->obtenirEnfants();
				for (int k = 0; k < noeud->obtenirNombreEnfants(); k++)
				{
					children->at(k)->setCustomSelectColor(r, g, b);
				}
			}
			noeud->setCustomSelectColor(r, g, b);
			noeud->selectionnerTout();
		}
	}

}

void FacadeModele::DeselectNoeuds(char * ids[], short size) //DeleteNodes
{
	NoeudAbstrait * node = NULL;
	for (int i = 1; i < size; i++)
	{
		node = GetNodeByID(ids[i]);
		node->assignerSelection(false);
	}
}

void FacadeModele::DeleteNodes(char * ids[], short size)
{
	std::vector<NoeudAbstrait*> nodesToDelete;
	NoeudAbstrait * node = NULL;
	std::cout << "je suis la size: " << size << std::endl;
	for (int i = 0; i < size; i++)
	{
		node = GetNodeByID(std::string(ids[i]));
		arbre_->effacer(node);
	}
}

void FacadeModele::ScaleSelectionOnline(char * IDsAndFactor)//exemple P1;M5:2.5
{
	std::cout << "ScaleSelectionOnline appelee" << std::endl;
	std::string dataString(IDsAndFactor);
	//diviser par le separateur ';'
	std::vector<std::string> components = utilitaire::split(dataString, ':');
	std::string factorString = components[0]; 
	double factor = std::stod(factorString)/1000 ; std::cout << "factor C++ = " << factor << std::endl;
	std::string IDsString = components[1];
	std::vector<std::string> IDs = utilitaire::split(IDsString, ';');

	std::vector<NoeudAbstrait*> nodesToScale;
	NoeudAbstrait * noeud = NULL;
	//trouver les noeuds a scaler
	for (int i = 0; i < IDs.size(); i++)
	{
		noeud = GetNodeByID(IDs[i]);
		nodesToScale.push_back(noeud);	
	}
	size_t nombreNoeuds = nodesToScale.size();

	std::vector<double> scales(nombreNoeuds);
	for (int i = 0; i < nombreNoeuds; i++)
	{
            scales[i] = nodesToScale[i]->obtenirRedimensionnementRelative()[0];
			nodesToScale[i]->changerScale(factor * nodesToScale[i]->obtenirScaleInitialeEnTraitement()[0] / scales[i]);
	}
	bool scaleCorrect = true;


	for (int i = 0; i < nombreNoeuds; i++)
	{
			if (nodesToScale[i]->obtenirRedimensionnementRelative()[0] < 0.05)
				scaleCorrect = false;
	}
	if (!scaleCorrect)
	{
		for (int i = 0; i < nombreNoeuds; i++)
		{
			nodesToScale[i]->changerScale(scales[i] / (factor * nodesToScale[i]->obtenirScaleInitialeEnTraitement()[0]));
		}
	}
}

//moveNodesOnline
void FacadeModele::moveNodesOnline(char * IDsAndDebutFin)
{
	glm::dvec3 debut;
	glm::dvec3 fin;
	std::string dataString(IDsAndDebutFin);
	//diviser par le separateur ':'
	std::vector<std::string> components = utilitaire::split(dataString, ':');
	std::string pointDebutString = components[0];
	std::string pointFinString = components[1];
	std::string IDsString = components[2];
	std::vector<std::string> IDs = utilitaire::split(IDsString, ';');
	
	std::vector<std::string> debutVecStr = utilitaire::split(pointDebutString, ';');
	std::vector<std::string> finVecStr = utilitaire::split(pointFinString, ';');

	debut.x = std::atof(debutVecStr[0].c_str()); debut.y = std::atof(debutVecStr[1].c_str()); debut.z = std::atof(debutVecStr[2].c_str());
	fin.x = std::atof(finVecStr[0].c_str()); fin.y = std::atof(finVecStr[1].c_str()); fin.z = std::atof(finVecStr[2].c_str());
	
	glm::dvec3 deplacement = fin - debut;
	//trouver les noeuds a deplacer
	std::vector<NoeudAbstrait*> nodesToMove;
	NoeudAbstrait * noeud = NULL;

	for (int i = 0; i < IDs.size(); i++)
	{
		noeud = GetNodeByID(IDs[i]);
		nodesToMove.push_back(noeud);
	}
	size_t nombreNoeuds = nodesToMove.size(); std::cout << "Nombre de noeuds : " << nombreNoeuds << std::endl;

	glm::dvec3 positionTemp, departTemp, finTemp;
	std::vector<NoeudAbstrait*> * children = NULL;
	for (int i = 0; i < nombreNoeuds; i++)
	{

		VisiteurDeplacerSelection* visiteurDeplacerSelection = new VisiteurDeplacerSelection(fin - debut);
		//arbre_->accepterVisiteur(visiteurDeplacerSelection);
		nodesToMove[i]->accepterVisiteur(visiteurDeplacerSelection);
		if (nodesToMove[i]->obtenirType() == arbre_->NOM_LIGNE)
		{
			children = nodesToMove[i]->obtenirEnfants();
			for (int k = 0; k < nodesToMove[i]->obtenirNombreEnfants(); k++)
			{
				children->at(k)->accepterVisiteur(visiteurDeplacerSelection);
			}
			delete visiteurDeplacerSelection;
		}
	}
}

//const char * duplicateSelNoAction(int x, int y, bool estFantome)
const char * FacadeModele::duplicateSelNoAction(int mouseX, int mouseY, bool estFantome)
{
	chaineDeDuplication = "";
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(mouseX, mouseY, point);
	std::string str = estFantome == true ? "1" : "0";
	chaineDeDuplication += std::to_string(point.x) + ";" + std::to_string(point.y) + ";" + str;
	std::cout << "chaine de dupication c++: " << chaineDeDuplication;
	return chaineDeDuplication.c_str();
}

bool FacadeModele::duplicateSelNodes(char * chaineDup)
{
	std::vector<NoeudAbstrait*> * children = NULL;
	glm::dvec3 point;
	std::string dataString(chaineDup);
	std::cout << "data string duplication ++"<< dataString << std::endl;
	std::vector<std::string> mainComponents = utilitaire::split(dataString, ':');
	std::string dataString1 = mainComponents[0];
	std::vector<std::string> IDsToDuplicate = utilitaire::split(mainComponents[1], ';');
	std::vector<std::string> components = utilitaire::split(dataString1, ';');
	point.x = std::atof(components[0].c_str()); point.y = std::atof(components[1].c_str()); point.z = 0;
	std::cout << "point x : " << point.x << "point y :" << point.y << "point z : " << point.z << std::endl;
	bool estFantome = false;
	if (components[2] == "0")
	{
		estFantome = false;
	}
	else if (components[2] == "1")
	{
		estFantome = true;
	}
	NoeudAbstrait * noeudTemp = NULL;
	auto visiteurDeterminerCentreSelection = new VisiteurDeterminerCentreSelection(true);
	for (int i = 0; i < IDsToDuplicate.size(); i++)
	{
		noeudTemp = GetNodeByID(IDsToDuplicate[i]);
		noeudTemp->accepterVisiteur(visiteurDeterminerCentreSelection);
		if (noeudTemp->obtenirType() == arbre_->NOM_LIGNE)
		{
			children = noeudTemp->obtenirEnfants();
			for (int k = 0; k < noeudTemp->obtenirNombreEnfants(); k++)
			{
				children->at(k)->accepterVisiteur(visiteurDeterminerCentreSelection);
			}
		}
	}

	glm::dvec3 deplacementDuplicata = point - visiteurDeterminerCentreSelection->obtenirCentreSelection() + glm::dvec3(0, 0, 14);
	auto visiteurVerifierDeplacementDuplication = new VisiteurVerifierDeplacementDuplication(deplacementDuplicata);
	
	for (int i = 0; i < IDsToDuplicate.size(); i++)
	{
		noeudTemp = GetNodeByID(IDsToDuplicate[i]);
		noeudTemp->accepterVisiteur(visiteurVerifierDeplacementDuplication);
		if (noeudTemp->obtenirType() == arbre_->NOM_LIGNE)
		{
			children = noeudTemp->obtenirEnfants();
			for (int k = 0; k < noeudTemp->obtenirNombreEnfants(); k++)
			{
				children->at(k)->accepterVisiteur(visiteurVerifierDeplacementDuplication);
			}
		}
	}
	bool reponse = false;
	if (visiteurVerifierDeplacementDuplication->estValide())
	{
		auto visiteurDupliquerSelection = new VisiteurDupliquerSelection(deplacementDuplicata, estFantome);
		for (int i = 0; i < IDsToDuplicate.size(); i++)
		{
			noeudTemp = GetNodeByID(IDsToDuplicate[i]);
			noeudTemp->accepterVisiteur(visiteurDupliquerSelection);
			if (noeudTemp->obtenirType() == arbre_->NOM_LIGNE)
			{
				children = noeudTemp->obtenirEnfants();
				for (int k = 0; k < noeudTemp->obtenirNombreEnfants(); k++)
				{
					children->at(k)->accepterVisiteur(visiteurDupliquerSelection);
				}
			}

		}
		reponse = true;
		delete visiteurDupliquerSelection;
	}
	delete visiteurVerifierDeplacementDuplication;
	delete visiteurDeterminerCentreSelection;
	return reponse;
}

void FacadeModele::UpdateMySelNodes(char* data)
{
	mySelectedNodesIDs.clear();
	std::string dataString(data);
	std::vector<std::string> IDs = utilitaire::split(data, ';');
	for (int i = 0; i < IDs.size(); i++)
	{
		mySelectedNodesIDs.push_back(IDs[i]);
	}
}


int FacadeModele::obtenirNombreMySelectedNodes()
{
	return mySelectedNodesIDs.size();
}

void FacadeModele::PivoterselectedNode(char * data)
{
	double deltaY;
	std::string dataString(data);
	std::vector<std::string> components = utilitaire::split(dataString, ':');
	deltaY = std::stod(components[0]);
	std::string IDObjet = components[1];
	deltaY /= 2;
	int nombreNoeud = 0;
	NoeudAbstrait* noeud = GetNodeByID(IDObjet);

	std::vector<NoeudAbstrait*> * children = NULL;
	glm::dvec3 centreSelection;
	auto visiteurDeterminerCentreSelection = new VisiteurDeterminerCentreSelection(false);
	noeud->accepterVisiteur(visiteurDeterminerCentreSelection);
	if (noeud->obtenirType() == arbre_->NOM_LIGNE)
	{
		children = noeud->obtenirEnfants();
		for (int k = 0; k < noeud->obtenirNombreEnfants(); k++)
		{
			children->at(k)->accepterVisiteur(visiteurDeterminerCentreSelection);
		}
	}
	centreSelection = visiteurDeterminerCentreSelection->obtenirCentreSelection();
	auto visiteur = new visiteurRotationUnObjet(deltaY, centreSelection);
	noeud->accepterVisiteur(visiteur);
	if (noeud->obtenirType() == arbre_->NOM_LIGNE)
	{
		children = noeud->obtenirEnfants();
		for (int k = 0; k < noeud->obtenirNombreEnfants(); k++)
		{
			children->at(k)->accepterVisiteur(visiteur);
		}
	}
	delete visiteurDeterminerCentreSelection;
	delete visiteur;
	if (noeud->obtenirType() == arbre_->NOM_LIGNE)
		dynamic_cast<NoeudLigne*>(noeud)->assignerRotation(deltaY + dynamic_cast<NoeudLigne*>(noeud)->obtenirRotation());
}

void FacadeModele::annulerRotationMySelection(char * theIDs)
{
	std::string dataString(theIDs);
	std::vector<std::string> LesIDs = utilitaire::split(dataString, ';');
	NoeudAbstrait * noeud = NULL;
	std::vector<NoeudAbstrait*> * children = NULL;
	VisiteurAnnulerRotationSelection * visiteur = new VisiteurAnnulerRotationSelection;
	for (int i = 0; i < LesIDs.size(); i++)
	{
		noeud = GetNodeByID(LesIDs[i]);
		noeud->accepterVisiteur(visiteur);
		if (noeud->obtenirType() == arbre_->NOM_LIGNE)
		{
			children = noeud->obtenirEnfants();
			for (int k = 0; k < noeud->obtenirNombreEnfants(); k++)
			{
				children->at(k)->accepterVisiteur(visiteur);
			}
		}
	}
	delete visiteur;
}

void FacadeModele::PivoterselectedNodes(char * data)
{
	double deltaY;
	std::string dataString(data);
	std::vector<std::string> components = utilitaire::split(dataString, ':');
	deltaY = std::stod(components[0]);
	std::vector<std::string> theIDs = utilitaire::split(components[1], ';');


	//int n = arbre_->chercher(arbre_->NOM_TABLE)->obtenirNombreEnfants();
	glm::dvec3 centre;
	NoeudAbstrait * noeud = NULL;
	std::vector<NoeudAbstrait*> * children = NULL;
	auto visiteurDeterminerCentreSelection = new VisiteurDeterminerCentreSelection(true);
	for (int i = 0; i < theIDs.size(); i++)
	{
		noeud = GetNodeByID(theIDs[i]);
		noeud->accepterVisiteur(visiteurDeterminerCentreSelection);
		if (noeud->obtenirType() == arbre_->NOM_LIGNE)
		{
			children = noeud->obtenirEnfants();
			for (int k = 0; k < noeud->obtenirNombreEnfants(); k++)
			{
				children->at(k)->accepterVisiteur(visiteurDeterminerCentreSelection);
			}
		}
	}

	centre = visiteurDeterminerCentreSelection->obtenirCentreSelection();
	VisiteurRotateSelection visiteur(deltaY);
	visiteur.setCentre(centre);
	for (int i = 0; i < theIDs.size(); i++)
	{
		noeud = GetNodeByID(theIDs[i]);
		noeud->accepterVisiteur(&visiteur);
		if (noeud->obtenirType() == arbre_->NOM_LIGNE)
		{
			children = noeud->obtenirEnfants();
			for (int k = 0; k < noeud->obtenirNombreEnfants(); k++)
			{
				children->at(k)->accepterVisiteur(&visiteur);
			}
		}
	}
	delete visiteurDeterminerCentreSelection;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
