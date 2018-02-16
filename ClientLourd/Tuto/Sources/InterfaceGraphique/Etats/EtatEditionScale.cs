///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionScale.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
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
    /// @class EtatEditionScale
    /// @brief Classe decrivant le redimensionnement d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionScale : EtatEdition
    {
        private int compteurDeplacement_ = 0;
        //private bool 
        private bool enScale_;
        int xDebut, yDebut;
     
     

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
            xDebut = x;
            yDebut = y;
            enScale_ = true;
            lock (Program.NoyauLock)
            {
                FonctionsNatives.initialiserScaleEnTraitement();
                if (Program.edition.OnLine) //en ligne
                {
                    Program.SDispatcher.EditionConnectionM.SpreadInitScaleSel();
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn  public override void interpreterGlissement( int x, int y )
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris avec un certain bouton enfonce.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterGlissement( int x, int y )
        {
            double facteur1000;
            string facteurStr = "";
            if (enScale_)
            {

                /// tutoriel
                /// 
                /// 
                /// 
                if (Program.edition.tuto == true)

                {
                    Program.edition.text1.Visible = true;
                    Program.edition.text1.Text = "vous pouvez relachez mais il faut faire attention à que l'objet ne sort pas de la table ";
                    Program.edition.text1.Location = new Point(284, 281);
                    Program.edition.felche1.Location = new Point(253, 19);
                    Program.edition.enregistrerToolStripButton.Enabled = false;
                    Program.edition.texthaut.Visible = false;
                    Program.edition.text2.Visible = false;


                }


                Program.edition.Cursor = Cursors.NoMoveVert;
                if (compteurDeplacement_ == 2)
                {
                    double facteurScale = 1.0 - (y - yDebut) / 60.0;

                    if (facteurScale <= 0.01)
                    {
                        facteurScale = 0.01;
                    }
                    lock (Program.NoyauLock)
                    {
                        if (Program.edition.OnLine == false)
                        {
                            facteurStr = Marshal.PtrToStringAnsi(FonctionsNatives.scaleSelection(facteurScale));
                        }
                        else if (Program.edition.OnLine) //en ligne
                        {
                            facteur1000 = facteurScale * 1000;//;
                            Program.SDispatcher.EditionConnectionM.SpreadScaleSelection(facteur1000.ToString());
                        }
                       
                    }
                    compteurDeplacement_ = 0;
                }
                else
                    compteurDeplacement_++;
            }
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
            double facteur1000;
            string factorStr = "";
            if (enScale_)
            {
                if (Program.edition.tuto == true)

                {
                    Program.edition.text1.Visible = true;
                   Program.edition.text1.Location = new Point(284, 100);
                    Program.edition.text1.Font = new Font(Program.edition.text1.Font, FontStyle.Bold);
                    Program.edition.text1.Text = "Pour effectuer la duppliquation de l'objet il faut cliquer le boutton indiqué par la fleche";
                                                 
                    Program.edition.felche1.Visible = true;
                    Program.edition.felche1.Location = new Point(353, 19);
                    Program.edition.miseAEchelleToolStripButton.Enabled = false;
                    Program.edition.duplicationToolStripButton.Enabled = true;
                    Program.edition.enregistrerToolStripButton.Enabled = false;
                    Program.edition.haut.Visible = false;
                    Program.edition.bas.Visible = false;
                    Program.edition.texthaut.Visible = false;
                    Program.edition.text2.Visible = false;
                }

                // code a executer quand le bouton est relaché
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    if (!FonctionsNatives.objetsSelectionnesSurLaTable())
                    {
                        if (Program.edition.OnLine == false)
                        {
                            factorStr = Marshal.PtrToStringAnsi(FonctionsNatives.scaleSelection(1.0));
                        }
                          
                            
                        if (Program.edition.OnLine) //en ligne
                        {
                            //FonctionsNatives.retournerAuScaleInitiale();
                            //facteur1000 = 1.0000;
                            //Program.SDispatcher.EditionConnectionM.SpreadScaleSelection(facteur1000.ToString());
                            Program.SDispatcher.EditionConnectionM.SpreadRetourAuscaleInit();
                        }
                        
                    }
                    else
                        Program.edition.marquerModificationDansLaScene();
                }
                enScale_ = false;
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
            if (enScale_)
            {
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.scaleSelection(1.0);
                }
                enScale_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
   }
}

