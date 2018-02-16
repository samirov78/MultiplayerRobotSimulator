///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "Utilitaire.h"
#include "Camera.h"
#include <iostream>

namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Camera::Camera(const glm::dvec3& position, const glm::dvec3& pointVise, const glm::dvec3& directionHautCamera, const glm::dvec3& directionHautMonde)
	///
	/// Constructeur de la cam�ra � partir des coordonn�es cart�siennes.
	///
	/// @param[in]  position            : position de la cam�ra.
	/// @param[in]  pointVise           : point vis�.
	/// @param[in]  directionHautCamera : direction du haut de la cam�ra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   cam�ra.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Camera::Camera(const glm::dvec3& position,
		const glm::dvec3& pointVise,
		const glm::dvec3& directionHautCamera,
		const glm::dvec3& directionHautMonde, bool cameraOrbite
		)
		: position_{ position },
		pointVise_{ pointVise },
		directionHaut_{ directionHautCamera },
		directionHautMonde_{ directionHautMonde }
	
	{
		dernierX = 0;
		dernierY = 0;
		distCam_ = 250.0;
		phiCam_ = 45.0;
		thetaCam_ = -90.0;
		cameraOrbite_ = cameraOrbite;
		distCam_ = std::sqrt(std::pow(position.x,2.0)+ std::pow(position.y, 2.0)+ std::pow(position.z, 2.0));

		if (cameraOrbite)
		{
			mettreAjourPositionCamera();
		}
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// D�place la cam�ra dans le plan perpendiculaire � la direction vis�e
	///
	/// @param[in]  deplacementX : D�placement sur l'axe horizontal du plan de
	///                            la cam�ra.
	/// @param[in]  deplacementY : D�placement sur l'axe vertical du plan de la
	///                            cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerXY(double deplacementX, double deplacementY, int x, int y)
	{
		if (!cameraOrbite_)
		{
			position_.x += deplacementX;
			position_.y += deplacementY;
			pointVise_.x += deplacementX;
			pointVise_.y += deplacementY;
		}
		else
		{
			if (x >= 0 && y >= 0)
			{
				x = x / 10;
				y = y / 10;

				if (dernierY > y) 
					orbiterXY(0.0, 8.0, true);
				if (dernierY < y)
					orbiterXY(0.0, -8.0, true);

				if (dernierX > x)
					orbiterXY(8.0, 0.0, true);
				if (dernierX < x)
					orbiterXY(-8.0, 0.0, true);

				dernierX = x;
				dernierY = y;

				phiCam_ = (phiCam_ <= 88.0) ? phiCam_ : 88.0;
				phiCam_ = (phiCam_ >= 10.0) ? phiCam_ : 10.0;

				thetaCam_ = (thetaCam_ > 360.0) ? 0 : thetaCam_;
				thetaCam_ = (thetaCam_ < -360.0) ? 360 : thetaCam_;
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
	///
	/// D�place la cam�ra dans l'axe de la direction vis�e.
	///
	/// @param[in]  deplacement    : D�placement sur l'axe de la direction vis�e
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerZ(double deplacement, bool bougePointVise)
	{
		position_.z += deplacement;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de sa position (et donc d�placement du
	/// point vis� en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point vis� par rapport � la position.
	/// @param[in] rotationY        : Modification de l'angle d'�l�vation du
	///                               point vis� par rapport � la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectu�e
	///                               si elle am�nerait une inversion de la
	///                               cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::tournerXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de son point de vis� (et donc d�placement
	/// de la position en gardant le point de vis� fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  rotationY        : Modification de l'angle d'�l�vation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectu�
	///                                si elle am�nerait une inversion de la
	///                                cam�ra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX, double rotationY, bool empecheInversion)
	{
		phiCam_ += rotationY/5;
		thetaCam_ += rotationX/5;

		phiCam_ = (phiCam_ <= 88.0) ? phiCam_ : 88.0;
		phiCam_ = (phiCam_ >= 10.0) ? phiCam_ : 10.0;

		thetaCam_ = (thetaCam_ > 360.0) ? 0 : thetaCam_; 
		thetaCam_ = (thetaCam_ < -360.0) ? 360 : thetaCam_;  

		mettreAjourPositionCamera();
		positionner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::positionner() const
	///
	/// Positionne la cam�ra dans la sc�ne � l'aide de gluLookAt().
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Camera::positionner() const
	{
		if (cameraOrbite_)
		{
			gluLookAt(position_[0], position_[1], position_[2],
				0,0,0 ,
				0, 0, 1);
		} 
		else
		{
			gluLookAt(position_[0], position_[1], position_[2],
				pointVise_[0], pointVise_[1], pointVise_[2],
				directionHaut_[0], directionHaut_[1], directionHaut_[2]);
		}
			
	}

	void Camera::reinitialiserCamera()
	{
		position_ = glm::dvec3(0, 0, 200 );
		pointVise_ = glm::dvec3(0, 0, 0);
		directionHaut_ = glm::dvec3(0, 1, 0);
		//directionHautMonde_ = glm::dvec3(0, 1, 0);
	}


	void Camera::effectuerZoomIn()
	{
		if (distCam_ > 30.0)
			distCam_ -= 12.0;

		mettreAjourPositionCamera();
		positionner();
	}

	void Camera::effectuerZoomOut()
	{
		if (distCam_ < 294.0)
			distCam_ += 12.0;
		mettreAjourPositionCamera();
		positionner();
	}

	void Camera::mettreAjourPositionCamera()
	{
		position_.x = distCam_*sin(utilitaire::DEG_TO_RAD(phiCam_))*cos(utilitaire::DEG_TO_RAD(thetaCam_));
		position_.y = distCam_*sin(utilitaire::DEG_TO_RAD(phiCam_))*sin(utilitaire::DEG_TO_RAD(thetaCam_));
		position_.z = distCam_*cos(utilitaire::DEG_TO_RAD(phiCam_));
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
