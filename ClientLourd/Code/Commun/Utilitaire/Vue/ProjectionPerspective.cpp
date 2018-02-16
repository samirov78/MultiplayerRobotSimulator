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
	/// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arri�re (en @a z).
	/// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
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
		//// � IMPLANTER.
		//std::cout << "ProjectionPerspective_zoomIn" << std::endl;
		//double dimensions[4] = { xMinFenetre_, xMaxFenetre_,
		//	yMinFenetre_, yMaxFenetre_ };
		//// Ajusteur de l'incr�ment pour un zoom proportionnel � la taille de la fenetre

		//double ajusteurX = ( 1 - 1 / incrementZoom_ ) * (xMaxFenetre_ - xMinFenetre_) / 2.0;
		//double ajusteurY = ( 1 - 1 / incrementZoom_ ) * (yMaxFenetre_ - yMinFenetre_) / 2.0;
		//
		//xMinFenetre_ += ajusteurX;
		//xMaxFenetre_ -= ajusteurX;
		//yMinFenetre_ += ajusteurY;
		//yMaxFenetre_ -= ajusteurY;

		//// v�rifier la limite du zoom
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
		////// � IMPLANTER.
		////std::cout << "ProjectionPerspective_zoomOut" << std::endl;
		////double dimensions[4] = { xMinFenetre_, xMaxFenetre_,
		////	yMinFenetre_, yMaxFenetre_ };
		////// Ajusteur de l'incr�ment pour un zoom proportionnel � la taille de la fenetre

		////double ajusteurX = ( incrementZoom_ - 1 ) * (xMaxFenetre_ - xMinFenetre_) / 2.0;
		////double ajusteurY = ( incrementZoom_ - 1 ) * (yMaxFenetre_ - yMinFenetre_) / 2.0;
		////xMinFenetre_ -= ajusteurX;
		////xMaxFenetre_ += ajusteurX;
		////yMinFenetre_ -= ajusteurY;
		////yMaxFenetre_ += ajusteurY;

		////// v�rifier la limite de zoom
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
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
	///                       nouvelle cl�ture
	/// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
	///                       nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		// � IMPLANTER.
		GLdouble width = xMaxCloture_ - xMinCloture_, height = yMaxCloture_ - yMinCloture_;
		GLdouble dx = xMaxFenetre_ - xMinFenetre_, dy = yMaxFenetre_ - yMinFenetre_; // utiliser valeurs courantes


		//Remarque: Par d�finition de la fenetre graphique, son rapetissement et agrandissement se font via ses cotes droit et bas
		GLdouble conservAspectX = dx / width;

		xMaxFenetre_ += ((coinMax.x - xMaxCloture_) * conservAspectX) / 2.0; //Rapetissement ou agrandissement cote droit
		xMinFenetre_ -= ((coinMax.x - xMaxCloture_) * conservAspectX) / 2.0;

		GLdouble conservAspectY = dy / height;

		yMinFenetre_ -= ((coinMax.y - yMaxCloture_) * conservAspectY) / 2.0; // Rapetissement ou agrandissement cote bas
		yMaxFenetre_ += ((coinMax.y - yMaxCloture_) * conservAspectY) / 2.0;
		// Mise � jour de la cloture
		xMaxCloture_ = coinMax.x;
		yMaxCloture_ = coinMax.y;

		appliquer();

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fen�tre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propri�t�s de la
	/// fen�tre.
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
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::zoomerIn(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle)
	{
		//// � IMPLANTER.
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
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::zoomerOut(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle)
	{
		//// � IMPLANTER.
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
	/// @param[in]  deplacementX : le d�placement en @a x.
	/// @param[in]  deplacementY : le d�placement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::translater(double deplacementX, double deplacementY)
	{
		//// � IMPLANTER.
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
	/// @param[in]  deplacement : Le d�placement en coordonn�es de cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::translater(const glm::ivec2& deplacement)
	{
		////// � IMPLANTER.
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
		// � IMPLANTER.
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
