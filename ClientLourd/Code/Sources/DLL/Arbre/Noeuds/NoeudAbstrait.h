///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2016-02-15
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
# define M_PI 3.14159265358979323846

#include "GL/glew.h"
#include <string>
#include <iostream>


#include "glm\glm.hpp"
#include "Utilitaire.h"
#include "../../Visiteur/VisiteurAbstrait.h"
// #include "VisiteurAbstrait.h"
#include <vector>
#include "Debug.h"
#include "Profil.h"

enum Direction { FORWARD, REVERSE };
const double SCALE_ROBOT{0.5};
/// Déclarations avancées pour contenir un pointeur vers un modèle3D et son storage
namespace modele{
	class Modele3D;
}
namespace opengl{
	class VBO;
}

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisée pour créer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant être présent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = std::string{ "" }
	);
	/// Destructeur.
	virtual ~NoeudAbstrait();

	const double NoeudAbstrait::RAYON_POTEAU{ 1.0 };

	// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur){};

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	/// Obtient la position relative du noeud.
	inline const glm::dvec3& obtenirPositionRelative() const;
	///Methode permettant d'obtenir la position initiale d'un objet.
	inline const glm::dvec3& obtenirPositionInitialeEnTraitement() const;

	///Methode permettant d'obtenir la rotation relative d'un objet avec son parent.
	inline const glm::dvec4& obtenirRotationRelative() const;
	///Methode permettant d'obtenir le redimensionnement relatif d'un objet avec son parent.
	inline const glm::dvec3& obtenirRedimensionnementRelative() const;
	///Methode permettant d'obtenir le redimensionnement intiale d'un objet.
	inline const glm::dvec3& obtenirScaleInitialeEnTraitement() const;


	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::dvec3& positionRelative);
	///Methode permettant d'initialiser les positions des objets en traitement.
	inline void initialiserPositionEnTraitement();
	///Methode permettant d'initialiser les positions des objets en traitement.
	virtual void initialiserEnTraitement(){ initialiserPositionEnTraitement(); };
	///Methode permettant d'initialiser le redimensionnement d'un objet en traitement.
	inline void initialiserScaleEnTraitement();
	///Methode permettant d'assigner une rotation relative a un objet par rapport a son parent.
	inline void assignerRotationRelative(const glm::dvec4& rotationRelative);
	///Methode permettant d'assigner un redimensionnement relatif d'un objet par rapport a son parent.
	inline void assignerRedimensionnementRelative(const glm::dvec3& redimensionnementRelative);
	///Methode permettant le redimensionnement d'un objet.
	virtual void changerScale(double scale){ };
	///Methode permettant d'augmenter la rotation d'un objet par rapport a son parent.
	virtual void augmenterRotationRelative(double rotation)
	{
		rotationRelative_ = glm::dvec4(rotationRelative_[0] + rotation, rotationRelative_[1], rotationRelative_[2], rotationRelative_[3]);
	};
	///Methode permettant de mettre a jour la position d'un objet.
	virtual void mettreAjourPosition(){};

	virtual bool verifierSelection(GLubyte couleurBack[], GLubyte couleurFront[]){ return false; };

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// Écrit l'état de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// Vérifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// Écrit l'état de la sélection du noeud.
	inline void assignerSelection(bool selectionne);
	/// Vérifie si le noeud est sélectionné.
	inline bool estSelectionne() const;
	/// Écrit si le noeud peut être sélectionné ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// Vérifie si le noeud est sélectionnable.
	inline bool estSelectionnable() const;
	/// Écrit si le noeud peut être enregistré ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// Vérifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;
	/// Vérifie si le noeud peut etre supprime.
	inline bool estFantome() const { return fantome_; };
	/// Vérifie si le noeud peut etre supprime.
	inline void assignerEstFantome(bool fantome) { fantome_ = fantome; };

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	inline void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste);

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	inline const glm::dvec3 obtenirCentre() const { return centre_; };
	virtual void assignerCentre(glm::dvec3 centre);
	virtual void mettreAjourCentre() { centre_ = obtenirPositionRelative(); };

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud passé en paramètre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);

	/// Ajoute un noeud enfant.
	virtual bool ajouter(NoeudAbstrait* enfant);

	virtual std::vector<NoeudAbstrait*> * obtenirEnfants(){ return nullptr; };
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;
	


	/// Changer la sélection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants sélectionnés.
	virtual void effacerSelection();
	/// Efface les enfants fantomes.
	virtual void effacerFantome();
	/// Sélectionne tous les enfants de même que le noeud.
	virtual void selectionnerTout();
	/// Désélectionne tous les enfants de même que le noeud.
	virtual void deselectionnerTout();
	///virtual void deselectIfSameColor(NoeudAbstrait & noeud);
	/// Vérifier si le noeud ou un de ses enfants est sélectionné.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher(const bool& attribuerCouleur) const;
	/// Affiche le noeud de manière concrète.
	virtual void afficherConcret(const bool& attribuerCouleur) const;
	/// Anime le noeud.
	virtual void animer(float dt);
	///Verifie si un click de souris touche un noeud.
	virtual bool clickToucheNoeud(glm::dvec3 point);
	///Permet le retour du modele du noeud.
	modele::Modele3D const& obtenirModel(){ return (*modele_); };
	///Permet d'initialiser le point de depart et de faire d'un noeud.
	//***void setPoints(glm::dvec3 point1, glm::dvec3 point2) { pointDepart_ = point1; pointFin_ = point2; };
	///Retourne le point de depart d'un noeud.
	glm::dvec3 getPointDepart() {
		double longueur = obtenirRedimensionnementRelative()[0];
		glm::dvec3 position = obtenirPositionRelative();
		double angle = rotationRelative_[0];
		glm::dvec3 depart;
		depart[0] = -(longueur / 2.0) * std::cos(utilitaire::DEG_TO_RAD(angle));
		depart[1] = -(longueur / 2.0) * std::sin(utilitaire::DEG_TO_RAD(angle));
		depart[2] = 0;
		return depart + position;
	}
		
	/*	
		double dimensionement = obtenirRedimensionnementRelative()[0];
		double positionX = obtenirPositionRelative()[0];
		double positionY = obtenirPositionRelative()[1];
		double angle = rotationRelative_[0];
		double xDebut = (positionX - dimensionement / 2) * std::cos(angle) - positionY * std::sin(angle);
		double yDebut = (positionX - dimensionement / 2) * std::sin(angle) + positionY * std::cos(angle);
	};
	*/
	///Retourne le point final d'un noeud.
	glm::dvec3 getPointFin() { 
		double longueur = obtenirRedimensionnementRelative()[0];
		glm::dvec3 position = obtenirPositionRelative();
		double angle = rotationRelative_[0];
		glm::dvec3 fin;
		fin[0] = (longueur / 2.0) * std::cos(utilitaire::DEG_TO_RAD(angle));
		fin[1] = (longueur / 2.0) * std::sin(utilitaire::DEG_TO_RAD(angle));
		fin[2] = 0;

		return fin + position;
	};
	/// verifier si la noeud est dans la table
	virtual bool estDansLaTableApresDeplacement(glm::dvec3 deplacement){ return true; };
	///Methode permettant de verifier si l'objet est toujours a l'interieur de la table apres redimensionnement.
	virtual bool estDansLaTableApresScale(double scale){ return true; };
	///Methode permettant de verifier si un objet est toujours a l'interieur de la table.
	virtual bool estDansLaTable(){ return true; };
	virtual bool dansLaTableSiSelectionne(){ return true; };
	///Methode permettant d'effectuer une rotation a un objet.
	virtual void tourner(double angle){ assignerRotationRelative(glm::dvec4(obtenirRotationRelative()[0] + angle, 0, 0, 1)); };
	///Methode permettant le retour de la rotation relative d'un objet par rapport a son parent.
	glm::dvec4 getRotationRelativeAvantraitement(){ return rotationRelativeAvantraitement_; };
	///Methode permettant le retour du dimensionnement initiale d'un objet.
	virtual void retournerAuScaleInitiale(){};
	///Methode permettant le retour de l'acceleration du robot.
	virtual double getAcceleration() const { return 0.0; };
	///Methode permettant le retour de la vitesse du robot.
	virtual double getVitesse() const { return 0.0; };
	///Methode permettant le retour de la direction du robot.
	virtual Direction getDirection() const { return FORWARD; };
	///Methode permettant le retour du rapport de vitesse du robot.
	virtual double getRapportVitesse() const { return 0.0; };
	///Methode permettant le retour de l'angle de rotation du robot.
	virtual double getAngleRotation() const { return 0.0; };
	///Methode permettant le retour de l'increment d'acceleration du robot.
	virtual double getIncrAcceleration() const { return 0.0; };
	///Methode permettant l'assignation de l'increment d'acceleration au robot.
	virtual void setIncrAcceleration(double incrAcceleration){ };
	///Methode permettant l'assignation d'une acceleration au robot.
	virtual void setAcceleration(double acceleration){ };
	///Methode permettant l'assignation d'une vitesse au robot.
	virtual void setVitesse(double vitesse){ };
	///Methode permettant l'assignation d'une direction au robot.
	virtual void setDirection(Direction direction){ };
	///Methode permettant le retour du noeud correspondant a la roue droite du robot.
	virtual NoeudAbstrait* getRoueDroite(){ return nullptr; };
	///Methode permettant ler etour du noeud correspondant a la roue gauche du robot.
	virtual NoeudAbstrait* getRoueGauche(){ return nullptr; };
	///Methode permettant l'assignation d'un noeud correspondant a la roue droite du robot.
	virtual void setRoueDroite(NoeudAbstrait* noeudRoue){ };
	///Methode permettant l'assignation d'un noeud correspondant a la roue gauche du robot.
	virtual void setRoueGauche(NoeudAbstrait* noeudRoue){ };
	///Methode permettant l'assignation d'un rapport de vitesse au robot.
	virtual void setRapportVitesse(double rapportVitesse) { };
	///Methode permettant d'actionner les moteurs du robot dans une certaine direction avec un certain rapport de vitesse.
	virtual void actionnerMoteurs(const double& rapportVitesseGauche, const double& rapportVitesseDroit, const Direction& direction){ };
	///Methode permettant d'arreter les moteurs du robot.
	virtual void arreterMoteurs(){ };
	///Getters des points des capteurs
	///Getters pour obtenir les differents points pour les capteurs de distance.
	virtual glm::dvec2 obtenirP2CapteurSecuritaireDroit(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP2CapteurSecuritaireMilieu(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP2CapteurSecuritaireGauche(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP2CapteurDangerDroit(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP2CapteurDangerMilieu(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP2CapteurDangerGauche(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP1CapteurDangerDroit(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP1CapteurDangerMilieu(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP1CapteurDangerGauche(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP3CapteurSecuritaireDroit(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP3CapteurSecuritaireMilieu(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP3CapteurSecuritaireGauche(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP3CapteurDangerDroit(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP3CapteurDangerMilieu(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP3CapteurDangerGauche(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP4CapteurDangerDroit(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP4CapteurDangerMilieu(){ return glm::dvec2(0.0); };
	virtual glm::dvec2 obtenirP4CapteurDangerGauche(){ return glm::dvec2(0.0); };
	///Setters des attributs de detection des capteurs.
	virtual void setDetectionSecuritaireDroit(const bool& detection) {};
	virtual void setDetectionSecuritaireMilieu(const bool& detection) {};
	virtual void setDetectionSecuritaireGauche(const bool& detection) {};
	virtual void setDetectionDangerDroit(const bool& detection) {};
	virtual void setDetectionDangerMilieu(const bool& detection) {};
	virtual void setDetectionDangerGauche(const bool& detection) {};
	///Methode permettant de verifier si une ligne est detecter ou non.
	virtual void ligneTouchee(glm::dvec3 point, bool& estTouche) { };
	///Getters des etats de detection des zones securitaire et danger des differents capteurs.
	///Getters de l'etat de detection des capteurs de distance.
	virtual bool getEtatCapteurSecuritaireDroit(){ return false; };
	virtual bool getEtatCapteurDangerDroit(){ return false; };
	virtual bool getEtatCapteurSecuritaireMilieu() { return false; }
	virtual bool getEtatCapteurDangerMilieu() { return false; };
	virtual bool getEtatCapteurSecuritaireGauche() { return false; }
	virtual bool getEtatCapteurDangerGauche() { return false; };
	///Methode permettant de charger le profil
	virtual void chargerProfil(char* nomProfil){};
	///Methode permettant de charger le profil de debug.
	virtual void chargerDebug(char* nomFichier){};
	///Methode permettant le retour du profil de debug.
	virtual Debug* obtenirDebug(){ return nullptr; };
	///Methode permettant le retour du profil.
	virtual Profil* obtenirProfil() { return nullptr; };
	///Methode permettant d'obtenir l'affichage de debugage.
	//virtual bool obtenirAffichageDebougage() { return false; };
	///Methode permettant de set l'affichage debugage correspondant au suivi de ligne.
	virtual void setAffichageDebogageSuiviLigne(const bool& booleen) {};
	///Methode permettant de set le comportement actuelle du robot pour des fins d'affichage debugage a la console.
	virtual void setEtat(const ETATS& etat) {};
	///methode permettant l'assignation de l'affichage debugage des capteurs de distance.
	virtual void setAffichageDebogageCapteurDangerDroit(const bool& booleen) {};
	virtual void setAffichageDebogageCapteurDangerMilieu(const bool& booleen) {};
	virtual void setAffichageDebogageCapteurDangerGauche(const bool& booleen) {};
	virtual void setAffichageDebogageCapteurSecuritaireDroit(const bool& booleen) {};
	virtual void setAffichageDebogageCapteurSecuritaireMilieu(const bool& booleen) {};
	virtual void setAffichageDebogageCapteurSecuritaireGauche(const bool& booleen) {};
	/// Attribut publique permettant d'enregistrer le rapport de vitesse des deux roues gauche et droite du robot.
	double rapportVitesseReel_{ 0.0 };

	///Ancienne direction des deux roues gauche et droite du robot.
	Direction oldDirection_{ FORWARD };

	virtual void attribuerCouleurSelection();
	virtual void setCustomSelectColor(short R, short G, short B);
	/// permet de verifier si un noeud est visite
	bool estVisite() const { return estVisiteParVisiteurRectElas_; };
	/// permet d'assigner a un noeud l'etat estVisite
	virtual void assignerEstVisite(const bool& estVisite) { estVisiteParVisiteurRectElas_ = estVisite; };
	virtual std::string toString();
	/// permet de contenir la couleur d'une ligne
	GLubyte couleurLigne_[3];
	/// permet de contenir la couleur de la selection
	GLubyte couleurSelection_[3];
	/// permet de determiner le nombre de lignes, de poteaux et de murs
	static int compteurLigne_;
	static int compteurPoteau_;
	static int compteurMur_;
	/// permet de determiner le nombre de selection effectuees
	static int compteurSelection_;
	//ID d un noeud
	std::string ID ="";
	//bool  selectedByOthers_{ false };
	/// Efface les enfants avec IDS sélectionnés.
	virtual void effacerIDSelectionnes(char * id){};
protected:
	/// Type du noeud.
	std::string      type_;

	/// Mode d'affichage des polygones.
	GLenum           modePolygones_{ GL_FILL };

	/// Position relative du noeud.
	glm::dvec3         positionRelative_;
	/// Rotation relative du noeud.
	glm::dvec4         rotationRelative_;
	/// Redimentionnement relative du noeud.
	glm::dvec3         redimensionnementRelative_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// Sélection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est sélectionnable.
	bool             selectionnable_{ true };

	/// Détermine si l'objet peut être sauvegardé en XML.
	bool             enregistrable_{ true };

	/// Détermine si l'objet peut être supprimé.
	bool             fantome_{ false };

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	/// Modèle 3D correspondant à ce noeud.
	modele::Modele3D const* modele_;
	/// Storage pour le dessin du modèle
	opengl::VBO const* vbo_;

	/// Angle de rotation en degré
	//double angleRotation_{ 0.f };
	///Position initial d'un noeud en traitement.
	glm::dvec3 positionInitialeEnTraitement_;
	///Scale initial d'un noeud en traitement.
	glm::dvec3 scaleInitialeEnTraitement_;
	///Point de depart d'un noeud.
	
	///Rotation relative d'un noeud avant un traitement.
	glm::dvec4 rotationRelativeAvantraitement_;
	///Centre d'un noeud.
	glm::dvec3 centre_{ 0.0 };
	///Boite englobante d'un noeud.
	utilitaire::BoiteEnglobante bteEnglobante_;
	///Cylindre engloant d'un noeud.
	utilitaire::CylindreEnglobant cylEnglobant_;
	/// compteurs permettant de generer les differents sortes de couleurs RGB
	static int compteurLigneRed_;
	static int compteurLigneGreen_;
	static int compteurSelectionRed_;
	/// permet de verifier si un noeud a deja ete visite par le visiteurRectangleElastique
	bool estVisiteParVisiteurRectElas_;
	//glm::dvec3 pointDepart_{ 0.0 };
	///Point final d'un noeud.
	//glm::dvec3 pointFin_{ 0.0 };
	const std::string separateurAttributs = "#";
	const std::string separateurEnfants = ":";
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_ = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}

////////////////////////////////////////////////////////////////////////
///
/// @nline const glm::dvec3& NoeudAbstrait::obtenirPositionInitialeEnTraitement() const
///
/// Cette fonction retourne la position relative initiale du noeud par rapport
/// à son parent au debut du traitement.
///
/// @return La position relative initiale.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionInitialeEnTraitement() const
{
	return positionInitialeEnTraitement_;
}

////////////////////////////////////////////////////////////////////////
///
/// @nline const glm::dvec3& NoeudAbstrait::obtenirPositionInitialeEnTraitement() const
///
/// Cette fonction retourne la position relative initiale du noeud par rapport
/// à son parent au debut du traitement.
///
/// @return La position relative initiale.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirScaleInitialeEnTraitement() const
{
	return scaleInitialeEnTraitement_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::dvec3& positionRelative
	)
{
	positionRelative_ = positionRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::initialiserPositionEnTraitement()
{
	positionInitialeEnTraitement_ = positionRelative_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::initialiserScaleEnTraitement()
{
	scaleInitialeEnTraitement_ = redimensionnementRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirRotationRelative() const
///
/// Cette fonction retourne la rotation relative du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec4& NoeudAbstrait::obtenirRotationRelative() const
{
	return rotationRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerRotationRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la rotation relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerRotationRelative(
	const glm::dvec4& rotationRelative
	)
{
	rotationRelative_ = rotationRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirRedimensionnementRelative() const
///
/// Cette fonction retourne le redimensionnement relatif du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirRedimensionnementRelative() const
{
	return redimensionnementRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerRedimensionnementRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner le redimensionnement relatif du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerRedimensionnementRelative(
	const glm::dvec3& redimensionnementRelative
	)
{
	redimensionnementRelative_ = redimensionnementRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une chaîne représentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'état affiché ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'état que le noeud se fait afficher ou non.
///
/// @return L'état affiché ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'état d'être sélectionné ou non du noeud.
///
/// @return L'état sélectionné ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'état d'être sélectionnable ou non du noeud.
///
/// @param selectionnable : L'état sélectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'état d'être sélectionnable ou non du noeud.
///
/// @return L'état sélectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'état d'être entregistrable ou non du noeud.
///
/// @param enregistrable : L'état enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable(bool enregistrable)
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'état d'être enregistrable en XML ou non du
/// noeud.
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D* modele, modele::opengl_storage::OpenGL_Liste* liste)
///
/// Cette fonction assigne l'objet de rendu au modèle, c'est-à-dire son
/// modèle 3D et sa liste d'affichage
///
/// @param modele : le modèle 3D
/// @param liste : la liste d'affichage OpenGL
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	modele_ = modele;
	vbo_ = liste;
}


#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
