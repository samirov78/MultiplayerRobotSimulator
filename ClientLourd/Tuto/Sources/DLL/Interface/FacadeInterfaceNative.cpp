////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "projection.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include <iostream>

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fenêtre
	/// identifiée par le handle passé en paramètre.  Cette fonction doit
	/// être la première à être appelée, car la création de l'objet du modèle
	/// C++ s'attend à avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libère le contexte OpenGL. Cette fonction doit être la
	/// dernière à être appelée, car elle libère également l'objet du modèle
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// Désinitialisation de la façade.  Le fait de le faire après la
		// désinitialisation du contexte OpenGL aura pour conséquence que la
		// libération des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scène.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL(double temps)
	{
		// Affiche la scène.
		FacadeModele::obtenirInstance()->afficher(temps);

		// Temporaire: pour détecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit être appelée lorsque la fenêtre est
	/// redimensionnée afin d'ajuster les paramètres de la machine à états
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenêtre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->redimensionnerFenetre(largeur, hauteur);
		
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
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
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float) temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->zoomIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arrière sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->zoomOut();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerFenetreVirtuelleSouris()
	///
	/// Cette fonction applique une translation a la fenetre virtuelle
	///
	/// @param[in] x : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] y : Position y de la souris en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerFenetreVirtuelleSouris(int x, int y)
	{
		FacadeModele::obtenirInstance()->deplacerFenetreVirtuelleSouris(x,y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl sauverPositionSouris(int x, int y)
	///
	/// Cette fonction permet la sauvegarde de la position de la souris 
	/// en coordonnée de cloture.
	///
	/// @param[in] x : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] y : Position y de la souris en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauverPositionSouris(int x, int y)
	{
		FacadeModele::obtenirInstance()->sauverPositionSouris(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void ajouterNoeudSimple(char* nom, int x, int y)
	///
	/// Cette fonction l'ajout d'un noeud à l'arbre de rendu.
	///
	/// @param[in] nom : Nom du type du noeud à ajouter
	///
	/// @param[in] x : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] y : Position y de la souris en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) const char* ajouterNoeudSimple(char* nom, int x, int y, bool enligne, char* id)
	{
		return FacadeModele::obtenirInstance()->ajouterNoeudSimple(nom, x, y, enligne, id);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void ajouterNoeudAvecScale(char* nom, int x1, int y1, int x2, int y2)
	///
	/// Cette fonction l'ajout d'un noeud avec un certain redimensionnement
	///
	/// @param[in] nom : Nom du type du noeud à ajouter
	///
	/// @param[in] x1 : Position x initiale de la souris en coordonnée de cloture.
	///
	/// @param[in] y1 : Position y initiale de la souris en coordonnée de cloture.
	///
	/// @param[in] x2 : Position x finale de la souris en coordonnée de cloture.
	///
	/// @param[in] y2 : Position y finale de la souris en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) const char* ajouterNoeudAvecScale(char* nom, int x1, int y1, int x2, int y2, bool estConcret, bool enLigne, char* id)
	{
		return FacadeModele::obtenirInstance()->ajouterNoeudAvecScale(nom, x1, y1, x2, y2, estConcret, enLigne, id);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void supprimerDernierNoeud()
	///
	/// Cette fonction permet la suppression du dernier noeud ajouté à l'arbre
	/// de rendu
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimerDernierNoeud()
	{
		FacadeModele::obtenirInstance()->supprimerDernierNoeud();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void supprimerDerniereLigne()
	///
	/// Cette fonction permet la suppression de la dernière ligne ajouté 
	/// à l'arbre de rendu
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimerDerniereLigne()
	{
		FacadeModele::obtenirInstance()->supprimerDerniereLigne();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool verifierPositionCursor(int x, int y)
	///
	/// Cette fonction permet la vérification du positionnement du curseur.
	///
	/// @param[in] x : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] y : Position y de la souris en coordonnée de cloture.
	///
	/// @return Vrai si le curseur est dans la zone de simulation, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool verifierPositionCurseur(int x, int y)
	{
		bool estEnZoneSimulation = FacadeModele::obtenirInstance()->verifierCurseur(x, y);
		return estEnZoneSimulation;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool verifierCursorPoteau(int x, int y)
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
	__declspec(dllexport) bool verifierCurseurPoteau(int x, int y)
	{
		bool curseurOk = FacadeModele::obtenirInstance()->verifierCurseurPoteau(x, y);
		return curseurOk;
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin)
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
	__declspec(dllexport) bool verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin)
	{
		bool curseurOk = FacadeModele::obtenirInstance()->verifierCurseurFinMur(xDebut, yDebut, xFin, yFin);
		return curseurOk;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin)
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
	__declspec(dllexport) bool verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin)
	{
		bool curseurOk = FacadeModele::obtenirInstance()->verifierCurseurFinLigne(xDebut, yDebut, xFin, yFin);
		return curseurOk;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void enregistrerZoneDeSimulation(char* nomFichier)
	///
	/// Cette fonction permet d'effectuer la sauvegarde de la zone de simulation dans
	/// un fichier XML
	///
	/// @param[in] nomFichier : Nom du fichier dans lequel on effectue la sauvegarde.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void enregistrerZoneDeSimulation(char* nomFichier)
	{
		FacadeModele::obtenirInstance()->enregistrerZoneDeSimulation(nomFichier);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void chargerZoneDeSimulation(char* nomFichier)
	///
	/// Cette fonction permet d'effectuer le chargement de la zone de simulation à
	/// partir d'un fichier XML.
	///
	/// @param[in] nomFichier : Nom du fichier dans lequel on effectue la sauvegarde.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void chargerZoneDeSimulation(char* nomFichier)
	{
		FacadeModele::obtenirInstance()->chargerZoneDeSimulation(nomFichier);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerHaut();
	///
	/// Cette fonction deplace la fenetre virtuelle vers le haut.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerHaut()
	{
		FacadeModele::obtenirInstance()->deplacerHaut();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerHaut();
	///
	/// Cette fonction deplace la fenetre virtuelle vers le bas.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerBas()
	{
		FacadeModele::obtenirInstance()->deplacerBas();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerHaut();
	///
	/// Cette fonction deplace la fenetre virtuelle vers la gauche.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerGauche()
	{
		FacadeModele::obtenirInstance()->deplacerGauche();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerHaut();
	///
	/// Cette fonction deplace la fenetre virtuelle vers la droite.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerDroite()
	{
		FacadeModele::obtenirInstance()->deplacerDroite();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool verifierPositionCursor(int x, int y)
	///
	/// Cette fonction de tracer le rectangle élastique à l'écran
	///
	/// @param[in] x : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] y : Position y de la souris en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void tracerRectangleElastique(int x, int y)
	{
		FacadeModele::obtenirInstance()->tracerRectangleElastique(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomInRectangle(int xMin, int xMax, int yMin, int yMax)
	///
	/// Cette fonction permet d'effectuer un zoomIn à l'aide d'un rectangle élastique
	///
	/// @param[in] xMin : Coordonnée xMin du rectangle élastique
	///
	/// @param[in] xMax : Coordonnée xMax du rectangle élastique
	///
	/// @param[in] yMin : Coordonnée yMin du rectangle élastique
	///
	/// @param[in] yMax : Coordonnée yMax du rectangle élastique
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomInRectangle(int xMin, int xMax, int yMin, int yMax)
	{
		FacadeModele::obtenirInstance()->zoomInRectangle(xMin, xMax, yMin, yMax);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOutRectangle(int xMin, int xMax, int yMin, int yMax)
	///
	/// Cette fonction permet d'effectuer un zoomOut à l'aide du rectangle élastique.
	///
	/// @param[in] xMin : Coordonnée xMin du rectangle élastique
	///
	/// @param[in] xMax : Coordonnée xMax du rectangle élastique
	///
	/// @param[in] yMin : Coordonnée yMin du rectangle élastique
	///
	/// @param[in] yMax : Coordonnée yMax du rectangle élastique
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOutRectangle(int xMin, int xMax, int yMin, int yMax)
	{
		FacadeModele::obtenirInstance()->zoomOutRectangle(xMin, xMax, yMin, yMax);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void terminerRectangleElastique(int x, int y)
	///
	/// Cette fonction permet de terminer le traçage du rectangle élastique
	///
	/// @param[in] x : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] y : Position y de la souris en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void terminerRectangleElastique(int x, int y)
	{
		FacadeModele::obtenirInstance()->terminerRectangleElastique(x, y);
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void reInitialiserScene()
	///
	/// Cette fonction permet de reinitialiser la scene.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void reInitialiserScene()
	{
		FacadeModele::obtenirInstance()->reinitialiser();
	}

	//Selection

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void selectionObjet(int mouseX, int mouseY, bool selectionUnique)
	///
	/// Cette fonction permet d'effectuer la sélection d'un objet.
	///
	/// @param[in] mouseX : Position x de la souris en coordonnée de cloture.
	///
	/// @param[in] mouseY : Position y de la souris en coordonnée de cloture.
	///
	/// @param[in] selectionUnique : booleen représentant si la sélection est effectuée sur un objet unique ou non.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) const char * selectionObjet(int mouseX, int mouseY, bool selectionUnique)
	{
		return FacadeModele::obtenirInstance()->selectionnerObjet(mouseX, mouseY, selectionUnique);

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void deplacerSelection(int xDebut, int yDebut, int xFin, int yFin)
	///
	/// Cette fonction permet d'effectuer le déplacement d'un objet sélectionné.
	///
	/// @param[in] xDebut	: Position x initiale de l'objet en coordonnée de cloture.
	///
	/// @param[in] yDebut	: Position x initiale de l'objet en coordonnée de cloture.
	///
	/// @param[in] xFin		: Position x finale de l'objet en coordonnée de cloture.
	///
	/// @param[in] yFin		: Position x finale de l'objet en coordonnée de cloture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) const char* deplacerSelection(int xDebut, int yDebut, int xFin, int yFin)
	{
		return FacadeModele::obtenirInstance()->deplacerSelection(xDebut, yDebut, xFin, yFin);
	}

	
	__declspec(dllexport) const char* deplacerSelNoAction(int xDebut, int yDebut, int xFin, int yFin)
	{
		return FacadeModele::obtenirInstance()->deplacerSelNoAction(xDebut, yDebut, xFin, yFin);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void selectRectElastique(int X_debut, int Y_debut, int X_fin, int Y_fin, bool estEnfonce)
	///
	/// Cette fonction permet d'effectuer la sélection d'objet à l'aide d'un rectangle élastique
	///
	/// @param[in] X_debut		: Position x initiale du rectangle élastique en coordonnée de cloture.
	///
	/// @param[in] Y_debut		: Position x initiale du rectangle élastique en coordonnée de cloture.
	///
	/// @param[in] X_fin		: Position x finale du rectangle élastique en coordonnée de cloture.
	///
	/// @param[in] Y_fin		: Position x finale du rectangle élastique en coordonnée de cloture.
	///
	/// @param[in] estEnfonce	: Booléen resprésentant si la sélection élastique avec rectangle élastique est terminer ou non.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) const char * selectRectElastique(int X_debut, int Y_debut, int X_fin, int Y_fin, bool estEnfonce)
	{
		return FacadeModele::obtenirInstance()->selectRectElastique(X_debut, Y_debut, X_fin, Y_fin, estEnfonce);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void supprimerSelection()
	///
	/// Cette fonction permet d'effectuer une suppression d'un objet sélectionné.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimerSelection()
	{
		FacadeModele::obtenirInstance()->supprimerSelection();

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void assignerPositionPourObjetSelectionne(double x, double y, double z)
	///
	/// Cette fonction permet d'assigner une position relative à un autre objet.
	///
	/// @param[in] x		: Coordonnée x de la position relative à un autre objet.
	///
	/// @param[in] y		: Coordonnée y de la position relative à un autre objet.
	///
	/// @param[in] z		: Coordonnée z de la position relative à un autre objet.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void assignerPositionPourObjetSelectionne(double x, double y, double z)
	{
		FacadeModele::obtenirInstance()->assignerPositionPourObjetSelectionne(x, y, z);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void assignerPositionPourObjetSelectionne(double x, double y, double z)
	///
	/// Cette fonction permet d'effectuer une rotation relative d'un objet sélectionné par rapport à un autre objet.
	///
	/// @param[in] rotation		: Angle de rotation relatif à un autre objet.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void assignerRotationPourObjetSelectionne(double rotation)
	{
		FacadeModele::obtenirInstance()->assignerRotationPourObjetSelectionne(rotation);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void changerScalePourObjetSelectionne(double scale)
	///
	/// Cette fonction permet d'effectuer le redimensionnement d'un objet sélectionné.
	///
	/// @param[in] scale : Facteur de redimensionnement.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void changerScalePourObjetSelectionne(double scale)
	{
		FacadeModele::obtenirInstance()->changerScalePourObjetSelectionne(scale);
	}

	/**
	* Demande l'initialisation de positionInitialeEnTraitement des objets selectionnees 
	* par la valeur de la position courante
	*/

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void initialiserPositionEnTraitement()
	///
	/// Cette fonction permet l'initialisation du positionnement d'un noeud
	/// par rapport à son parent
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserEnTraitement()
	{
		FacadeModele::obtenirInstance()->initialiserEnTraitement();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void initialiserScaleEnTraitement()
	///
	/// Cette fonction permet l'initialisation du redimensionnement d'un noeud
	/// par rapport à son parent
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserScaleEnTraitement()
	{
		FacadeModele::obtenirInstance()->initialiserScaleEnTraitement();
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void dupliquerObjetsSelectionnes(int x, int y, bool estConcret)
	///
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool dupliquerObjetsSelectionnes(int x, int y, bool estFantome)
	{
		return FacadeModele::obtenirInstance()->dupliquerSelection(x, y, estFantome);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void supprimerNoeudsDupliques()
	///
	/// Cette fonction permet la suppression d'un noeud ou plusieurs noeud
	/// duplique(s).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimerNoeudsDupliques()
	{
		FacadeModele::obtenirInstance()->supprimerNoeudsDupliques();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void scaleSelection(double facteurScale)
	///
	/// Cette fonction permet d'effectuer le redimensionnement d'un objet sélectionné.
	///
	/// @param[in] scale : Facteur de redimensionnement.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) const char* scaleSelection(double facteurScale)
	{
		return FacadeModele::obtenirInstance()->scaleSelection(facteurScale);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void PivoterObjetSelectionne(double rotation)
	///
	/// Cette fonction permet d'effectuer la rotation d'un objet selectionné.
	///
	/// @param[in] rotation : angle de rotation.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void PivoterObjetSelectionne(double deltaY)
	{
		FacadeModele::obtenirInstance()->PivoterObjetSelectionne(deltaY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void PivoterObjetsMultiples(double rotation)
	///
	/// Cette fonction permet la rotation de plusieurs objets selectionnes.
	///
	/// @param[in] rotation : angle de rotation.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void PivoterObjetsMultiples(double rotation)
	{
		FacadeModele::obtenirInstance()->PivoterObjetsMultiples(rotation);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) int obtenirNombreNoeudsSelectionnes()
	///
	/// Cette fonction permet le retour du nombre de noeud sélectionné.
	///
	/// @return Le nombre de noeud selectionné.
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) int obtenirNombreNoeudsSelectionnes()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreNoeudsSelectionnes();
	}

	
	__declspec(dllexport) int obtenirNombreMySelectedNodes()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreMySelectedNodes();
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool objetsSurLaTable()
	///
	/// Cette fonction permet de verifier si un objet est toujours sur la table.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool objetsSelectionnesSurLaTable()
	{
		return FacadeModele::obtenirInstance()->objetsSelectionnesSurLaTable();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool tournerObjetSelectionne(double angle)
	///
	/// Cette fonction permet d'effectuer une rotation sur un objet selectionne.
	///
	/// @param[in] angle : angle de rotation.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool tournerObjetSelectionne(double angle)
	{
		return FacadeModele::obtenirInstance()->tournerObjetSelectionne(angle);
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void annulerRotationSelection()
	///
	/// Cette fonction permet d'annuler la rotation d'un objet selectionne.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void annulerRotationSelection()
	{
		return FacadeModele::obtenirInstance()->annulerRotationSelection();
	}
	
	__declspec(dllexport) void annulerRotationMySelection(char * theIDs)
	{
		return FacadeModele::obtenirInstance()->annulerRotationMySelection(theIDs);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void retournerAuScaleInitiale()
	///
	/// Cette fonction permet de reinitialiser le dimensionnement d'un objet.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void retournerAuScaleInitiale()
	{
		FacadeModele::obtenirInstance()->retournerAuScaleInitiale();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void actionnerRobot(double rapportVitesseGauche, double rapportVitesseDroit, bool sensDirect)
	///
	/// Methode permettant d'actionner le robot.
	///
	/// @param[in] rapportVitesseGauche: Rapport de vitesse de la roue gauche.
	///
	/// @param[in] rapportVitesseDroit: Rapport de vitesse de la roue droite.
	///
	/// @param[in] sensDirect: booleen representant le sens du robot.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void actionnerRobot(double rapportVitesseGauche, double rapportVitesseDroit, bool sensDirect)
	{
		FacadeModele::obtenirInstance()->actionnerRobot(rapportVitesseGauche, rapportVitesseDroit, sensDirect);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void debuterSimulation()
	///
	/// Methode permettant de debuter la simulation du robot.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void debuterSimulation()
	{
		FacadeModele::obtenirInstance()->debuterSimulation();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void initialiserRobot()
	///
	/// Methode permettant d'initialiser le robot.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserRobot(bool vuePremierePersonne)
	{
		FacadeModele::obtenirInstance()->initialiserRobot(vuePremierePersonne);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void arreterRobot()
	///
	/// Methode permettant d'arreter le robot.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void arreterRobot()
	{
		FacadeModele::obtenirInstance()->arreterRobot();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void stopperModeAutomatique()
	///
	/// Methode permettant d'arreter le mode automatique.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void stopperModeAutomatique()
	{
		FacadeModele::obtenirInstance()->stopperModeAutomatique();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void actionnerModeAutomatique()
	///
	/// Methode permettant d'actionner le mode automatique.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void actionnerModeAutomatique()
	{
		FacadeModele::obtenirInstance()->actionnerModeAutomatique();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void chargerProfilRobot(char* nomProfil)
	///
	/// Methode permettant de charger le nom du profil.
	///
	/// @param[in] nomProfil: Nom du profil.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void chargerProfilRobot(char* nomProfil)
	{
		FacadeModele::obtenirInstance()->chargerProfilRobot(nomProfil);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void libererRobot()
	///
	/// Methode permettant de liberer le robot.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void libererRobot()
	{
		FacadeModele::obtenirInstance()->libererRobot();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void basculerActivationLumiereAmbiante()
	///
	/// Methode permettant d'activer ou desactiver la lumiere ambiante.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void basculerActivationLumiereAmbiante()
	{
		FacadeModele::obtenirInstance()->basculerActivationLumiereAmbiante();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void basculerActivationLumiereDirectionnelle()
	///
	/// Methode permettant d'activer ou desactiver la lumiere directionnelle.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void basculerActivationLumiereDirectionnelle()
	{
		FacadeModele::obtenirInstance()->basculerActivationLumiereDirectionnelle();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void basculerActivationSpots()
	///
	/// Methode permettant d'activer ou desactiver le spot.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void basculerActivationSpots()
	{
		FacadeModele::obtenirInstance()->basculerActivationSpots();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void basculerActivationDebougage()
	///
	/// Methode permettant d'activer ou desactiver le mode debugage.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void basculerActivationDebougage()
	{
		FacadeModele::obtenirInstance()->basculerActivationDebougage();
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void activerVueOrbite()
	///
	/// Methode permettant d'activer la vue orbite.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerVueOrbite()
	{
		FacadeModele::obtenirInstance()->activerVueOrbite();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void activerVueOrthographique()
	///
	/// Methode permettant d'activer la vue orthographique.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerVueOrthographique()
	{
		FacadeModele::obtenirInstance()->activerVueOrthographique();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void activerVuePremierePersonne()
	///
	/// Methode permettant d'activer la vue Premiere Personne.
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerVuePremierePersonne()
	{
		FacadeModele::obtenirInstance()->activerVuePremierePersonne();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void changerModeApplication(char mode)
	///
	/// Methode permettant de changer le mode de l'application dans le noyeau
	///
	/// @param: Aucun.
	///
	/// @return Aucun.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void changerModeApplication(char mode)
	{
		FacadeModele::obtenirInstance()->changerModeApplication(mode);
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) void __cdecl jouerMusiqueSimulation()
	///
	/// initie le son dans le mode simulation
	///
	/// @return Aucun
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl jouerMusiqueSimulation()
	{
		FacadeModele::obtenirInstance()->jouerMusiqueSimulation();
	}
	__declspec(dllexport) bool __cdecl obstacleDetecte()
	{
		return FacadeModele::obtenirInstance()->obstacleDetecte();
	}

	
	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) void __cdecl initialiserSonEditeur()
	///
	/// initie le son dans le mode edition
	///
	/// @return Aucun
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserSonEditeur()
	{
		FacadeModele::obtenirInstance()->initialiserSonEditeur();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) void __cdecl libererFmod()
	///
	/// Fonction permettant de liberer le son.
	///
	/// @return Aucun
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererFmod()
	{
		FacadeModele::obtenirInstance()->libererFmod();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) double obtenirPositionXElementSelectionne()
	///
	/// Fonction permettant d'obtenir la position X de l'element selectionne.
	///
	/// @return Position X de l'objet.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirPositionXElementSelectionne()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionXElementSelectionne();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) double obtenirPositionYElementSelectionne()
	///
	/// Fonction permettant d'obtenir la position Y de l'element selectionne.
	///
	/// @return Position Y de l'objet.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirPositionYElementSelectionne()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionYElementSelectionne();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) double obtenirRotationElementSelectionne()
	///
	/// Fonction permettant d'obtenir la rotation relative d'un element selectionne
	/// par rapport a son objet parent.
	///
	/// @return Angle de rotation.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirRotationElementSelectionne()
	{
		return FacadeModele::obtenirInstance()->obtenirRotationElementSelectionne();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) double obtenirEchelleElementSelectionne()
	///
	/// Fonction permettant d'obtenir le redimensionnement relatif d'un element selectionne
	/// par rapport a son objet parent.
	///
	/// @return L'echelle de l'objet selectionne.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirEchelleElementSelectionne()
	{
		return FacadeModele::obtenirInstance()->obtenirEchelleElementSelectionne();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) double obtenirEchelleElementSelectionne()
	///
	/// Fonction permettant de determiner si l'objet selectionne est la fleche.
	///
	/// @return Vrai si fleche, faux sinon.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool noeudSelectionneEstFleche()
	{
		return FacadeModele::obtenirInstance()->noeudSelectionneEstFleche();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) bool noeudSelectionneEstLigne()
	///
	/// Fonction permettant de determiner si l'objet selectionne est une ligne.
	///
	/// @return Vrai si ligne, faux sinon.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool noeudSelectionneEstLigne()
	{
		return FacadeModele::obtenirInstance()->noeudSelectionneEstLigne();
	}
	
	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) void __cdecl pauseSonSimulation()
	///
	/// Fonction permettant de mettre en pause le son.
	///
	/// @return Aucun.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl pauseSonSimulation()
	{
		FacadeModele::obtenirInstance()->pauseSonSimulation();
	}

	////////////////////////////////////////////////////////////////////////
	///  @fn __declspec(dllexport) void __cdecl UnPauseSonSimulation()
	///
	/// Fonction permettant de mettre en marche le son apres une pause.
	///
	/// @return Aucun.
	///////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl UnPauseSonSimulation()
	{
		FacadeModele::obtenirInstance()->UnPauseSonSimulation();
	}


	/////projet 3
	__declspec(dllexport) void __cdecl CreatePoteau(char* data)
	{
		FacadeModele::obtenirInstance()->CreatePoteau(data);
	}

	__declspec(dllexport) void __cdecl CreateMur(char* data)
	{
		FacadeModele::obtenirInstance()->CreateMur(data);
	}

	__declspec(dllexport) void __cdecl CreateLine(char* data)
	{
		FacadeModele::obtenirInstance()->CreateLine(data);
	}

	__declspec(dllexport) void __cdecl ModifyPoteau(char* data)
	{
		FacadeModele::obtenirInstance()->ModifyPoteau(data);
	}

	__declspec(dllexport) void __cdecl ModifyMur(char* data)
	{
		FacadeModele::obtenirInstance()->ModifyMur(data);
	}

	__declspec(dllexport) void __cdecl ModifyLine(char* data)
	{
		FacadeModele::obtenirInstance()->ModifyLine(data);
	}

	__declspec(dllexport) bool __cdecl ChangerConfigurationObjetSelectionne(double x, double y, double rotation, double echelle)
	{
		return FacadeModele::obtenirInstance()->ChangerConfigurationObjetSelectionne(x, y, rotation, echelle);
	}

	__declspec(dllexport) void __cdecl SelectNodes(char * broadcastElements)
	{
		FacadeModele::obtenirInstance()->SelectNodes(broadcastElements);//void ScaleSelectionOnline(char * IDsAndFactor)
	}

	__declspec(dllexport) void __cdecl ScaleSelectionOnline(char * IDsAndFactor)
	{
		FacadeModele::obtenirInstance()->ScaleSelectionOnline(IDsAndFactor);//void 
	}
	//moveNodesOnline(char * IDsAndDebutFin)
	__declspec(dllexport) void __cdecl moveNodesOnline(char * IDsAndDebutFin)
	{
		FacadeModele::obtenirInstance()->moveNodesOnline(IDsAndDebutFin);//void 
	}

	__declspec(dllexport) void __cdecl DeselectNoeuds(char * ids[], short size)
	{
		FacadeModele::obtenirInstance()->DeselectNoeuds(ids, size);
	}

	__declspec(dllexport) void __cdecl DeleteNodes(char * ids[], short size)
	{
		FacadeModele::obtenirInstance()->DeleteNodes(ids, size);
	}

	__declspec(dllexport) const char * duplicateSelNoAction(int x, int y, bool estFantome)
	{
		return FacadeModele::obtenirInstance()->duplicateSelNoAction(x, y, estFantome);
	}

	__declspec(dllexport) bool __cdecl duplicateSelNodes(char * chaineDup)
	{
		return FacadeModele::obtenirInstance()->duplicateSelNodes(chaineDup);//void 
	}
	
	__declspec(dllexport) void __cdecl UpdateMySelNodes(char* data)
	{
		FacadeModele::obtenirInstance()->UpdateMySelNodes(data);//void 
	}
	
	__declspec(dllexport) void __cdecl PivoterselectedNode(char* data)
	{
		FacadeModele::obtenirInstance()->PivoterselectedNode(data);
	}

	__declspec(dllexport) void __cdecl PivoterselectedNodes(char* data)
	{
		FacadeModele::obtenirInstance()->PivoterselectedNodes(data);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


