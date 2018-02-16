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
	/// Constructeur de la caméra à partir des coordonnées cartésiennes.
	///
	/// @param[in]  position            : position de la caméra.
	/// @param[in]  pointVise           : point visé.
	/// @param[in]  directionHautCamera : direction du haut de la caméra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   caméra.
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
	/// Déplace la caméra dans le plan perpendiculaire à la direction visée
	///
	/// @param[in]  deplacementX : Déplacement sur l'axe horizontal du plan de
	///                            la caméra.
	/// @param[in]  deplacementY : Déplacement sur l'axe vertical du plan de la
	///                            caméra.
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
	/// Déplace la caméra dans l'axe de la direction visée.
	///
	/// @param[in]  deplacement    : Déplacement sur l'axe de la direction visée
	/// @param[in]  bougePointVise : Si vrai, le point de visé est également
	///                              déplacé.
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
	/// Rotation de la caméra autour de sa position (et donc déplacement du
	/// point visé en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point visé par rapport à la position.
	/// @param[in] rotationY        : Modification de l'angle d'élévation du
	///                               point visé par rapport à la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectuée
	///                               si elle amènerait une inversion de la
	///                               caméra.
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
	/// Rotation de la caméra autour de son point de visé (et donc déplacement
	/// de la position en gardant le point de visé fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de visé.
	/// @param[in]  rotationY        : Modification de l'angle d'élévation de la
	///                                position par rapport au point de visé.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectué
	///                                si elle amènerait une inversion de la
	///                                caméra.
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
	/// Positionne la caméra dans la scène à l'aide de gluLookAt().
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
