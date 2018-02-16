//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2016-02-15
/// @version 2.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once


#include <windows.h>
#include <math.h>
#include <string>
#include "ArbreRenduINF2990.h"
#include "NoeudAbstrait.h"
#include "utilitaire.h"
#include "tinyxml2.h"
#include "aidecollision.h"
#include "SegmentDroite2D.h"
#include "VisiteurDetectionNoeud.h"
#include <stdio.h>
#include "Profil.h"
#include "../../Commun/Utilitaire/OpenGL/BoiteEnvironnement.h"
#include <FTGL/ftgl.h>
#include <ctime>
#include <chrono>
#include "son.h"

class NoeudAbstrait;
class NoeudRobot;
class ArbreRenduINF2990;

enum TypeVue {
	ORTHO = 0,
	ORBITE,
	PREM_PERSONNE
};

enum Attribute
{
	Id = 0,
	Type,
	Affiche,
	Enregistrable,
	Selectionnable,
	Angle,
	x,
	y,
	z,
	Pos_x,
	Pos_y,
	Pos_z,
	Redim_x,
	Redim_y,
	Redim_z,
	Depart_x,
	Depart_y,
	Depart_z,
	Fin_x,
	Fin_y,
	Fin_z
};

namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Libère l'instance unique de la classe.
   static void libererInstance();

   const double FacadeModele::LARGEUR_LIGNE{ 0.75 };
   const double FacadeModele::LARGEUR_TABLE{ 48.0 };
   const double FacadeModele::LONGUEUR_TABLE{ 96.0 };
   const double FacadeModele::RAYON_POTEAU{ 1.0 };
   const double FacadeModele::HAUTEUR_POTEAU{ 8.0 };
   const double FacadeModele::LONGUEUR_FLECHE{ 5.0 };
   const double FacadeModele::LARGEUR_FLECHE{ 2.0 };
   const double FacadeModele::LARGEUR_MUR{ 0.25 };
   const double FacadeModele::HAUTEUR_MUR{ 6 };

   /// Crée un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration à partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// sauvgarder les noeuds de l'arbre dans un fichier XML.
   void enregistrerZoneDeSimulation(char* nomFichier);
   /// cree un noeud et l'ajoute a l'arbre 
   void ajouterNoeudArbre(const tinyxml2::XMLElement* elementXML);
   /// charger les noeuds d'un fichier XML dans l'arbre de rendu.
   void chargerZoneDeSimulation(char* nomFichier);
   /// Libère le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du modèle.
   void afficher(double temps) const;
   /// Affiche la base du contenu du modèle.
   void afficherBase() const;

   ///Permet l'appel de la fonction permettant le deplacement de la fenetre vers la gauche
   void deplacerGauche();
   ///Permet l'appel de la fonction permettant le deplacement de la fenetre vers la droite
   void deplacerDroite();
   ///Permet l'appel de la fonction permettant le deplacement de la fenetre vers le haut
   void deplacerHaut();
   ///Permet l'appel de la fonction permettant le deplacement de la fenetre vers la bas
   void deplacerBas();
   ///Permet le deplacement de la fenetre virtuelle avec la souris
   void deplacerFenetreVirtuelleSouris(int x, int y);
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// Réinitialise la scène.
   void reinitialiser();

   /// Anime la scène.
   void animer(float temps);

   /// Ajout de noeud
   const char* ajouterNoeudSimple(char* nom, int x, int y, bool enligne = false, char* id = "");
   ///Ajout d'un noeud a l'arbre de rendu avec un certain redimensionnement.
   const char* ajouterNoeudAvecScale(char* nom, int x1, int y1, int x2, int y2, bool estConcret, bool enLigne = false, char* id = "");


   /// Suppression du dernier noeud ajouté
   void supprimerDernierNoeud();
   /// Suppression de la dernière ligne ajoutée
   void supprimerDerniereLigne();

   ///Permet de calculer les dimensions d'une ligne
   glm::dvec3 calculerDimensions(double& longueur, double& angle, const glm::dvec3& point1, const glm::dvec3& point2);
   ///Permet le calcul des quatres points d'un segment
   void FacadeModele::calculerPointsSegment(const double& longueur, const double& angle, const glm::dvec3& centre, glm::dvec3& point1, glm::dvec3& point2);

   /// Vérification de la position du curseur si dans la zone de simulation
   bool verifierCurseur(int x, int y);

   /// Vérification si la position du curseur permet d'editer un poteau dans la zone de simulation
   bool verifierCurseurPoteau(int x, int y);

   /// Vérification si la position du curseur permet d'editer un mur dans la zone de simulation
   bool verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin);

   /// Vérification si la position du curseur permet d'editer une ligne dans la zone de simulation
   bool verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin);

   /// verifie si un rectangle defini par point debut et point fin et la largeur est dans la table
   //bool rectangleDansLaTable(glm::dvec3 pointDebut, glm::dvec3 pointFin, double largeur);

   ///Sauvegarde la position de la souris lors d'un clic.
   void sauverPositionSouris(int x, int y);
   
   /// intialise et met a jour le rectangle elastique
   void tracerRectangleElastique(int x, int y);
   /// permet d'effacer le rectangle elastique
   void terminerRectangleElastique(int x, int y);

   ///Permet le zoom in avec le rectangle elastique
   void zoomInRectangle(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture);
   ///Permet le zoom out avec le rectangle elastique
   void zoomOutRectangle(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture);

   /// permet de deplacer les objets selectionnes
   const char * deplacerSelection(int xDebut, int yDebut, int xFin, int yFin);
   const char * deplacerSelNoAction(int xDebut, int yDebut, int xFin, int yFin);
   /// permet un redimensionnement sur les objets selectionnes
   const char* scaleSelection(double facteurScale);
   /// permet de supprimer tous les noeuds selectionnes
   void supprimerSelection();
   
   ///--- Fonctions selection
   /// selectionner un objet avec la souris
   ///void selectionnerObjet(int mouseX, int mouseY, bool selectionUnique);
   const char * selectionnerObjet(int mouseX, int mouseY, bool selectionUnique);
   /// dupliquer les objets selectionnes selon la position du click de la souris
   bool dupliquerSelection(int mouseX, int mouseY, bool estFantome);
   /// ajouter noeud suite a la duplication d'objets selectionne
   NoeudAbstrait* ajouterNoeudDuplique(char* nom, NoeudAbstrait* parent, glm::dvec3 position, double scale, 
										double angleRotation, glm::dvec3 pointDepart, glm::dvec3 pointFin, bool estFantome);
   /// suppression de noeuds dupliques
   void supprimerNoeudsDupliques();
   //selection avec le rectangle elastique
   const char * selectRectElastique(int X_debut, int Y_debut, int X_fin, int Y_fin, bool estEnfonce);
   void selectRectElastique1(int X_debut, int Y_debut, int X_fin, int Y_fin, bool estEnfonce);

   void assignerPositionPourObjetSelectionne(double x, double y, double z);
   ///Assigne la nouvelle rotation d'un objet selectionné
   void assignerRotationPourObjetSelectionne(double rotation);
   ///Assigne une nouvelle dimension à un objet selectionné
   void changerScalePourObjetSelectionne(double scale);
   ///Permet la recherche d'un noeud sur lequel un clic a été fait
   NoeudAbstrait* chercherNouedSelectionne(int& nombre);
   /// permet de sauvgarder la poisiton courante avant une modification
   void initialiserEnTraitement();
   /// permet le sauvgarder le rediemensionnement courant avant une modification
   void initialiserScaleEnTraitement();

   //rotation
   //PivoterObjetSelectionne
   ///Permet la rotation d'un objet selectionné
   void PivoterObjetSelectionne(double deltaY);
   ///Méthode permettant le retour du nombre de noeud selectionné
   int obtenirNombreNoeudsSelectionnes();
   int obtenirNombreMySelectedNodes();
   ///Methode permettant de faire pivoter plusieurs objets a la fois.
   void PivoterObjetsMultiples(double rotation);
   ///Methode permettant de faire pivoter des objets autour de leurs centre.
   void rotaterPointAutourDecentre(double centreX, double centreY, double angle, glm::dvec3 & point);
   ///Methode permettant de verifier un objet est sur la table ou non.
   bool objetsSelectionnesSurLaTable();
   ///Methode permettant d'effectuer une rotation a un certain objet avec un certain angle.
   bool tournerObjetSelectionne(double angle);
   ///Methode permettant d'obtenir l'angle initiale de rotation relatif a son objet parent.
   double obtenirAngleAvantRotation(NoeudAbstrait * noeud){ return noeud->getRotationRelativeAvantraitement()[0]; };
   ///Methode permettant d'annuler la rotation d'un objet selectionne.
   void annulerRotationSelection();
   void annulerRotationMySelection(char * theIDs);
   ///Methode permettant d'annuler un redimensionnement.
   void retournerAuScaleInitiale();
   /// permet d'ajouter le robot et le positionner au point de départ 
   void initialiserRobot(bool vuePremierePersonne);
   /// permet de détruire le noeud robot et les noeuds roue droite et gauche
   void libererRobot();

   /// permet d'arreter le robot
   void arreterRobot();
   /// permet de controller le mouvement du robot
   void actionnerRobot(double rapportVitesseGauche, double rapportVitesseDroit, bool sensDirect);
   /// permet de retourner le pointeur vers l'objet Robot 
   NoeudRobot* obtenirRobot(){ return leRobot_; };
   /// Methode permettant de lancer la simulation en initilalisant le robot 
   void debuterSimulation();
   //void detectionCapteurs();
   ///Cette methode permet de calculer les coins d'un noeud mur.
   void calculerCoinMur(glm::dvec2 pointInitial, glm::dvec2 pointFinal, glm::dvec2& p1, glm::dvec2& p2, glm::dvec2& p3, glm::dvec2& p4, const double& theta);
   ///Methode permettant d'actionner le mode automatique.
   void actionnerModeAutomatique();
   ///Methode permettant d'arreter le mode automatique.
   void stopperModeAutomatique();
   ///Visiteur public permettant la detection des noeud poteau et mur par les capteurs de distance.
   VisiteurAbstrait* visiteurDetectionNoeud{nullptr};
   ///Setter de l'attribut arbre pour les test.
   void setArbreFacadeModeleTest(ArbreRenduINF2990* arbre)
   {
	   arbre_ = arbre; 
   }
   ///Methode permettant le chargement du profil present dans un fichier xml.
   void chargerProfilRobot(char* nomProfil);
   ///Methode permettant l'affichage des timestamps pour le deboguage console.
   std::string timestamps();

   ///Methode permettant de faire basculer l'activation de debougage.
   void basculerActivationDebougage();
   ///Permet l'affichage de l'etat de comportement du robot dans la console.
   std::string etatToString(const ETATS& etat);

   ///Methode permettant l'obtention de l'affichage de debugage console.
   bool obtenirAffichageDebougage() { return affichageDebougageActivee_; };

   /// permet de modifier la vue, projection courante a projection perspective;
   void activerVueOrbite();
   /// permet de modifier la vue, projection courante a projection orthographique
   void activerVueOrthographique();
   /// permet d'activer la vue premier personne
   void activerVuePremierePersonne();

   /// basculer les divers mode d'affichage.
   void basculerActivationLumiereAmbiante();
   /// permet de basucler la lumiere directionnelle
   void basculerActivationLumiereDirectionnelle();
   /// permet de basculer les spots
   void basculerActivationSpots();

   /// permet d'afficher le texte en openGL a l'ecran
   void afficherTexteEcran(const std::string& texte, const glm::fvec4& color, const FTPoint& coordDebut, const FTPoint& espacement, const int& taille, const std::string& police) const;
   /// retourne le temps ecoule depuis le debut de la simulation
   int timeElapsed();
   /// permet de d'effectuer un redimensionnement de la fenetre
   void redimensionnerFenetre(int largeur, int hauteur);
   /// permet d'afficher le profil et le chronometre a l'ecran
   //void afficherProfilEtChrono() const;
   void afficherProfilEtChrono(double tempAccumulee) const;
   /// permet de changer le mode courant du lancement de l'application (edition/test/simulation)
   void changerModeApplication(char mode);
   /// permet d'obtenir la position X d'un element selectionne
   double obtenirPositionXElementSelectionne();
   /// permet d'obtenir la position Y d'un element selectionne
   double obtenirPositionYElementSelectionne();
   /// permet d'obtenir la rotation d'un element selectionne
   double obtenirRotationElementSelectionne();
   /// permet d'obtenir la mise a l'echelle d'un element selectionne
   double obtenirEchelleElementSelectionne();
   /// permet de savoir si le noeud selectionne est une fleche
   bool noeudSelectionneEstFleche();
   /// permet de savoir si le noeud selectionne est une ligne
   bool noeudSelectionneEstLigne();
   /// permet d'effectuer un zoomIn 
   void zoomIn();
   /// permet d'effectuer un zoomOut 
   void zoomOut();
   
   // FMOD
   /// permet de jouer la musique de la simulation
   void jouerMusiqueSimulation(); 
   /// permet d'initialiser le son en mode editeur
   void initialiserSonEditeur();
   /// permet de jouer le son lors de la rotation
   void jouerSonTourner(bool pause);
   /// permet de librer le FMOD
   void libererFmod();

   bool obstacleDetecte();
   /// instance du son 
   Son * son_;
   /// permet de determiner la couleur du pixel a la position x, y
   void determinerCouleurPixel(int mouseX, int mouseY, GLubyte  couleurPixel[]);
   void pauseSonSimulation();
   void UnPauseSonSimulation();

   //////// Projet 3
   std::string  chaineSelection ; // pour contourner le probleme de Marshaling de char *
   int obtenirNbreNoeudsParType(std::string type);
   std::string obtenirIDsNoeudsSelectionnes();
   //methodes utilisees pour l'edition en ligne
   NoeudAbstrait* GetNodeByID(std::string id);
   void SelectNodes(char * broadcastElements);
   void ScaleSelectionOnline(char * IDsAndFactor);
   void moveNodesOnline(char * IDsAndDebutFin);
   void DeselectNoeuds(char * ids[], short size);
   void DeleteNodes(char * ids[], short size);
   void CreatePoteau(const char* data);
   void CreateMur(const char* data);
   NoeudAbstrait* CreateSegment(const char* data);
   void CreateLine(const char* data);
   void ModifyPoteau(const char* data);
   void ModifyMur(const char* data);
   void ModifyLine(const char* data);
   void UpdateMySelNodes(char* data);
   void PivoterselectedNode(char * data);
   void PivoterselectedNodes(char * data);
   bool ChangerConfigurationObjetSelectionne(double x, double y, double rotation, double echelle);
   void modifyNode(char* data);
   const char * duplicateSelNoAction(int x, int y, bool estFantome);
   bool duplicateSelNodes(char * chaineDup);

   std::string chaineDeSauvegarde;
   std::string chaineDeDeplacement;
   std::string mySelectedIDs_;
   std::string chaineDeDuplication;
   int compteurDupliques = 1;
   std::vector<std::string> mySelectedNodesIDs;
