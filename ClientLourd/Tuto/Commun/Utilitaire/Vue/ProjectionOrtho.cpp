////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionOrtho.h"
#include "iostream"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
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
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		// � IMPLANTER.
		double dimensions[4] = { xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_ };
		// Ajusteur de l'incr�ment pour un zoom proportionnel � la taille de la fenetre

		double ajusteurX = ( 1 - 1 / incrementZoom_ ) * (xMaxFenetre_ - xMinFenetre_) / 2.0;
		double ajusteurY = ( 1 - 1 / incrementZoom_ ) * (yMaxFenetre_ - yMinFenetre_) / 2.0;
		
		xMinFenetre_ += ajusteurX;
		xMaxFenetre_ -= ajusteurX;
		yMinFenetre_ += ajusteurY;
		yMaxFenetre_ -= ajusteurY;

		// v�rifier la limite du zoom
		if (!(xMaxFenetre_ - xMinFenetre_ > zoomInMax_
			&& yMaxFenetre_ - yMinFenetre_ > zoomInMax_))
		{
			xMinFenetre_ = dimensions[0];
			xMaxFenetre_ = dimensions[1];
			yMinFenetre_ = dimensions[2];
			yMaxFenetre_ = dimensions[3];
		}

		appliquer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		// � IMPLANTER.

		double dimensions[4] = { xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_ };
		// Ajusteur de l'incr�ment pour un zoom proportionnel � la taille de la fenetre

		double ajusteurX = ( incrementZoom_ - 1 ) * (xMaxFenetre_ - xMinFenetre_) / 2.0;
		double ajusteurY = ( incrementZoom_ - 1 ) * (yMaxFenetre_ - yMinFenetre_) / 2.0;
		xMinFenetre_ -= ajusteurX;
		xMaxFenetre_ += ajusteurX;
		yMinFenetre_ -= ajusteurY;
		yMaxFenetre_ += ajusteurY;

		// v�rifier la limite de zoom
		if (!(xMaxFenetre_ - xMinFenetre_ < zoomOutMax_ &&
			yMaxFenetre_ - yMinFenetre_ < zoomOutMax_))
		{
			xMinFenetre_ = dimensions[0];
			xMaxFenetre_ = dimensions[1];
			yMinFenetre_ = dimensions[2];
			yMaxFenetre_ = dimensions[3];
		}

		appliquer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
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
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		// � IMPLANTER.
		GLdouble width = xMaxCloture_ - xMinCloture_, height = yMaxCloture_ - yMinCloture_;
		GLdouble dx = xMaxFenetre_ - xMinFenetre_, dy = yMaxFenetre_ - yMinFenetre_; // utiliser valeurs courantes


		//Remarque: Par d�finition de la fenetre graphique, son rapetissement et agrandissement se font via ses cotes droit et bas
		GLdouble conservAspectX = dx/width;

		xMaxFenetre_ += ((coinMax.x - xMaxCloture_) * conservAspectX) / 2.0; //Rapetissement ou agrandissement cote droit
		xMinFenetre_ -= ((coinMax.x - xMaxCloture_) * conservAspectX) / 2.0;

		GLdouble conservAspectY = dy/height;

		yMinFenetre_ -= ((coinMax.y - yMaxCloture_) * conservAspectY) / 2.0; // Rapetissement ou agrandissement cote bas
		yMaxFenetre_ += ((coinMax.y - yMaxCloture_) * conservAspectY) / 2.0;
		// Mise � jour de la cloture
		xMaxCloture_ = coinMax.x;
		yMaxCloture_ = coinMax.y;

		appliquer();
		
		
		      
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fen�tre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propri�t�s de la
	/// fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle d�termin� par deux coins.
	/// Ainsi la r�gion d�limit�e par le rectangle deviendra la fen�tre
	/// virtuelle.  La fen�tre r�sultante est ajust�e pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle)
	{
		// � IMPLANTER.
		xMinFenetre_ = pointMinVirtuelle.x; //fmin(pointMinVirtuelle.x,pointMaxVirtuelle.x);
		xMaxFenetre_ = pointMaxVirtuelle.x;//fmax(pointMinVirtuelle.x,pointMaxVirtuelle.x);
		yMinFenetre_ = pointMinVirtuelle.y;//fmin(pointMinVirtuelle.y, pointMaxVirtuelle.y);
		yMaxFenetre_ = pointMaxVirtuelle.y;//fmax(pointMinVirtuelle.y,pointMaxVirtuelle.y);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle d�limit� par deux coins.
	/// Ainsi la fen�tre virtuelle avant le zoom sera plac�e � l'interieur de
	/// la r�gion d�limit� par le rectangle.  La fen�tre r�sultante est ajust�e
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::dvec3& pointMinVirtuelle, const glm::dvec3& pointMaxVirtuelle)
	{
		// � IMPLANTER.
		xMinFenetre_ = pointMinVirtuelle.x;
		xMaxFenetre_ = pointMaxVirtuelle.x;
		yMinFenetre_ = pointMinVirtuelle.y;
		yMaxFenetre_ = pointMaxVirtuelle.y;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de d�placer la fen�tre virtuelle en @a x et en @a y.  Les
	/// d�placement doivent �tre exprim�s en proportion de la fen�tre virtuelle.
	///
	/// @param[in]  deplacementX : le d�placement en @a x.
	/// @param[in]  deplacementY : le d�placement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(double deplacementX, double deplacementY)
	{
		// � IMPLANTER.
		
		xMaxFenetre_ += deplacementX;
		xMinFenetre_ += deplacementX;
		yMaxFenetre_ += deplacementY;
		yMinFenetre_ += deplacementY;
		appliquer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	///
	/// Permet de translater la fen�tre virtuelle en fonction d'un d�placement
	/// en coordonn�es de cl�ture.
	///
	/// @param[in]  deplacement : Le d�placement en coordonn�es de cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	{
		xMaxFenetre_ += deplacement.x;
		xMinFenetre_ += deplacement.x;
		yMinFenetre_ += deplacement.y;
		yMaxFenetre_ += deplacement.y;
		appliquer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fen�tre virtuelle sur un point de l'�cran. Le
	/// point de l'�cran est convertit en coordonn�es virtuelles et il devient
	/// le centre de la fen�tre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		// � IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		

	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
