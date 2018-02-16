///////////////////////////////////////////////////////////////////////////////
/// @file visiteurSelectElastique.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "visiteurSelectElastique.h"
#include <iostream>
#include "FacadeModele.h"
#include "Utilitaire.h"

namespace math {
	class Plan3D;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  visiteurSelectElastique::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection à l'aide 
/// d'un rectangle élastique à un objet de la classe NoeudPoteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void  visiteurSelectElastique::visiter(NoeudPoteau& noeud)
{
	glm::dvec3 position = noeud.obtenirPositionRelative();
	glm::dvec3 normal = vue_->obtenirCamera().obtenirPosition();
	const math::Plan3D plan{ normal, glm::dvec3(position.x, position.y, -14 + 4) };
	glm::dvec3 coin1;
	vue_->convertirClotureAVirtuelle(xDebut_, yDebut_, plan, coin1);

	glm::dvec3 coin2;
	vue_->convertirClotureAVirtuelle(xDebut_, yFin_, plan, coin2);

	glm::dvec3 coin3;
	vue_->convertirClotureAVirtuelle(xFin_, yFin_, plan, coin3);

	glm::dvec3 coin4;
	vue_->convertirClotureAVirtuelle(xFin_, yDebut_, plan, coin4);

	if (utilitaire::pointDansUnRectangle(position, coin1, coin2, coin3, coin4))
	{
		if (selectionCTRL_)
		{
			noeud.inverserSelection();
		}
		else
		{
			noeud.assignerSelection(true);
		}
		if (noeud.couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			noeud.attribuerCouleurSelection();

		}
	}
	//noeud.setCustomSelectColor(230, 0, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void visiteurSelectElastique::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection à l'aide 
/// d'un rectangle élastique à un objet de la classe NoeudMur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void  visiteurSelectElastique::visiter(NoeudMur& noeud)
{
	glm::dvec3 position = noeud.obtenirPositionRelative();
	glm::dvec3 normal = vue_->obtenirCamera().obtenirPosition();
	const math::Plan3D plan{ normal, glm::dvec3(position.x, position.y, -14 + 3) };
	glm::dvec3 coin1;
	vue_->convertirClotureAVirtuelle(xDebut_, yDebut_, plan, coin1);

	glm::dvec3 coin2;
	vue_->convertirClotureAVirtuelle(xDebut_, yFin_, plan, coin2);

	glm::dvec3 coin3;
	vue_->convertirClotureAVirtuelle(xFin_, yFin_, plan, coin3);

	glm::dvec3 coin4;
	vue_->convertirClotureAVirtuelle(xFin_, yDebut_, plan, coin4);

	if (utilitaire::pointDansUnRectangle(position, coin1, coin2, coin3, coin4))
	{
		if (selectionCTRL_)
		{
			noeud.inverserSelection();
		}
		else
		{
			noeud.assignerSelection(true);
		}
		if (noeud.couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			noeud.attribuerCouleurSelection();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void visiteurSelectElastique::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection à l'aide 
/// d'un rectangle élastique à un objet de la classe NoeudSegment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void visiteurSelectElastique::visiter(NoeudSegment& noeud)
{
	glm::dvec3 position = noeud.obtenirPositionRelative();
	glm::dvec3 normal = vue_->obtenirCamera().obtenirPosition();
	const math::Plan3D plan{ normal, glm::dvec3(position.x, position.y, -14) };
	glm::dvec3 coin1;
	vue_->convertirClotureAVirtuelle(xDebut_, yDebut_, plan, coin1);

	glm::dvec3 coin2;
	vue_->convertirClotureAVirtuelle(xDebut_, yFin_, plan, coin2);

	glm::dvec3 coin3;
	vue_->convertirClotureAVirtuelle(xFin_, yFin_, plan, coin3);

	glm::dvec3 coin4;
	vue_->convertirClotureAVirtuelle(xFin_, yDebut_, plan, coin4);

	if (utilitaire::pointDansUnRectangle(position, coin1, coin2, coin3, coin4))
	{
		if (selectionCTRL_)
		{
			noeud.inverserSelection();
		}
		else
		{
			noeud.assignerSelection(true);
		}
		if (noeud.couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			noeud.obtenirParent()->attribuerCouleurSelection();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void visiteurSelectElastique::visiter(NoeudLigne& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection à l'aide 
/// d'un rectangle élastique à un objet de la classe NoeudLigne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void visiteurSelectElastique::visiter(NoeudLigne& noeud)
{
	if (!selectionCTRL_)
	{
		bool sontSelectionnes = false;
		for (unsigned int i = 0; i < noeud.obtenirNombreEnfants(); i++)
		{
			if (noeud.obtenirEnfants()->at(i)->estSelectionne())
			{
				sontSelectionnes = true;
			}
		}
		if (sontSelectionnes)
		{
			noeud.selectionnerTout();
		}
		else
		{
			noeud.deselectionnerTout();
		}
	}
	else
	{
		if (noeud.estSelectionne())
		{
			bool estSelectionne = true;
			for (unsigned int i = 0; i < noeud.obtenirNombreEnfants(); i++)
			{
				if (!noeud.obtenirEnfants()->at(i)->estSelectionne())
				{
					noeud.inverserSelection();
					estSelectionne = false;
				}
			}
			if (!estSelectionne)
			{
				noeud.deselectionnerTout();
			}
		}
		else
		{
			bool estSelectionne = false;
			for (unsigned int i = 0; i < noeud.obtenirNombreEnfants(); i++)
			{
				if (noeud.obtenirEnfants()->at(i)->estSelectionne())
				{
					noeud.inverserSelection();
					estSelectionne = true;
				}
			}
			if (estSelectionne)
			{
				noeud.selectionnerTout();				
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void visiteurSelectElastique::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection à l'aide 
/// d'un rectangle élastique à un objet de la classe NoeudFleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void visiteurSelectElastique::visiter(NoeudFleche& noeud)
{
	glm::dvec3 position = noeud.obtenirPositionRelative();
	glm::dvec3 normal = vue_->obtenirCamera().obtenirPosition();
	const math::Plan3D plan{ normal, glm::dvec3(position.x, position.y, -14) };
	glm::dvec3 coin1;
	vue_->convertirClotureAVirtuelle(xDebut_, yDebut_, plan, coin1);

	glm::dvec3 coin2;
	vue_->convertirClotureAVirtuelle(xDebut_, yFin_, plan, coin2);

	glm::dvec3 coin3;
	vue_->convertirClotureAVirtuelle(xFin_, yFin_, plan, coin3);

	glm::dvec3 coin4;
	vue_->convertirClotureAVirtuelle(xFin_, yDebut_, plan, coin4);

	if (utilitaire::pointDansUnRectangle(position, coin1, coin2, coin3, coin4))
	{
		if (selectionCTRL_)
		{
			noeud.inverserSelection();
		}
		else
		{
			noeud.assignerSelection(true);
		}
		if (noeud.couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			noeud.attribuerCouleurSelection();
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void visiteurSelectElastique::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection à l'aide 
/// d'un rectangle élastique à un objet de la classe NoeudTable.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void visiteurSelectElastique::visiter(NoeudTable& noeud)
{

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
