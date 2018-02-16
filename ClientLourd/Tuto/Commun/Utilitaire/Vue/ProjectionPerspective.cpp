////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionPerspective.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionPerspective.h"
#include "iostream"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionPerspective::ProjectionPerspective(int xMinCloture, int xMaxCloture,int yMinCloture, int yMaxCloture,double zAvant, double zArriere,double zoomInMax, double zoomOutMax,double incrementZoom,double xMinFenetre, double xMaxFenetre,double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection en perspective.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionPerspective::ProjectionPerspective(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, true },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::zoomerIn()
	///
	/// Ne fait rien
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::zoomerIn()
	{
		//// À IMPLANTER.
		//std::cout << "ProjectionPerspective_zoomIn" << std::endl;
		//double dimensions[4] = { xMinFenetre_, xMaxFenetre_,
		//	yMinFenetre_, yMaxFenetre_ };
		//// Ajusteur de l'incrément pour un zoom proportionnel à la taille de la fenetre

		//double ajusteurX = ( 1 - 1 / incrementZoom_ ) * (xMaxFenetre_ - xMinFenetre_) / 2.0;
		//double ajusteurY = ( 1 - 1 / incrementZoom_ ) * (yMaxFenetre_ - yMinFenetre_) / 2.0;
		//
		//xMinFenetre_ += ajusteurX;
		//xMaxFenetre_ -= ajusteurX;
		//yMinFenetre_ += ajusteurY;
		//yMaxFenetre_ -= ajusteurY;

		//// vérifier la limite du zoom
		//if (!(xMaxFenetre_ - xMinFenetre_ > zoomInMax_
		//	&& yMaxFenetre_ - yMinFenetre_ > zoomInMax_))
		//{
		//	xMinFenetre_ = dimensions[0];
		//	xMaxFenetre_ = dimensions[1];
		//	yMinFenetre_ = dimensions[2];
		//	yMaxFenetre_ = dimensions[3];
		//}

		//appliquer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void void ProjectionPerspective::zoomerOut()
	///
	/// Ne fait rien
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionPerspective::zoomerOut()
	{
		////// À IMPLANTER.
		////std::cout << "ProjectionPerspective_zoomOut" << std::endl;
		////double dimensions[4] = { xMinFenetre_, xMaxFenetre_,
		////	yMinFenetre_, yMaxFenetre_ };
		////// Ajusteur de l'incrément pour un zoom proportionnel à la taille de la fenetre

		////double ajusteurX = ( incrementZoom_ - 1 ) * (xMaxFenetre_ - xMinFenetre_) / 2.0;
		////double ajusteurY = ( incrementZoom_ - 1 ) * (yMaxFenetre_ - yMinFenetre_) / 2.0;
		////xMinFenetre_ -= ajusteurX;
		////xMaxFenetre_ += ajusteurX;
		////yMinFenetre_ -= ajusteurY;
		////yMaxFenetre_ += ajusteurY;

		////// vérifier la limite de zoom
		////if (!(xMaxFenetre_ - xMinFenetre_ < zoomOutMax_ &&
		////	yMaxFenetre_ - yMinFenetre_ < zoomOutMax_))
		////{
		////	xMinFenetre_ = dimensions[0];
		////	xMaxFenetre_ = dimensions[1];
		////	yMinFenetre_ = dimensions[2];
		////	yMaxFenetre_ = dimensions[3];
		////}

		////appliquer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// L'agrandissement de la fenêtre virtuelle est proportionnel à
	/// l'agrandissement de la clotûre afin que les objets gardent la même
	/// grandeur apparente lorsque la fenêtre est redimensionnée.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		// À IMPLANTER.
		GLdouble width = xMaxCloture_ - xMinCloture_, height = yMaxCloture_ - yMinCloture_;
		GLdouble dx = xMaxFenetre_ - xMinFenetre_, dy = yMaxFenetre_ - yMinFenetre_; // utiliser valeurs courantes


		//Remarque: Par définition de la fenetre graphique, son rapetissement et agrandissement se font via ses cotes droit et bas
		GLdouble conservAspectX = dx / width;

		xMaxFenetre_ += ((coinMax.x - xMaxCloture_) * conservAspectX) / 2.0; //Rapetissement ou agrandissement cote droit
		xMinFenetre_ -= ((coinMax.x - xMaxCloture_) * conservAspectX) / 2.0;

		GLdouble conservAspectY = dy / height;

		yMinFenetre_ -= ((coinMax.y - yMaxCloture_) * conservAspectY) / 2.0; // Rapetissement ou agrandissement cote bas
		yMaxFenetre_ += ((coinMax.y - yMaxCloture_) * conservAspectY) / 2.0;
		// Mise à jour de la cloture
		xMaxCloture_ = coinMax.x;
		yMaxCloture_ = coinMax.y;

		appliquer();

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fenêtre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propriétés de la
	/// fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::appliquer() const
	{
		 //glOrtho(xMinFenetre_, xMaxFenetre_,yMinFenetre_, yMaxFenetre_,zAvant_, zArriere_);
		// void Perspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far);
		// void gluPerspective(GLdouble fovy,GLdouble aspect, GLdouble zNear, GLdouble zFar);
		gluPerspective(15.0, ((xMaxFenetre_- xMinFenetre_) / (yMaxFenetre_- yMinFenetre_)), 0.5, 500.0);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Ne fait rien
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::zoomerIn(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle)
	{
		//// À IMPLANTER.
		//std::cout << "zoomerIn" << std::endl;
		//xMinFenetre_ = pointMinVirtuelle.x; //fmin(pointMinVirtuelle.x,pointMaxVirtuelle.x);
		//xMaxFenetre_ = pointMaxVirtuelle.x;//fmax(pointMinVirtuelle.x,pointMaxVirtuelle.x);
		//yMinFenetre_ = pointMinVirtuelle.y;//fmin(pointMinVirtuelle.y, pointMaxVirtuelle.y);
		//yMaxFenetre_ = pointMaxVirtuelle.y;//fmax(pointMinVirtuelle.y,pointMaxVirtuelle.y);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Ne fait rien
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::zoomerOut(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle)
	{
		//// À IMPLANTER.
		//xMinFenetre_ = pointMinVirtuelle.x;
		//xMaxFenetre_ = pointMaxVirtuelle.x;
		//yMinFenetre_ = pointMinVirtuelle.y;
		//yMaxFenetre_ = pointMaxVirtuelle.y;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::translater( double deplacementX, double deplacementY )
	///
	/// Ne fait rien.
	///
	/// @param[in]  deplacementX : le déplacement en @a x.
	/// @param[in]  deplacementY : le déplacement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::translater(double deplacementX, double deplacementY)
	{
		//// À IMPLANTER.
		//xMaxFenetre_ += deplacementX;
		//xMinFenetre_ += deplacementX;
		//yMaxFenetre_ += deplacementY;
		//yMinFenetre_ += deplacementY;
		//appliquer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::translater(const glm::ivec2& deplacement)
	///
	///Ne fait rien
	///
	/// @param[in]  deplacement : Le déplacement en coordonnées de clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::translater(const glm::ivec2& deplacement)
	{
		////// À IMPLANTER.
		////xMaxFenetre_ += deplacement.x;
		////xMinFenetre_ += deplacement.x;
		////yMinFenetre_ += deplacement.y;
		////yMaxFenetre_ += deplacement.y;
		////appliquer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Ne fait rien
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		// À IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::ajusterRapportAspect()
	///
	/// Ne fait rien
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::ajusterRapportAspect()
	{
		

	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
