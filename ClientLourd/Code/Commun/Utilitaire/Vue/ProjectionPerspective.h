////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionPerspective.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONPERSPECTIVE_H__
#define __UTILITAIRE_PROJECTIONPERSPECTIVE_H__


#include "Projection.h"
#define FACTEUR_ZOOM_UNITAIRE 1


namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionPerspective
	/// @brief Classe implantant une projection orthogonale.
	///
	/// Cette classe implante l'interface de projection d�finie par la
	/// classe de base Projection et ajoute certaines fonctionnalit�es
	/// sp�cifiques � la projection orthogonale, comme le zoom autour d'un
	/// point en particulier et le zoom �lastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class ProjectionPerspective : public Projection
	{
	public:
		/// Constructeur.
		ProjectionPerspective(int xMinCloture, int xMaxCloture,
			int yMinCloture, int yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double xMinFenetre, double xMaxFenetre,
			double yMinFenetre, double yMaxFenetre);


		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la cl�ture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);
		/// Application de la projection.
		virtual void appliquer() const;


		/// Zoom out �lastique, sur un rectangle.
		void zoomerOut(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle);
		/// Zoom in �latique, sur un rectangle.
		void zoomerIn(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle);

		/// Translater la fen�tre virtuelle d'un pourcentage en @a X ou en @a Y
		void translater(double deplacementX, double deplacementY);
		/// Translater la fen�tre virtuelle d'un vecteur
		void translater(const glm::ivec2& deplacement);
		/// Centrer la fen�tre virtuelle sur un point
		void centrerSurPoint(const glm::ivec2& pointCentre);

		/// Obtenir les coordonn�es de la fen�tre virtuelle.
		inline void obtenirCoordonneesFenetreVirtuelle(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const;

		/// Obtenir le niveau de zoom
		inline double obtenirIncrementZoom() const;

	private:
		/// Ajuste la fen�tre virtuelle pour respecter le rapport d'aspect.
		void ajusterRapportAspect();

		/// Borne inf�rieure en X de la fen�tre virtuelle.
		double xMinFenetre_;
		/// Borne s�rieure en X de la fen�tre virtuelle.
		double xMaxFenetre_;
		/// Borne inf�rieure en Y de la fen�tre virtuelle.
		double yMinFenetre_;
		/// Borne sup�rieure en Y de la fen�tre virtuelle.
		double yMaxFenetre_;
		

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
	///
	/// Cette fonction retourne les coordonn�es de la fen�tre virtuelle
	/// associ�e � cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonn�e minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonn�e maximale.
	///
	/// @return Les coordonn�es de la fen�tre virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline void ProjectionPerspective::obtenirCoordonneesFenetreVirtuelle(
		double& xMin, double& xMax, double& yMin, double& yMax
		) const
	{
		xMin = xMinFenetre_;
		xMax = xMaxFenetre_;
		yMin = yMinFenetre_;
		yMax = yMaxFenetre_;
	}
	inline double ProjectionPerspective::obtenirIncrementZoom() const
	{
		return Projection::obtenirIncrementZoom();
	}
}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTIONORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
