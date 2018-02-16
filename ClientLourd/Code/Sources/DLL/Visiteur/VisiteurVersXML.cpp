///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurVersXML.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurVersXML.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVersXML::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de sauvegarde
/// à un objet de la classe NoeudPoteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVersXML::visiter(NoeudPoteau& noeud)
{
	if (noeud.estEnregistrable()){

		// http://www.grinninglizard.com/tinyxml2docs/classtinyxml2_1_1_x_m_l_element.html

		// creation d'un nouveau noeud 
		tinyxml2::XMLElement* noeudPoteauXML{ (documentXML_->NewElement("poteau")) };

		// ecrire l'id du noeud visite 
		noeudPoteauXML->SetAttribute("ID", noeud.ID.c_str());

		// ecrire type du noeud visite 
		noeudPoteauXML->SetAttribute("Type", noeud.obtenirType().c_str());

		// proprietes avec bool 
		noeudPoteauXML->SetAttribute("Affiche", noeud.estAffiche());
		noeudPoteauXML->SetAttribute("Enregistrable", noeud.estEnregistrable());
		noeudPoteauXML->SetAttribute("Selectionnable", noeud.estSelectionnable());
		///noeudPoteauXML->SetAttribute("Selectionne", false);

		//ecrire la rotation relative du poteau
		glm::dvec4 tableauRotatioRelative = noeud.obtenirRotationRelative();
		noeudPoteauXML->SetAttribute("Angle", tableauRotatioRelative[0]);
		noeudPoteauXML->SetAttribute("x", tableauRotatioRelative[1]);
		noeudPoteauXML->SetAttribute("y", tableauRotatioRelative[2]);
		noeudPoteauXML->SetAttribute("z", tableauRotatioRelative[3]);

		// ecrire position relative du poteau
		glm::dvec3 tableauPositionRelative = noeud.obtenirPositionRelative();

		noeudPoteauXML->SetAttribute("Pos_x", tableauPositionRelative[0]);
		noeudPoteauXML->SetAttribute("Pos_y", tableauPositionRelative[1]);
		noeudPoteauXML->SetAttribute("Pos_z", tableauPositionRelative[2]);

		// ecrire redimentionnement relatif du poteau

		glm::dvec3 tableauRedimensionRelative = noeud.obtenirRedimensionnementRelative();
		noeudPoteauXML->SetAttribute("Redim_x", tableauRedimensionRelative[0]);
		noeudPoteauXML->SetAttribute("Redim_y", tableauRedimensionRelative[1]);
		noeudPoteauXML->SetAttribute("Redim_z", tableauRedimensionRelative[2]);

		/*3glm::dvec3 pointDepart = noeud.getPointDepart();
		glm::dvec3 pointFin = noeud.getPointFin();

		noeudPoteauXML->SetAttribute("Depart_x", pointDepart.x);
		noeudPoteauXML->SetAttribute("Depart_y", pointDepart.y);
		noeudPoteauXML->SetAttribute("Depart_z", pointDepart.z);

		noeudPoteauXML->SetAttribute("Fin_x", pointFin.x);
		noeudPoteauXML->SetAttribute("Fin_y", pointFin.y);
		noeudPoteauXML->SetAttribute("Fin_z", pointFin.z);*/

		// on lie le noeud cree au noued XML du visiteur 
		elementXML_->LinkEndChild(noeudPoteauXML);
	}
	// permet de rajouter les noeud, un a la suite de l'autre	
	// -- decommente moi pour voir ce que je peux faire dans un fichier XML 
	//elementXML_ = noeudPoteauXML;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVersXML::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de sauvegarde
/// à un objet de la classe NoeudMur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVersXML::visiter(NoeudMur& noeud)
{
	if (noeud.estEnregistrable()){

		// creation d'un nouveau noeud 
		tinyxml2::XMLElement* noeudMurXML{ (documentXML_->NewElement("mur")) };

		// ecrire l'id du noeud visite 
		noeudMurXML->SetAttribute("ID", noeud.ID.c_str());

		// ecrire type du noeud visite 
		noeudMurXML->SetAttribute("Type", noeud.obtenirType().c_str());

		// proprietes avec bool 
		noeudMurXML->SetAttribute("Affiche", noeud.estAffiche());
		noeudMurXML->SetAttribute("Enregistrable", noeud.estEnregistrable());
		noeudMurXML->SetAttribute("Selectionnable", noeud.estSelectionnable());
		////noeudMurXML->SetAttribute("Selectionne", false);

		//ecrire la rotation relative du mur
		glm::dvec4 tableauRotatioRelative = noeud.obtenirRotationRelative();
		noeudMurXML->SetAttribute("Angle", tableauRotatioRelative[0]);
		noeudMurXML->SetAttribute("x", tableauRotatioRelative[1]);
		noeudMurXML->SetAttribute("y", tableauRotatioRelative[2]);
		noeudMurXML->SetAttribute("z", tableauRotatioRelative[3]);

		// ecrire position relative du mur
		glm::dvec3 tableauPositionRelative = noeud.obtenirPositionRelative();

		noeudMurXML->SetAttribute("Pos_x", tableauPositionRelative[0]);
		noeudMurXML->SetAttribute("Pos_y", tableauPositionRelative[1]);
		noeudMurXML->SetAttribute("Pos_z", tableauPositionRelative[2]);

		// ecrire redimentionnement relatif du mur
		glm::dvec3 tableauRedimensionRelative = noeud.obtenirRedimensionnementRelative();
		noeudMurXML->SetAttribute("Redim_x", tableauRedimensionRelative[0]);
		noeudMurXML->SetAttribute("Redim_y", tableauRedimensionRelative[1]);
		noeudMurXML->SetAttribute("Redim_z", tableauRedimensionRelative[2]);

		/*3glm::dvec3 pointDepart = noeud.getPointDepart();
		glm::dvec3 pointFin = noeud.getPointFin();

		noeudMurXML->SetAttribute("Depart_x", pointDepart.x);
		noeudMurXML->SetAttribute("Depart_y", pointDepart.y);
		noeudMurXML->SetAttribute("Depart_z", pointDepart.z);

		noeudMurXML->SetAttribute("Fin_x", pointFin.x);
		noeudMurXML->SetAttribute("Fin_y", pointFin.y);
		noeudMurXML->SetAttribute("Fin_z", pointFin.z);*/

		// on lie le noeud cree au noued XML du visiteur 
		elementXML_->LinkEndChild(noeudMurXML);
	}
	// voir la note ci-haut 
	//elementXML_ = noeudMurXML;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVersXML::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de sauvegarde
/// à un objet de la classe NoeudTable.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVersXML::visiter(NoeudTable& noeud)
{
	// a implemanter
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVersXML::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de sauvegarde
/// à un objet de la classe NoeudFleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVersXML::visiter(NoeudFleche& noeud)
{
	if (noeud.estEnregistrable()){
		// creation d'un nouveau noeud 
		tinyxml2::XMLElement* noeudFlecheXML{ (documentXML_->NewElement("fleche")) };

		
		// ecrire l'id du noeud visite 
		noeudFlecheXML->SetAttribute("ID", noeud.ID.c_str());

		// ecrire type du noeud visite 
		noeudFlecheXML->SetAttribute("Type", noeud.obtenirType().c_str());


		// proprietes avec bool 
		noeudFlecheXML->SetAttribute("Affiche", noeud.estAffiche());
		noeudFlecheXML->SetAttribute("Enregistrable", noeud.estEnregistrable());
		noeudFlecheXML->SetAttribute("Selectionnable", noeud.estSelectionnable());
		///noeudFlecheXML->SetAttribute("Selectionne", false);

		//ecrire la rotation relative du poteau
		glm::dvec4 tableauRotatioRelative = noeud.obtenirRotationRelative();
		noeudFlecheXML->SetAttribute("Angle", tableauRotatioRelative[0]);
		noeudFlecheXML->SetAttribute("x", tableauRotatioRelative[1]);
		noeudFlecheXML->SetAttribute("y", tableauRotatioRelative[2]);
		noeudFlecheXML->SetAttribute("z", tableauRotatioRelative[3]);

		// ecrire position relative du poteau
		glm::dvec3 tableauPositionRelative = noeud.obtenirPositionRelative();

		noeudFlecheXML->SetAttribute("Pos_x", tableauPositionRelative[0]);
		noeudFlecheXML->SetAttribute("Pos_y", tableauPositionRelative[1]);
		noeudFlecheXML->SetAttribute("Pos_z", tableauPositionRelative[2]);

		// ecrire redimentionnement relatif du poteau

		glm::dvec3 tableauRedimensionRelative = noeud.obtenirRedimensionnementRelative();
		noeudFlecheXML->SetAttribute("Redim_x", tableauRedimensionRelative[0]);
		noeudFlecheXML->SetAttribute("Redim_y", tableauRedimensionRelative[1]);
		noeudFlecheXML->SetAttribute("Redim_z", tableauRedimensionRelative[2]);

		/*glm::dvec3 pointDepart = noeud.getPointDepart();
		glm::dvec3 pointFin = noeud.getPointFin();

		noeudFlecheXML->SetAttribute("Depart_x", pointDepart.x);
		noeudFlecheXML->SetAttribute("Depart_y", pointDepart.y);
		noeudFlecheXML->SetAttribute("Depart_z", pointDepart.z);

		noeudFlecheXML->SetAttribute("Fin_x", pointFin.x);
		noeudFlecheXML->SetAttribute("Fin_y", pointFin.y);
		noeudFlecheXML->SetAttribute("Fin_z", pointFin.z);*/

		// on lie le noeud cree au noued XML du visiteur 
		elementXML_->LinkEndChild(noeudFlecheXML);
	}
	// permet de rajouter les noeud, un a la suite de l'autre	
	// -- decommente moi pour voir ce que je peux faire dans un fichier XML 
	//elementXML_ = noeudPoteauXML;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVersXML::visiter(NoeudLigne& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de sauvegarde
/// à un objet de la classe NoeudLigne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVersXML::visiter(NoeudLigne& noeud)
{

	// creation d'un nouveau noeud 
	tinyxml2::XMLElement* noeudLigneXML{ (documentXML_->NewElement("ligne")) };
	// ecrire type du noeud visite 
	noeudLigneXML->SetAttribute("Type", noeud.obtenirType().c_str());
	// ecrire l'id du noeud visite 
	noeudLigneXML->SetAttribute("ID", noeud.ID.c_str());
	// ecriture des attributs de la ligne 
	// proprietes avec bool 
		noeudLigneXML->SetAttribute("Affiche", noeud.estAffiche());
		noeudLigneXML->SetAttribute("Enregistrable", noeud.estEnregistrable());
		noeudLigneXML->SetAttribute("Selectionnable", noeud.estSelectionnable());
		///noeudLigneXML->SetAttribute("Selectionne",false);

		//ecrire la rotation relative du mur
		glm::dvec4 tableauRotatioRelative = noeud.obtenirRotationRelative();
		noeudLigneXML->SetAttribute("Angle", tableauRotatioRelative[0]);
		noeudLigneXML->SetAttribute("x", tableauRotatioRelative[1]);
		noeudLigneXML->SetAttribute("y", tableauRotatioRelative[2]);
		noeudLigneXML->SetAttribute("z", tableauRotatioRelative[3]);

		// ecrire position relative du mur
		glm::dvec3 tableauPositionRelative = noeud.obtenirPositionRelative();

		noeudLigneXML->SetAttribute("Pos_x", tableauPositionRelative[0]);
		noeudLigneXML->SetAttribute("Pos_y", tableauPositionRelative[1]);
		noeudLigneXML->SetAttribute("Pos_z", tableauPositionRelative[2]);

		// ecrire redimentionnement relatif du mur
		glm::dvec3 tableauRedimensionRelative = noeud.obtenirRedimensionnementRelative();
		noeudLigneXML->SetAttribute("Redim_x", tableauRedimensionRelative[0]);
		noeudLigneXML->SetAttribute("Redim_y", tableauRedimensionRelative[1]);
		noeudLigneXML->SetAttribute("Redim_z", tableauRedimensionRelative[2]);
		
		/*

		//ecriture du point de depart et de fin de la ligne 
		glm::dvec3 pointDepart = noeud.getPointDepart();
		glm::dvec3 pointFin = noeud.getPointFin();

		noeudLigneXML->SetAttribute("Depart_x", pointDepart.x);
		noeudLigneXML->SetAttribute("Depart_y", pointDepart.y);
		noeudLigneXML->SetAttribute("Depart_z", pointDepart.z);

		noeudLigneXML->SetAttribute("Fin_x", pointFin.x);
		noeudLigneXML->SetAttribute("Fin_y", pointFin.y);
		noeudLigneXML->SetAttribute("Fin_z", pointFin.z);

		*/


	// ecriture des segments de la ligne 
	int nombreDeSegements = 0;
	std::string chainevide = "";
	for (unsigned int i = 0; i < noeud.obtenirNombreEnfants(); i++)
	{
		nombreDeSegements++;
		
		// creation d'un nouveau noeud 
		tinyxml2::XMLElement* noeudSegmentXML{ (documentXML_->NewElement("segment")) };
		// ecrire l'id du noeud visite 
		noeudSegmentXML->SetAttribute("ID", "");

		// ecrire type du noeud visite 
		noeudSegmentXML->SetAttribute("Type", noeud.obtenirEnfants()->at(i)->obtenirType().c_str());

		// proprietes avec bool 
		noeudSegmentXML->SetAttribute("Affiche", noeud.obtenirEnfants()->at(i)->estAffiche());
		noeudSegmentXML->SetAttribute("Enregistrable", noeud.obtenirEnfants()->at(i)->estEnregistrable());
		noeudSegmentXML->SetAttribute("Selectionnable", noeud.obtenirEnfants()->at(i)->estSelectionnable());
		////noeudSegmentXML->SetAttribute("Selectionne", false);

		//ecrire la rotation relative du mur
		glm::dvec4 tableauRotatioRelative = noeud.obtenirEnfants()->at(i)->obtenirRotationRelative();
		noeudSegmentXML->SetAttribute("Angle", tableauRotatioRelative[0]);
		noeudSegmentXML->SetAttribute("x", tableauRotatioRelative[1]);
		noeudSegmentXML->SetAttribute("y", tableauRotatioRelative[2]);
		noeudSegmentXML->SetAttribute("z", tableauRotatioRelative[3]);

		// ecrire position relative du mur
		glm::dvec3 tableauPositionRelative = noeud.obtenirEnfants()->at(i)->obtenirPositionRelative();

		noeudSegmentXML->SetAttribute("Pos_x", tableauPositionRelative[0]);
		noeudSegmentXML->SetAttribute("Pos_y", tableauPositionRelative[1]);
		noeudSegmentXML->SetAttribute("Pos_z", tableauPositionRelative[2]);

		// ecrire redimentionnement relatif du mur
		glm::dvec3 tableauRedimensionRelative = noeud.obtenirEnfants()->at(i)->obtenirRedimensionnementRelative();
		noeudSegmentXML->SetAttribute("Redim_x", tableauRedimensionRelative[0]);
		noeudSegmentXML->SetAttribute("Redim_y", tableauRedimensionRelative[1]);
		noeudSegmentXML->SetAttribute("Redim_z", tableauRedimensionRelative[2]);

		//ecriture du point de depart et de fin de la ligne 
		/*glm::dvec3 pointDepart = noeud.obtenirEnfants()->at(i)->getPointDepart();
		glm::dvec3 pointFin = noeud.obtenirEnfants()->at(i)->getPointFin();

		noeudSegmentXML->SetAttribute("Depart_x", pointDepart.x);
		noeudSegmentXML->SetAttribute("Depart_y", pointDepart.y);
		noeudSegmentXML->SetAttribute("Depart_z", pointDepart.z);

		noeudSegmentXML->SetAttribute("Fin_x", pointFin.x);
		noeudSegmentXML->SetAttribute("Fin_y", pointFin.y);
		noeudSegmentXML->SetAttribute("Fin_z", pointFin.z);*/

		// on lie le noeud cree au noued XML du visiteur 
		noeudLigneXML->LinkEndChild(noeudSegmentXML);
	}
	elementXML_->LinkEndChild(noeudLigneXML);

}



/*
void VisiteurVersXML::visiter(NoeudSegment& noeud)
{
std::cout << "J'ai visite un noeud segment ici " << std::endl;
}
*/


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