private:
	/// permet d'initialiser un rectangle elsatique 
	void intialiserRectangleElastique(int x, int y);
	/// permet de mettre a jour le rectangle elastique
	void mettreAjourRectangleElastique(int x, int y);
   /// Constructeur par défaut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie désactivé.
   FacadeModele(const FacadeModele&) = delete;
   /// Opérateur d'assignation désactivé.
   FacadeModele& operator =(const FacadeModele&) = delete;
   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;
   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;
   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_{ nullptr };
   glm::dvec3 positionSourisClick_;
   /// Vue courante de la scène.
   vue::Vue* vue_{ nullptr };
   /// vues possibles 
   vue::Vue* vueOrtho_{ nullptr };
   vue::Vue* vueOrbite_{ nullptr };
   /// Arbre de rendu contenant les différents objets de la scène.
   ArbreRenduINF2990* arbre_{ nullptr };
   /// la facade a une reference vers le robot 
   NoeudRobot* leRobot_{ nullptr };
   /// Attribut contenant le dernier noeud enfant ajouté à la zone de simulation.
   NoeudAbstrait* dernierNoeudEnfantAjoute_{ nullptr };
   /// Attribut contenant le dernier noeud enfant concret (non fantôme) ajouté à la zone de simulation.
   NoeudAbstrait* dernierNoeudEnfantConcretAjoute_{ nullptr };
   /// Attribut contenant le dernier noeud composite ajouté à la zone de simulation.
   NoeudAbstrait* dernierNoeudCompositeAjoute_{ nullptr };
   /// Attribut contenant l'angle du dernier noeud de type segment ajouté.
   double angleDernierSegment_;

   /// point lors du clic pour continuer a tracer le rectangle elastique
   glm::ivec2 pointAncrage_;
   /// point avant qu'un drag and drop a ete realise
   glm::ivec2 pointAvant_;
   /// point apres drag and drop permettant de mettre a jour le rectangle elastique
   glm::ivec2 pointApres_;
   /// point au moment ou on relache le bouton du click afin d'effacer le rectangle elastique
   glm::ivec2 pointFinal_;
   /// si true le rectangle a ete trace  
   bool rectangleElastiqueTrace_ = false;
   /// permet de verifier si le mode automatique est actif
   bool estLeTourModeAutomatique_ = false;
   /// permet de verifier le debogague doit etre actif
   bool affichageDebougageActivee_ = true;
   /// permet de verifier si la lumiere ambiante est active ou non
   bool lumiereAmbiante_ = true;
   /// permet de verifier si la lumiere directionnelle est active ou non
   bool lumiereDirectionnelle_ = true;
   /// instance de la skybox
   utilitaire::BoiteEnvironnement* skybox_{ nullptr };
   /// tableau permettant d'expoter les images formant la skybox
   std::string skyboxSimulation[6];
   /// permet de lancer la skybox
   clock_t start;
   /// longeur de l'ecran
   int width_;
   /// hauteur de l'ecran
   int height_;
   /// temps ecoule depuis le debut de la simulation en millisecondes
   mutable double millisecondes_ = 0;
   /// permet de verifier en quel mode l'application a ete lancee
   char modeApplication_{'E'};
   /// compteur permettant de verifier l'etat du zoom
   static int compteurZoom_;
   /// permet de verifier si la vue premiere personne a ete activee
   bool vuePremierePersonneFacadeModele_{ false };
   /// permet de verifier quel type de vue est active
   TypeVue typeVue_{ ORTHO };
   mutable int compteurAffichageChrono_ = 0;
   static int compteurAjouts;
};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
