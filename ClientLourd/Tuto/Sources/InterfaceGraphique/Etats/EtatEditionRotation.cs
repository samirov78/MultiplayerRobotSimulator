///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionRotation.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.IO;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


// pour tutoriel
using System.Drawing;
using Commun;
using InterfaceGraphique.Forms;
using System.Globalization;
using System.Media;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionRotation
    /// @brief Classe decrivant l'etat de rotation d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionRotation : EtatEdition
    {
        private int xDebut_ = 0;
        private int yDebut_ = 0;
        int nbreObjetsSelectionnes = 0;
        double rotation_;
        int ancienY = 0;
        bool enRotation_;
        private int compteurEnvoi_ = 0;
        //private Keys modificateur_ = Keys.None;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void initialiserDebut(int x, int y)
        ///
        /// Methode permettant l'initialisation de certaines donnees lors d'un
        /// clic de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void initialiserDebut(int x, int y)
        {
            xDebut_ = x;
            yDebut_ = y;
            ancienY = yDebut_;
            enRotation_ = true;
            lock (Program.NoyauLock)
            {
                FonctionsNatives.initialiserEnTraitement();
                if (Program.edition.OnLine == false) //hors ligne
                {
                    nbreObjetsSelectionnes = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
                }
                else if (Program.edition.OnLine)
                {
                    Program.SDispatcher.EditionConnectionM.SpreadUpdateMySelectedNodes();
                    Program.SDispatcher.EditionConnectionM.SpreadInitDeplacement();
                    nbreObjetsSelectionnes =FonctionsNatives.obtenirNombreMySelectedNodes();
                }
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterClic(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors d'un clic d'une
        /// touche quelconque.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterClic(int x, int y, Keys k)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterDepot(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors du relachement d'un
        /// bouton de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterDepot(int x, int y, Keys k)
        {
            bool dansLaTable = false;


            if (enRotation_)
            {
                //tutoriel
                if (Program.edition.tuto == true)

                {
                    Program.edition.text1.Visible = true;
                    Program.edition.text1.Location = new Point(284, 100);
                    Program.edition.text1.Font = new Font(Program.edition.text1.Font, FontStyle.Bold);
                    Program.edition.text1.Text = " Pour effectuer la Mise à sacle de cet objet il faut appuyer sur le boutton indiqué par la fleche";
                                                 // Pour effectuer la Rotation de cet objet il faut appuyer sur le boutton indiqué par la fleche
                    Program.edition.felche1.Visible = true;
                    Program.edition.felche1.Location = new Point(311, 14);
                    Program.edition.bas.Visible = false;
                    Program.edition.haut.Visible = false;
                    Program.edition.texthaut.Visible = false;
                    Program.edition.text2.Visible = false;
                   
                  
                    Program.edition.rotationToolStripButton.Enabled = false;
                    Program.edition.miseAEchelleToolStripButton.Enabled = true;
                    Program.edition.enregistrerToolStripButton.Enabled = false;

                }


                ///


                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    if (Program.edition.OnLine == false) //hors ligne
                    {
                        dansLaTable = FonctionsNatives.objetsSelectionnesSurLaTable();
                        if (!dansLaTable)
                        {
                            FonctionsNatives.annulerRotationSelection();
                        }
                        else
                            Program.edition.marquerModificationDansLaScene();
                    }
                    else if (Program.edition.OnLine) //en ligne
                    {
                        dansLaTable = FonctionsNatives.objetsSelectionnesSurLaTable();
                        if (!dansLaTable)
                        {
                            //FonctionsNatives.annulerRotationMySelection()
                            Program.SDispatcher.EditionConnectionM.SpreadAnnulerRotation();

                        }
                        else
                            Program.edition.marquerModificationDansLaScene();
                    }
                   
                }
                enRotation_ = false;
            }
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterGlissement(int x, int y)
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris avec un certain bouton enfonce.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///native
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterGlissement(int x, int y)
        {
            if (enRotation_)
            {
                // tutoriel
                if (Program.edition.tuto == true)

                {
                    Program.edition.text1.Visible = true;
                   Program.edition.text1.Text = "vous pouvez relachez mais il faut faire attention à que l'objet ne sort pas de la table ";
                    Program.edition.text1.Location = new Point(284, 281);
                    Program.edition.enregistrerToolStripButton.Enabled = false;
                    Program.edition.texthaut.Visible = false;
                    Program.edition.text2.Visible = false;
                    ///
                }

                compteurEnvoi_++;
                double deltaY = 0;
                Program.edition.Cursor = Cursors.NoMoveVert;

                deltaY = y - ancienY;
                rotation_ = deltaY;
                lock (Program.NoyauLock)
                {
                    if (Program.edition.OnLine == false) //hors ligne
                    {
                        if (nbreObjetsSelectionnes == 1)
                        {
                            FonctionsNatives.PivoterObjetSelectionne(deltaY);
                        }
                        else
                        {
                            FonctionsNatives.PivoterObjetsMultiples(deltaY);
                        }
                    }
                    else if (Program.edition.OnLine) //En ligne
                    {
                        if (nbreObjetsSelectionnes == 1 && compteurEnvoi_ > 2)
                        {
                            Program.SDispatcher.EditionConnectionM.SpreadPivoterObjetSelectionne(deltaY.ToString());
                            compteurEnvoi_ = 0;
                        }
                        else
                        {
                            Program.SDispatcher.EditionConnectionM.SpreadPivoterObjetsMultiples(deltaY.ToString());
                        }
                    }
                }
                ancienY = y;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool interpreterEchap()
        ///
        /// Methode permettant le lancement d'algorithme lors de l'appui de la touche
        /// Echap.
        /// 
        /// @return True par defaut.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool interpreterEchap()
        {
            if (enRotation_)
            {
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.annulerRotationSelection();
                }
                enRotation_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
        
    }

}
