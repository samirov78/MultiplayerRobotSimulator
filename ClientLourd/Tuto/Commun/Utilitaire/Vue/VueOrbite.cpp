////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.cpp
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VueOrbite.h"
#include "Plan3D.h"
#include <iostream>
#include <cmath>

namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VueOrbite::VueOrbite(Camera const& camera, ProjectionPerspective const& projection)
	///
	/// Constructeur d'une vue orbitale.  Ne fait que créer les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Caméra à utiliser au départ pour cette vue.
	/// @param[in] projection    : Projection à utiliser pour cette vue
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	VueOrbite::VueOrbite(Camera const& camera, ProjectionPerspective const& projection, bool vuePremierePersonne) :
		Vue{ camera },
		projection_{ projection }
	{
		vuePremierePersonne_ = vuePremierePersonne;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionPerspective& VueOrtho::obtenirProjection() const
	///
	///
	/// @return La projection orbitale
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionPerspective& VueOrbite::obtenirProjection() const
	{
		return projection_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::appliquerProjection() const
	///
	/// Applique la matrice de projection correspondant à cette vue.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::appliquerProjection() const
	{
		projection_.mettreAJourProjection();
		//std::cout << "orthogonale " << std::endl;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::appliquerCamera() const
	///
	/// Applique la matrice correspondant à cette vue selon la position de
	/// la caméra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::appliquerCamera() const
	{
		camera_.positionner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture.
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		projection_.redimensionnerFenetre(coinMin, coinMax);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerIn()
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.effectuerZoomIn();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerOut()
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.effectuerZoomOut();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Ne fait rien.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerInElastique(const glm::ivec2& pointMin,
		const glm::ivec2& pointMax)
	{
		//glm::dvec3 pointMinVirtuelle;
		//glm::dvec3 pointMaxVirtuelle;
		//convertirClotureAVirtuelle(pointMin.x, pointMin.y, pointMinVirtuelle);
		//convertirClotureAVirtuelle(pointMax.x, pointMax.y, pointMaxVirtuelle);
		//projection_.zoomerIn(pointMinVirtuelle, pointMaxVirtuelle);
		//camera_.reinitialiserCamera();
		}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Ne fait rien
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerOutElastique(const glm::ivec2& pointMin,
		const glm::ivec2& pointMax)
	{
		////glm::dvec3 pointMinVirtuelle;
		////glm::dvec3 pointMaxVirtuelle;
		////convertirClotureAVirtuelle(pointMin.x, pointMin.y, pointMinVirtuelle);
		////convertirClotureAVirtuelle(pointMax.x, pointMax.y, pointMaxVirtuelle);
		////projection_.zoomerOut(pointMinVirtuelle, pointMaxVirtuelle);
		////camera_.reinitialiserCamera();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : Déplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Déplacement en pourcentage de la hauteur.
	///
	/// Ne fait rien
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
	{

	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
	///
	/// Ne fait rien
	///
	/// @param[in]  deplacement : Déplacement en coordonnées de clôture
	///                           (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerFenetreVirtuelleClavierHaut()
	///
	///
	/// Permet le déplacement de la fenêtre virtuelle à l'aide de la touche
	/// haut du clavier.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerFenetreVirtuelleClavierHaut()
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.orbiterXY(0.0, 8.0, true);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerFenetreVirtuelleClavierBas()
	///
	///
	/// Permet le déplacement de la fenêtre virtuelle à l'aide de la touche
	/// bas du clavier.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerFenetreVirtuelleClavierBas()
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.orbiterXY(0.0, -8.0, true);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerFenetreVirtuelleClavierBas()
	///
	///
	/// Permet le déplacement de la fenêtre virtuelle à l'aide de la touche
	/// droite du clavier.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerFenetreVirtuelleClavierDroite()
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.orbiterXY(-8.0, 0.0, true);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerFenetreVirtuelleClavierBas()
	///
	///
	/// Permet le déplacement de la fenêtre virtuelle à l'aide de la touche
	/// gauche du clavier.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerFenetreVirtuelleClavierGauche()
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.orbiterXY(8.0, 0.0, true);
		}
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerSouris(glm::dvec3 variationSouris, int x, int y)
	///
	///
	/// Permet le déplacement de la fenetre virtuelle à l'aide de la souris
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerSouris(glm::dvec3 variationSouris, int x, int y)
	{
		if (vuePremierePersonne_ == false)
		{
			camera_.deplacerXY(variationSouris.x, variationSouris.y, x, y);
		}
		/*camera_.assignerPosition(variationSouris);
		camera_.assignerPointVise(variationSouris)*/;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se déplacer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue orbitale.
	///
	/// @param[in]  deplacement : Déplacement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerZ(double deplacement)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::rotaterXY(double rotationX, double rotationY)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Une rotation de 100% correspondant à 360 degrés en X (angle de
	/// rotation) ou 180 degrés en Y (angle d'élévation).
	///
	/// @param[in]  rotationX : Rotation en pourcentage de la largeur.
	/// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::rotaterXY(double rotationX, double rotationY)
	{
		camera_.orbiterXY(rotationX * 360, rotationY * 180);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::rotaterXY(const glm::ivec2& rotation)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Un déplacement de la taille de la fenêtre correspond à 100%.
	///
	/// @param[in]  rotation : Rotation en coordonnées de clotûre (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::rotaterXY(const glm::ivec2& rotation)
	{
		const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
		rotaterXY(rotation[0] / (double) dimensions[0],
			rotation[1] / (double) dimensions[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait à un roulis et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::rotaterZ(double rotation)
	{
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
